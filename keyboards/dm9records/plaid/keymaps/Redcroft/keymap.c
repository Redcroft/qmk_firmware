/* 2019
 * Takuya Copyright Urakawa (dm9records.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "timer.h"
#include "stdlib.h"


enum plaid_layers {
  _COLEMAK,
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum plaid_keycodes {
  LED_1 = SAFE_RANGE,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0,
  SCRATCH
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)
#define COLEMAK PDF(_COLEMAK)
#define DVORAK PDF(_DVORAK)

#define ESC_CTL LCTL_T(KC_ESC)

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
  KC_LCTL,
  KC_RCTL,
  KC_LALT,
  KC_RALT,
  KC_LSFT,
  KC_RSFT,
  KC_LGUI,
  KC_RGUI,
  ESC_CTL,
  SC_SENT,
  LOWER,
  RAISE
};

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_ENTER 5 // On with enter key

// Timer for blinking LEDs
static uint16_t blink_timer = 0;
static uint16_t blink_delay = 500;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Colemak
   * ,-----------------------------------------------------------------------.
   * | Tab |  Q  |  W  |  F  |  P  |  B  |  J  |  L  |  U  |  Y  |  ;  |  '  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * | Ctl |  A  |  R  |  S  |  T  |  D  |  M  |  N  |  E  |  I  |  O  |  -  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * | Sft |  Z  |  X  |  C  |  D  |  V  |  K  |  H  |  ,  |  .  |  /  |Sent |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * | Ctl |Scrth| Sup | Alt | Spc | Lwr | Rse | Bsp | Sup | PDn | PUp |Sent |
   * `-----------------------------------------------------------------------'
   */
  [_COLEMAK] = LAYOUT_ortho_4x12(
                                 KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT,
                                 ESC_CTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_MINUS,
                                 KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
                                 KC_LCTL, SCRATCH, KC_LGUI, KC_LALT, KC_SPC,  LOWER,   RAISE,   KC_BSPC, KC_LGUI, KC_PGDN, KC_PGUP, SC_SENT
                                 ),

  /* Qwerty
   * ,-----------------------------------------------------------------------.
   * |     |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     |
   * `-----------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_ortho_4x12(
                                _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
                                _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
                                _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                                ),

  /* Dvorak
   * ,-----------------------------------------------------------------------.
   * |     |  "  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |  A  |  O  |  E  |  U  |  I  |  D  |  H  |  T  |  N  |  S  |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |  ;  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     |
   * `-----------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_ortho_4x12(
                                _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______,
                                _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    _______,
                                _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                                ),

  /* Lower
   * ,-----------------------------------------------------------------------.
   * |  ~  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  | F12 |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     | Mute| Vol-| Vol+| Esc | Sup |     |     |  [  |  ]  |  #  |  \  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     |
   * `-----------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_ortho_4x12(
                               KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,      KC_F8,      KC_F9,   KC_F10,  KC_F11,
                               _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,       KC_8,       KC_9,    KC_0,    KC_F12,
                               _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_ESC,  KC_LGUI, _______, _______,    KC_LBRC,    KC_RBRC, KC_HASH, KC_BSLS,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
                               ),

  /* Raise
   * ,-----------------------------------------------------------------------.
   * |  `  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  =  |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     | Lft | Dwn |  Up | Rgt |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |  ⏮  |  ⏯  |  ⏭  |     |     | Del | Hme | Pdn | Pup | End |     |
   * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
   * |     |     |     |     |     |     |     |     |     |     |     |     |
   * `-----------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_4x12(
                               KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_EQL,
                               _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
                               _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_DEL,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   _______,
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
                               ),


  /* Adjust (Lower + Raise)
   * ,-----------------------------------------------------------------------------------.
   * |      |Colemk|Qwerty|Dvorak|      |      |      |      |      |      |      | RBT  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      | G ON | G MOD| G BLK| G KEY| G ENT|      |      |      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      | R ON | R MOD| R BLK| R KEY| R ENT|      |      |      |      |      | CLR  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      | BOOT |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] = LAYOUT_ortho_4x12(
                                _______, COLEMAK, QWERTY,  DVORAK,  _______, _______, _______, _______, _______, _______, _______, QK_RBT,
                                _______, LED_2,   LED_4,   LED_6,   LED_8,   LED_0,   _______, _______, _______, _______, _______, _______,
                                _______, LED_1,   LED_3,   LED_5,   LED_7,   LED_9,   _______, _______, _______, _______, _______, EE_CLR,
                                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT
                                )


};

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
  // set LED pin modes
  gpio_set_pin_output(LED_RED);
  gpio_set_pin_output(LED_GREEN);

  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
    gpio_write_pin_high(LED_RED);
  }

  if(led_config.green_mode == LEDMODE_ON) {
    gpio_write_pin_high(LED_GREEN);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_ON;
  led_config.green_mode = LEDMODE_KEY;
  eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_scan_user(void) {
  if (led_config.red_mode == LEDMODE_BLINKIN) {
    if (timer_elapsed(blink_timer) > blink_delay) {
      gpio_write_pin(LED_RED, !gpio_read_pin(LED_RED));
      blink_delay = (rand() % 600) + 40;
      blink_timer = timer_read();
    }
  }
  if (led_config.green_mode == LEDMODE_BLINKIN) {
    if (timer_elapsed(blink_timer) > blink_delay) {
      gpio_write_pin(LED_GREEN, !gpio_read_pin(LED_GREEN));
      blink_delay = (rand() % 600) + 40;
      blink_timer = timer_read();
    }
  }
}

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
  switch (led_mode) {
  case LEDMODE_MODS:
    for (int i=0;i<ARRAY_SIZE(modifiers);i++) {
      if(keycode==modifiers[i]) {
        if (record->event.pressed) {
          gpio_write_pin_high(led);
        }
        else {
          gpio_write_pin_low(led);
        }
      }
    }
    break;
  case LEDMODE_KEY:
    if (record->event.pressed) {
      gpio_write_pin_high(led);
      return;
    }
    else {
      gpio_write_pin_low(led);
      return;
    }
    break;
  case LEDMODE_ENTER:
    if (keycode==KC_ENT) {
      gpio_write_pin_high(led);
    }
    else {
      gpio_write_pin_low(led);
    }
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_ENTER) {
    led_keypress_update(LED_RED, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_ENTER) {
    led_keypress_update(LED_GREEN, led_config.green_mode, keycode, record);
  }
  switch (keycode) {
  case LED_1:
    if (record->event.pressed) {
      if (led_config.red_mode==LEDMODE_ON) {
        led_config.red_mode=LEDMODE_OFF;
        gpio_write_pin_low(LED_RED);
      }
      else {
        led_config.red_mode=LEDMODE_ON;
        gpio_write_pin_high(LED_RED);
      }
    }
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_2:
    if (record->event.pressed) {
      if (led_config.green_mode==LEDMODE_ON) {
        led_config.green_mode=LEDMODE_OFF;
        gpio_write_pin_low(LED_GREEN);
      }
      else {
        led_config.green_mode=LEDMODE_ON;
        gpio_write_pin_high(LED_GREEN);
      }
    }
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_3:
    led_config.red_mode=LEDMODE_MODS;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_4:
    led_config.green_mode=LEDMODE_MODS;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_5:
    led_config.red_mode=LEDMODE_BLINKIN;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_6:
    led_config.green_mode=LEDMODE_BLINKIN;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_7:
    led_config.red_mode=LEDMODE_KEY;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_8:
    led_config.green_mode=LEDMODE_KEY;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_9:
    led_config.red_mode=LEDMODE_ENTER;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case LED_0:
    led_config.green_mode=LEDMODE_ENTER;
    eeconfig_update_user(led_config.raw);
    return false;
    break;
  case SCRATCH:
    if (record->event.pressed) {
      register_code(KC_LGUI);
      register_code(KC_MINUS);
    } else {
      unregister_code(KC_MINUS);
      unregister_code(KC_LGUI);
    }
    return false;
    break;
  }
  return true;
}
