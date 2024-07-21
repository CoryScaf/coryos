#include "utils.h"
#include "efi/efidefs.h"
#include "efi/efivars.h"
#include "efi/protocols/efi_loaded_image_protocol.h"

#include <stdarg.h>

#define SEC_TO_USEC(seconds) seconds * 1000 * 1000

EFI_GUID efi_loaded_image_protocol_guid =
    (EFI_GUID)EFI_LOADED_IMAGE_PROTOCOL_GUID;

static EFI_SYSTEM_TABLE *st;
static EFI_HANDLE hdl;

void init_utils(EFI_HANDLE handle, EFI_SYSTEM_TABLE *system_table) {
    st = system_table;
    hdl = handle;
}

EFI_STATUS efi_print(CHAR16 *str) {
    return st->ConOut->OutputString(st->ConOut, str);
}

static CHAR16 *ultos(UINT64 num, int base, BOOLEAN negative) {
    static CHAR16 convert[] = L"0123456789abcdef";
    static CHAR16 buffer[64];
    CHAR16 *str = buffer + 63;
    *str = L'\0';

    do {
        str--;
        *str = convert[num % base];
        num /= base;
    } while (num != 0);

    if (negative) {
        str--;
        *str = L'-';
    }

    return str;
}

EFI_STATUS efi_printf(CHAR16 *str, ...) {
    EFI_STATUS status = EFI_SUCCESS;
    CHAR16 *checkpoint = str;
    CHAR16 *curr;
    UINT64 lu;
    INT64 ld;

    va_list arg;
    va_start(arg, str);

    for (curr = str; *curr != L'\0'; ++curr) {
        if (*curr != L'%')
            continue;

        *curr = L'\0';
        status = efi_print(checkpoint);
        *curr = L'%';
        curr++;

        if (status != EFI_SUCCESS)
            goto cleanup;

        switch (*curr) {
        case L'%':
            curr--;
            break;
        case L'd':
            ld = va_arg(arg, INT32);
            if (ld < 0) {
                ld = -ld;
                efi_print(ultos(ld, 10, TRUE));
            } else {
                efi_print(ultos(ld, 10, FALSE));
            }
            break;
        case L'x':
            efi_print(ultos(ld, 16, FALSE));
            break;
        case L'u':
            efi_print(ultos(ld, 10, FALSE));
            break;
        case L'l':
            curr++;
            if (*curr == L'd') {
                ld = va_arg(arg, UINT64);
                if (ld < 0) {
                    ld = -ld;
                    efi_print(ultos(ld, 10, TRUE));
                } else {
                    efi_print(ultos(ld, 10, FALSE));
                }
            } else if (*curr == L'x') {
                efi_print(ultos(ld, 16, FALSE));
            } else if (*curr == L'u') {
                efi_print(ultos(ld, 10, FALSE));
            } else if (*curr == L'\0') {
                goto cleanup;
            }
            break;
        case L's':
            status = efi_print(va_arg(arg, CHAR16 *));
            if (status != EFI_SUCCESS)
                goto cleanup;
            break;
        case L'\0':
            goto cleanup;
            break;
        }

        curr++;
        checkpoint = curr;
    }

    status = efi_print(checkpoint);

cleanup:
    va_end(arg);
    return status;
}

EFI_STATUS efi_clear_screen() { return st->ConOut->ClearScreen(st->ConOut); }

EFI_STATUS efi_wait_next_key(EFI_INPUT_KEY *key) {
    EFI_STATUS status = st->ConIn->Reset(st->ConIn, FALSE);
    if (status != EFI_SUCCESS)
        return status;

    while ((status = st->ConIn->ReadKeyStroke(st->ConIn, key)) == EFI_NOT_READY)
        ;

    return status;
}

EFI_STATUS efi_stall_sec(UINTN sec) {
    return st->BootServices->Stall(SEC_TO_USEC(sec));
}
