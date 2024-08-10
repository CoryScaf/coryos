#ifndef UTILS_H_
#define UTILS_H_

#include "efi/efivars.h"
#include "efi/protocols/device_path_protocol.h"
#include "efi/system_table.h"

inline UINT16 device_path_length(const EFI_DEVICE_PATH_PROTOCOL *path) {
    return ((UINT16)path->Length[0]) | ((UINT16)path->Length[1] << 8);
}

extern EFI_GUID efi_loaded_image_protocol_guid;
extern EFI_GUID efi_simple_file_system_protocol_guid;
extern EFI_GUID efi_file_info_guid;

void init_utils(EFI_HANDLE handle, EFI_SYSTEM_TABLE *system_table);

EFI_STATUS efi_simple_open_protocol(EFI_HANDLE handle, EFI_GUID *guid,
                                    void **interface);

void *efi_alloc_pool(UINTN size);
EFI_STATUS efi_free_pool(void *ptr);

UINTN simple_strlen(CHAR16 *str);

EFI_STATUS efi_print(CHAR16 *str);
EFI_STATUS efi_printf(CHAR16 *str, ...);
EFI_STATUS efi_clear_screen();

EFI_STATUS efi_wait_next_key(EFI_INPUT_KEY *key);

EFI_STATUS efi_stall_sec(UINTN sec);

#endif // UTILS_H_
