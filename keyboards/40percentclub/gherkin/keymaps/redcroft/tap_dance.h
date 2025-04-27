enum {
  TD_ENT_Z,
  TD_ENT_DOT,
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_ENT_Z] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_Z),
  [TD_ENT_DOT] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_DOT),
  };
