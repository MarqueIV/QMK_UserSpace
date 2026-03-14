#include "rgb.h"

bool rgb_color_layer_keys(layer_t layer, uint8_t red, uint8_t green, uint8_t blue) {

    // Check if the layer is active or the default layer
    layer_state_t layerMask = ((layer_state_t)1 << layer);
    bool is_active = (layer == 0) || ((layer_state | default_layer_state) & layerMask) == layerMask;
    if(!is_active) return false;

    // Then light up only the mapped keys
    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {

        ledindex_t led_index = g_led_config.matrix_co[row][col];
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

bool rgb_color_keycode(keycode_t target, uint8_t red, uint8_t green, uint8_t blue) {

    bool found = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {

        keypos_t pos = {col, row};
        layer_t layer = layer_switch_get_layer(pos);
        keycode_t keycode = keymap_key_to_keycode(layer, pos);

        // Check both the full keycode and the tap keycode for layer-tap keys (e.g. LT(layer, KC_CAPS))
        bool match = (keycode == target);
        if (!match && IS_QK_LAYER_TAP(keycode))
            match = (QK_LAYER_TAP_GET_TAP_KEYCODE(keycode) == target);
        if (!match && IS_QK_MOD_TAP(keycode))
            match = (QK_MOD_TAP_GET_TAP_KEYCODE(keycode) == target);
        if (!match)
            continue;

        ledindex_t led_index = g_led_config.matrix_co[row][col];
        if (led_index == NO_LED)
            continue;

        rgb_matrix_set_color(led_index, red, green, blue);
        found = true;
    }

    return found;
}
