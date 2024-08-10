#ifndef EFIDEFS_H_
#define EFIDEFS_H_

// UEFI visual info defines
#define IN
#define OUT
#define OPTIONAL

// useful definitions
#define TRUE 1
#define FALSE 0

// status codes
// https://uefi.org/specs/UEFI/2.10/Apx_D_Status_Codes.html#efi-status-code-ranges-apx-d-status-codes
#define EFIERR(a) (0x8000000000000000 | a)

#define EFI_SUCCESS 0
#define EFI_UNSUPPORTED EFIERR(3)
#define EFI_NOT_READY EFIERR(6)
#define EFI_DEVICE_ERROR EFIERR(7)
#define EFI_NOT_FOUND EFIERR(14)

#endif // EFIDEFS_H_
