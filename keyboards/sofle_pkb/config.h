#pragma once

#define TAPPING_TERM 100
#define DEBOUNCE 5

/* encoder support */
#define ENCODER_A_PINS { GP29 }
#define ENCODER_B_PINS { GP28 }
#define ENCODER_A_PINS_RIGHT { GP28 }
#define ENCODER_B_PINS_RIGHT { GP29 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 10

//#define MASTER_LEFT
#define SPLIT_HAND_PIN GP4
#define	SPLIT_HAND_PIN_LOW_IS_LEFT
#define USE_SERIAL
#define SERIAL_PIO_USE_PIO0
#define SERIAL_USART_TX_PIN   GP1
#define USB_VBUS_PIN 19

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#ifdef OLED_ENABLE
// settings for the oled keyboard demo with Adafruit 0.91" OLED display on the Stemma QT port
    #define OLED_DISPLAY_128X32
    #define I2C_DRIVER I2CD1
    #define I2C1_SDA_PIN GP2
    #define I2C1_SCL_PIN GP3
    #define OLED_BRIGHTNESS 180
    #define OLED_TIMEOUT 60000
    #define OLED_FONT_H "lib/oledFont.c"
    // #define WPM_ESTIMATED_WORD_SIZE 5
    #define SPLIT_LAYER_STATE_ENABLE
    #define SPLIT_LED_STATE_ENABLE
    #define SPLIT_MODS_ENABLE
    #define SPLIT_WPM_ENABLE
    #define SPLIT_OLED_ENABLE
#endif

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_LED_COUNT        72 // Number of LEDs
    #define DRIVER_LED_TOTAL            RGBLED_NUM
    #define WS2812_DI_PIN               GP0
    #define WS2812_PIO_USE_PIO1

    #define SPLIT_TRANSPORT_MIRROR
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_SLEEP
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT

    #define ENABLE_RGB_MATRIX_ALPHAS_MODS         //  1. Static dual hue, speed is hue for secondary hue
    #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN    //  2. Static gradient top to bottom, speed controls how much gradient changes
    #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT //  3. Static gradient left to right, speed controls how much gradient changes
    #define ENABLE_RGB_MATRIX_BREATHING           //  4. Single hue brightness cycling animation
    #define ENABLE_RGB_MATRIX_BAND_SAT            //  5. Single hue band fading saturation scrolling left to right
    #define ENABLE_RGB_MATRIX_BAND_VAL            //  6. Single hue band fading brightness scrolling left to right
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT   //  7.  Single hue 3 blade spinning pinwheel fades saturation
    #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL   //  8. Single hue 3 blade spinning pinwheel fades brightness
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT     //  9. Single hue spinning spiral fades saturation
    #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // 10. Single hue spinning spiral fades brightness
    #define ENABLE_RGB_MATRIX_CYCLE_ALL           // 11. Full keyboard solid hue cycling through full gradient
    #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT    // 12. Full gradient scrolling left to right
    #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN       // 13. Full gradient scrolling top to bottom
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN        // 14. Full gradient scrolling out to in
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL   // 15. Full dual gradients scrolling out to in
    #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  //16.  Full gradient Chevron shapped scrolling left to right
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL      // 17. Full gradient spinning pinwheel around center of keyboard
    #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL        // 18. Full gradient spinning spiral around center of keyboard
    #define ENABLE_RGB_MATRIX_DUAL_BEACON         // 19. Full gradient spinning around center of keyboard
    #define ENABLE_RGB_MATRIX_RAINBOW_BEACON      // 20. Full tighter gradient spinning around center of keyboard
    #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS   // 21. Full dual gradients spinning two halfs of keyboard
    #define ENABLE_RGB_MATRIX_RAINDROPS           // 22. Randomly changes a single key's hue
    #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS // 23. Randomly changes a single key's hue and saturation
    #define ENABLE_RGB_MATRIX_HUE_BREATHING       // 24. Hue shifts up a slight ammount at the same time, then shifts back
    #define ENABLE_RGB_MATRIX_HUE_PENDULUM        // 25. Hue shifts up a slight ammount in a wave to the right, then back to the left
    #define ENABLE_RGB_MATRIX_HUE_WAVE            // 26. Hue shifts up a slight ammount and then back down in a wave to the right
    #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL       // 27. Single hue fractal filled keys pulsing horizontally out to edges
    #define ENABLE_RGB_MATRIX_PIXEL_FLOW          // 28. Pulsing RGB flow along LED wiring with random hues
    #define ENABLE_RGB_MATRIX_PIXEL_RAIN          // 29. Randomly light keys with random hues
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP      // 30. How hot is your WPM!
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN        // 31. That famous computer simulation
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // 32.  Pulses keys hit to hue & value then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE      // 33. Static single hue, pulses keys hit to shifted hue then fades to current hue
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // 34. Hue & value pulse near a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // 35. Hue & value pulse near multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // 36. Hue & value pulse the same column and row of a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // 37. Hue & value pulse the same column and row of multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // 38. Hue & value pulse away on the same column and row of a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // 39. Hue & value pulse away on the same column and row of multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SPLASH              // 40. Full gradient & value pulse away from a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_MULTISPLASH         // 41. Full gradient & value pulse away from multiple key hits then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_SPLASH        // 42. Hue & value pulse away from a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH   // 43. Hue & value pulse away from multiple key hits then fades value out
#endif
