CFLAGS=-target x86_64-unknown-windows \
	   -ffreestanding \
	   -fshort-wchar \
	   -mno-red-zone
LDFLAGS=-target x86_64-unknown-windows \
		-nostdlib \
		-Wl,-entry:efi_main \
		-Wl,-subsystem:efi_application \
		-fuse-ld=lld-link
CC=clang

OBJ=bootloader.o \
	utils.o

all: $(BUILD_DIR)/bootx64.efi

$(BUILD_DIR)/bootx64.efi: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
