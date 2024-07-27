#ifndef CONSOLE_PROTOCOLS_H_
#define CONSOLE_PROTOCOLS_H_

#include "../efidefs.h"
#include "../efivars.h"

// ---------------------------------------------------------------------------
// Console support protocols
// https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// EFI_SIMPLE_TEXT_INPUT_PROTOCOL
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
// ---------------------------------------------------------------------------

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

#endif // CONSOLE_PROTOCOLS_H_
