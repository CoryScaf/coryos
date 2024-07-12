#ifndef RUNTIME_SERVICES_H_
#define RUNTIME_SERVICES_H_

#include "../efidefs.h"
#include "../efivars.h"
#include "boot_services.h"

// ---------------------------------------------------------------------------
// Runtime services
// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Time Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#gettime
typedef struct {
    UINT16 Year;
    UINT8 Month;
    UINT8 Day;
    UINT8 Hour;
    UINT8 Minute;
    UINT8 Second;
    UINT8 Pad1;
    UINT32 Nanosecond;
    UINT16 TimeZone;
    UINT8 Daylight;
    UINT8 Pad2;
} EFI_TIME;

typedef struct {
    UINT32 Resolution;
    UINT32 Accuracy;
    BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS (*EFI_GET_TIME)(
    OUT EFI_TIME *Time, OUT EFI_TIME_CAPABILITIES *Capabilities OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#settime
typedef EFI_STATUS (*EFI_SET_TIME)(IN EFI_TIME *Time);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#getwakeuptime
typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(OUT BOOLEAN *Enabled,
                                          OUT BOOLEAN *Pending,
                                          OUT EFI_TIME *Time);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#setwakeuptime
typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(IN BOOLEAN Enable,
                                          IN EFI_TIME *Time OPTIONAL);

// ---------------------------------------------------------------------------
// Virtual Memory Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#setvirtualaddressmap
typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(
    IN UINTN MemoryMapSize, IN UINTN DescriptorSize,
    IN UINT32 DescriptorVersion, IN EFI_MEMORY_DESCRIPTION *VirtualMap);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#convertpointer
typedef EFI_STATUS (*EFI_CONVERT_POINTER)(IN UINTN DebugDisposition,
                                          IN void **Address);

// ---------------------------------------------------------------------------
// Variable Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#getvariable
typedef EFI_STATUS (*EFI_GET_VARIABLE)(IN CHAR16 *VariableName,
                                       IN EFI_GUID *VenderGuid,
                                       OUT UINT32 *Attributes OPTIONAL,
                                       IN OUT UINTN *DataSize,
                                       OUT void *Data OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#getnextvariablename
typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(IN OUT UINTN *VariableNameSize,
                                                 IN OUT CHAR16 *VariableName,
                                                 IN OUT EFI_GUID *VenderGuid);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#setvariable
typedef EFI_STATUS (*EFI_SET_VARIABLE)(IN CHAR16 *VariableName,
                                       IN EFI_GUID *VendorGuid,
                                       IN UINT32 Attributes, IN UINTN DataSize,
                                       IN void *Data);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#queryvariableinfo
typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(
    IN UINT32 Attributes, OUT UINT64 *MaximumVariableStorageSize,
    OUT UINT64 *RemainingVariableStorageSize, OUT UINT64 *MaximumVariableSize);

// ---------------------------------------------------------------------------
// Miscellaneous Runtime Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#get-next-high-monotonic-count
typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(OUT UINT32 *HighCount);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#reset-system
typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef void (*EFI_RESET_SYSTEM)(IN EFI_RESET_TYPE ResetType,
                                 IN EFI_STATUS ResetStatus, IN UINTN DataSize,
                                 IN void *ResetData OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#update-capsule
typedef struct {
    UINT64 Length;
    union {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
} EFI_CAPSULE_BLOCK_DESCRIPTOR;

typedef struct {
    EFI_GUID CapsuleGuid;
    UINT32 HeaderSize;
    UINT32 Flags;
    UINT32 CapsuleImageSize;
} EFI_CAPSULE_HEADER;

typedef EFI_STATUS (*EFI_UPDATE_CAPSULE)(
    IN EFI_CAPSULE_HEADER **CapsuleHeaderArray, IN UINTN CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#querycapsulecapabilities
typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES)(
    IN EFI_CAPSULE_HEADER **CapsuleHeaderArray, IN UINTN CapsuleCount,
    OUT UINT64 *MaximumCapsuleSize, OUT EFI_RESET_TYPE *ResetType);

#endif // RUNTIME_SERVICES_H_
