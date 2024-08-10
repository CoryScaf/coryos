#ifndef DEVICE_PATH_PROTOCOL_H_
#define DEVICE_PATH_PROTOCOL_H_

#include "../efivars.h"

// ---------------------------------------------------------------------------
// Device Path Protocol
// https://uefi.org/specs/UEFI/2.10/10_Protocols_Device_Path_Protocol.html
// ---------------------------------------------------------------------------

// https://uefi.org/specs/UEFI/2.10/10_Protocols_Device_Path_Protocol.html#efi-device-path-protocol
typedef struct {
    UINT8 Type;
    UINT8 SubType;
    UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

#endif
