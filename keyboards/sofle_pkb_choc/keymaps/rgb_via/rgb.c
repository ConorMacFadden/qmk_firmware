// RGB
    // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 11 12 21 22 31 32       52 39 40 49 50 57  0
  //  
  // 10 13 20 23 30 33       31 38 41 48 51 46  1
  //                
  // 09 14 19 24 29 34       32 37 42 47 52 45  2
  //
  // 08 15 18 25 28 35       33 36 43 46 53 34  3
  //
  //    04 03 02  01 00     34 35  44 45 54      4
  //    

#include "layers.h"

#ifdef RGB_MATRIX_ENABLE

// Variables for Dimming of RGB on layers
static uint8_t prev_val;
static bool dimmed = false;

void dim_rgb(void) {
    if (!dimmed) {
        hsv_t current_hsv = rgb_matrix_get_hsv();
        prev_val = current_hsv.v;
        uint8_t new_v = current_hsv.v * 128 / 255; // Half the current val
        rgb_matrix_sethsv(current_hsv.h, current_hsv.s, new_v);
        dimmed = true;
    }
}

void restore_rgb_brightness(void) {
    if (dimmed) {
        hsv_t current_hsv = rgb_matrix_get_hsv();
        rgb_matrix_sethsv(current_hsv.h, current_hsv.s, prev_val);
        dimmed = false;
    }
}

// === Helper functions ===
static uint8_t get_brightness(void) {
    if (dimmed) {
        return prev_val;
    } else {
        return rgb_matrix_get_val();
    }
}

static RGB hsv_to_rgb_brightness(HSV hsv, uint8_t brightness) {
    RGB rgb = hsv_to_rgb(hsv);
    rgb.r = (rgb.r * brightness) / 255;
    rgb.g = (rgb.g * brightness) / 255;
    rgb.b = (rgb.b * brightness) / 255;
    return rgb;
}

static void set_lighting(bool dimRgb) {
    if (dimRgb) {
        dim_rgb();
    } else { 
        restore_rgb_brightness();
    }
}

// === Layer lighting ===

// _NUMPAD
static void layer_numpad_lighting(void) {
    set_lighting(true);

    // Example: numpad keys in blue
    HSV hsv = {HSV_ORANGE};     
    RGB rgb = hsv_to_rgb_brightness(hsv, get_brightness());
    uint8_t numpad_keys[] = { 31, 32, 33, 36, 37, 38, 41, 42, 43, 48, 49, 50 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }
}

static void layer_qwerty_lighting(void) {
    restore_rgb_brightness();
}

static void layer_lower_lighting(void) {
    restore_rgb_brightness();
}

static void layer_raise_lighting(void) {
    set_lighting(true);

    HSV hsv = {HSV_BLUE};
    RGB rgb = hsv_to_rgb_brightness(hsv,get_brightness());
    uint8_t numpad_keys[] = { 37, 42, 47, 41  };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }

}

static void layer_adjust_lighting(void) {
    restore_rgb_brightness();
}


// === Dispatcher ===
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY: layer_qwerty_lighting(); return true;
        case _NUMPAD:  layer_numpad_lighting();  return true;
        case _LOWER:  layer_lower_lighting();  return true;
        case _RAISE: layer_raise_lighting(); return true;
        case _ADJUST:  layer_adjust_lighting();  return true;
        default: return false; // fall back to normal effect
    }
}

#endif

