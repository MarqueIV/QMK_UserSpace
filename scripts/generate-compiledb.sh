#!/bin/bash
# Generates compile_commands.json for VSCode IntelliSense from QMK build output.
# Usage: generate-compiledb.sh [keyboard] [keymap]
# If no args, reads from .last_build

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
USERSPACE_DIR="$(dirname "$SCRIPT_DIR")"
FIRMWARE_DIR="$HOME/Code_ReallyNew/Hardware/QMK_Firmware"
LAST_BUILD_FILE="$USERSPACE_DIR/.last_build"
OUTPUT="$USERSPACE_DIR/compile_commands.json"

KEYBOARD="$1"
KEYMAP="$2"

if [[ -z "$KEYBOARD" || -z "$KEYMAP" ]]; then
    if [[ -f "$LAST_BUILD_FILE" ]]; then
        source "$LAST_BUILD_FILE"
    else
        echo "Error: No keyboard/keymap specified and no .last_build found."
        echo "Usage: generate-compiledb.sh <keyboard> <keymap>"
        exit 1
    fi
fi

echo "Generating compile_commands.json for ${KEYBOARD}:${KEYMAP}..."

# Get dry-run build output with full commands
RAW=$(cd "$FIRMWARE_DIR" && QMK_USERSPACE="$USERSPACE_DIR" make "${KEYBOARD}:${KEYMAP}" -n 2>&1)

# Extract gcc compile commands and build JSON entries
echo "[" > "$OUTPUT"
FIRST=true

while IFS= read -r line; do
    # Extract the source file (last .c argument before -o)
    SRC=$(echo "$line" | grep -o '[^ ]*\.c' | tail -1)
    if [[ -z "$SRC" ]]; then
        continue
    fi

    # Make source path absolute
    if [[ "$SRC" != /* ]]; then
        SRC="$FIRMWARE_DIR/$SRC"
    fi

    # Skip if file doesn't exist
    if [[ ! -f "$SRC" ]]; then
        continue
    fi

    if [[ "$FIRST" != true ]]; then
        echo "," >> "$OUTPUT"
    fi
    FIRST=false

    # Escape the command for JSON
    ESCAPED_LINE=$(echo "$line" | sed 's/\\/\\\\/g; s/"/\\"/g')

    cat >> "$OUTPUT" <<ENTRY
  {
    "directory": "$FIRMWARE_DIR",
    "command": "$ESCAPED_LINE",
    "file": "$SRC"
  }
ENTRY

done < <(echo "$RAW" | grep 'arm-none-eabi-gcc -c' | sed 's/.*arm-none-eabi-gcc/arm-none-eabi-gcc/')

echo "]" >> "$OUTPUT"

COUNT=$(grep -c '"file"' "$OUTPUT")
echo "Generated $OUTPUT with $COUNT entries."
