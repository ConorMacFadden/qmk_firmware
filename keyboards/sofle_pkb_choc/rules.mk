# MCU name
MCU = RP2040
# Bootloader selection
BOOTLOADER = rp2040

SPLIT_KEYBOARD = yes
SWAP_HANDS_ENABLE = yes

# Build Options
#   change yes to no to disable
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes

QMK_SETTINGS    = yes
COMBO_ENABLE    = no
KEY_OVERRIDE_ENABLE = no

SERIAL_DRIVER = vendor
WS2812_DRIVER = vendor
OLED_DRIVER   = ssd1306
