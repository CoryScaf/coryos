#![cfg(test)]

use lazy_static::lazy_static;
use spin::Mutex;
use uart_16550::SerialPort;

lazy_static! {
    pub static ref out_serial: Mutex<SerialPort> = {
        let mut serial_port = unsafe { SerialPort::new(0x3f8) };
        serial_port.init();

        Mutex::new(serial_port)
    };
}

#[doc(hidden)]
pub fn _print(args: core::fmt::Arguments) {
    use core::fmt::Write;
    out_serial
        .lock()
        .write_fmt(args)
        .expect("Failed to print to serial");
}

#[macro_export]
macro_rules! serial_print {
    ($($arg:tt)*) => ($crate::serial_stdout::_print(format_args!($($arg)*)));
}

#[macro_export]
macro_rules! serial_println {
    () => (serial_print!("\n"));
    ($($arg:tt)*) => (serial_print!("{}\n", format_args!($($arg)*)));
}
