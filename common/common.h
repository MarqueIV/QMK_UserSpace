#ifndef COMMON_H
#define COMMON_H

#include "quantum.h"

typedef uint16_t keycode_t;
typedef uint8_t  layer_t;
typedef uint8_t  ledindex_t;

keycode_t keypos_to_keycode(keypos_t pos);

// Custom Key Code Combos
#define KCC_SSHOT     LCTL(LGUI(LALT(LSFT(KC_C))))
#define KCC_DOCK      LCTL(KC_F3)
#define KCC_MENU      LCTL(KC_F2)
#define KCC_SYSMENU   LCTL(KC_F8)
#define KCC_FSCRN     LCTL(LGUI(KC_F))

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

#endif
