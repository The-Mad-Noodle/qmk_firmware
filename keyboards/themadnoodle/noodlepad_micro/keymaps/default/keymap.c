// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum custom_keycodes {
    // existing keycodes
    RGB_IND = SAFE_RANGE // add this line for the LED toggle
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,--ENC2--       --ENC1--.
     * |   <<  |       |  >>   |
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MAIL  | PC/FN |
     * `-----------------------'
     */

    [0] = LAYOUT(
      KC_MPRV,           KC_MNXT, 
      KC_MSTP, KC_MPLY, KC_MSEL,
      LT(2,RGB_IND), KC_MAIL, LT(1, KC_MYCM)
      ),


    /* LAYER 1
     * ,--ENC2--       --ENC1--.
     * | MODE+ |       | MODE- |  
     * |-------+-------+-------|
     * |Bright-|  Tog  |Bright+|
     * |-------+-------+-------|
     * | PLAIN |BREATH |       |
     * `-----------------------'
     */
    
    [1] = LAYOUT(
      RGB_MOD,          RGB_RMOD, 
      RGB_VAD, RGB_TOG, RGB_VAI, 
      RGB_M_P, RGB_M_B, KC_TRNS
      ),

      
    /* LAYER 2 (ENCODER)
     * ,--ENC2--       --ENC1--.
     * |       |       |       |  
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */
    
    [2] = LAYOUT(
      KC_TRNS,          KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS
    )
};


/*Encoder Mapping*/
//-----------------------(ENC1)---------------------------------(ENC2)-----------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_LEFT, KC_RGHT),      ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),      ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),      ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  }
};
#endif

const rgblight_segment_t PROGMEM layer_zero_all[]  = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_one_all[]   = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_RED});
const rgblight_segment_t PROGMEM layer_two_all[]   = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_GREEN});
const rgblight_segment_t PROGMEM layer_three_all[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_BLUE});
const rgblight_segment_t PROGMEM layer_zero[]      = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_one[]       = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_two[]       = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_three[]     = RGBLIGHT_LAYER_SEGMENTS({3, 1, HSV_WHITE});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_zero_all,  // 0
    layer_one_all,   // 1
    layer_two_all,   // 2
    layer_three_all, // 3
    layer_zero,      // 4
    layer_one,       // 5
    layer_two,       // 6
    layer_three      // 7

);

void keyboard_post_init_user(void) {
    // Enable the LED layers

    rgblight_layers = my_rgb_layers;
}

bool led_mode = false; // false for first LED mode, true for second LED mode

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_IND:
            if (record->event.pressed) {
                // Code to toggle between the two LED modes
                led_mode = !led_mode; // Toggle the mode
            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (led_mode) {
        // Code from the second block for blinking lights

        uint8_t layer = get_highest_layer(state);

        switch (layer) {
            case 0:
                rgblight_blink_layer(0, 1000);
                break;
            case 1:
                rgblight_blink_layer(1, 1000);
                break;
            case 2:
                rgblight_blink_layer(2, 1000);
                break;
            case 3:
                rgblight_blink_layer(3, 1000);
                break;

            default:
                rgblight_blink_layer(0, 1000);
        }
    } else {
        // Code from the first block for static lights

        rgblight_set_layer_state(4, layer_state_cmp(state, 0));

        rgblight_set_layer_state(5, layer_state_cmp(state, 1));

        rgblight_set_layer_state(6, layer_state_cmp(state, 2));

        rgblight_set_layer_state(7, layer_state_cmp(state, 3));
    }
    return state;
}
