#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _RGB,
    _FN,
    _LAYSEL
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    [_BASE] = LAYOUT_ortho_3x4(
  		LT(_FN, KC_E), 
		KC_1, KC_2, KC_3, KC_4, 
		KC_5, KC_6, KC_7, KC_8, 
		KC_9, KC_0, KC_Q, LT(_RGB, KC_W)
        ),
    
    [_RGB] = LAYOUT_ortho_3x4(
		RGB_TOG, 
		RGB_MOD, KC_TRNS, KC_TRNS, RGB_RMOD, 
		RGB_SPI, KC_TRNS, KC_TRNS, RGB_SPD, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        ),
  
    [_FN] = LAYOUT_ortho_3x4(
		KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        ),

    [_LAYSEL] = LAYOUT_ortho_3x4(
		KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
        ),


};

bool encoder_update_user(uint8_t index, bool clockwise) {
    
  switch (get_highest_layer(layer_state)) {
      case 1:
          if (clockwise) {
              rgblight_increase_hue();
          } else {
              rgblight_decrease_hue();
          }
          break;
      case 2:
          if (clockwise) {
              tap_code(KC_RGHT);
          } else {
              tap_code(KC_LEFT);
          }
          break;
      case 3:
          if (clockwise) {
              tap_code(KC_RGHT);
          } else {
              tap_code(KC_LEFT);
          }
          break;

      default:
          if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
          break;
          
  }
    return false;

}



#ifdef OLED_ENABLE
/*

//---Murphpad Stuff--------------------------------------------------------------------------------------------

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 270 degrees
}


	static void render_logo(void) {     // Render MechWild "MW" Logo
		static const char PROGMEM logo_1[] = {0x8A, 0x8B, 0x8C, 0x8D, 0x00};
		static const char PROGMEM logo_2[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x00};
		static const char PROGMEM logo_3[] = {0xCA, 0xCB, 0xCC, 0xCD, 0x00};
		static const char PROGMEM logo_4[] = {0x20, 0x8E, 0x8F, 0x90, 0x00};
		oled_set_cursor(0,0);
		oled_write_P(logo_1, false);
		oled_set_cursor(0,1);
		oled_write_P(logo_2, false);
		oled_set_cursor(0,2);
		oled_write_P(logo_3, false);
		oled_set_cursor(0,3);
		oled_write_P(logo_4, false);
	}

	void oled_task_user(void) {
		//render_logo();
		oled_set_cursor(0,1);

		oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _RGB:
            oled_write_ln_P(PSTR("RGB"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("FN"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
	oled_write_ln_P(PSTR(""), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	}

*/
//------------------------------------------------------------------------------------------------

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;  // flips the display 180 degrees if offhand
}
 

/* 
//------Test Logo
static void render_logo(void) {
  static const char PROGMEM my_logo[] = {
0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x04, 0x06, 0x82, 0xc3, 0x43, 0x61, 0xa1, 0xa1, 
0xa1, 0xa1, 0x61, 0x43, 0xc3, 0x82, 0x06, 0x04, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 
0xf8, 0x1e, 0xc3, 0xf8, 0x5c, 0x76, 0x7b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x6d, 0x7b, 0x76, 0x5e, 
0x7e, 0x77, 0x5b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x4d, 0x7b, 0x66, 0x5c, 0xf0, 0xc3, 0x3e, 0xf0, 
0x1f, 0x78, 0xc1, 0x0f, 0x38, 0xe0, 0xc0, 0x00, 0x00, 0x02, 0x0e, 0x0e, 0x8e, 0xc6, 0xc0, 0x40, 
0x40, 0xc0, 0xc6, 0x8e, 0x0e, 0x0e, 0x02, 0x00, 0x80, 0xc0, 0x60, 0x38, 0x0f, 0xc0, 0x7c, 0x0f, 
0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x31, 0x23, 0x66, 0x44, 0x44, 0xc4, 0xc4, 0x84, 0x84, 
0x84, 0x84, 0xc4, 0xc4, 0x44, 0x46, 0x66, 0x23, 0x11, 0x18, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00
  };

  oled_write_raw_P(my_logo, sizeof(my_logo));
}
//-----------



//------Test Logo
static void render_logo(void) {
    static const char PROGMEM my_logo[] = {
0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x04, 0x06, 0x82, 0xc3, 0x43, 0x61, 0xa1, 0xa1, 
0xa1, 0xa1, 0x61, 0x43, 0xc3, 0x82, 0x06, 0x04, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 
0xf8, 0x1e, 0xc3, 0xf8, 0x5c, 0x76, 0x7b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x6d, 0x7b, 0x76, 0x5e, 
0x7e, 0x77, 0x5b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x4d, 0x7b, 0x66, 0x5c, 0xf0, 0xc3, 0x3e, 0xf0, 
0x1f, 0x78, 0xc1, 0x0f, 0x38, 0xe0, 0xc0, 0x00, 0x00, 0x02, 0x0e, 0x0e, 0x8e, 0xc6, 0xc0, 0x40, 
0x40, 0xc0, 0xc6, 0x8e, 0x0e, 0x0e, 0x02, 0x00, 0x80, 0xc0, 0x60, 0x38, 0x0f, 0xc0, 0x7c, 0x0f, 
0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x31, 0x23, 0x66, 0x44, 0x44, 0xc4, 0xc4, 0x84, 0x84, 
0x84, 0x84, 0xc4, 0xc4, 0x44, 0x46, 0x66, 0x23, 0x11, 0x18, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00
    };

   oled_write_raw_P(my_logo, sizeof(my_logo));;
}
*/



static void render_logo(void) {     // Render MechWild "MW" Logo
    static const char PROGMEM logo_1[] = {0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x04, 0x06, 0x82, 0xc3, 0x43, 0x61, 0xa1, 0xa1,0xa1, 0xa1, 0x61, 0x43, 0xc3, 0x82, 0x06, 0x04, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00};
    static const char PROGMEM logo_2[] = {0xf8, 0x1e, 0xc3, 0xf8, 0x5c, 0x76, 0x7b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x6d, 0x7b, 0x76, 0x5e,0x7e, 0x77, 0x5b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x4d, 0x7b, 0x66, 0x5c, 0xf0, 0xc3, 0x3e, 0xf0};
    static const char PROGMEM logo_3[] = {0x1f, 0x78, 0xc1, 0x0f, 0x38, 0xe0, 0xc0, 0x00, 0x00, 0x02, 0x0e, 0x0e, 0x8e, 0xc6, 0xc0, 0x40,0x40, 0xc0, 0xc6, 0x8e, 0x0e, 0x0e, 0x02, 0x00, 0x80, 0xc0, 0x60, 0x38, 0x0f, 0xc0, 0x7c, 0x0f};
    static const char PROGMEM logo_4[] = {0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x31, 0x23, 0x66, 0x44, 0x44, 0xc4, 0xc4, 0x84, 0x84,0x84, 0x84, 0xc4, 0xc4, 0x44, 0x46, 0x66, 0x23, 0x11, 0x18, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00};
    oled_set_cursor(0,0);
    oled_write_raw_P(logo_1, sizeof(logo_1));
    oled_set_cursor(0,1);
    oled_write_raw_P(logo_2, sizeof(logo_2));
    oled_set_cursor(0,2);
    oled_write_raw_P(logo_3, sizeof(logo_3));
    oled_set_cursor(0,3);
    oled_write_raw_P(logo_4, sizeof(logo_4));
}
//-----------



bool oled_task_user(void) {

    
    render_logo();
    oled_set_cursor(7,0);
    oled_write_P(PSTR("The Mad Noodle"), false);

    oled_set_cursor(7,1);
    oled_write_P(PSTR("Layer: "), false);

   switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write_P(PSTR("Main"), false);
      break;
    case _RGB:
      oled_write_P(PSTR("RGB "), false);
      break;
    case _FN:
      oled_write_P(PSTR("FN  "), false);
      break;      
    case _LAYSEL:
      oled_write_P(PSTR("Layers"), false);
      break; 
    
    
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_P(PSTR("N/A "), false);
  }
  	oled_set_cursor(7,2);
    oled_write_P(PSTR("Status: "), false);
    oled_set_cursor(7,3);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("   "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("   "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("   "), false);


/*
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("The Mad Noodle Proto"), false);
  
  
  oled_write_P(PSTR("Active layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write_ln_P(PSTR("Main"), false);
      break;
    case _RGB:
      oled_write_ln_P(PSTR("RGB"), false);
      break;
    case _FN:
      oled_write_ln_P(PSTR("FN"), false);
      break;      
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("N/A"), false);
  }
  	oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("Status: "), false);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
*/


/*
//----MacroPad 8 Stuff------------------------------------------------------------------------------------------------

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("Num Lock: "), false);
  oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Caps Lock: "), false);
  oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Scroll Lock: "), false);
  oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);

#ifdef RGBLIGHT_ENABLE
  static char rgbStatusLine1[26] = {0};
  snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
  oled_write_ln(rgbStatusLine1, false);
  static char rgbStatusLine2[26] = {0};
  snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
  oled_write_ln(rgbStatusLine2, false);
#endif
 //----------------------------------------------------------------------------------------------------
 */   


return false;
}

#endif