#include <stdint.h>

#define EFI_STATUS uint64_t
#define EFI_SUCCESS 0
#define EFI_NOT_READY 6

#define EFI_HANDLE void*

typedef struct {
    uint64_t signature;
    uint32_t revision;
    uint32_t header_size;
    uint32_t crc32;
    uint32_t reserved;
} EFI_TABLE_HEADER;

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    /*
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;

    Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!\r\n"); // EFI Applications use Unicode and CRLF, a la Windows
    if (EFI_ERROR(Status))
        return Status;

    Status = SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
    if (EFI_ERROR(Status))
        return Status;

    while ((Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY)
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"POLLING UWU\r\n"); // EFI Applications use Unicode and CRLF, a la Windows

    while (TRUE)
        ;

    return Status;
    */
    return EFI_SUCCESS;
}
