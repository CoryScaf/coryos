use crate::println;
use crate::print;
use core::panic::PanicInfo;

// Test code
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    println!("[failed]");
    println!("\nError: {}\n", _info);

    loop {}
}

pub trait Testable {
    fn run(&self);
}

impl<T> Testable for T
    where T: Fn(),
{
    fn run(&self) {
        print!("{}...    ", core::any::type_name::<T>());
        self();
        println!("[success]");
    }
}

pub fn test_runner(tests: &[&dyn Testable]) {
    println!("Running {} tests", tests.len());
    for test in tests {
        test.run();
    }
}
