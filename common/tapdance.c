#include "tapdance.h"

// Generic tap dance state determination
int get_tapdance_value(tap_dance_state_t *state) {

    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return DOUBLE_TAP;
        else return DOUBLE_HOLD;
    }
    return 0;
}

// Tapdance Functions
void password_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("mad8448\n");
            break;

        case SINGLE_HOLD:
            SEND_STRING("Mad6275!\n");
            break;

        case DOUBLE_TAP:
            SEND_STRING("Aapl1357911!\n");
            break;
    }
}

void username_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("MarqueIV");
            break;

        case SINGLE_HOLD:
            SEND_STRING("marqueiv");
            break;

        case DOUBLE_TAP:
            SEND_STRING("mark_donohoe");
            break;
    }
}

void email_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Mark@MarkDonohoe.com");
            break;

        case SINGLE_HOLD:
            SEND_STRING("mark@markdonohoe.com");
            break;

        case DOUBLE_TAP:
            SEND_STRING("MarqueIV@Gmail.com");
            break;

        case DOUBLE_HOLD:
            SEND_STRING("Mark.Donohoe@Apple.com");
            break;
    }
}

void phone_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("(973) 420-6275");
            break;

        case SINGLE_HOLD:
            SEND_STRING("9734206275");
            break;

        case DOUBLE_TAP:
            SEND_STRING("(234) 248-6275");
            break;

        case DOUBLE_HOLD:
            SEND_STRING("2342486275");
            break;
    }
}

void credit_card_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("6011-2089-0897-4937");
            break;

        case SINGLE_HOLD:
            SEND_STRING("6011208908974937");
            break;
    }
}

void address_full_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("42-12 28th Street\nUnit 8C\nLong Island City, NY 11101\n");
            break;

        case SINGLE_HOLD:
            SEND_STRING("42-12 28th Street Unit 8C, Long Island City, NY 11101");
            break;

        case DOUBLE_TAP:
            SEND_STRING("Mark A. Donohoe\n42-12 28th Street\nUnit 8C\nLong Island City, NY 11101-5391\nMark@MarkDonohoe.com\n(973) 420-6275\n");
            break;

        case DOUBLE_HOLD:
            SEND_STRING("Mark A. Donohoe\n42-12 28th Street\nUnit 8C\nLong Island City, NY 11101-5391\nMark@MarkDonohoe.com\nMarqueIV@Gmail.com\n(973) 420-6275 - Cell\n(234) 248-6275 - Google Voice\n");
            break;
    }
}

void address_street_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("42-12 28th Street");
            break;

        case SINGLE_HOLD:
            SEND_STRING("42-12 28th Street Unit 8C");
            break;
    }
}

void address_street2_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Unit 8C");
            break;
    }
}

void address_city_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Long Island City");
            break;

        case SINGLE_HOLD:
            SEND_STRING("Long Island City, NY 11101");
            break;
    }
}

void address_state_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("NY");
            break;

        case SINGLE_HOLD:
            SEND_STRING("New York");
            break;
    }
}

void address_zip_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("11101");
            break;

        case SINGLE_HOLD:
            SEND_STRING("11101-5391");
            break;
    }
}

void name_tapdance(tap_dance_state_t *state, void *user_data) {

    switch (get_tapdance_value(state)) {

        case SINGLE_TAP:
            SEND_STRING("Mark A. Donohoe");
            break;

        case SINGLE_HOLD:
            SEND_STRING("Mark Andrew Donohoe");
            break;
    }
}
