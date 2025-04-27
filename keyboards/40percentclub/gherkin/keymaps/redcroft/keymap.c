#include QMK_KEYBOARD_H
#include "tap_dance.h"
#include "aliases.h"


enum gherkin_layers {
  _COLEMAK,
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  SMTD_KEYCODES_BEGIN = SAFE_RANGE,
  CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
  CKC_R,
  CKC_S,
  CKC_T,
  CKC_N,
  CKC_E,
  CKC_I,
  CKC_O,
  DKC_A,
  DKC_O,
  DKC_E,
  DKC_U,
  DKC_H,
  DKC_T,
  DKC_N,
  DKC_S,
  SMTD_KEYCODES_END,
};

#include "sm_td/sm_td.h"

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
        SMTD_MT(CKC_R, KC_R, KC_LEFT_ALT)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_CTRL)
        SMTD_MT(CKC_T, KC_T, KC_LSFT)
	SMTD_MT(CKC_N, KC_N, KC_LSFT)
        SMTD_MT(CKC_E, KC_E, KC_LEFT_CTRL)
        SMTD_MT(CKC_I, KC_I, KC_LEFT_ALT)
        SMTD_MT(CKC_O, KC_O, KC_LEFT_GUI)

	SMTD_MT(DKC_A, KC_A, KC_LEFT_GUI)
        SMTD_MT(DKC_O, KC_O, KC_LEFT_ALT)
        SMTD_MT(DKC_E, KC_E, KC_LEFT_CTRL)
        SMTD_MT(DKC_U, KC_U, KC_LSFT)
	SMTD_MT(DKC_H, KC_H, KC_LSFT)
        SMTD_MT(DKC_T, KC_T, KC_LEFT_CTRL)
        SMTD_MT(DKC_N, KC_N, KC_LEFT_ALT)
        SMTD_MT(DKC_S, KC_S, KC_LEFT_GUI)
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#define DVORAK DF(0)
#define COLEMAK DF(1)
#define QWERTY DF(2)

#define L310 LAYOUT_ortho_3x10

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Dvorak
   * ,-------------------------------------------------------------------------------.
   * |   '   |   ,   |   .   |   P   |   Y   |   F   |   G   |   C   |   R   |   L   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⌃ A  |  ⌥ O  |  ⇧ E  |  ⌘ U  |   I   |   D   |  ⌘ H  |  ⇧ T  |  ⌥ N  |  ⌃ S  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |   Q   |   J   |   K   | ↓ Spc |  ↑ X  |   B   |   M   |   W   |   V   |  ⏎ Z |
   * `-------------------------------------------------------------------------------'
   */
  [_DVORAK] = L310(
                   KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
                   DKC_A,   DKC_O,   DKC_E,   DKC_U,   KC_I,    KC_D,    DKC_H,   DKC_T,   DKC_N,   DKC_S,
                   KC_Q,    KC_J,    KC_K,    F1_SPC,  F2_X,    KC_B,    KC_M,    KC_W,    KC_V,    ENT_Z
                   ),

  /* Colemak
   * ,-------------------------------------------------------------------------------.
   * |   Q   |   W   |   F   |   P   |   B   |   J   |   L   |   U   |   Y   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⌃ A  |  ⌥ R  |  ⇧ S  |  ⌘ T  |   G   |   M   |  ⌘ N  |  ⇧ E  |  ⌥ I  |  ⌃ O  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |   X   |   C   |   D   | ↓ Spc |  ↑ V  |   Z   |   K   |   H   |   ,   |   ⏎   |
   * `-------------------------------------------------------------------------------'
   */
  [_COLEMAK] = L310(
                    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
                    CKC_A,   CKC_R,   CKC_S,   CKC_T,   KC_G,    KC_M,    CKC_N,   CKC_E,   CKC_I,   CKC_O,
                    KC_X,    KC_C,    KC_D,    F1_SPC,  F2_V,    KC_Z,    KC_K,    KC_H,    KC_COMM, ENT_DOT
                    ),

  /* Qwerty
   * ,-------------------------------------------------------------------------------.
   * |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⌃ A  |  ⌥ S  |  ⇧ D  |  ⌘ F  |   G   |   H   |  ⌘ J  |  ⇧ K  |  ⌥ L  |  ⌃ -  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |   Z   |   X   |   C   | ↓ Spc |  ↑ V  |   B   |   N   |   M   |   ,   |   ⏎   |
   * `-------------------------------------------------------------------------------'
   */
  [_QWERTY] = L310(
                   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_BSPC, KC_O,
                   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_MINS,
                   KC_LSFT, KC_Z,    ALT_X,   F1_SPC,  F2_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_BSPC
                   ),

  /* Lower
   * ,-------------------------------------------------------------------------------.
   * |  Tab  |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       | _____ |       |       |   ⌫   |       |       |       |
   * `-------------------------------------------------------------------------------'
   */
  [_LOWER] = L310(
                  KC_TAB,  KC_GRV,  KC_LBRC, KC_RBRC, KC_EQL,  KC_SCLN, KC_END,  KC_UP,   KC_HOME, KC_BSPC,
                  KC_LCTL, KC_BSLS, KC_SLSH, KC_ESC,  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS,
                  KC_LSFT, KC_LGUI, KC_LALT, _______, KC_DEL,  _______, KC_PGDN, _______, KC_PGUP, KC_ENT
                  ),

  /* Raise
   * ,-------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       | _____ |       |       |       |
   * `-------------------------------------------------------------------------------'
   */
  [_RAISE] = L310(
                  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
                  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                  KC_LSFT, KC_LGUI, KC_LALT, _______, _______, KC_LCA,  KC_COMM, KC_DOT,  KC_F11,  KC_F12
                  ),

  /* Adjust
   * ,-------------------------------------------------------------------------------.
   * |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       |       |       |       |       |       |       |       |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |       |       |       | _____ |       |       | _____ |       |       |       |
   * `-------------------------------------------------------------------------------'
   */
  [_ADJUST] = L310(
                   KC_ESC,  DVORAK,  COLEMAK, QWERTY,  _______, _______, _______, KC_UP,   _______, KC_BSPC,
                   KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,
                   KC_LSFT, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, _______, QK_BOOT
                   )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_smtd(keycode, record)) {
    return false;
  }
  return true;
}
