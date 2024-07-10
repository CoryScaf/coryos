#include "efi.h"

EFI_STATUS efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    EFI_STATUS status;
    EFI_INPUT_KEY key;

    status = system_table->ConOut->OutputString(system_table->ConOut,
                                                L"Hello World\r\n");
    if (status != EFI_SUCCESS)
        return status;

    status = system_table->ConIn->Reset(system_table->ConIn, FALSE);
    if (status != EFI_SUCCESS)
        return status;

    while ((status = system_table->ConIn->ReadKeyStroke(system_table->ConIn,
                                                        &key)) == EFI_NOT_READY)
        ;
    return status;
}
