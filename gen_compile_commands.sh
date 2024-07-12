#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

echo "
[
  {
    \"arguments\": [
      \"clang\",
      \"-target\",
      \"x86_64-unknown-windows\",
      \"-ffreestanding\",
      \"-fshort-wchar\",
      \"-mno-red-zone\",
      \"-I/usr/include\",
      \"-c\",
      \"-o\",
      \"bootloader.o\",
      \"bootloader.c\"
    ],
    \"directory\": \"$SCRIPT_DIR/src/bootloader\",
    \"file\": \"$SCRIPT_DIR/src/bootloader/bootloader.c\",
    \"output\": \"$SCRIPT_DIR/src/bootloader/bootloader.o\"
  }
  ]" > $SCRIPT_DIR/src/bootloader/compile_commands.json
