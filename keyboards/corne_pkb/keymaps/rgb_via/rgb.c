// RGB
    // Physical Layout
  // Columns
  // 0  1  2  3  4  5        
  //                                             /ROWS
  // 24 23 18 17 10 09       36 37 44 45 50 51   /0
  //    02    01    00       27    28    29                       
  // 25 22 19 16 11 08       35 38 43 46 49 52   /1
  //    03                              30
  // 26 21 20 15 12 07       34 39 42 47 48 53   /2
  //        04    05           32    31
  //          14 13 06       33 40 41            /3


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

static void set_underglow(HSV hsv) {
    uint8_t brightness = get_brightness();
    RGB rgb = hsv_to_rgb_brightness(hsv, brightness);
    uint8_t underglow[] = {0, 1, 2, 3, 4, 5, 27, 28, 29, 30, 31, 32};
    for (uint8_t i = 0; i < sizeof(underglow); i++) {
        rgb_matrix_set_color(underglow[i], rgb.r, rgb.g, rgb.b);
    }
}

static void set_lighting(bool dimRgb, HSV indicatorHSV, HSV underglowHSV) {
    if (dimRgb) {
        dim_rgb();
    } else { 
        restore_rgb_brightness();
    }
    set_underglow(underglowHSV);
}

// === Layer lighting ===

// _NUMPAD
static void layer_numpad_lighting(void) {
    set_lighting(true,(HSV){HSV_ORANGE},(HSV){HSV_ORANGE});

    // Example: numpad keys in blue
    HSV hsv = {HSV_ORANGE};     
    RGB rgb = hsv_to_rgb_brightness(hsv, get_brightness());
uint8_t numpad_keys[] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }
}

static void layer_qwerty_lighting(void) {
    restore_rgb_brightness();
}

static void layer_lower_lighting(void) {
    restore_rgb_brightness();
    set_lighting(false, (HSV){HSV_BLUE},(HSV){HSV_BLUE});
}

static void layer_raise_lighting(void) {
    set_lighting(true, (HSV){HSV_PURPLE},(HSV){HSV_PURPLE});

    HSV hsv = {HSV_BLUE};
    RGB rgb = hsv_to_rgb_brightness(hsv,get_brightness());
    uint8_t numpad_keys[] = { 38, 43, 44, 46 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }

}

static void layer_adjust_lighting(void) {
    restore_rgb_brightness();
    set_underglow((HSV){HSV_GREEN});
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

