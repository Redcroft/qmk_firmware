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

#define ESC_CTL LCTL_T(KC_ESC)
#define ALT_SPC LALT_T(KC_SPC)
#define KCT KC_TRNS
#define SUPL MO(3) //LT(_LOWER, KC_LGUI)
#define KC_MNS KC_MINUS

const uint8_t RGB_LED_BREATHING_INTERVALS[] PROGMEM = {50, 30};
const uint8_t RGBLED_TWINKLE_INTERVALS[] PROGMEM = {50, 25};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3( //Colemak
			   //,-----------------------------------------------.          ,-----------------------------------------------.
			      KC_TAB, KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,              KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_QUOT,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      ESC_CTL,KC_A,   KC_R,   KC_S,   KC_T,   KC_G,              KC_M,   KC_N,   KC_E,   KC_I,   KC_O,   KC_MNS,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,              KC_K,   KC_H,   KC_COMM,KC_DOT, KC_SLSH,SC_SENT,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			                                  KC_LALT, KC_SPC, SUPL,     MO(4), KC_BSPC, KC_LGUI \
			                               //`-----------------------'  `----------------------'
			   ),
  [1] = LAYOUT_split_3x6_3( //Qwerty
			   //,-----------------------------------------------.          ,-----------------------------------------------.
			      KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,              KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_QUOT,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KC_LCTL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,              KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_MNS,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,              KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,SC_SENT,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			                                  KC_LALT, KC_SPC, SUPL,     MO(4), KC_BSPC, KC_LGUI \
			                               //`-----------------------'  `----------------------'
			   ),
  [2] = LAYOUT_split_3x6_3( //Dvorak
			   //,-----------------------------------------------.          ,-----------------------------------------------.
			      KC_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,              KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      ESC_CTL,KC_A,   KC_O,   KC_E,   KC_U,   KC_I,              KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MNS,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KC_LSFT,KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,              KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   SC_SENT,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			                                  KC_LALT, KC_SPC, SUPL,     MO(4), KC_BSPC, KC_LGUI \
			                               //`-----------------------'  `----------------------'
			   ),
  [3] = LAYOUT_split_3x6_3(
			   //,-----------------------------------------------.          ,-----------------------------------------------.
			      KC_TILD,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,             KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KCT,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,              KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KCT,    KC_MUTE,KC_VOLD,KC_VOLU,KC_ESC,KC_LGUI,            KCT,    KCT,    KC_LBRC,KC_RBRC,KC_HASH,KC_BSLS,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			                                  KC_LALT, KC_SPC, SUPL,     MO(4), KC_BSPC, KC_LGUI \
			                               //`-----------------------'  `----------------------'
                           ),
  [4] = LAYOUT_split_3x6_3(
			   //,-----------------------------------------------.          ,-----------------------------------------------.
			      KC_GRV, KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,           KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_EQL,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      KCT,    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,DF(0),             DF(2),  KC_LEFT,KC_DOWN,KC_UP,  KC_RIGHT,KC_RCTL,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			      QK_BOOT,RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,DF(1),             KC_DEL, KC_HOME,KC_PGDN,KC_PGUP,KC_END, QK_RBT,\
			   //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
			                                  KC_LALT, KC_SPC, SUPL,     MO(4), KC_BSPC, KC_LGUI \
			                               //`-----------------------'  `----------------------'
			   ),
};
