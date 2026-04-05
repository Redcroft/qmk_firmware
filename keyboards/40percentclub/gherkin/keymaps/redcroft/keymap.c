#include QMK_KEYBOARD_H
#include "sm_td.h"

enum custom_keycodes {
  TD_N = SAFE_RANGE,
  TD_R,
  TD_T,
  TD_S,
  TD_H,
  TD_A,
  TD_E,
  TD_I
};

enum layers {
  _GAL = 0,
  _NUM,
  _NAV
};

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
  switch (keycode) {
  case TD_N: SMTD_MT(KC_N, KC_LGUI);
  case TD_R: SMTD_MT(KC_R, KC_LALT);
  case TD_T: SMTD_MT(KC_T, KC_LCTL);
  case TD_S: SMTD_MT(KC_S, KC_LSFT);

  case TD_H: SMTD_MT(KC_H, KC_RSFT);
  case TD_A: SMTD_MT(KC_A, KC_RCTL);
  case TD_E: SMTD_MT(KC_E, KC_RALT);
  case TD_I: SMTD_MT(KC_I, KC_RGUI);
  }
  return SMTD_RESOLUTION_UNHANDLED;
}

const uint16_t PROGMEM spc_combo[] = {KC_W, KC_Z, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_Z, KC_K, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_B, KC_L, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_X, KC_Q, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_SLSH, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    COMBO(spc_combo, KC_SPC),
    COMBO(del_combo, KC_BSPC), // Backspace is usually more useful than Del
    COMBO(tab_combo, KC_TAB),
    COMBO(esc_combo, KC_ESC),
    COMBO(ent_combo, KC_ENT)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GAL] = LAYOUT_ortho_3x10(
			     KC_B,   KC_L,   KC_D,   KC_C,   KC_V,      KC_J,   KC_Y,   KC_O,   KC_U,   KC_COMM,
			     TD_N,   TD_R,   TD_T,   TD_S,   KC_G,      KC_P,   TD_H,   TD_A,   TD_E,   TD_I,
			     KC_X,   KC_Q,   KC_M,   KC_W,   KC_Z,      KC_K,   KC_F,   KC_QUOT, KC_SLSH, KC_DOT
			     ),

  [_NUM] = LAYOUT_ortho_3x10(
			     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
			     KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
			     KC_GRV,  KC_TILD, KC_UNDS, KC_MINS, KC_PLUS,   KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_PIPE
			     ),

  [_NAV] = LAYOUT_ortho_3x10(
			     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
			     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
			     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS
			     )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_smtd(keycode, record)) {
    return false;
  }
  return true;
}
