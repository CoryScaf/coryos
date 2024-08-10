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
      \"-I$SCRIPT_DIR/include\",
      \"-c\",
      \"-o\",
      \"bootloader.o\",
      \"bootloader.c\"
    ],
    \"directory\": \"$SCRIPT_DIR/bootloader\",
    \"file\": \"$SCRIPT_DIR/bootloader/bootloader.c\",
    \"output\": \"$SCRIPT_DIR/build/bootloader/bootloader.o\"
  },
  {
    \"arguments\": [
      \"clang\",
      \"-target\",
      \"x86_64-unknown-windows\",
      \"-ffreestanding\",
      \"-fshort-wchar\",
      \"-mno-red-zone\",
      \"-I$SCRIPT_DIR/include\",
      \"-c\",
      \"-o\",
      \"utils.o\",
      \"utils.c\"
    ],
    \"directory\": \"$SCRIPT_DIR/bootloader\",
    \"file\": \"$SCRIPT_DIR/bootloader/utils.c\",
    \"output\": \"$SCRIPT_DIR/build/bootloader/utils.o\"
  }
]" > $SCRIPT_DIR/bootloader/compile_commands.json

echo "
[
  {
    \"arguments\": [
      \"clang\",
      \"-target\",
      \"x86_64-unknown-none\",
      \"-ffreestanding\",
      \"-mno-red-zone\",
      \"-I$SCRIPT_DIR/include\",
      \"-c\",
      \"-o\",
      \"main.o\",
      \"main.c\"
    ],
    \"directory\": \"$SCRIPT_DIR/kernel\",
    \"file\": \"$SCRIPT_DIR/kernel/main.c\",
    \"output\": \"$SCRIPT_DIR/build/kernel/main.o\"
  }
]" > $SCRIPT_DIR/kernel/compile_commands.json
