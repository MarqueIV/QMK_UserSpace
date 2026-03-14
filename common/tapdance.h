#ifndef TAPDANCE_H
#define TAPDANCE_H

#include "common.h"

// Tap dance state values
enum {

    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
};

// Tap dance state tracking
typedef struct {

    bool is_press_action;
    int state;
} tap;

// Utility
int get_tapdance_value(tap_dance_state_t *state);

// Personal data tap dance functions
void password_tapdance(tap_dance_state_t *state, void *user_data);
void username_tapdance(tap_dance_state_t *state, void *user_data);
void email_tapdance(tap_dance_state_t *state, void *user_data);
void phone_tapdance(tap_dance_state_t *state, void *user_data);
void credit_card_tapdance(tap_dance_state_t *state, void *user_data);
void address_full_tapdance(tap_dance_state_t *state, void *user_data);
void address_street_tapdance(tap_dance_state_t *state, void *user_data);
void address_street2_tapdance(tap_dance_state_t *state, void *user_data);
void address_city_tapdance(tap_dance_state_t *state, void *user_data);
void address_state_tapdance(tap_dance_state_t *state, void *user_data);
void address_zip_tapdance(tap_dance_state_t *state, void *user_data);
void name_tapdance(tap_dance_state_t *state, void *user_data);

#endif
