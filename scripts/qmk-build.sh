#!/bin/bash
# Extracts keyboard:keymap from the current file path and runs make.
# Usage: qmk-build.sh <relative-file-path> [flash]

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
USERSPACE_DIR="$(dirname "$SCRIPT_DIR")"
FIRMWARE_DIR="$HOME/Code_ReallyNew/Hardware/QMK_Firmware"
LAST_BUILD_FILE="$USERSPACE_DIR/.last_build"

REL_PATH="$1"
ACTION="$2"

if [[ -z "$REL_PATH" ]]; then
    echo "Error: No file path provided."
    echo "This script is meant to be called from a VSCode build task."
    exit 1
fi

# Try to extract keyboard and keymap from path
KEYBOARD=""
KEYMAP=""

if [[ "$REL_PATH" =~ ^keyboards/ ]] && [[ "$REL_PATH" =~ /keymaps/ ]]; then
    AFTER_KEYBOARDS="${REL_PATH#keyboards/}"
    KEYBOARD="${AFTER_KEYBOARDS%%/keymaps/*}"
    AFTER_KEYMAPS="${AFTER_KEYBOARDS#*/keymaps/}"
    KEYMAP="${AFTER_KEYMAPS%%/*}"
fi

# If detection failed, fall back to last build
if [[ -z "$KEYBOARD" || -z "$KEYMAP" ]]; then
    if [[ -f "$LAST_BUILD_FILE" ]]; then
        source "$LAST_BUILD_FILE"
        echo "Not in a keyboard/keymap folder — using last build: ${KEYBOARD}:${KEYMAP}"
        echo ""
    else
        echo "Error: Could not detect keyboard/keymap from path: $REL_PATH"
        echo "Open a file under keyboards/<manufacturer>/<board>/keymaps/<keymap>/ first."
        exit 1
    fi
fi

# Save for next time
echo "KEYBOARD=\"$KEYBOARD\"" > "$LAST_BUILD_FILE"
echo "KEYMAP=\"$KEYMAP\"" >> "$LAST_BUILD_FILE"

TARGET="${KEYBOARD}:${KEYMAP}"
if [[ "$ACTION" == "flash" ]]; then
    TARGET="${TARGET}:flash"
fi

echo "Building: $TARGET"
echo ""

QMK_USERSPACE="$USERSPACE_DIR" make -C "$FIRMWARE_DIR" "$TARGET"
