#ifndef UTILS_H_
#define UTILS_H_

#include "efi/efivars.h"
#include "efi/system_table.h"

extern EFI_GUID efi_loaded_image_protocol_guid;

void init_utils(EFI_HANDLE handle, EFI_SYSTEM_TABLE *system_table);

EFI_STATUS efi_print(CHAR16 *str);
EFI_STATUS efi_printf(CHAR16 *str, ...);
EFI_STATUS efi_clear_screen();

EFI_STATUS efi_wait_next_key(EFI_INPUT_KEY *key);

EFI_STATUS efi_stall_sec(UINTN sec);

#endif // UTILS_H_
