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
#include <stdio.h>

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)
#define COLEMAK PDF(_COLEMAK)
#define DVORAK PDF(_DVORAK)

#define ESC_CTL LCTL_T(KC_ESC)
#define ALT_SPC LALT_T(KC_SPC)
#define KCT KC_TRNS
#define KC_MNS KC_MINUS

enum crkbd_layers {
  _COLEMAK,
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint8_t RGB_LED_BREATHING_INTERVALS[] PROGMEM = {50, 30};
const uint8_t RGBLED_TWINKLE_INTERVALS[] PROGMEM = {50, 25};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Colemak
   * ,-----------------------------------.     .-----------------------------------.
   * | Tab |  Q  |  W  |  F  |  P  |  B  |     |  J  |  L  |  U  |  Y  |  ;  |  '  |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * | Ctl |  A  |  R  |  S  |  T  |  D  |     |  M  |  N  |  E  |  I  |  O  |  -  |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * | Sft |  Z  |  X  |  C  |  D  |  V  |     |  K  |  H  |  ,  |  .  |  /  |Sent |
   * `-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----'
   *                   | Alt | Spc | Lwr |     | Rse | Bsp | Sup |
   *                   `-----------------'     `-----------------'
   */
  [_COLEMAK] = LAYOUT_split_3x6_3(
                                  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,             KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT,
			          ESC_CTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,             KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_MNS,
			          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,             KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
			                                     KC_LALT, KC_SPC,  MO(3),            MO(4),   KC_BSPC, KC_LGUI
			   ),

  /* Qwerty
   * ,-----------------------------------.     .-----------------------------------.
   * |     |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  |     |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |  A  |  S  |  D  |  F  |  G  |     |  H  |  J  |  K  |  L  |  ;  |     |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  /  |     |
   * `-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----'
   *                   |     |     |     |     |     |     |     |
   *                   `-----------------'     `-----------------'
   */
  [_QWERTY] = LAYOUT_split_3x6_3(
                                 _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
			         _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
			         _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
			                                    _______, _______, _______,          _______, _______, _______
			   ),

   /* Dvorak
   * ,-----------------------------------.     .-----------------------------------.
   * |     |  '  |  ,  |  .  |  P  |  Y  |     |  F  |  G  |  C  |  R  |  L  |  /  |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |  A  |  O  |  E  |  U  |  I  |     |  D  |  H  |  T  |  N  |  S  |     |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |  ;  |  Q  |  J  |  K  |  X  |     |  B  |  M  |  W  |  V  |  Z  |     |
   * `-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----'
   *                   |     |     |     |     |     |     |     |
   *                   `-----------------'     `-----------------'
   */
   [_DVORAK] = LAYOUT_split_3x6_3(
                                  _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,             KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
                                  _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,             KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    _______,
			          _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,             KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
			                                     _______, _______, _______,          _______, _______, _______
			   ),

   /* Lower
   * ,-----------------------------------.     .-----------------------------------.
   * |  ~  |  F1 |  F2 |  F3 |  F4 |  F5 |     |  F6 |  F7 |  F8 |  F9 | F10 | F11 |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |  1  |  2  |  3  |  4  |  5  |     |  6  |  7  |  8  |  9  |  0  | F12 |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     | Mute| Vol-| Vol+| Esc | Sup |     |     |     |  [  |  ]  |  #  |  \  |
   * `-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----'
   *                   |     |     |     |     |     |     |     |
   *                   `-----------------'     `-----------------'
   */
   [_LOWER] = LAYOUT_split_3x6_3(
                                 KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                                 _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
			         _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_ESC,  KC_LGUI,          _______, _______, KC_LBRC, KC_RBRC, KC_HASH, KC_BSLS,
			                                    _______, _______, _______,          _______, _______, _______
                            ),

   /* Raise
   * ,-----------------------------------.     .-----------------------------------.
   * |  `  |  !  |  @  |  #  |  $  |  %  |     |  ^  |  &  |  *  |  (  |  )  |  =  |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     | RGB | <RGB| RGB>| Val+| Cmk |     | Dvk | Lft | Dwn |  Up | Rgt | Ctl |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     | Hue+| Spd-| Spd+| Val-| Qwr |     | Del | Hme | Pdn | Pup | End |     |
   * `-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----'
   *                   |     |     |     |     |     |     |     |
   *                   `-----------------'     `-----------------'
   */
   [_RAISE] = LAYOUT_split_3x6_3(
                                KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_EQL,
                                _______, RM_TOGG, RM_PREV, RM_NEXT, RM_VALU, DF(0),            DF(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_RCTL,
			        _______, RM_HUED, RM_SPDD, RM_SPDU, RM_VALD, DF(1),            KC_DEL,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
			                                   _______, _______, _______,          _______, _______, _______
			        ),

   /* Adjust
   * ,-----------------------------------.     .-----------------------------------.
   * |     | CMK | QWR | DVK |     |     |     |     | MLFT| MRGT|     |     | RBT |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     |     |
   * |-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     | Boot|
   * `-----+-----+-----+-----+-----+-----|     |-----+-----+-----+-----+-----+-----'
   *                   |     |     |     |     |     |     |     |
   *                   `-----------------'     `-----------------'
   */
   [_ADJUST] = LAYOUT_split_3x6_3(
                                _______, COLEMAK, QWERTY,  DVORAK,  _______, _______,          _______, EH_LEFT, EH_RGHT, _______, _______, QK_RBT,
                                _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, QK_BOOT,
			                                   _______, _______, _______,          _______, _______, _______
			   ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
