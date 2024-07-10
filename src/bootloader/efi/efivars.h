#ifndef EFIVARS_H_
#define EFIVARS_H_

#include <stddef.h>
#include <stdint.h>

// variable definitions
// https://uefi.org/specs/UEFI/2.10/02_Overview.html#data-types
// only support x86_64
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef uint8_t BOOLEAN;
typedef char CHAR8;
typedef wchar_t CHAR16;

typedef UINTN EFI_STATUS;
typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;

typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

typedef struct {
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    UINT8 Data4[8];
} EFI_GUID;

#endif // EFIVARS_H_
