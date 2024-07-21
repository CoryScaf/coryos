include Make.defaults

SUBDIRS = bootloader

all: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $(OBJ_DIR)/$@
	mkdir -p $(BUILD_DIR)/$@
	$(MAKE) -C $(OBJ_DIR)/$@ -f $(SRC_DIR)/$@/Makefile BUILD_DIR=$(BUILD_DIR)/$@ SRC_DIR=$(SRC_DIR)/$@

$(BOOT_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/OVMF_CODE.fd: | $(BUILD_DIR)
	cp /usr/share/edk2-ovmf/OVMF_CODE.fd $(BUILD_DIR)

$(BUILD_DIR)/OVMF_VARS.fd: | $(BUILD_DIR)
	cp /usr/share/edk2-ovmf/OVMF_VARS.fd $(BUILD_DIR)

run: $(SUBDIRS) $(BUILD_DIR)/OVMF_CODE.fd $(BUILD_DIR)/OVMF_VARS.fd | $(BOOT_DIR)
	cp $(BOOTLOADER_BLD)/bootx64.efi $(BOOT_DIR)/bootx64.efi
	qemu-system-x86_64 \
		-net none \
		-drive format=raw,file=fat:rw:$(IMAGE_DIR) \
		-drive if=pflash,format=raw,unit=0,file=$(BUILD_DIR)/OVMF_CODE.fd,readonly=on \
		-drive if=pflash,format=raw,unit=1,file=$(BUILD_DIR)/OVMF_VARS.fd

clean:
	rm -rf $(BUILD_DIR)

.PHONY: $(SUBDIRS) clean run
