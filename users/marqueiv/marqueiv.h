#ifndef MARQUEIV_H
#define MARQUEIV_H

#include "quantum.h"

typedef uint16_t keycode_t;
typedef uint8_t  ledindex_t;
typedef uint8_t  layer_t;

keycode_t keypos_to_keycode(keypos_t pos);

#endif