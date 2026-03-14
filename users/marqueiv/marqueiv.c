#include "marqueiv.h"

keycode_t keypos_to_keycode(keypos_t keyPos) {

    layer_t layerRespondingForKeyPos = layer_switch_get_layer(keyPos);
    return keymap_key_to_keycode(layerRespondingForKeyPos, keyPos);    
}