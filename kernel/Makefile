CFLAGS=-target x86_64-pc-none-elf \
	   -ffreestanding \
	   -mno-red-zone \
	   -I$(ROOT_DIR)/include
LDFLAGS=-target x86_64-pc-none-elf \
		-nostdlib \
		-T $(SRC_DIR)/linker.ld \
		-static \
		-fuse-ld=lld
CC=clang

OBJ=main.o

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
