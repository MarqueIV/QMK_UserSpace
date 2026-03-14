#include "hardware.h"

bool dip_switch_update_user(uint8_t index, bool active) {

    // Mac/Win Toggle - Active = true is mac side, false is win side
    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 1));
    }

    return true;
}
