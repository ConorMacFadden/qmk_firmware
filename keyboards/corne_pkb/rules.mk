# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output
QMK_SETTINGS    = yes
COMBO_ENABLE    = no
KEY_OVERRIDE_ENABLE = no
AUTO_SHIFT_ENABLE = yes

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor

WS2812_DRIVER = vendor
OLED_DRIVER   = ssd1306 

LAYOUTS = split_3x6_3
