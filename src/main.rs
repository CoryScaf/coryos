#![no_std]
#![no_main]
#![feature(custom_test_frameworks)]
#![test_runner(crate::test_setup::test_runner)]
#![reexport_test_harness_main = "test_main"]

mod vga_buffer;

#[cfg(test)]
mod test_setup;

#[cfg(not(test))]
use core::panic::PanicInfo;

#[cfg(not(test))]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("{}", info);
    loop {}
}

#[no_mangle]
pub extern "C" fn _start() -> ! {
    println!("Welcome to coryos!!!");

    #[cfg(test)]
    test_main();

    loop {}
}

