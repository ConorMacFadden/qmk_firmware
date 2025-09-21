// RGB
    // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 11 12 21 22 31 32       68 67 58 57 48 47  0
  //    01    02    03       39    38    37
  // 10 13 20 23 30 33       69 66 59 56 49 46  1
  //                00       36
  // 09 14 19 24 29 34       70 65 60 55 50 45  2
  //
  // 08 15 18 25 28 35       71 64 61 54 51 44  3
  //
  //     07 16 17 26 27     63 62 53 52 43      4
  //    06    05    04       40    41    42


#include "layers.h"

#ifdef RGB_MATRIX_ENABLE

// Scaling parameter for indicators - Max 255.
static uint8_t indicator_brightness_scaler = 32;

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

static void set_indicators(HSV hsv) {
    uint8_t current_brightness = get_brightness();
    uint8_t indicator_brightness  = indicator_brightness_scaler * current_brightness / 255;
    RGB rgb = hsv_to_rgb_brightness(hsv,indicator_brightness);
    rgb_matrix_set_color(0,  rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color(36, rgb.r, rgb.g, rgb.b);
}

static void set_underglow(HSV hsv) {
    uint8_t brightness = get_brightness();
    RGB rgb = hsv_to_rgb_brightness(hsv, brightness);
    uint8_t underglow[] = {1, 2, 3, 4, 5, 6, 37, 38, 39, 40, 41, 42};
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
    set_indicators(indicatorHSV);
    set_underglow(underglowHSV);
}

// === Layer lighting ===

// _NUMPAD
static void layer_numpad_lighting(void) {
    set_lighting(true,(HSV){HSV_ORANGE},(HSV){HSV_ORANGE});

    // Example: numpad keys in blue
    HSV hsv = {HSV_ORANGE};     
    RGB rgb = hsv_to_rgb_brightness(hsv, get_brightness());
    uint8_t numpad_keys[] = { 43, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 65, 66, 67 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }
}

static void layer_qwerty_lighting(void) {
    restore_rgb_brightness();
    set_indicators((HSV){HSV_WHITE});
}

static void layer_lower_lighting(void) {
    set_lighting(false, (HSV){HSV_BLUE},(HSV){HSV_BLUE});
}

static void layer_raise_lighting(void) {
    set_lighting(true, (HSV){HSV_PURPLE},(HSV){HSV_PURPLE});

    HSV hsv = {HSV_BLUE};
    RGB rgb = hsv_to_rgb_brightness(hsv,get_brightness());
    uint8_t numpad_keys[] = { 55, 59, 60, 65 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }

}

static void layer_adjust_lighting(void) {
    restore_rgb_brightness();
    set_indicators((HSV){HSV_GREEN});
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

