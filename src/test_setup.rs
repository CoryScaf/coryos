use crate::{serial_print, serial_println};
use core::panic::PanicInfo;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u32)]
enum QemuExitCode {
    Success = 0x10,
    Failure = 0x11,
}

fn exit_qemu(exit_code: QemuExitCode) {
    use x86_64::instructions::port::Port;

    unsafe {
        let mut port = Port::new(0xf4);
        port.write(exit_code as u32);
    }
}

// Test code
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    serial_println!("[failed]");
    serial_println!("\nError: {}\n", _info);

    exit_qemu(QemuExitCode::Failure);
    loop {}
}

pub trait Testable {
    fn run(&self);
}

impl<T> Testable for T
where
    T: Fn(),
{
    fn run(&self) {
        serial_print!("{}...\t\t", core::any::type_name::<T>());
        self();
        serial_println!("[success]");
    }
}

pub fn test_runner(tests: &[&dyn Testable]) {
    serial_println!("Running {} tests", tests.len());
    for test in tests {
        test.run();
    }

    exit_qemu(QemuExitCode::Success);
}
