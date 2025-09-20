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

static uint8_t indicator_brightness_scaler = 64;

static hsv_t prev_hsv;
static bool saved_prev = false;

// Helper to save current global HSV
void save_current_hsv(void) {
    if (!saved_prev) {
        prev_hsv = rgb_matrix_get_hsv();
        saved_prev = true;
    }
}

// Restore previous global HSV
void restore_previous_hsv(void) {
    if (saved_prev) {
        rgb_matrix_sethsv(prev_hsv.h, prev_hsv.s, prev_hsv.v);
        saved_prev = false;
    }
}

// === Helper functions ===
static RGB hsv_to_rgb_brightness(HSV hsv, uint8_t brightness) {
    RGB rgb = hsv_to_rgb(hsv);
    rgb.r = (rgb.r * brightness) / 255;
    rgb.g = (rgb.g * brightness) / 255;
    rgb.b = (rgb.b * brightness) / 255;
    return rgb;
}

static void set_indicators(HSV hsv) {
    uint8_t current_brightness = rgb_matrix_get_val();
    uint8_t indicator_brightness  = indicator_brightness_scaler * current_brightness / 255;
    RGB rgb = hsv_to_rgb_brightness(hsv,indicator_brightness);
    rgb_matrix_set_color(0,  rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color(36, rgb.r, rgb.g, rgb.b);
}

static void set_underglow(HSV hsv) {
    RGB rgb = hsv_to_rgb(hsv);
    uint8_t underglow[] = {1, 2, 3, 4, 5, 6, 37, 38, 39, 40, 41, 42};
    for (uint8_t i = 0; i < sizeof(underglow); i++) {
        rgb_matrix_set_color(underglow[i], rgb.r, rgb.g, rgb.b);
    }
}

// === Layer lighting ===
static void layer_numpad_lighting(void) {
    set_indicators((HSV){HSV_ORANGE});
    set_underglow((HSV){HSV_ORANGE});

    // Example: numpad keys in blue
    HSV hsv = {HSV_BLUE};
    RGB rgb = hsv_to_rgb(hsv);
    uint8_t numpad_keys[] = { 43, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 65, 66, 67 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }
}

static void layer_qwerty_lighting(void) {
    set_indicators((HSV){HSV_WHITE});
}

static void layer_lower_lighting(void) {
    set_indicators((HSV){HSV_BLUE});
    set_underglow((HSV){HSV_BLUE});
}

static void layer_raise_lighting(void) {
    set_indicators((HSV){HSV_PURPLE});
    set_underglow((HSV){HSV_PURPLE});

    HSV hsv = {HSV_BLUE};
    RGB rgb = hsv_to_rgb(hsv);
    uint8_t numpad_keys[] = { 55, 59, 60, 65 };
    for (uint8_t i = 0; i < sizeof(numpad_keys); i++) {
        rgb_matrix_set_color(numpad_keys[i], rgb.r, rgb.g, rgb.b);
    }

}

static void layer_adjust_lighting(void) {
    set_indicators((HSV){HSV_GREEN});
    set_underglow((HSV){HSV_GREEN});
    // Maybe light only top row instead of full underglow here
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

