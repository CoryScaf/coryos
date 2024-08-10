#include "utils.h"
#include "efi/efidefs.h"
#include "efi/efivars.h"
#include "efi/protocols/boot_services.h"
#include "efi/protocols/device_path_protocol.h"
#include "efi/protocols/efi_loaded_image_protocol.h"
#include "efi/protocols/media_access_protocol.h"

#include <stdarg.h>
#include <stddef.h>

#define SEC_TO_USEC(seconds) seconds * 1000 * 1000

EFI_GUID efi_loaded_image_protocol_guid =
    (EFI_GUID)EFI_LOADED_IMAGE_PROTOCOL_GUID;

EFI_GUID efi_simple_file_system_protocol_guid =
    (EFI_GUID)EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

EFI_GUID efi_file_info_guid = (EFI_GUID)EFI_FILE_INFO_GUID;

#define FILE_PATH_MEDIA_TYPE 0x4
#define MEDIA_DEV_PATH_TYPE 0x4
typedef struct {
    EFI_DEVICE_PATH_PROTOCOL device_path;
    CHAR16 filepath[1];
} FILE_PATH_MEDIA_DEVICE_PATH;

static EFI_SYSTEM_TABLE *st;
static EFI_HANDLE hdl;

static void *simple_memcpy(void *dst, const void *src, UINTN n) {
    char *dstc = (char *)dst;
    const char *srcc = (char *)src;

    while (n--) {
        *dstc++ = *srcc++;
    }

    return dst;
}

static void *simple_memset(void *dst, int val, UINTN n) {
    char *dstc = (char *)dst;

    while (n--) {
        *dstc++ = val;
    }

    return dst;
}

UINTN simple_strlen(CHAR16 *str) {
    UINTN count = 0;
    while ((*str) != L'\0') {
        count++;
        str++;
    }

    return count;
}

void init_utils(EFI_HANDLE handle, EFI_SYSTEM_TABLE *system_table) {
    st = system_table;
    hdl = handle;
}

EFI_STATUS efi_simple_open_protocol(EFI_HANDLE handle, EFI_GUID *guid,
                                    void **interface) {
    return st->BootServices->OpenProtocol(handle, guid, interface, hdl, NULL,
                                          EFI_OPEN_PROTOCOL_GET_PROTOCOL);
}

void *efi_alloc_pool(UINTN size) {
    void *ptr;
    EFI_STATUS status;

    status = st->BootServices->AllocatePool(EfiLoaderData, size, (void **)&ptr);
    if (status != EFI_SUCCESS) {
        efi_printf(L"Failed to allocate pool: %lx\r\n", status);
        return NULL;
    }

    return ptr;
}

EFI_STATUS efi_free_pool(void *ptr) {
    EFI_STATUS status;

    status = st->BootServices->FreePool(ptr);
    return status;
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
    INT64 ld;

    va_list arg;
    va_start(arg, str);

    for (curr = str; *curr != L'\0'; ++curr) {
        if (*curr != L'%')
            continue;

        if (checkpoint != curr) {
            *curr = L'\0';
            status = efi_print(checkpoint);
            *curr = L'%';

            if (status != EFI_SUCCESS)
                goto cleanup;
        }

        curr++;

        switch (*curr) {
        case L'%':
            efi_print(L"%");
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
            ld = va_arg(arg, UINT32);
            efi_print(ultos(ld, 16, FALSE));
            break;
        case L'u':
            ld = va_arg(arg, UINT32);
            efi_print(ultos(ld, 10, FALSE));
            break;
        case L'l':
            curr++;
            if (*curr == L'd') {
                ld = va_arg(arg, INT64);
                if (ld < 0) {
                    ld = -ld;
                    efi_print(ultos(ld, 10, TRUE));
                } else {
                    efi_print(ultos(ld, 10, FALSE));
                }
            } else if (*curr == L'x') {
                ld = va_arg(arg, UINT64);
                efi_print(ultos(ld, 16, FALSE));
            } else if (*curr == L'u') {
                ld = va_arg(arg, UINT64);
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

        checkpoint = curr + 1;
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
