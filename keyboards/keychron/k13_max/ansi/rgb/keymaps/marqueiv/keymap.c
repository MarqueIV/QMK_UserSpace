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

#include <stdint.h>
#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "host.h"
#include "marqueiv.h"

// Forward declarations
void set_kvm(keycode_t keycode);

// Tap dance macro with user_data support
#define ACTION_TAP_DANCE_FN_USER(user_fn, data) { \
    .fn        = { NULL, user_fn, NULL, NULL }, \
    .user_data = (void *)(uintptr_t)(data) \
}

// Tap dance macro with user_data support
#define ACTION_TAP_DANCE_FN_USER_EX(user_fn, user_release_fn, data) { \
    .fn        = { NULL, user_fn, user_release_fn, NULL }, \
    .user_data = (void *)(uintptr_t)(data) \
}

// External mousekey variables for runtime speed adjustment (inertia mode)
extern uint8_t mk_max_speed;
extern uint8_t mk_time_to_max;
extern uint8_t mk_wheel_max_speed;
extern uint8_t mk_wheel_time_to_max;

enum layers {
    DEFAULT,
    HOME_ROW_MODS,
    LAYOUT_60,
    LAYOUT_40,
    NUM_ROW_OVERLAY,
    MOD_SWAP,
    ZOOM,
    NUMPAD,
    FKEYS,
    NAVIGATION,
    MOUSE,
    MOUSE_SCROLL,
    CUSTOM_1,
    CUSTOM_2,
    SET_KVM_KEY,
    QUICK_ACTIONS,
};

// IMPORTANT!!!
// Make sure this enum starts on line 63 so the line numbers match the 
// custom key codes you can use in Keychron Launcher and VIA
enum custom_keycodes { 
    KC_BOOTLOADER = SAFE_RANGE,
    KC_DISABLE_MOD_SWAP,
    KC_ENABLE_MOD_SWAP,
    KC_TOGGLE_MOD_SWAP,
    KC_TOGGLE_BACKLIGHT,
    KC_TOGGLE_FKEYS,
    KC_TOGGLE_MOUSE,
    KC_MODE_NORMAL,
    KC_MOUSE_SPEED_DOWN,
    KC_MOUSE_SPEED_UP,
    KC_KVM_PORT1,
    KC_KVM_PORT2,
    KC_KVM_PORT3,
    KC_KVM_PORT4,
    KC_KVM_MONA_PORT1,
    KC_KVM_MONA_PORT2,
    KC_KVM_MONA_PORT3,
    KC_KVM_MONA_PORT4,
    KC_KVM_MONB_PORT1,
    KC_KVM_MONB_PORT2,
    KC_KVM_MONB_PORT3,
    KC_KVM_MONB_PORT4,
    KC_KVM_MONC_PORT1,
    KC_KVM_MONC_PORT2,
    KC_KVM_MONC_PORT3,
    KC_KVM_MONC_PORT4,
    KC_DICT,               // HID Consumer Control 0x0CF - Voice Command
    KC_DICTATION_SESSION,  // HID Consumer Control 0x0D8 - Start/Stop Voice Dictation Session
    KC_DEBUG
};

// Custom Key Codes
#define KC_SSHOT     LCTL(LGUI(LALT(LSFT(KC_C))))
#define KC_DOCK      LCTL(KC_F3)
#define KC_MENU      LCTL(KC_F2)
#define KC_STATMENU  LCTL(KC_F8)
#define KC_ZOOM      LCTL(LGUI(KC_F))

enum mouse_speed_mode {
    SPEED_SLOWEST,
    SPEED_SLOWER,
    SPEED_NORMAL,
    SPEED_FASTER,
    SPEED_FASTEST,
};

// Tap Dance declarations
enum {
    TD_PASSWORD,
    TD_USERNAME,
    TD_EMAIL,
    TD_PHONE,
    TD_CREDIT_CARD,
    TD_ADDRESS_FULL,
    TD_ADDRESS_STREET,
    TD_ADDRESS_STREET2,    
    TD_ADDRESS_CITY,
    TD_ADDRESS_STATE,
    TD_ADDRESS_ZIP,
    TD_NAME,
    TD_KVM_PORT1,
    TD_KVM_PORT2,
    TD_KVM_PORT3,
    TD_KVM_PORT4,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_ansi_90(       
        KC_ESC,                         KC_F1,    KC_F2,  KC_MCTL,  KC_ZOOM,  KC_F5,   KC_F6,  KC_SSHOT,  KC_DICT,  KC_F9,              KC_MUTE,  KC_VOLD,          KC_VOLU,  KC_MPRV,           KC_MNXT,           KC_MPLY,
        KC_GRV,              KC_1,      KC_2,     KC_3,   KC_4,     KC_5,     KC_6,    KC_7,   KC_8,      KC_9,     KC_0,               KC_MINS,  KC_EQL,           KC_BSPC,  KC_INS,            KC_HOME,           KC_PGUP,
        KC_TAB,              KC_Q,      KC_W,     KC_E,   KC_R,     KC_T,     KC_Y,    KC_U,   KC_I,      KC_O,     KC_P,               KC_LBRC,  KC_RBRC,          KC_BSLS,  KC_DEL,            KC_END,            KC_PGDN,
        LT(NUMPAD, KC_CAPS), KC_A,      KC_S,     KC_D,   KC_F,     KC_G,     KC_H,    KC_J,   KC_K,      KC_L,     KC_SCLN,            KC_QUOT,                    KC_ENT,   TD(TD_KVM_PORT1),  TD(TD_KVM_PORT2),  TD(TD_KVM_PORT4),
        KC_LSFT,                        KC_Z,     KC_X,   KC_C,     KC_V,     KC_B,    KC_N,   KC_M,      KC_COMM,  KC_DOT,             KC_SLSH,                    KC_RSFT,                     KC_UP,
        LM(ZOOM, MOD_LCTL),  KC_LOPTN,  KC_LCMD,                              KC_SPC,                               MO(QUICK_ACTIONS),  _______,  KC_TOGGLE_MOUSE,  KC_RCTL,  KC_LEFT,           KC_DOWN,           KC_RGHT),

    [HOME_ROW_MODS] = LAYOUT_ansi_90(
        _______,                      _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,            _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,            _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,  _______,  _______,  _______,  _______,  _______,
        _______, MT(MOD_LSFT, KC_A),  MT(MOD_LCTL, KC_S),  MT(MOD_LALT, KC_D),  MT(MOD_LGUI, KC_F),  _______,  _______,                 MT(MOD_RGUI, KC_J),  MT(MOD_RALT, KC_K),  MT(MOD_RCTL, KC_L),  MT(MOD_RSFT, KC_SCLN),  _______,            _______,  _______,  _______,  _______,
        _______,                      _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,            _______,            _______,
        _______,  _______,            _______,                                                                 LT(NAVIGATION, KC_SPC),                                                                 _______,                _______,  _______,  _______,  _______,  _______,  _______),
 
    [LAYOUT_60] = LAYOUT_ansi_90(
        KC_NO,                        KC_NO,               KC_NO,               KC_NO,               KC_NO,    KC_NO,                   KC_NO,               KC_NO,               KC_NO,               KC_NO,                  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_ESC,   _______,            _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,  _______,  _______,  KC_NO,    KC_NO,    KC_NO,
        _______,  _______,            _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,  _______,  _______,  KC_NO,    KC_NO,    KC_NO,
        KC_CAPS, MT(MOD_LSFT, KC_A),  MT(MOD_LCTL, KC_S),  MT(MOD_LALT, KC_D),  MT(MOD_LGUI, KC_F),  _______,  _______,                 MT(MOD_RGUI, KC_J),  MT(MOD_RALT, KC_K),  MT(MOD_RCTL, KC_L),  MT(MOD_RSFT, KC_SCLN),  _______,            _______,  _______,  _______,  _______,
        _______,                      _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,            _______,            KC_NO,
        _______,  _______,            _______,                                                                 LT(NAVIGATION, KC_SPC),                                                                 _______,                _______,  _______,  _______,  KC_NO,    KC_NO,    KC_NO),

    [LAYOUT_40] = LAYOUT_ansi_90(
        KC_NO,                        KC_NO,               KC_NO,               KC_NO,               KC_NO,    KC_NO,                   KC_NO,               KC_NO,               KC_NO,               KC_NO,                  KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_NO,    KC_NO,              KC_NO,               KC_NO,               KC_NO,               KC_NO,    KC_NO,                   KC_NO,               KC_NO,               KC_NO,               KC_NO,                  KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
        KC_ESC,   _______,            _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,              _______,  KC_BSPC,  KC_NO,    KC_NO,    KC_NO,
        KC_TAB,  MT(MOD_LSFT, KC_A),  MT(MOD_LCTL, KC_S),  MT(MOD_LALT, KC_D),  MT(MOD_LGUI, KC_F),  _______,  _______,                 MT(MOD_RGUI, KC_J),  MT(MOD_RALT, KC_K),  MT(MOD_RCTL, KC_L),  MT(MOD_RSFT, KC_SCLN),  _______,                        _______,  _______,  _______,  _______,
        _______,                      _______,             _______,             _______,             _______,  _______,                 _______,             _______,             _______,             _______,                _______,                        _______,            KC_NO,
        _______,  _______,            _______,                                                                 LT(NAVIGATION, KC_SPC),                                                                 _______,                MO(NUM_ROW_OVERLAY),  _______,  _______,  KC_NO,    KC_NO,    KC_NO),

    [NUM_ROW_OVERLAY] = LAYOUT_ansi_90(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSLS,  _______,  _______,  _______,
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),

    [MOD_SWAP] = LAYOUT_ansi_90(
        _______,            _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
        _______,            _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        KC_LCMD,  _______,  LM(ZOOM, MOD_LCTL),                                _______,                                _______,  _______,  _______,  KC_RCMD,  _______,  _______,  _______),

    [ZOOM] = LAYOUT_ansi_90(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_MINS,  KC_P0,    KC_EQL,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),

    [NUMPAD] = LAYOUT_ansi_90(
        KC_MODE_NORMAL,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P7,    KC_P8,    KC_P9,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P4,    KC_P5,    KC_P6,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_P1,    KC_P2,    KC_P3,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_PMNS,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  KC_P0,    KC_PDOT,  KC_PENT),

    [FKEYS] = LAYOUT_ansi_90(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),

    [NAVIGATION] = LAYOUT_ansi_90(
        _______,           KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  
        KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    _______,  KC_NO,    KC_NO,    KC_NO,  
        KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  
        KC_NO,    _______, _______,  _______,  _______,  KC_NO,    KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_NO,    KC_NO,              KC_NO,    KC_NO,    KC_NO,    KC_NO,  
        _______,           _______,  _______,  _______,  _______,  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,              KC_NO,              KC_NO,  
        _______,  _______, _______,                                KC_NO,                                  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO),

    [MOUSE] = LAYOUT_ansi_90(
        KC_MODE_NORMAL,               KC_NO,                KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,            KC_NO,    KC_NO,      KC_NO,      KC_NO,
        KC_NO,            KC_NO,      KC_NO,                KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,            KC_NO,    KC_NO,      KC_NO,      KC_NO,
        KC_NO,            KC_NO,      KC_NO,                KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,            KC_NO,    KC_NO,      KC_NO,      KC_NO,
        KC_NO,            KC_NO,      KC_NO,                KC_NO,                KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                      KC_NO,    KC_NO,      KC_NO,      KC_NO,
        MO(MOUSE_SCROLL),             KC_MOUSE_SPEED_DOWN,  KC_MOUSE_SPEED_UP,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                      KC_NO,                KC_MS_UP,
        KC_MS_BTN1,       KC_MS_BTN3, KC_MS_BTN2,                                                     KC_MS_BTN1,                             KC_NO,    KC_NO,    KC_MODE_NORMAL,   KC_NO,    KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT),

    [MOUSE_SCROLL] = LAYOUT_ansi_90(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,        _______,        _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,        _______,        _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,        _______,        _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,    _______,        _______,        _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                    KC_MS_WH_UP,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,    KC_MS_WH_LEFT,  KC_MS_WH_DOWN,  KC_MS_WH_RIGHT),

    [CUSTOM_1] = LAYOUT_ansi_90(
        _______,            _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
        _______,            _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                           _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),

    [CUSTOM_2] = LAYOUT_ansi_90(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),

    [SET_KVM_KEY] = LAYOUT_ansi_90(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_SCROLL_LOCK,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,         _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,         _______,  _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,                   _______,
        KC_LCTL,  _______,  _______,                                _______,                                _______,  _______,  _______,  KC_RCTL,         _______,  _______,  _______),

    [QUICK_ACTIONS] = LAYOUT_ansi_90(
        KC_TOGGLE_FKEYS,                      DF(0),               DF(1),         DF(2),               DF(3),                KC_NO,                  KC_NO,                   KC_NO,                KC_NO,                 KC_NO,                KC_NO,          KC_NO,  KC_SCROLL_LOCK,      KC_KVM_MONA_PORT1,  KC_KVM_MONB_PORT1,  KC_KVM_MONC_PORT1,
        KC_TOGGLE_BACKLIGHT, TD(TD_USERNAME), TD(TD_EMAIL),        TD(TD_PHONE),  TD(TD_CREDIT_CARD),  TD(TD_ADDRESS_FULL),  TD(TD_ADDRESS_STREET),  TD(TD_ADDRESS_STREET2),  TD(TD_ADDRESS_CITY),  TD(TD_ADDRESS_STATE),  TD(TD_ADDRESS_ZIP),   KC_NO,          KC_NO,  KC_DEL,              KC_KVM_MONA_PORT2,  KC_KVM_MONB_PORT2,  KC_KVM_MONC_PORT2,
        KC_NO,               BT_HST1,         BT_HST2,             BT_HST3,       P2P4G,               KC_NO,                KC_NO,                  KC_NO,                   KC_NO,                KC_NO,                 KC_NO,                KC_NO,          KC_NO,  KC_NO,               KC_KVM_MONA_PORT3,  KC_KVM_MONB_PORT3,  KC_KVM_MONC_PORT3,
        KC_NO,               KC_NO,           KC_STATMENU,         KC_DOCK,       KC_NO,               KC_NO,                KC_NO,                  KC_NO,                   KC_NO,                KC_NO,                 KC_NO,                KC_NO,                  TD(TD_NAME),         KC_KVM_MONA_PORT4,  KC_KVM_MONB_PORT4,  KC_KVM_MONC_PORT4,
        KC_NO,                                KC_NO,               KC_NO,         KC_NO,               KC_NO,                BAT_LVL,                KC_NO,                   KC_MENU,              KC_NO,                 KC_NO,                KC_NO,                  TG(NUMPAD),                              KC_NO,
        KC_TOGGLE_MOD_SWAP,  KC_NO,           KC_TOGGLE_MOD_SWAP,                                                            TD(TD_PASSWORD),                                                                              _______,              KC_BOOTLOADER,  KC_NO,  KC_TOGGLE_MOD_SWAP,  KC_NO,              KC_NO,              KC_NO)
};
// clang-format on

// Tap Dance state tracking
typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
};

// Generic tap dance state determination
int get_tapdance_value(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return DOUBLE_TAP;
        else return DOUBLE_HOLD;
    }
    return 0;
}

// Tapdance Functions
void password_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("mad8448\n");
            break;

        case SINGLE_HOLD:
            SEND_STRING("Mad6275!\n");
            break;

        case DOUBLE_TAP:
            SEND_STRING("Aapl1357911!\n");
            break;
    }
}

void username_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("MarqueIV");
            break;

        case SINGLE_HOLD:
            SEND_STRING("marqueiv");
            break;

        case DOUBLE_TAP:
            SEND_STRING("mark_donohoe");
            break;
    }
}

void email_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Mark@MarkDonohoe.com");
            break;

        case SINGLE_HOLD:
            SEND_STRING("mark@markdonohoe.com");
            break;

        case DOUBLE_TAP:
            SEND_STRING("MarqueIV@Gmail.com");
            break;
        
        case DOUBLE_HOLD:
            SEND_STRING("Mark.Donohoe@Apple.com");
            break;
    }
}

void phone_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("(973) 420-6275");
            break;

        case SINGLE_HOLD:
            SEND_STRING("9734206275");
            break;
            
        case DOUBLE_TAP:
            SEND_STRING("(234) 248-6275");
            break;

        case DOUBLE_HOLD:
            SEND_STRING("2342486275");
            break;
    }
}

void credit_card_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("6011-2089-0897-4937");
            break;

        case SINGLE_HOLD:
            SEND_STRING("6011208908974937");
            break;
    }
}

void address_full_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("42-12 28th Street\nUnit 8C\nLong Island City, NY 11101\n");
            break;

        case SINGLE_HOLD:
            SEND_STRING("42-12 28th Street Unit 8C, Long Island City, NY 11101");
            break;
        
        case DOUBLE_TAP:
            SEND_STRING("Mark A. Donohoe\n42-12 28th Street\nUnit 8C\nLong Island City, NY 11101-5391\nMark@MarkDonohoe.com\n(973) 420-6275\n");
            break;

        case DOUBLE_HOLD:
            SEND_STRING("Mark A. Donohoe\n42-12 28th Street\nUnit 8C\nLong Island City, NY 11101-5391\nMark@MarkDonohoe.com\nMarqueIV@Gmail.com\n(973) 420-6275 - Cell\n(234) 248-6275 - Google Voice\n");
            break;
    }
}

void address_street_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("42-12 28th Street");
            break;

        case SINGLE_HOLD:
            SEND_STRING("42-12 28th Street Unit 8C");
            break;
    }
}

void address_street2_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Unit 8C");
            break;
    }
}

void address_city_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Long Island City");
            break;

        case SINGLE_HOLD:
            SEND_STRING("Long Island City, NY 11101");
            break;
    }
}

void address_state_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("NY");
            break;

        case SINGLE_HOLD:
            SEND_STRING("New York");
            break;
    }
}

void address_zip_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("11101");
            break;

        case SINGLE_HOLD:
            SEND_STRING("11101-5391");
            break;
    }
}

void name_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Mark A. Donohoe");
            break;

        case SINGLE_HOLD:
            SEND_STRING("Mark Andrew Donohoe");
            break;
    }
}

void kvm_tapdance(tap_dance_state_t *state, void *user_data) {

    keycode_t kvmKeycode = (keycode_t)(uintptr_t)user_data;

    switch (get_tapdance_value(state)) {

        case SINGLE_HOLD:
            layer_on(SET_KVM_KEY);
            break;

        case DOUBLE_TAP:
            set_kvm(kvmKeycode);
            break;
    }
}

void kvm_tapdance_release(tap_dance_state_t *state, void *user_data) {
    layer_off(SET_KVM_KEY);
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_USERNAME]        = ACTION_TAP_DANCE_FN(username_tapdance),
    [TD_PASSWORD]        = ACTION_TAP_DANCE_FN(password_tapdance),
    [TD_EMAIL]           = ACTION_TAP_DANCE_FN(email_tapdance),
    [TD_PHONE]           = ACTION_TAP_DANCE_FN(phone_tapdance),
    [TD_CREDIT_CARD]     = ACTION_TAP_DANCE_FN(credit_card_tapdance),
    [TD_ADDRESS_FULL]    = ACTION_TAP_DANCE_FN(address_full_tapdance),
    [TD_ADDRESS_STREET]  = ACTION_TAP_DANCE_FN(address_street_tapdance),
    [TD_ADDRESS_STREET2] = ACTION_TAP_DANCE_FN(address_street2_tapdance),
    [TD_ADDRESS_CITY]    = ACTION_TAP_DANCE_FN(address_city_tapdance),
    [TD_ADDRESS_STATE]   = ACTION_TAP_DANCE_FN(address_state_tapdance),
    [TD_ADDRESS_ZIP]     = ACTION_TAP_DANCE_FN(address_zip_tapdance),
    [TD_NAME]            = ACTION_TAP_DANCE_FN(name_tapdance),

    [TD_KVM_PORT1]       = ACTION_TAP_DANCE_FN_USER_EX(kvm_tapdance, kvm_tapdance_release, KC_KVM_PORT1),
    [TD_KVM_PORT2]       = ACTION_TAP_DANCE_FN_USER_EX(kvm_tapdance, kvm_tapdance_release, KC_KVM_PORT2),
    [TD_KVM_PORT3]       = ACTION_TAP_DANCE_FN_USER_EX(kvm_tapdance, kvm_tapdance_release, KC_KVM_PORT3),
    [TD_KVM_PORT4]       = ACTION_TAP_DANCE_FN_USER_EX(kvm_tapdance, kvm_tapdance_release, KC_KVM_PORT4),
};

// Mouse speed mode tracking
static enum mouse_speed_mode mouse_speed_mode = SPEED_NORMAL;

// Mouse activity bitmask
// Bits 0-3: mouse movement (left, up, right, down)
// Bits 4-7: mouse scroll (left, up, right, down)
static uint16_t mouse_activity = 0;

#define MOUSE_MOVE_LEFT   (1 << 0)
#define MOUSE_MOVE_UP     (1 << 1)
#define MOUSE_MOVE_RIGHT  (1 << 2)
#define MOUSE_MOVE_DOWN   (1 << 3)
#define MOUSE_SCROLL_LEFT (1 << 4)
#define MOUSE_SCROLL_UP   (1 << 5)
#define MOUSE_SCROLL_RIGHT (1 << 6)
#define MOUSE_SCROLL_DOWN (1 << 7)

// Mouse key tap/hold state
static bool     mouse_key_pressed = false;
static uint16_t mouse_key_timer   = 0;
static uint16_t mouse_inactivity_timer = 0;

// Bootloader hold timer
static uint16_t bootloader_timer      = 0;
static bool     bootloader_key_pressed = false;

// EEPROM storage for MOD_SWAP state, backlight state, and fkeys state
typedef union {
    uint32_t raw;
    struct {
        bool mod_swap_enabled :1;
        bool backlight_off    :1;
        bool fkeys_enabled    :1;
    };
} user_config_t;

user_config_t user_config;

void apply_mouse_speed(enum mouse_speed_mode speed) {

    switch (speed) {

        case SPEED_SLOWEST:
            mk_max_speed = 2;
            mk_time_to_max = 8;
            mk_wheel_max_speed = 1;
            mk_wheel_time_to_max = 1;
            break;

        case SPEED_SLOWER:
            mk_max_speed = 12;
            mk_time_to_max = 12;
            mk_wheel_max_speed = 2;
            mk_wheel_time_to_max = 2;
            break;

        case SPEED_NORMAL:
            mk_max_speed = 36;
            mk_time_to_max = 16;
            mk_wheel_max_speed = 4;
            mk_wheel_time_to_max = 4;
            break;

        case SPEED_FASTER:
            mk_max_speed = 80;
            mk_time_to_max = 16;
            mk_wheel_max_speed = 12;
            mk_wheel_time_to_max = 8;
            break;

        case SPEED_FASTEST:
            mk_max_speed = 127;
            mk_time_to_max = 16;
            mk_wheel_max_speed = 36;
            mk_wheel_time_to_max = 8;
            break;
    }
}

void keyboard_post_init_user(void) {

    // Read user config from EEPROM
    user_config.raw = eeconfig_read_user();

    if (user_config.mod_swap_enabled) layer_on(MOD_SWAP);
    if (user_config.fkeys_enabled)    layer_on(FKEYS);

    // Initialize mouse speed to normal
    apply_mouse_speed(SPEED_NORMAL);
}

layer_state_t layer_state_set_user(layer_state_t state) {

    if (layer_state_cmp(state, MOUSE))
        mouse_inactivity_timer = timer_read();

    return state;
}

void matrix_scan_user(void) {

    if (bootloader_key_pressed && timer_elapsed(bootloader_timer) >= 600) {
        reset_keyboard();
    }

    // Keep mouse layer on while toggle key is held
    if (mouse_key_pressed)
        layer_on(MOUSE);

    if (mouse_activity)
        mouse_inactivity_timer = timer_read();

    // Auto-disable mouse layer after 2.5s inactivity
    if (layer_state_is(MOUSE)
        && !mouse_key_pressed
        && mouse_inactivity_timer > 0
        && timer_elapsed(mouse_inactivity_timer) >= 2500
        && mouse_activity == 0) {

        layer_off(MOUSE);
        mouse_inactivity_timer = 0;
    }
}

bool rgb_color_layer_keys(uint8_t layer, uint8_t red, uint8_t green, uint8_t blue) {

    // Check if the layer is active or the default layer
    layer_state_t layerMask = ((layer_state_t)1 << layer);
    bool is_active = (layer == 0) || ((layer_state | default_layer_state) & layerMask) == layerMask;
    if(!is_active) return false;

    // Then light up only the mapped keys
    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {

        uint8_t led_index = g_led_config.matrix_co[row][col];
        if(led_index == NO_LED)
            continue;

        keycode_t keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});

        switch (keycode) {

            case KC_TRNS:
                continue;
            
            case KC_NO: 
                rgb_matrix_set_color(led_index, RGB_BLACK);
                break;

            default:
                rgb_matrix_set_color(led_index, red, green, blue);
                break;
        }
    }

    return true;
}

bool rgb_matrix_indicators_user(void) {

    rgb_matrix_set_color_all(RGB_BLACK);

    if(layer_state_is(SET_KVM_KEY)) {
        rgb_color_layer_keys(SET_KVM_KEY, RGB_WHITE);
        return true;
    }

    rgb_color_layer_keys(DEFAULT,        RGB_WHITE  );
    rgb_color_layer_keys(HOME_ROW_MODS,  RGB_WHITE  );
    rgb_color_layer_keys(LAYOUT_60,      RGB_WHITE  );
    rgb_color_layer_keys(LAYOUT_40,      RGB_WHITE  );

    // If backlight is off, set all keys to black first
    if (user_config.backlight_off)
        rgb_matrix_set_color_all(RGB_BLACK);

    // Caps Lock indicator - set caps lock key to red when active (overrides backlight off)
    if (host_keyboard_led_state().caps_lock) {
        // Caps Lock is at matrix position [3, 0]
        ledindex_t led_index = g_led_config.matrix_co[3][0];
        if (led_index != NO_LED)
            rgb_matrix_set_color(led_index, RGB_RED);
    }

    rgb_color_layer_keys(NUM_ROW_OVERLAY, RGB_BLUE   );
    rgb_color_layer_keys(MOD_SWAP,        RGB_BLUE   );
    rgb_color_layer_keys(ZOOM,            RGB_BLUE   );
    rgb_color_layer_keys(NUMPAD,          RGB_YELLOW );    
    rgb_color_layer_keys(FKEYS,           RGB_BLUE   );
    rgb_color_layer_keys(NAVIGATION,      RGB_GREEN  );
    rgb_color_layer_keys(MOUSE,           RGB_GREEN  );    
    rgb_color_layer_keys(MOUSE_SCROLL,    RGB_YELLOW );
    rgb_color_layer_keys(CUSTOM_1,        RGB_YELLOW );    
    rgb_color_layer_keys(CUSTOM_2,        RGB_YELLOW );            
    rgb_color_layer_keys(QUICK_ACTIONS,   RGB_CYAN   );

    // MOUSE layer additions
    if (layer_state_is(MOUSE)) {

        // Show current speed on number keys 1-5 (row 1, columns 1-5)
        // Keys: 1=SLOWEST, 2=SLOWER, 3=NORMAL, 4=FASTER, 5=FASTEST
        uint8_t speed_key_col = 0;
        switch (mouse_speed_mode) {
            case SPEED_SLOWEST: speed_key_col = 1; break;
            case SPEED_SLOWER:  speed_key_col = 2; break;
            case SPEED_NORMAL:  speed_key_col = 3; break;
            case SPEED_FASTER:  speed_key_col = 4; break;
            case SPEED_FASTEST: speed_key_col = 5; break;
        }

        ledindex_t speed_led = g_led_config.matrix_co[1][speed_key_col];
        if (speed_led != NO_LED) {
            // Green if any mouse activity, yellow if idle
            if (mouse_activity)
                rgb_matrix_set_color(speed_led, RGB_YELLOW);
            else
                rgb_matrix_set_color(speed_led, RGB_RED);
        }
    }
    
    if (layer_state_is(QUICK_ACTIONS)) {
        // Highlight the default layer in red
        uint8_t default_layer = get_highest_layer(default_layer_state);
        ledindex_t default_layer_led = g_led_config.matrix_co[0][default_layer + 2];
        rgb_matrix_set_color(default_layer_led, RGB_RED);
    }

    return true;
}

void set_kvm(keycode_t keycode) {
    
    uint16_t delay = 50;
    keycode_t KC_KVM_ACTION = KC_LEFT_CTRL;

    // KVM Trigger
    tap_code_delay(KC_KVM_ACTION, delay);
    wait_ms(delay);
    tap_code_delay(KC_KVM_ACTION, delay);
    wait_ms(delay);

    // Monitor-specific, if appropriate
    switch(keycode) {
        
        case KC_KVM_MONA_PORT1:
        case KC_KVM_MONA_PORT2:
        case KC_KVM_MONA_PORT3:
        case KC_KVM_MONA_PORT4: tap_code_delay(KC_LEFT, delay); break;
        
        case KC_KVM_MONB_PORT1:
        case KC_KVM_MONB_PORT2:
        case KC_KVM_MONB_PORT3:
        case KC_KVM_MONB_PORT4: tap_code_delay(KC_DOWN, delay); break;
        
        case KC_KVM_MONC_PORT1:
        case KC_KVM_MONC_PORT2:
        case KC_KVM_MONC_PORT3:
        case KC_KVM_MONC_PORT4: tap_code_delay(KC_RIGHT, delay); break;
    }

    // Port-specific
    switch(keycode) {
        
        case KC_KVM_PORT1:
        case KC_KVM_MONA_PORT1:
        case KC_KVM_MONB_PORT1:
        case KC_KVM_MONC_PORT1: tap_code_delay(KC_1, delay); break;
        
        case KC_KVM_PORT2:
        case KC_KVM_MONA_PORT2:
        case KC_KVM_MONB_PORT2:
        case KC_KVM_MONC_PORT2: tap_code_delay(KC_2, delay); break;
    
        case KC_KVM_PORT3:
        case KC_KVM_MONA_PORT3:
        case KC_KVM_MONB_PORT3:
        case KC_KVM_MONC_PORT3: tap_code_delay(KC_3, delay); break;

        case KC_KVM_PORT4:
        case KC_KVM_MONA_PORT4:
        case KC_KVM_MONB_PORT4:
        case KC_KVM_MONC_PORT4: tap_code_delay(KC_4, delay); break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {

        // Cancel tap detection if typing on held mouse layer
        if (mouse_key_pressed && layer_state_is(MOUSE))
            mouse_key_timer = 0;

        // Reset inactivity timer on any key press while mouse layer is active
        if (layer_state_is(MOUSE))
            mouse_inactivity_timer = timer_read();
    }

    switch (keycode) {

        case KC_LCMD:

            if (record->event.pressed)
                layer_on(ZOOM);
            else
                layer_off(ZOOM);
            break;

        case KC_TOGGLE_MOUSE:

            if (record->event.pressed) {
                mouse_key_pressed = true;
                mouse_key_timer = timer_read();
                // Toggle mouse layer immediately on key down
                layer_invert(MOUSE);

            } else {
                mouse_key_pressed = false;
                // If held past tapping term, undo the toggle (momentary behavior)
                if (timer_elapsed(mouse_key_timer) >= TAPPING_TERM)
                    layer_off(MOUSE);
            }

            return false;

        case KC_MODE_NORMAL:

            if (record->event.pressed) {
                layer_off(MOUSE);
                layer_off(NUMPAD);
                mouse_inactivity_timer = 0;
            }

            return false;

        case KC_DISABLE_MOD_SWAP:

            if (record->event.pressed) {
                layer_off(MOD_SWAP);
                user_config.mod_swap_enabled = false;
                eeconfig_update_user(user_config.raw);
            }

            return false;

        case KC_ENABLE_MOD_SWAP:

            if (record->event.pressed) {
                layer_on(MOD_SWAP);
                user_config.mod_swap_enabled = true;
                eeconfig_update_user(user_config.raw);
            }

            return false;

        case KC_TOGGLE_MOD_SWAP:

            if (record->event.pressed) {

                if (layer_state_is(MOD_SWAP)) {
                    layer_off(MOD_SWAP);
                    user_config.mod_swap_enabled = false;
                } else {
                    layer_on(MOD_SWAP);
                    user_config.mod_swap_enabled = true;
                }

                eeconfig_update_user(user_config.raw);
            }
            return false;

        case KC_BOOTLOADER:
            if (record->event.pressed) {
                bootloader_timer = timer_read();
                bootloader_key_pressed = true;
            } else {
                bootloader_key_pressed = false;
                bootloader_timer = 0;
            }
            return false;

        case KC_TOGGLE_BACKLIGHT:

            if (record->event.pressed) {
                user_config.backlight_off = !user_config.backlight_off;
                eeconfig_update_user(user_config.raw);
            }

            return false;

        case KC_TOGGLE_FKEYS:

            if (record->event.pressed) {

                if (layer_state_is(FKEYS)) {
                    layer_off(FKEYS);
                    user_config.fkeys_enabled = false;
                } else {
                    layer_on(FKEYS);
                    user_config.fkeys_enabled = true;
                }
                eeconfig_update_user(user_config.raw);
            }

            return false;

        case KC_MOUSE_SPEED_DOWN:

            if (record->event.pressed) {

                mouse_speed_mode = (mouse_speed_mode == SPEED_NORMAL)
                    ? SPEED_SLOWER
                    : SPEED_FASTEST;

            } else {

                mouse_speed_mode = (mouse_speed_mode == SPEED_SLOWER)
                    ? SPEED_NORMAL
                    : SPEED_FASTER;
            }

            apply_mouse_speed(mouse_speed_mode);

            return false;

        case KC_MOUSE_SPEED_UP:

            if (record->event.pressed) {

                mouse_speed_mode = (mouse_speed_mode == SPEED_NORMAL)
                    ? SPEED_FASTER
                    : SPEED_SLOWEST;

            } else {

                mouse_speed_mode = (mouse_speed_mode == SPEED_FASTER)
                    ? SPEED_NORMAL
                    : SPEED_SLOWER;
            }

            apply_mouse_speed(mouse_speed_mode);

            return false;

        // Track mouse movement keys

        case KC_MS_LEFT:
            if (record->event.pressed) mouse_activity |= MOUSE_MOVE_LEFT;
            else mouse_activity &= ~MOUSE_MOVE_LEFT;
            break;

        case KC_MS_UP:
            if (record->event.pressed) mouse_activity |= MOUSE_MOVE_UP;
            else mouse_activity &= ~MOUSE_MOVE_UP;
            break;

        case KC_MS_RIGHT:
            if (record->event.pressed) mouse_activity |= MOUSE_MOVE_RIGHT;
            else mouse_activity &= ~MOUSE_MOVE_RIGHT;
            break;

        case KC_MS_DOWN:
            if (record->event.pressed) mouse_activity |= MOUSE_MOVE_DOWN;
            else mouse_activity &= ~MOUSE_MOVE_DOWN;
            break;

        // Track mouse scroll keys

        case KC_MS_WH_LEFT:
            if (record->event.pressed) mouse_activity |= MOUSE_SCROLL_LEFT;
            else mouse_activity &= ~MOUSE_SCROLL_LEFT;
            break;

        case KC_MS_WH_UP:
            if (record->event.pressed) mouse_activity |= MOUSE_SCROLL_UP;
            else mouse_activity &= ~MOUSE_SCROLL_UP;
            break;

        case KC_MS_WH_RIGHT:
            if (record->event.pressed) mouse_activity |= MOUSE_SCROLL_RIGHT;
            else mouse_activity &= ~MOUSE_SCROLL_RIGHT;
            break;

        case KC_MS_WH_DOWN:
            if (record->event.pressed) mouse_activity |= MOUSE_SCROLL_DOWN;
            else mouse_activity &= ~MOUSE_SCROLL_DOWN;
            break;

        // KVM Switching
        case KC_KVM_PORT1:
        case KC_KVM_PORT2:
        case KC_KVM_PORT3:
        case KC_KVM_PORT4:
        case KC_KVM_MONA_PORT1:
        case KC_KVM_MONB_PORT1:
        case KC_KVM_MONC_PORT1:
        case KC_KVM_MONA_PORT2:
        case KC_KVM_MONB_PORT2:
        case KC_KVM_MONC_PORT2:
        case KC_KVM_MONA_PORT3:
        case KC_KVM_MONB_PORT3:
        case KC_KVM_MONC_PORT3:
        case KC_KVM_MONA_PORT4:
        case KC_KVM_MONB_PORT4:
        case KC_KVM_MONC_PORT4:
            if (record->event.pressed) set_kvm(keycode);
            return false;

        // HID Consumer Control - Dictation Keys
        case KC_DICT:

            if (record->event.pressed) {
                host_consumer_send(0x0CF);  // HUTRR99 Voice Command
            } else {
                host_consumer_send(0);       // Clear on release
            }

            return false;

        case KC_DICTATION_SESSION:

            if (record->event.pressed) {
                host_consumer_send(0x0D8);  // Start/Stop Voice Dictation Session
            } else {
                host_consumer_send(0);
            }
            
            return false;
    }

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    return true;
}
