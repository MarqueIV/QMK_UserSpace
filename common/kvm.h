#ifndef KVM_H
#define KVM_H

#include "common.h"

// Constants

enum {
    KC_KVM_PORT1 = SAFE_RANGE + 400,
    KC_KVM_PORT2,
    KC_KVM_PORT3,
    KC_KVM_PORT4,

    KC_KVM_MONA_PORT1 = SAFE_RANGE + 410,
    KC_KVM_MONA_PORT2,
    KC_KVM_MONA_PORT3,
    KC_KVM_MONA_PORT4,

    KC_KVM_MONB_PORT1 = SAFE_RANGE + 420,
    KC_KVM_MONB_PORT2,
    KC_KVM_MONB_PORT3,
    KC_KVM_MONB_PORT4,

    KC_KVM_MONC_PORT1 = SAFE_RANGE + 430,
    KC_KVM_MONC_PORT2,
    KC_KVM_MONC_PORT3,
    KC_KVM_MONC_PORT4,
};

// Variables

extern keycode_t KC_KVM_ACTION_KEY;

// Functions

void set_kvm(keycode_t keycode);

#endif
