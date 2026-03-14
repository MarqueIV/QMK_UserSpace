#include "kvm.h"

keycode_t KC_KVM_ACTION_KEY = KC_LEFT_CTRL;

void set_kvm(keycode_t keycode) {

    uint16_t delay = 50;

    // KVM Trigger
    tap_code_delay(KC_KVM_ACTION_KEY, delay);
    wait_ms(delay);
    tap_code_delay(KC_KVM_ACTION_KEY, delay);
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
