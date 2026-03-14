#ifndef RGB_H
#define RGB_H

#include "common.h"

bool rgb_color_layer_keys(layer_t layer, uint8_t red, uint8_t green, uint8_t blue);
bool rgb_color_keycode(keycode_t target, uint8_t red, uint8_t green, uint8_t blue);

#endif
