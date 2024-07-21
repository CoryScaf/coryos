#ifndef BOOT_SERVICES_H_
#define BOOT_SERVICES_H_

#include "../efidefs.h"
#include "../efivars.h"
#include "device_path_protocol.h"

// ---------------------------------------------------------------------------
// Boot Services
// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html
// ---------------------------------------------------------------------------

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

// ---------------------------------------------------------------------------
// Event, Timer, and Task Priority Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-raisetpl
typedef UINTN EFI_TPL;

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-createevent
typedef void *EFI_EVENT;

typedef void (*EFI_EVENT_NOTIFY)(IN EFI_EVENT Event, IN void *Context);

typedef EFI_STATUS (*EFI_CREATE_EVENT)(
    IN UINT32 Type, IN EFI_TPL NotifyTpl,
    IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
    IN void *NotifyContext OPTIONAL, OUT EFI_EVENT *Event);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-createeventex
typedef EFI_STATUS (*EFI_CREATE_EVENT_EX)(
    IN UINT32 Type, IN EFI_TPL NotifyTpl,
    IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
    IN void *NotifyContext OPTIONAL, IN EFI_GUID *EventGroup OPTIONAL,
    OUT EFI_EVENT *Event);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-closeevent
typedef EFI_STATUS (*EFI_CLOSE_EVENT)(IN EFI_EVENT Event);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-signalevent
typedef EFI_STATUS (*EFI_SIGNAL_EVENT)(IN EFI_EVENT Event);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-waitforevent
typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT)(IN UINTN NumberOfEvents,
                                         IN EFI_EVENT *Event, OUT UINTN *Index);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-checkevent
typedef EFI_STATUS (*EFI_CHECK_EVENT)(IN EFI_EVENT Event);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-settimer
typedef enum { TimerCancel, TimerPeriodic, TimerRelative } EFI_TIMER_DELAY;

typedef EFI_STATUS (*EFI_SET_TIMER)(IN EFI_EVENT Event, IN EFI_TIMER_DELAY Type,
                                    IN UINT64 TriggerTime);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-raisetpl
typedef EFI_TPL (*EFI_RAISE_TPL)(IN EFI_TPL NewTpl);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-restoretpl
typedef void (*EFI_RESTORE_TPL)(IN EFI_TPL OldTpl);

// ---------------------------------------------------------------------------
// Memory Allocation Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-allocatepages
typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(IN EFI_ALLOCATE_TYPE Type,
                                         IN EFI_MEMORY_TYPE MemoryType,
                                         IN UINTN Pages,
                                         IN OUT EFI_PHYSICAL_ADDRESS *Memory);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-freepages
typedef EFI_STATUS (*EFI_FREE_PAGES)(IN EFI_PHYSICAL_ADDRESS Memory,
                                     IN UINTN Pages);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-getmemorymap
typedef struct {
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTION;

typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(IN OUT UINTN *MemoryMapSize,
                                         OUT EFI_MEMORY_DESCRIPTION *MemoryMap,
                                         OUT UINTN *MapKey,
                                         OUT UINTN *DescriptorSize,
                                         OUT UINT32 *DescriptorVersion);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-allocatepool
typedef EFI_STATUS (*EFI_ALLOCATE_POOL)(IN EFI_MEMORY_TYPE PoolType,
                                        IN UINTN Size, OUT void **Buffer);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-freepool
typedef EFI_STATUS (*EFI_FREE_POOL)(IN void *Buffer);

// ---------------------------------------------------------------------------
// Protocol Handler Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-installprotocolinterface
typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE)(
    IN OUT EFI_HANDLE *Handle, IN EFI_GUID *Protocol,
    IN EFI_INTERFACE_TYPE InterfaceType, IN void *Interface);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-uninstallprotocolinterface
typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE)(IN EFI_HANDLE Handle,
                                                       IN EFI_GUID *Protocol,
                                                       IN void *Interface);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-reinstallprotocolinterface
typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE)(IN EFI_HANDLE Handle,
                                                       IN EFI_GUID *Protocol,
                                                       IN void *OldInterface,
                                                       IN void *NewInterface);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-registerprotocolnotify
typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(IN EFI_GUID *Protocol,
                                                   IN EFI_EVENT Event,
                                                   OUT void **Registration);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-locatehandle
typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef EFI_STATUS (*EFI_LOCATE_HANDLE)(IN EFI_LOCATE_SEARCH_TYPE SearchType,
                                        IN EFI_GUID *Protocol OPTIONAL,
                                        IN void *SearchKey OPTIONAL,
                                        IN OUT UINTN *BufferSize,
                                        OUT EFI_HANDLE *Buffer);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-handleprotocol
typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(IN EFI_HANDLE Handle,
                                          IN EFI_GUID *Protocol,
                                          OUT void **Interface);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-locatedevicepath
typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(
    IN EFI_GUID *Protocol, IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
    OUT EFI_HANDLE *Device);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-openprotocol
typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(IN EFI_HANDLE Handle,
                                        IN EFI_GUID *Protocol,
                                        OUT void **Interface OPTIONAL,
                                        IN EFI_HANDLE AgentHandle,
                                        IN EFI_HANDLE ControllerHandle,
                                        IN UINT32 Attributes);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-closeprotocol
typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(IN EFI_HANDLE Handle,
                                         IN EFI_GUID *Protocol,
                                         IN EFI_HANDLE AgentHandle,
                                         IN EFI_HANDLE ControllerHandle);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-openprotocolinformation
typedef struct {
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    UINT32 Attributes;
    UINT32 OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(
    IN EFI_HANDLE Handle, IN EFI_GUID *Protocol,
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
    OUT UINTN *EntryCount);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-connectcontroller
typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(
    IN EFI_HANDLE ControllerHandle, IN EFI_HANDLE *DriverImageHandle OPTIONAL,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
    IN BOOLEAN Recursive);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-disconnectcontroller
typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(
    IN EFI_HANDLE ControllerHandle, IN EFI_HANDLE DriverImageHandle OPTIONAL,
    IN EFI_HANDLE ChildHandle OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-protocolsperhandle
typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(IN EFI_HANDLE Handle,
                                               OUT EFI_GUID ***ProtocolBuffer,
                                               OUT UINTN *ProtocolBufferCount);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-locatehandlebuffer
typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(
    IN EFI_LOCATE_SEARCH_TYPE SearchType, IN EFI_GUID *Protocol OPTIONAL,
    IN void *SearchKey OPTIONAL, OUT UINTN *NoHandles, OUT EFI_HANDLE **Buffer);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-locateprotocol
typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(IN EFI_GUID *Protocol,
                                          IN void *Registration OPTIONAL,
                                          OUT void **Interface);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-installmultipleprotocolinterfaces
typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    IN OUT EFI_HANDLE *Handle, ...);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-uninstallmultipleprotocolinterfaces
typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    IN EFI_HANDLE Handle, ...);

// ---------------------------------------------------------------------------
// Image Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-loadimage
typedef EFI_STATUS (*EFI_IMAGE_LOAD)(
    IN BOOLEAN BootPolicy, IN EFI_HANDLE ParentImageHandle,
    IN EFI_DEVICE_PATH_PROTOCOL *DevicePath OPTIONAL,
    IN void *SourceBuffer OPTIONAL, IN UINTN SourceSize,
    OUT EFI_HANDLE *ImageHandle);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-startimage
typedef EFI_STATUS (*EFI_IMAGE_START)(IN EFI_HANDLE ImageHandle,
                                      OUT UINTN *ExitDataSize,
                                      OUT CHAR16 **ExitData OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-unloadimage
typedef EFI_STATUS (*EFI_IMAGE_UNLOAD)(IN EFI_HANDLE ImageHandle);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-exit
typedef EFI_STATUS (*EFI_EXIT)(IN EFI_HANDLE ImageHandle,
                               IN EFI_STATUS ExitStatus, IN UINTN ExitDataSize,
                               IN CHAR16 *ExitData OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-exitbootservices
typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(IN EFI_HANDLE ImageHandle,
                                             IN UINTN MapKey);

// ---------------------------------------------------------------------------
// Miscellaneous Boot Services
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-setwatchdogtimer
typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(IN UINTN Timeout,
                                             IN UINT64 WatchdogCode,
                                             IN UINTN DataSize,
                                             IN CHAR16 *WatchdogData OPTIONAL);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-stall
typedef EFI_STATUS (*EFI_STALL)(IN UINTN Microseconds);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-copymem
typedef void (*EFI_COPY_MEM)(IN void *Destination, IN void *Source,
                             IN UINTN Length);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-setmem
typedef void (*EFI_SET_MEM)(IN void *Buffer, IN UINTN Size, IN UINT8 Value);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-getnextmonotoniccount
typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(OUT UINT64 *Count);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-installconfigurationtable
typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(IN EFI_GUID *Guid,
                                                      IN void *Table);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-calculatecrc32
typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(IN void *Data, IN UINTN DataSize,
                                          OUT UINT32 *Crc32);

#endif
