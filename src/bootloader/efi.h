#ifndef EFI_H_
#define EFI_H_

#include "efi/efidefs.h"
#include "efi/efivars.h"

// protocols

// EFI_SIMPLE_TEXT_INPUT_PROTOCOL
// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#simple-text-input-protocol
typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-input-protocol-reset
typedef EFI_STATUS (*EFI_INPUT_RESET)(IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
                                      IN BOOLEAN ExtendedVerification);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-input-protocol-readkeystroke
typedef struct {
    UINT16 ScanCode;
    CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef EFI_STATUS (*EFI_INPUT_READ_KEY)(
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, OUT EFI_INPUT_KEY *Key);

struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_INPUT_RESET Reset;
    EFI_INPUT_READ_KEY ReadKeyStroke;
    EFI_EVENT WaitForKey;
};

// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#simple-text-output-protocol
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-reset
typedef EFI_STATUS (*EFI_TEXT_RESET)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
                                     IN BOOLEAN ExtendedVerification);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-outputstring
typedef EFI_STATUS (*EFI_TEXT_STRING)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
                                      IN CHAR16 *String);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-teststring
typedef EFI_STATUS (*EFI_TEXT_TEST_STRING)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN CHAR16 *String);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-querymode
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ModeNumber,
    OUT UINTN *Columns, OUT UINTN *Rows);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-setmode
typedef EFI_STATUS (*EFI_TEXT_SET_MODE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ModeNumber);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-setattribute
typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN Attribute);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-clearscreen
typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-setcursorposition
typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN Column, IN UINTN Row);

// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html#efi-simple-text-output-protocol-enablecursor
typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR)(
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN BOOLEAN Visible);

typedef struct {
    UINT32 MaxMode;
    UINT32 Mode;
    UINT32 Attribute;
    UINT32 CursorColumn;
    UINT32 CursorRow;
    BOOLEAN CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET Reset;
    EFI_TEXT_STRING OutputString;
    EFI_TEXT_TEST_STRING TestString;
    EFI_TEXT_QUERY_MODE QueryMode;
    EFI_TEXT_SET_MODE SetMode;
    EFI_TEXT_SET_ATTRIBUTE SetAttribute;
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR EnableCursor;
    SIMPLE_TEXT_OUTPUT_MODE *Mode;
};

// EFI_RUNTIME_SERVICES

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

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-getmemorymap
typedef struct {
    UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    UINT64 NumberOfPages;
    UINT64 Attribute;
} EFI_MEMORY_DESCRIPTION;

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#setvirtualaddressmap
typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(
    IN UINTN MemoryMapSize, IN UINTN DescriptorSize,
    IN UINT32 DescriptorVersion, IN EFI_MEMORY_DESCRIPTION *VirtualMap);

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#convertpointer
typedef EFI_STATUS (*EFI_CONVERT_POINTER)(IN UINTN DebugDisposition,
                                          IN void **Address);

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

// https://uefi.org/specs/UEFI/2.10/08_Services_Runtime_Services.html#queryvariableinfo
typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(
    IN UINT32 Attributes, OUT UINT64 *MaximumVariableStorageSize,
    OUT UINT64 *RemainingVariableStorageSize, OUT UINT64 *MaximumVariableSize);

// EFI_BOOT_SERVICES
// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-raisetpl
typedef UINTN EFI_TPL;
typedef EFI_TPL (*EFI_RAISE_TPL)(IN EFI_TPL NewTpl);

// https://uefi.org/specs/UEFI/2.10/07_Services_Boot_Services.html#efi-boot-services-restoretpl

// EFI_TABLE_HEADER
// https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html
typedef struct {
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

// EFI_BOOT_SERVICES
// https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html#efi-boot-services-table
/*typedef struct {
    EFI_TABLE_HEADER Hdr;
    EFI_RAISE_TPL RaiseTPL;     // EFI 1.0+
    EFI_RESTORE_TPL RestoreTPL; // EFI 1.0+

    //
    // Memory Services
    //
    EFI_ALLOCATE_PAGES AllocatePages; // EFI 1.0+
    EFI_FREE_PAGES FreePages;         // EFI 1.0+
    EFI_GET_MEMORY_MAP GetMemoryMap;  // EFI 1.0+
    EFI_ALLOCATE_POOL AllocatePool;   // EFI 1.0+
    EFI_FREE_POOL FreePool;           // EFI 1.0+

    //
    // Event & Timer Services
    //
    EFI_CREATE_EVENT CreateEvent;    // EFI 1.0+
    EFI_SET_TIMER SetTimer;          // EFI 1.0+
    EFI_WAIT_FOR_EVENT WaitForEvent; // EFI 1.0+
    EFI_SIGNAL_EVENT SignalEvent;    // EFI 1.0+
    EFI_CLOSE_EVENT CloseEvent;      // EFI 1.0+
    EFI_CHECK_EVENT CheckEvent;      // EFI 1.0+

    //
    // Protocol Handler Services
    //
    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;     // EFI 1.0+
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+
    EFI_HANDLE_PROTOCOL HandleProtocol;                          // EFI 1.0+
    VOID *Reserved;                                              // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;         // EFI  1.0+
    EFI_LOCATE_HANDLE LocateHandle;                              // EFI 1.0+
    EFI_LOCATE_DEVICE_PATH LocateDevicePath;                     // EFI 1.0+
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;   // EFI 1.0+

    //
    // Image Services
    //
    EFI_IMAGE_UNLOAD LoadImage;              // EFI 1.0+
    EFI_IMAGE_START StartImage;              // EFI 1.0+
    EFI_EXIT Exit;                           // EFI 1.0+
    EFI_IMAGE_UNLOAD UnloadImage;            // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES ExitBootServices; // EFI 1.0+

    //
    // Miscellaneous Services
    //
    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL Stall;                                    // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;            // EFI 1.0+

    //
    // DriverSupport Services
    //
    EFI_CONNECT_CONTROLLER ConnectController;       // EFI 1.1
    EFI_DISCONNECT_CONTROLLER DisconnectController; // EFI 1.1+

    //
    // Open and Close Protocol Services
    //
    EFI_OPEN_PROTOCOL OpenProtocol;                        // EFI 1.1+
    EFI_CLOSE_PROTOCOL CloseProtocol;                      // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation; // EFI 1.1+

    //
    // Library Services
    //
    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle; // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer; // EFI 1.1+
    EFI_LOCATE_PROTOCOL LocateProtocol;          // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES
    InstallMultipleProtocolInterfaces; // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES
    UninstallMultipleProtocolInterfaces; // EFI 1.1+*

    //
    // 32-bit CRC Services
    //
    EFI_CALCULATE_CRC32 CalculateCrc32; // EFI 1.1+

    //
    // Miscellaneous Services
    //
    EFI_COPY_MEM CopyMem;              // EFI 1.1+
    EFI_SET_MEM SetMem;                // EFI 1.1+
    EFI_CREATE_EVENT_EX CreateEventEx; // UEFI 2.0+
} EFI_BOOT_SERVICES; */

// EFI_RUNTIME_SERVICES
// https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html#efi-runtime-services-table
typedef struct {
    EFI_TABLE_HEADER Hdr;
    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;
    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;
    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;
    EFI_UPDATE_CAPSULE UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;
    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
} EFI_RUNTIME_SERVICES;

// system table
// https://uefi.org/specs/UEFI/2.10/04_EFI_System_Table.html
typedef struct {
    EFI_TABLE_HEADER Hdr;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    void *BootServices;
    UINTN NumberOfTableEntries;
    void *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif // EFI_H_
