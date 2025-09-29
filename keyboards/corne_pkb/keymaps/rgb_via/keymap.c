/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "layers.h"
#include "oled.c"
#include "rgb.c"

enum custom_keycodes {
  KC_QWERTY = SAFE_RANGE,
  KC_LOWER,
  KC_RAISE,
  KC_ADJUST,
  KC_PRVWD,
  KC_NXTWD,
  KC_LSTRT,
  KC_LEND,
  KC_DLINE
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
            KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
LT(_NUMPAD,KC_TAB),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                          KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_LGUI,
                                                KC_LCTL, KC_LOWER,  KC_SPC,   KC_ENT,  KC_RAISE, KC_RALT

),

  [_LOWER] = LAYOUT_split_3x6_3(
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
    _______, KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,                       KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                                        KC_LCTL, _______, KC_SPC,      KC_ENT,  _______,   KC_RALT
),

  [_RAISE] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_INS,  KC_PSCR, KC_APP,  KC_DLR,  KC_PERC,                       KC_PGUP, KC_PRVWD, KC_UP,   KC_NXTWD, _______,  KC_DEL,
    _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, KC_CAPS,                       KC_PGDN, KC_LEFT,  KC_DOWN, KC_RGHT,  KC_DEL,  KC_BSPC,
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE,XXXXXXX,                       _______, KC_HOME,  XXXXXXX, KC_END,   XXXXXXX, _______,
                                        KC_LCTL, _______,   KC_SPC,      KC_ENT,  _______, KC_RALT
),

  [_ADJUST] = LAYOUT_split_3x6_3(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX,                       KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,
    _______, RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX,                       KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, EE_CLR,  QK_BOOT,
                                        KC_LCTL, _______, KC_SPC,      KC_ENT,  _______, KC_RALT
),

[_NUMPAD] = LAYOUT_split_3x6_3(
  KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_NUM,  KC_P7,  KC_P8,   KC_P9,   KC_ASTR,  KC_F11,
  _______, XXXXXXX, KC_LALT, KC_BSPC, XXXXXXX, XXXXXXX,                       KC_MINS, KC_P4,  KC_P5,   KC_P6,   KC_SLSH,  KC_PIPE,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_PLUS, KC_P1,  KC_P2,   KC_P3,   KC_EQL,   _______,
                                      KC_LCTL, XXXXXXX, KC_SPC,      KC_ENT,  KC_0, KC_PDOT
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case KC_QWERTY:
          if (record->event.pressed) {
              set_single_persistent_default_layer(_QWERTY);
          }
          return false;
      case KC_LOWER:
          if (record->event.pressed) {
              layer_on(_LOWER);
              update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
              layer_off(_LOWER);
              update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
      case KC_RAISE:
          if (record->event.pressed) {
              layer_on(_RAISE);
              update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
              layer_off(_RAISE);
              update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
      case KC_ADJUST:
          if (record->event.pressed) {
              layer_on(_ADJUST);
          } else {
              layer_off(_ADJUST);
          }
          return false;
      case KC_PRVWD:
          if (record->event.pressed) {
              if (keymap_config.swap_lctl_lgui) {
                  register_mods(mod_config(MOD_LALT));
                  register_code(KC_LEFT);
              } else {
                  register_mods(mod_config(MOD_LCTL));
                  register_code(KC_LEFT);
              }
          } else {
              if (keymap_config.swap_lctl_lgui) {
                  unregister_mods(mod_config(MOD_LALT));
                  unregister_code(KC_LEFT);
              } else {
                  unregister_mods(mod_config(MOD_LCTL));
                  unregister_code(KC_LEFT);
              }
          }
          break;
      case KC_NXTWD:
           if (record->event.pressed) {
              if (keymap_config.swap_lctl_lgui) {
                  register_mods(mod_config(MOD_LALT));
                  register_code(KC_RIGHT);
              } else {
                  register_mods(mod_config(MOD_LCTL));
                  register_code(KC_RIGHT);
              }
          } else {
              if (keymap_config.swap_lctl_lgui) {
                  unregister_mods(mod_config(MOD_LALT));
                  unregister_code(KC_RIGHT);
              } else {
                  unregister_mods(mod_config(MOD_LCTL));
                  unregister_code(KC_RIGHT);
              }
          }
          break;
      case KC_LSTRT:
          if (record->event.pressed) {
              if (keymap_config.swap_lctl_lgui) {
                   //CMD-arrow on Mac, but we have CTL and GUI swapped
                  register_mods(mod_config(MOD_LCTL));
                  register_code(KC_LEFT);
              } else {
                  register_code(KC_HOME);
              }
          } else {
              if (keymap_config.swap_lctl_lgui) {
                  unregister_mods(mod_config(MOD_LCTL));
                  unregister_code(KC_LEFT);
              } else {
                  unregister_code(KC_HOME);
              }
          }
          break;
      case KC_LEND:
          if (record->event.pressed) {
              if (keymap_config.swap_lctl_lgui) {
                  //CMD-arrow on Mac, but we have CTL and GUI swapped
                  register_mods(mod_config(MOD_LCTL));
                  register_code(KC_RIGHT);
              } else {
                  register_code(KC_END);
              }
          } else {
              if (keymap_config.swap_lctl_lgui) {
                  unregister_mods(mod_config(MOD_LCTL));
                  unregister_code(KC_RIGHT);
              } else {
                  unregister_code(KC_END);
              }
          }
          break;
      case KC_DLINE:
          if (record->event.pressed) {
              register_mods(mod_config(MOD_LCTL));
              register_code(KC_BSPC);
          } else {
              unregister_mods(mod_config(MOD_LCTL));
              unregister_code(KC_BSPC);
          }
          break;
      case KC_COPY:
          if (record->event.pressed) {
              register_mods(mod_config(MOD_LCTL));
              register_code(KC_C);
          } else {
              unregister_mods(mod_config(MOD_LCTL));
              unregister_code(KC_C);
          }
          return false;
      case KC_PASTE:
          if (record->event.pressed) {
              register_mods(mod_config(MOD_LCTL));
              register_code(KC_V);
          } else {
              unregister_mods(mod_config(MOD_LCTL));
              unregister_code(KC_V);
          }
          return false;
      case KC_CUT:
          if (record->event.pressed) {
              register_mods(mod_config(MOD_LCTL));
              register_code(KC_X);
          } else {
              unregister_mods(mod_config(MOD_LCTL));
              unregister_code(KC_X);
          }
          return false;
          break;
      case KC_UNDO:
          if (record->event.pressed) {
              register_mods(mod_config(MOD_LCTL));
              register_code(KC_Z);
          } else {
              unregister_mods(mod_config(MOD_LCTL));
              unregister_code(KC_Z);
          }
          return false;
  }
  return true;
}
