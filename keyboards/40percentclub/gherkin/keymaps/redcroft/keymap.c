#include QMK_KEYBOARD_H
#include "tap_dance.h"
#include "aliases.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_P,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
    CTL_A,   KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    CTL_S,
    SFT_Q,   GUI_J,   ALT_K,   F1_SPC,  F2_X,    KC_B,    KC_M,    KC_W,    KC_V,    ENT_Z
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_TAB,  KC_GRV,  KC_LBRC, KC_RBRC, KC_EQL,  KC_SCLN, KC_HOME, KC_UP,   KC_END,  KC_BSPC,
    KC_LCTL, KC_BSLS, KC_SLSH, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS,
    KC_LSFT, KC_LGUI, KC_LALT, _______, F3_DEL,  _______, KC_PGDN, _______, KC_PGUP, KC_ENT
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_LSFT, KC_LGUI, KC_LALT, _______, KC_DEL,  KC_LCA,  KC_COMM, KC_DOT,  KC_F11,  KC_F12
  ),


  [3] = LAYOUT_ortho_3x10(
    KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM, _______, _______, _______, _______, _______, KC_PSCR,
    KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______,
    KC_MUTE, KC_VOLU, KC_VOLD, _______, _______, _______, _______, _______, _______, QK_BOOT
  )

};
