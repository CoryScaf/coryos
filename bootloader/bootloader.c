#include "utils.h"

#include <efi/efidefs.h>
#include <efi/protocols/console_protocols.h>
#include <efi/protocols/efi_loaded_image_protocol.h>
#include <efi/protocols/media_access_protocol.h>
#include <efi/system_table.h>
#include <elf/elf.h>

#define REVISION_MAJOR(rev) rev >> 16
#define REVISION_MINOR(rev) rev & 0xffff

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    EFI_STATUS status;
    EFI_FILE_INFO *kernel_info = NULL;
    EFI_FILE_PROTOCOL *root = NULL;
    EFI_FILE_PROTOCOL *kernel_file = NULL;
    uint8_t *kernel = NULL;

    init_utils(image_handle, system_table);
    status = efi_clear_screen();
    if (status != EFI_SUCCESS) {
        efi_print(L"Failed to clear screen\r\n");
    }

    efi_printf(L"%s %d.%d\r\n", system_table->FirmwareVendor,
               REVISION_MAJOR(system_table->FirmwareRevision),
               REVISION_MINOR(system_table->FirmwareRevision));

    efi_printf(L"UEFI %d.%d\r\n", REVISION_MAJOR(system_table->Hdr.Revision),
               REVISION_MINOR(system_table->Hdr.Revision));

    // get loaded image protocol for storage device
    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;
    status = efi_simple_open_protocol(
        image_handle, &efi_loaded_image_protocol_guid, (void **)&loaded_image);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to open loaded image protocol: %lx\r\n", status);
        goto fail;
    }

    // get simple file system protocol
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *simple_file_system;
    status = efi_simple_open_protocol(loaded_image->DeviceHandle,
                                      &efi_simple_file_system_protocol_guid,
                                      (void **)&simple_file_system);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to open load file protocol: %lx\r\n", status);
        goto fail;
    }

    // open volume for root
    status = simple_file_system->OpenVolume(simple_file_system, &root);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to open volume: %lx\r\n", status);
        goto fail;
    }

    // open kernel file
    status = root->Open(root, &kernel_file, L"kernel.bin", EFI_FILE_MODE_READ,
                        EFI_FILE_READ_ONLY);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to open kernel: %lx\r\n", status);
        if (status == EFI_NOT_FOUND)
            efi_print(L"File was not found.\r\n");
        goto fail;
    }
    efi_print(L"Kernel opened\r\n");

    // no longer need root
    root->Close(root);
    root = NULL;

    // get kernel info
    UINTN kernel_info_size = 0;
    status = kernel_file->GetInfo(kernel_file, &efi_file_info_guid,
                                  &kernel_info_size, NULL);

    kernel_info = efi_alloc_pool(kernel_info_size);
    if (!kernel_info) {
        efi_print(L"Failed to allocate pool for kernel info.\r\n");
        efi_free_pool(kernel_info);
        goto fail;
    }

    status = kernel_file->GetInfo(kernel_file, &efi_file_info_guid,
                                  &kernel_info_size, kernel_info);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to get kernel info: %lx\r\n", status);
        efi_free_pool(kernel_info);
        goto fail;
    }

    efi_printf(L"Kernel '%s' is %lu bytes\r\n", kernel_info->FileName,
               kernel_info->FileSize);

    UINTN kernel_size = kernel_info->FileSize;

    efi_free_pool(kernel_info);

    // load kernel
    kernel = efi_alloc_pool(kernel_size);
    if (!kernel) {
        efi_print(L"Failed to allocate pool for kernel.\r\n");
        goto fail;
    }

    status = kernel_file->Read(kernel_file, &kernel_size, kernel);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to read kernel file: %lx\r\n", status);
        goto fail;
    }
    efi_print(L"Kernel loaded to memory.\r\n");

    // Verify ELF header
    Elf64_Ehdr *kernel_header = (Elf64_Ehdr *)kernel;

    for (int i = EI_MAG0; i < SELFMAG; ++i) {
        if (kernel_header->e_ident[i] != ELFMAG[i]) {
            efi_print(L"Kernel does not have expected ELF64 header\r\n");
            goto fail;
        }
    }
    efi_print(L"Verified ELF64 header in kernel\r\n");

    efi_print(L"Success!\r\n");
    EFI_INPUT_KEY key;
    efi_wait_next_key(&key);

fail:
    if (kernel)
        efi_free_pool(kernel);
    if (kernel_info)
        efi_free_pool(kernel_info);
    if (kernel_file)
        kernel_file->Close(kernel_file);
    if (root)
        root->Close(root);
    efi_stall_sec(5);
    return status;
}
