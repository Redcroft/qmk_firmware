#include QMK_KEYBOARD_H
#include <stdio.h>

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)
#define COLEMAK PDF(_COLEMAK)
#define DVORAK PDF(_DVORAK)
#define GAME PDF(_GAME)

#define LWR MO(_LOWER)
#define RSE MO(_RAISE)

#define ESC_CTL LCTL_T(KC_ESC)
#define ALT_SPC LALT_T(KC_SPC)
#define KCT KC_TRNS
#define KC_MNS KC_MINUS

enum crkbd_layers {
  _COLEMAK,
  _QWERTY,
  _DVORAK,
  _GAME,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
                      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,             KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT,
                      ESC_CTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,             KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_MNS,
                      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,             KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
                      KC_LALT, KC_SPC,  LWR,            RSE,   KC_BSPC, KC_LGUI
                      ),
  [_QWERTY] = LAYOUT(
                     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
                     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
                     _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                     _______, _______, _______,          _______, _______, _______
                     ),
  [_DVORAK] = LAYOUT(
                     _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,             KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
                     _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,             KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    _______,
                     _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,             KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
                     _______, _______, _______,          _______, _______, _______
                     ),

  [_GAME] = LAYOUT(
                   KC_T, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
                   KC_G, KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
                   KC_B, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                   _______, _______, _______,          _______, _______, _______
                   ),
  [_LOWER] = LAYOUT(
                    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
                    _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_ESC,  KC_LGUI,          _______, _______, KC_LBRC, KC_RBRC, KC_HASH, KC_BSLS,
                    _______, _______, _______,          _______, _______, _______
                    ),
  [_RAISE] = LAYOUT(
                    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
                    _______, _______, _______, _______, GAME,    COLEMAK,          DVORAK,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_RCTL,
                    _______, _______, _______, _______, _______, QWERTY,           KC_DEL,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
                    _______, _______, _______,          _______, _______, _______
                    ),
  [_ADJUST] = LAYOUT(
                     _______, COLEMAK, QWERTY,  DVORAK,  GAME,    _______,          NK_TOGG, EH_LEFT, EH_RGHT, _______, _______, QK_RBT,
                     _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                     _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, QK_BOOT,
                     _______, _______, _______,          _______, _______, _______
                     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
