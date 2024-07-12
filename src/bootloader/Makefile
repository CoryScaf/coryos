CFLAGS=-target x86_64-unknown-windows -ffreestanding -fshort-wchar -mno-red-zone
LDFLAGS=-target x86_64-unknown-windows -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -fuse-ld=lld-link
CC=clang

all: $(BUILD_DIR)/bootx64.efi

$(BUILD_DIR)/bootx64.efi: bootloader.o
	$(CC) $(LDFLAGS) -o $@ $<

bootloader.o: $(SRC_DIR)/bootloader.c
	$(CC) $(CFLAGS) -c -o $@ $<
