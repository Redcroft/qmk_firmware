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

#define ESC_CTL LCTL_T(KC_ESC)
#define ALT_SPC LALT_T(KC_SPC)
#define KCT KC_TRNS
#define SUPL MO(_LOWER) //LT(_LOWER, KC_LGUI)


enum layers {
    _COLEMAK,
    _GAME,
    _LOWER,
    _RAISE
};

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  GAME,
  LOWER,
  RAISE,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_TAB,   KC_Q,  KC_W,   KC_F,   KC_P,   KC_B,              KC_J,   KC_L,   KC_U,   KC_Y,  KC_SCLN,KC_QUOT,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     ESC_CTL,  KC_A,  KC_R,   KC_S,   KC_T,   KC_G,              KC_M,   KC_N,   KC_E,   KC_I,   KC_O, KC_MINUS,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_LSFT,  KC_Z,  KC_X,   KC_C,   KC_D,   KC_V,              KC_K,   KC_H, KC_COMM,KC_DOT,KC_SLSH,KC_SFTENT,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                 KC_LALT, KC_SPC, SUPL,   MO(_RAISE), KC_BSPC, KC_LGUI \
                             //`-----------------------'  `----------------------'
  ),

  [_GAME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,              KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,  KC_BSPC,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,              KC_H,   KC_J,   KC_K,   KC_L, KC_SCLN, KC_QUOT,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,              KC_N,   KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_SFTENT,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                 KC_LALT, KC_SPC, SUPL,   MO(_RAISE), KC_BSPC, KC_LGUI \
                             //`-----------------------'  `----------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_TILD, KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_F5,              KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KCT,     KC_1,  KC_2,   KC_3,   KC_4,   KC_5,               KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KCT,     KC_MUTE,KC_VOLD,KC_VOLU,KC_ESC,KC_LGUI,            KCT,    KCT,   KC_LBRC,KC_RBRC,KC_HASH,KC_BSLS,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                       KCT, KCT, KCT,           KCT, KCT, KCT
                             //`-----------------------'  `--------------------qmk--'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------.          ,-----------------------------------------------.
     KC_GRV,KC_EXLM, KC_AT,  KC_HASH,KC_DLR, KC_PERC,          KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN, KC_EQL,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KCT,RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,DF(_COLEMAK),          KCT,   KC_LEFT,KC_DOWN, KC_UP, KC_RIGHT,   KCT,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KCT,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,  DF(_GAME),           KC_DEL,KC_HOME,KC_PGDN,KC_PGUP,KC_END,   RESET,\
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
                                       KCT, KCT, KCT,           KCT, KCT, KCT
                             //`-----------------------'  `----------------------'
  ),
};

#ifdef OLED_DRIVER_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _GAME:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
  }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,252,252,252,252,252,252,252,124,124,124,124,124,252,252,252,248,252,124,124,124,124,252,252,252,252,252,252,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,255,255,255,255,255,193,224,240,248,252,254,127, 31, 15,  7,  1,  0,  0,192,224,224,240,240,255,255,255,255,191,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,112, 48, 48, 48, 32, 96,192,224,112, 56, 56, 28, 15,  0,  0,  0,  0,  0,  0,  0,  0,240,240, 16,  0,  0,  0, 16,240, 48,  0,  0,  0,  0, 24,240,240,  0,  0,  0,  0,  0,  0,  0,  0,240,120, 28, 14,  6,  7,  7,  7,  7,  6,  6, 14, 28,120,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,192,255,255,255,255,127, 31, 15,135,129,192,224,240,248,252,254,254,127, 63, 31, 15,  7,131,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63, 28, 28, 28, 28, 28, 28, 28, 31, 28, 28, 28, 28, 28, 62,  0,  0,  0,  0,  0,  0,  0,  0, 15,  7,  6,  6,  6,  6,  6,  7,  6,  6,  6,  6,  6,  6,  7, 15,  0,  0,  0,  0,  0,  0,  0,  0,127, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 56,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0, 63, 63, 63, 63, 63, 63, 62, 63, 63, 63, 63, 63, 63, 63, 31, 31, 30, 30, 30, 30, 62, 63, 63, 63, 63, 63, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
