/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Disable factory test so we can override dip_switch_update_user
#undef FACTORY_TEST_ENABLE

// Increase EEPROM to support 16 layers + macros
#undef WEAR_LEVELING_LOGICAL_SIZE
#define WEAR_LEVELING_LOGICAL_SIZE 4096
#undef WEAR_LEVELING_BACKING_SIZE
#define WEAR_LEVELING_BACKING_SIZE 8192

// VIA layer count (must match number of layers in keymap)
#define DYNAMIC_KEYMAP_LAYER_COUNT 16
#define DYNAMIC_KEYMAP_MACRO_COUNT 28

// Set default RGB matrix to solid white
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE 0        // Hue for white
#define RGB_MATRIX_DEFAULT_SAT 0        // Saturation 0 = white (no color)
#define RGB_MATRIX_DEFAULT_VAL 255      // Full brightness

// Mouse keys - Inertia mode (smooth gliding movement)
#define MOUSEKEY_INERTIA
#define MOUSEKEY_DELAY 10
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 32
#define MOUSEKEY_TIME_TO_MAX 20
#define MOUSEKEY_FRICTION 12
#define MOUSEKEY_MOVE_DELTA 1

// Tap-Hold Related
// Note: You can also set per-key tapping terms by enabling TAPPING_TERM_PER_KEY and 
// implementing get_tapping_term() — useful if you want a faster term on your LT()
// key but keep 200ms for your other custom tap/hold keys.
#define TAPPING_TERM 200