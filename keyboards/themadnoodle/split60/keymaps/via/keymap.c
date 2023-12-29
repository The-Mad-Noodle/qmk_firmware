// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_END,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, XXXXXXX, KC_PGUP,
        KC_LCTL, KC_LGUI, KC_LALT, LT(1, KC_SPC), KC_SPC,  KC_RALT, LT(2, KC_NO), KC_RGUI, KC_RCTL, KC_PGDN
    ),
    [1] = LAYOUT(
        KC_GRV, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_MSTP,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, KC_BSPC, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,
        _______, _______, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD,
        _______, RGB_SAD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAI,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD
    )
};

/*Encoder Mapping*/
//-----------------------(ENC1)
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif