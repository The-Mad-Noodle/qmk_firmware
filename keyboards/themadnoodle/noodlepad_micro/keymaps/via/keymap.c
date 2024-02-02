// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    L_IND = QK_KB_0, // Toggle the Layer Indicators Modes
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,--ENC2--       --ENC1--.
     * |   <<  |       |  >>   |  
     * |-------+-------+-------|
     * |  STOP |  PLAY | MEDIA |
     * |-------+-------+-------|
     * | CALC  | MY PC | TO(3) |
     * `-----------------------'
     */

    [0] = LAYOUT(
      KC_MPRV,           KC_MNXT, 
      KC_MSTP, KC_MPLY, KC_MSEL,
      KC_CALC, KC_MYCM, TO(3)
      ),


    /* LAYER 1
     * ,--ENC2--       --ENC1--.
     * | MODE+ |       | MODE- |  
     * |-------+-------+-------|
     * |Bright-|  Tog  |Bright+|
     * |-------+-------+-------|
     * | PLAIN |BREATH | TO(0) |
     * `-----------------------'
     */
    
    [1] = LAYOUT(
      RGB_MOD,          RGB_RMOD, 
      RGB_VAD, RGB_TOG, RGB_VAI, 
      RGB_M_P, RGB_M_B, TO(0)
      ),

      
    /* LAYER 2 
     * ,--ENC2--       --ENC1--.
     * |       |       |       |  
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       | TO(0) |
     * `-----------------------'
     */
    
    [2] = LAYOUT(
      KC_TRNS,          KC_TRNS, 
      KC_TRNS, KC_TRNS, KC_TRNS, 
      KC_TRNS, KC_TRNS, TO(0)
      ),

    /* LAYER 3 
     * ,--ENC2--       --ENC1--.
     * |       |       |       |  
     * |-------+-------+-------|
     * | TO(1) |       | TO(2) |
     * |-------+-------+-------|
     * |       |       | TO(0) |
     * `-----------------------'
     */
    
    [3] = LAYOUT(
      KC_TRNS,         KC_TRNS, 
      TO(1), KC_TRNS, TO(2), 
      KC_TRNS, KC_TRNS, TO(0)
      )
    
};


/*Encoder Mapping*/
//-----------------------(ENC1)---------------------------------(ENC2)-----------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_LEFT, KC_RGHT),      ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),      ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),      ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [3] =  { ENCODER_CCW_CW(KC_LEFT, KC_RGHT),      ENCODER_CCW_CW(KC_DOWN, KC_UP)    },

};
#endif

//  ======================Layer Light Setup==========================

const rgblight_segment_t PROGMEM layer_zero_all[]  = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_one_all[]   = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_RED});
const rgblight_segment_t PROGMEM layer_two_all[]   = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_GREEN});
const rgblight_segment_t PROGMEM layer_three_all[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_BLUE});

const rgblight_segment_t PROGMEM layer_zero[]  = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_one[]   = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_two[]   = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM layer_three[] = RGBLIGHT_LAYER_SEGMENTS({3, 1, HSV_WHITE});

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


//  ======================Custom Keycodes==========================

bool led_mode; // false for Blinking Mode, true for Static mode

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case L_IND:
            if (record->event.pressed) {
                // Code to toggle between the two Layer Indicators
                led_mode = !led_mode; // Toggle the mode

                // Updateing lighting layer when key is pressed
                if (led_mode) {
                    if (layer_state_is(0)) {
                        rgblight_set_layer_state(4, true);
                    }
                    if (layer_state_is(1)) {
                        rgblight_set_layer_state(5, true);
                    }
                    if (layer_state_is(2)) {
                        rgblight_set_layer_state(6, true);
                    }
                    if (layer_state_is(3)) {
                        rgblight_set_layer_state(7, true);
                    }
                } else {
                    rgblight_set_layer_state(4, false);
                    rgblight_set_layer_state(5, false);
                    rgblight_set_layer_state(6, false);
                    rgblight_set_layer_state(7, false);

                    if (layer_state_is(0)) {
                        rgblight_blink_layer(0, 1000);
                    }
                    if (layer_state_is(1)) {
                        rgblight_blink_layer(1, 1000);
                    }
                    if (layer_state_is(2)) {
                        rgblight_blink_layer(2, 1000);
                    }
                    if (layer_state_is(3)) {
                        rgblight_blink_layer(3, 1000);
                    }
                }
            } else {

            }
            return false; // Skip all further processing of this key
        default:
            return true; // Process all other keycodes normally
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    
    if (led_mode) {
        // Code for Static Layer Indicators 

        rgblight_set_layer_state(4, layer_state_cmp(state, 0));
        rgblight_set_layer_state(5, layer_state_cmp(state, 1));
        rgblight_set_layer_state(6, layer_state_cmp(state, 2));
        rgblight_set_layer_state(7, layer_state_cmp(state, 3));
        

    } else {
        // Code for Blinking Layer Indicators
        
         uint8_t layer = get_highest_layer(state);

        switch (layer) {
            case 0:
                rgblight_blink_layer(0, 500);
                break;
            case 1:
                rgblight_blink_layer(1, 500);
                break;
            case 2:
                rgblight_blink_layer(2, 500);
                break;
            case 3:
                rgblight_blink_layer(3, 500);
                break;

            default:
                rgblight_blink_layer(0, 500); 
        }

  
            
            }        
    return state;

}
