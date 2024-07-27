#include "efi/efidefs.h"
#include "efi/protocols/boot_services.h"
#include "efi/protocols/console_protocols.h"
#include "efi/protocols/efi_loaded_image_protocol.h"
#include "efi/system_table.h"
#include "utils.h"

#define REVISION_MAJOR(rev) rev >> 16
#define REVISION_MINOR(rev) rev & 0xffff

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL *loaded_image;

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

    status = system_table->BootServices->OpenProtocol(
        image_handle, &efi_loaded_image_protocol_guid, (void **)&loaded_image,
        image_handle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (status != EFI_SUCCESS) {
        efi_printf(
            L"Failed opening protocol EFI_LOADED_IMAGE_PROTOCOL: %lx\r\n",
            status);
        efi_stall_sec(5);
        return status;
    }

    EFI_INPUT_KEY key;
    efi_wait_next_key(&key);

    return status;
}
