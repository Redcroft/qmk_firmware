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

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#define ALT_J  LALT_T(KC_J)
#define ALT_X  LALT_T(KC_X)
#define CTL_A  LCTL_T(KC_A)
#define CTL_S  LCTL_T(KC_S)
#define ENT_Z  TD(TD_ENT_Z)
#define F1_SPC LT(2, KC_SPC)
#define F2_C   LT(3, KC_C)
#define F2_K   LT(3, KC_K)
#define F3_B   LT(4, KC_B)
#define F3_M   LT(4, KC_M)
#define GUI_Q  LGUI_T(KC_Q)
#define KC_LCA LCA_T(KC_NO)
#define SFT_X  LSFT_T(KC_X)
#define DVORAK DF(0)
#define COLEMAK DF(1)
#define QWERTY DF(2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Dvorak
   * ,-------------------------------------------------------------------------------.
   * |   '   |   ,   |   .   |   P   |   Y   |   F   |   G   |   C   |   R   |   L   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⌃ A  |   O   |   E   |   U   |   I   |   D   |   H   |   T   |   N   |  ⌃ S  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⇧ Q  |  ⌘ J  |  ⌥ K  | ↓ Spc |  ↑ X  |   B   |   M   |   W   |   V   |  ⏎ Z  |
   * `-------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_ortho_3x10(
                                KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,
                                CTL_A,   KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    CTL_S,
                                SFT_Q,   GUI_J,   ALT_K,   F1_SPC,  F2_X,    KC_B,    F3_M,    KC_W,    KC_V,    ENT_Z
                                ),

  /* Colemak
   * ,-------------------------------------------------------------------------------.
   * |   Q   |   W   |   F   |   P   |   B   |   J   |   L   |   U   |   Y   |   '   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⌃ A  |   R   |   S   |   T   |   G   |   M   |   N   |   E   |   I   |  ⌃ O  |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⇧ X  |  ⌘ C  |  ⌥ D  | ↓ Spc |  ↑ V  |   Z   |   K   |   H   |   ,   |   ⏎   |
   * `-------------------------------------------------------------------------------'
   */
  [_Colemak] = LAYOUT_ortho_3x10(
                                 KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
                                 CTL_A,   KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    CTL_O,
                                 SFT_X,   GUI_C,   ALT_D,   F1_SPC,  F2_V,    KC_Z,    F3_K,    KC_H,    KC_COMM, ENT_DOT
                                 ),

  /* Qwerty
   * ,-------------------------------------------------------------------------------.
   * |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⌃ A  |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   | ⌃ Esc |
   * |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
   * |  ⇧ Z  |  ⌘ X  |  ⌥ C  | ↓ Spc |  ↑ V  |   B   |   N   |   M   |   ,   |   ⏎   |
   * `-------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_ortho_3x10(
                                KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_BSPC,
                                KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,
                                KC_LSFT, KC_Z,    ALT_X,   F1_SPC,  F2_C,    KC_V,    F3_B,    KC_N,    KC_M,    KC_BSPC
                                ),

  /* Lower
   * ,-----------------------------------------------------------.
   * |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  A  |  S  |  D  |  G  |  H  |  J  |  K  |  L  |  ;  |  -  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  Z  |  X  |  C  | Spc |  V  |  B  |  N  |  M  |  ,  |  .  |
   * `-----------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_ortho_3x10(
                               KC_TAB,  KC_GRV,  KC_LBRC, KC_RBRC, KC_EQL,  KC_SCLN, KC_END,  KC_UP,   KC_HOME, KC_BSPC,
                               KC_LCTL, KC_BSLS, KC_SLSH, KC_ESC,  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_MINS,
                               KC_LSFT, KC_LGUI, KC_LALT, _______, KC_DEL,  _______, KC_PGDN , _______, KC_PGUP, KC_ENT
                               ),

  /* Raise
   * ,-----------------------------------------------------------.
   * |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  A  |  S  |  D  |  G  |  H  |  J  |  K  |  L  |  ;  |  -  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  Z  |  X  |  C  | Spc |  V  |  B  |  N  |  M  |  ,  |  .  |
   * `-----------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_3x10(
                               KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
                               KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                               KC_LSFT, KC_LGUI, KC_LALT, _______, _______, KC_LCA,  KC_COMM, KC_DOT,  KC_F11,  KC_F12
                               ),

  /* Adjust
   * ,-----------------------------------------------------------.
   * |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  A  |  S  |  D  |  G  |  H  |  J  |  K  |  L  |  ;  |  -  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |  Z  |  X  |  C  | Spc |  V  |  B  |  N  |  M  |  ,  |  .  |
   * `-----------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT_ortho_3x10(
                                KC_ESC,  DVORAK,  COLEMAK, QWERTY,  _______, _______, _______, KC_UP,   _______, KC_BSPC,
                                KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,
                                KC_LSFT, KC_LGUI, KC_LALT, _______, _______, _______, _______, _______, _______, QK_BOOT
                                )

};
