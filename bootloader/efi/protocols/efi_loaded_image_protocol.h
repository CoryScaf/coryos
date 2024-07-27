#ifndef EFI_LOADED_IMAGE_PROTOCOL_H_
#define EFI_LOADED_IMAGE_PROTOCOL_H_

#include "../system_table.h"

// ---------------------------------------------------------------------------
// EFI loaded image protocol
// https://uefi.org/specs/UEFI/2.10/09_Protocols_EFI_Loaded_Image.html
// ---------------------------------------------------------------------------

#define EFI_LOADED_IMAGE_PROTOCOL_GUID                                         \
    {                                                                          \
        0x5B1B31A1, 0x9562, 0x11d2, {                                          \
            0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B                     \
        }                                                                      \
    }

typedef struct {
    UINT32 Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE *SystemTable;

    // Source location of the image
    EFI_HANDLE DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL *FilePath;
    void *Reserved;

    // Image’s load options
    UINT32 LoadOptionsSize;
    void *LoadOptions;

    // Location where image was loaded
    void *ImageBase;
    UINT64 ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    EFI_IMAGE_UNLOAD Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

#endif
