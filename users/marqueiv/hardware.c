#include "hardware.h"

// Override Keychron's default Mac/Win DIP switch mapping (layers 0/2) to use layers 0/1
bool dip_switch_update_user(uint8_t index, bool active) {

    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 1));
    }
    return true;
}
