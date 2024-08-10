include Make.defaults

SUBDIRS = bootloader \
		  kernel

all: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $(OBJ_DIR)/$@
	mkdir -p $(BUILD_DIR)/$@
	$(MAKE) -C $(OBJ_DIR)/$@ -f $(ROOT_DIR)/$@/Makefile BUILD_DIR=$(BUILD_DIR)/$@ SRC_DIR=$(ROOT_DIR)/$@ ROOT_DIR=$(ROOT_DIR)

$(BOOT_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/OVMF_CODE.fd: | $(BUILD_DIR)
	cp /usr/share/edk2-ovmf/OVMF_CODE.fd $(BUILD_DIR)

$(BUILD_DIR)/OVMF_VARS.fd: | $(BUILD_DIR)
	cp /usr/share/edk2-ovmf/OVMF_VARS.fd $(BUILD_DIR)

$(BUILD_DIR)/limine: | $(BUILD_DIR)
	git clone https://github.com/limine-bootloader/limine.git --branch=v8.x-binary --depth=1 $(BUILD_DIR)/limine
	make -C $(BUILD_DIR)/limine

run: $(SUBDIRS) $(BUILD_DIR)/OVMF_CODE.fd $(BUILD_DIR)/OVMF_VARS.fd | $(BOOT_DIR)
	cp $(BOOTLOADER_BLD)/bootx64.efi $(BOOT_DIR)/bootx64.efi
	cp $(KERNEL_BLD)/kernel.bin $(IMAGE_DIR)/kernel.bin
	qemu-system-x86_64 \
		-net none \
		-drive format=raw,file=fat:rw:$(IMAGE_DIR) \
		-drive if=pflash,format=raw,unit=0,file=$(BUILD_DIR)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=$(BUILD_DIR)/OVMF_VARS.fd

rlimine: $(SUBDIRS) $(BUILD_DIR)/limine $(BUILD_DIR)/OVMF_CODE.fd $(BUILD_DIR)/OVMF_VARS.fd | $(BOOT_DIR)
	mkdir -p $(BUILD_DIR)/limage/boot/limine
	cp $(BUILD_DIR)/kernel/kernel.bin $(BUILD_DIR)/limage/boot/coryos
	cp $(ROOT_DIR)/limine.conf $(BUILD_DIR)/limine/limine-bios.sys \
		$(BUILD_DIR)/limine/limine-bios-cd.bin \
		$(BUILD_DIR)/limine/limine-uefi-cd.bin \
		$(BUILD_DIR)/limage/boot/limine/
	mkdir -p $(BUILD_DIR)/limage/EFI/BOOT
	cp $(BUILD_DIR)/limine/BOOTX64.EFI $(BUILD_DIR)/limage/EFI/BOOT/
	qemu-system-x86_64 \
		-net none \
		-drive format=raw,file=fat:rw:$(BUILD_DIR)/limage \
		-drive if=pflash,format=raw,unit=0,file=$(BUILD_DIR)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=$(BUILD_DIR)/OVMF_VARS.fd

clean:
	rm -rf $(BUILD_DIR)

.PHONY: $(SUBDIRS) clean run rlimine
