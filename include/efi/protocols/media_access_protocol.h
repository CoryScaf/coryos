#ifndef MEDIA_ACCESS_PROTOCOL_H_
#define MEDIA_ACCESS_PROTOCOL_H_

#include "../efidefs.h"
#include "../efivars.h"
#include "device_path_protocol.h"
#include "runtime_services.h"

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#file-protocol
#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

//******************************************************
// Open Modes
//******************************************************
#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

//******************************************************
// File Attributes
//******************************************************
#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

typedef struct _EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-open
typedef EFI_STATUS (*EFI_FILE_OPEN)(IN EFI_FILE_PROTOCOL *This,
                                    OUT EFI_FILE_PROTOCOL **NewHandle,
                                    IN CHAR16 *FileName, IN UINT64 OpenMode,
                                    IN UINT64 Attributes);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-close
typedef EFI_STATUS (*EFI_FILE_CLOSE)(IN EFI_FILE_PROTOCOL *This);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-delete
typedef EFI_STATUS (*EFI_FILE_DELETE)(IN EFI_FILE_PROTOCOL *This);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-read
typedef EFI_STATUS (*EFI_FILE_READ)(IN EFI_FILE_PROTOCOL *This,
                                    IN OUT UINTN *BufferSize, OUT void *Buffer);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-write
typedef EFI_STATUS (*EFI_FILE_WRITE)(IN EFI_FILE_PROTOCOL *This,
                                     IN OUT UINTN *BufferSize, IN void *Buffer);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-openex
typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    UINTN BufferSize;
    void *Buffer;
} EFI_FILE_IO_TOKEN;

typedef EFI_STATUS (*EFI_FILE_OPEN_EX)(IN EFI_FILE_PROTOCOL *This,
                                       OUT EFI_FILE_PROTOCOL **NewHandle,
                                       IN CHAR16 *FileName, IN UINT64 OpenMode,
                                       IN UINT64 Attributes,
                                       IN OUT EFI_FILE_IO_TOKEN *Token);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-readex
typedef EFI_STATUS (*EFI_FILE_READ_EX)(IN EFI_FILE_PROTOCOL *This,
                                       IN OUT EFI_FILE_IO_TOKEN *Token);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-writeex
typedef EFI_STATUS (*EFI_FILE_WRITE_EX)(IN EFI_FILE_PROTOCOL *This,
                                        IN OUT EFI_FILE_IO_TOKEN *Token);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-flushex
typedef EFI_STATUS (*EFI_FILE_FLUSH_EX)(IN EFI_FILE_PROTOCOL *This,
                                        IN OUT EFI_FILE_IO_TOKEN *Token);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-setposition
typedef EFI_STATUS (*EFI_FILE_SET_POSITION)(IN EFI_FILE_PROTOCOL *This,
                                            IN UINT64 Position);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-getposition
typedef EFI_STATUS (*EFI_FILE_GET_POSITION)(IN EFI_FILE_PROTOCOL *This,
                                            OUT UINT64 *Position);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-getinfo
typedef EFI_STATUS (*EFI_FILE_GET_INFO)(IN EFI_FILE_PROTOCOL *This,
                                        IN EFI_GUID *InformationType,
                                        IN OUT UINTN *BufferSize,
                                        OUT void *Buffer);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-setinfo
typedef EFI_STATUS (*EFI_FILE_SET_INFO)(IN EFI_FILE_PROTOCOL *This,
                                        IN EFI_GUID *InformationType,
                                        IN UINTN BufferSize, IN void *Buffer);

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-protocol-flush
typedef EFI_STATUS (*EFI_FILE_FLUSH)(IN EFI_FILE_PROTOCOL *This);

struct _EFI_FILE_PROTOCOL {
    UINT64 Revision;
    EFI_FILE_OPEN Open;
    EFI_FILE_CLOSE Close;
    EFI_FILE_DELETE Delete;
    EFI_FILE_READ Read;
    EFI_FILE_WRITE Write;
    EFI_FILE_GET_POSITION GetPosition;
    EFI_FILE_SET_POSITION SetPosition;
    EFI_FILE_GET_INFO GetInfo;
    EFI_FILE_SET_INFO SetInfo;
    EFI_FILE_FLUSH Flush;
    EFI_FILE_OPEN_EX OpenEx;
    EFI_FILE_READ_EX ReadEx;
    EFI_FILE_WRITE_EX WriteEx;
    EFI_FILE_FLUSH_EX FlushEx;
};

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#simple-file-system-protocol
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                                   \
    {                                                                          \
        0x0964e5b22, 0x6459, 0x11d2, {                                         \
            0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                     \
        }                                                                      \
    }

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef EFI_STATUS (*EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(
    IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, OUT EFI_FILE_PROTOCOL **Root);

struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    UINT64 Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
};

// https://uefi.org/specs/UEFI/2.10/13_Protocols_Media_Access.html#efi-file-info
#define EFI_FILE_INFO_GUID                                                     \
    {                                                                          \
        0x9576e92, 0x6d3f, 0x11d2, {                                           \
            0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b                      \
        }                                                                      \
    }

typedef struct {
    UINT64 Size;
    UINT64 FileSize;
    UINT64 PhysicalSize;
    EFI_TIME CreateTime;
    EFI_TIME LastAccessTime;
    EFI_TIME ModificationTime;
    UINT64 Attribute;
    CHAR16 FileName[1];
} EFI_FILE_INFO;

#endif
