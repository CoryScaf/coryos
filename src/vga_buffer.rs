use core::fmt;

use volatile::Volatile;
use lazy_static::lazy_static;
use spin::Mutex;

const BUFFER_HEIGHT: usize = 25;
const BUFFER_WIDTH: usize = 80;

lazy_static! {
    pub static ref vga_writer: Mutex<Writer> = Mutex::new(Writer {
        column_pos: 0,
        color_code: ColorCode::new(Color::Cyan, Color::Black),
        buffer: unsafe { &mut *(0xb8000 as *mut Buffer) },
    });
}

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => ($crate::vga_buffer::_print(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! println {
    () => (print!("\n"));
    ($($arg:tt)*) => (print!("{}\n", format_args!($($arg)*)));
}

#[allow(dead_code)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u8)]
pub enum Color {
    Black           = 0,
    Blue            = 1,
    Green           = 2,
    Cyan            = 3,
    Red             = 4,
    Magenta         = 5,
    Brown           = 6,
    LightGray       = 7,
    DarkGray        = 8,
    LightBlue       = 9,
    LightGreen      = 10,
    LightCyan       = 11,
    LightRed        = 12,
    Pink            = 13,
    Yellow          = 14,
    White           = 15,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(C)]
struct ScreenChar {
    character: u8,
    color_code: ColorCode,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(transparent)]
struct ColorCode(u8);

#[repr(transparent)]
struct Buffer {
    chars: [[Volatile<ScreenChar>; BUFFER_WIDTH]; BUFFER_HEIGHT],
}

pub struct Writer {
    column_pos: usize,
    color_code: ColorCode,
    buffer: &'static mut Buffer,
}

#[doc(hidden)]
pub fn _print(args: fmt::Arguments) {
    use core::fmt::Write;
    vga_writer.lock().write_fmt(args).unwrap();
}

impl ColorCode {
    fn new(foreground: Color, background: Color) -> ColorCode {
        ColorCode((background as u8) << 4 | (foreground as u8))
    }
}

impl fmt::Write for Writer {
    fn write_str(&mut self, out_str: &str) -> fmt::Result {
        for byte in out_str.bytes() {
            self.write_byte(byte);
        }

        Ok(())
    }
}

impl Writer {
    pub fn write_byte(&mut self, byte: u8) {
        match byte {
            b'\n' => self.new_line(),
            byte => {
                if self.column_pos >= BUFFER_WIDTH {
                    self.new_line();
                }

                let row = BUFFER_HEIGHT-1;
                let col = self.column_pos;
                let color_code = self.color_code;

                self.buffer.chars[row][col].write(ScreenChar {
                    character: byte,
                    color_code,
                });

                self.column_pos += 1;
            }
        }
    }

    fn new_line(&mut self) {
        for row in 1..BUFFER_HEIGHT {
            for col in 0..BUFFER_WIDTH {
                let character = self.buffer.chars[row][col].read();
                self.buffer.chars[row-1][col].write(character);
            }
        }
        self.clear_row(BUFFER_HEIGHT-1);
        self.column_pos = 0;
    }

    fn clear_row(&mut self, row: usize) {
        let blank = ScreenChar {
            character: b' ',
            color_code: self.color_code,
        };
        for col in 0..BUFFER_WIDTH {
            self.buffer.chars[row][col].write(blank);
        }
    }
}

#[cfg(test)]
mod tests {
    #[test_case]
    fn test_println_no_panic() {
        println!("testing println");
    }

    #[test_case]
    fn test_println_many() {
        for i in 0..500 {
            println!("test {}", i);
        }
    }

    #[test_case]
    fn test_println_long_line() {
        println!("this is a very long print statement which is longer than the vga width of 80 characters long so it should split into multiple lines");
    }
}
