#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _SYMBOLS 1
#define _NUM 2
#define _NAV 3
#define _MOUSE 4
#define _FN 5
#define _SETTINGS 6
#define _GAMING 7

#define GUI_A MT(MOD_LGUI, KC_A)
#define ALT_S MT(MOD_LALT, KC_S)
#define CTL_D MT(MOD_LCTL, KC_D)
#define SFT_F MT(MOD_LSFT, KC_F)

#define SFT_J MT(MOD_RGUI, KC_J)
#define CTL_K MT(MOD_RALT, KC_K)
#define ALT_L MT(MOD_RCTL, KC_L)
#define GUI_SCLN MT(MOD_RSFT, KC_SCLN)

#define REDO2 LCTL(KC_Y)

#define ENT_NUM LT(_NUM, KC_ENT)
#define SPC_NAV LT(_NAV, KC_SPC)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOLS, // PROGRAMMING SYMBOLS
  NUM,
  NAV,
  MOUSE,
  FN,
  SETTINGS,
  GAMING,
  PREVWIN,
  NEXTWIN,
  REDO
};

// Tap Dance Code //

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap Dance Declarations
enum {
    SYM_FN_LAYER,
    ESC_GAMING
};

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void sym_fn_finished(qk_tap_dance_state_t *state, void *user_data);
void sym_fn_reset(qk_tap_dance_state_t *state, void *user_data);

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [SYM_FN_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_fn_finished, sym_fn_reset),
  [ESC_GAMING] = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _QWERTY)
};

// End Tap Dance Code //

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;


uint8_t colourDefault[] = {57, 184, 255};   //default underglow colour
uint8_t colourNum[] = {219, 76, 76};    //symbol layer underglow colour
uint8_t colourSymbol[] = {54, 204, 31};       //numpad layer underglow colour
uint8_t colourNav[] = {0, 255, 0};       //nav layer underglow colour
uint8_t colourGaming[] = {0, 0, 255};       //mouse layer underglow colour
uint8_t colourFn[] = {141, 15, 166};       //fn layer underglow colour
uint8_t colourSettings[] = {255, 255, 255};       //settings layer underglow colour
uint8_t colourMouse[] = {255, 0, 0};       //gaming layer underglow colour



int underglowLED[6] = {28, 29, 30, 31, 32, 33};
int backlightLEDinner[15] = {6, 7, 8, 9, 10, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
int backlightLEDall[28] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌───────────────────────┬────────────────────┬───────────────────┬───────────────────┬───────────────────┬────────────┐                              ┌───────────┬───────────────────────┬───────────────────┬───────────────────┬───────────────────────┬────────┐
        KC_GRV,              KC_1,                     KC_2,                KC_3,            KC_4,              KC_5,                                          KC_6,            KC_7,               KC_8,                KC_9,               KC_0,             KC_ESC,
  //├───────────────────────┼────────────────────┼───────────────────┼───────────────────┼───────────────────┼────────────┤                              ├───────────┼───────────────────────┼───────────────────┼───────────────────┼───────────────────────┼────────┼
     KC_LBRC,                  KC_Q,                     KC_W,              KC_E,            KC_R,              KC_T,                                          KC_Y,            KC_U,                KC_I,                KC_O,               KC_SCLN,           KC_QUOT,
  //├───────────────────────┼────────────────────┼───────────────────┼───────────────────┼───────────────────┼────────────┤                              ├───────────┼───────────────────────┼───────────────────┼───────────────────┼───────────────────────┼────────┼
     KC_LCBR,                  MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT, KC_F),  KC_G,                                          KC_H,      MT(MOD_RSFT, KC_J),  MT(MOD_RCTL, KC_K), MT(MOD_LALT, KC_L), MT(MOD_RGUI, KC_P),  KC_BSPC,
  //├───────────────────────┼────────────────────┼───────────────────┼───────────────────┼───────────────────┼────────────┼─────────┐           ┌────────┴───────────┼───────────────────────┼───────────────────┼───────────────────┼───────────────────────┼────────┼
     KC_TAB,                  KC_Z,                   KC_X,                 KC_C,                KC_V,          KC_B,      KC_MINUS,              KC_BSPC,     KC_N,          KC_M,               KC_COMM,              KC_DOT,              KC_SLSH,          KC_BSLS,
  //└───────────────────────┴────────────────────┴───────────────────┴───────────────────┬───────────────────┴────────────┴─────────┘           └────────┴───────────┴───────────────────────┴───────────────────┴───────────────────┴───────────────────────┴────────┘
                                                                                               PREVWIN, TD(SYM_FN_LAYER),  ENT_NUM,              SPC_NAV,  TT(_MOUSE),   NEXTWIN
                                               //                                        └──────────────┴─────────────────┴─────────┘           └────────┴────────────┴──────────┘
  ),

  [_SYMBOLS] = LAYOUT(
    //┌─────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______,      _______, _______, _______, _______, _______,                      MO(_SETTINGS), _______, _______, _______, _______, _______,
    //├─────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______,      KC_HASH, KC_PIPE, KC_AMPR, KC_EXLM, _______,                            _______, KC_LBRC, KC_RBRC,  KC_LT,   KC_GT,  _______,
    //├─────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CAPS,      KC_MINS, KC_PLUS, KC_UNDS, KC_EQL,  KC_GRV,                             _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_DEL,
    //├─────────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______,      _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    //└─────────────┴────────┴────────┴────────┴───┬────────────┼─────────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        _______,     _______,     _______,              _______, _______, _______
                                   // └────────────┴────────────┴─────────┘            └────────┴────────┴────────┘
  ),

  [_NUM] = LAYOUT(
    //┌──────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______,       _______, KC_F10, KC_F11,  KC_F12,  _______,                       MO(_SETTINGS), _______, _______, _______, _______, _______,
    //├──────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______,       _______, KC_F7,   KC_F8,   KC_F9, _______,                             _______,   KC_7,    KC_8,    KC_9,  _______,  _______,
    //├──────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______,       _______, KC_F4,   KC_F5,  KC_F6,   _______,                            _______,   KC_4,    KC_5,    KC_6,  KC_DOT, _______,
    //├──────────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______,       _______, KC_F1,  KC_F2,    KC_F3, _______, _______,          _______,  KC_0,      KC_1,    KC_2,    KC_3,  KC_COMM, _______,
    //└──────────────┴────────┴────────┴────────┴───┬────────────┼─────────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        _______,       _______,    _______,              _______, _______, _______
                                    // └────────────┴────────────┴─────────┘            └────────┴────────┴────────┘
  ),



  [_NAV] = LAYOUT(
  //┌─────────────┬─────────────┬────────┬────────┬────────┬─────────────┐                          ┌────────────┬─────────┬────────┬──────────┬───────────────┬────────┐
     _______,       _______,      _______, _______, _______, _______,                               MO(_SETTINGS), _______, _______, _______,     _______,      _______,
  //├─────────────┼─────────────┼────────┼────────┼────────┼─────────────┤                          ├────────────┼─────────┼────────┼──────────┼───────────────┼────────┤
     _______,      _______,       KC_WH_U,  KC_UP,  KC_WH_D, _______,                                  _______,    _______, KC_PGUP,  _______,     _______,     _______,
  //├─────────────┼─────────────┼────────┼────────┼────────┼─────────────┤                          ├────────────┼─────────┼────────┼──────────┼───────────────┼────────┤
     _______,      LCTL(KC_LEFT),KC_LEFT, KC_DOWN, KC_RIGHT,LCTL(KC_RIGHT),                           _______,    KC_HOME,  KC_PGDN, KC_END,     _______,       _______,
  //├─────────────┼─────────────┼────────┼────────┼────────┼─────────────┼────────┐        ┌────────┼────────────┼─────────┼────────┼──────────┼───────────────┼────────┤
     _______,        _______,    _______, _______, _______, _______,      _______,          _______,  _______,    _______,  _______, _______,    _______,       _______,
  //└─────────────┴─────────────┴────────┴┬───────┴───┬────┴───────┬─────┴────┬───┘        └───┬─────────────────┴─────────┴────────┴──────────┴───────────────┴────────┴
                                             _______,   _______,    _______,                     _______,          _______,       _______
                                      //  └───────────┴────────────┴──────────┘                 └─────────────┴──────────────┴────────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌─────────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,      _______, _______, _______, _______, _______,                       MO(_SETTINGS), _______, _______, _______, _______, _______,
  //├─────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,      _______, _______, KC_MS_U, _______, _______,                            _______, KC_WH_L, KC_WH_U, KC_WH_R, _______, _______,
  //├─────────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,      _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                            _______, KC_BTN1, KC_WH_D, KC_BTN2, _______, _______,
  //├─────────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,      _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└─────────────┴────────┴────────┴────────┴───┬────────────┼─────────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______,      _______,     _______,              _______, _______, _______
                                 // └────────────┴────────────┴─────────┘            └────────┴────────┴────────┘
  ),

  [_FN] = LAYOUT(
    //┌────────┬────────┬───────────┬──────────┬────────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬───────────┐
       _______,  _______, _______,    _______,    _______,    _______,                      MO(_SETTINGS), _______, _______, _______, _______, _______,
    //├────────┼────────┼───────────┼──────────┼────────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼───────────┤
       _______, _______, LCTL(KC_Z),    REDO,       REDO2,    _______,                           _______, KC_VOLD, KC_VOLU, _______, _______,  _______,
    //├────────┼────────┼───────────┼──────────┼────────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼───────────┤
       _______, _______, LCTL(KC_C), LCTL(KC_X), LCTL(KC_V), _______,                            _______, _______, _______, _______,  _______,  _______,
    //├────────┼────────┼───────────┼──────────┼────────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼───────────┤
       _______, _______, _______,     _______,    _______,    _______, _______,          _______, _______,KC_MSTP, KC_MPLY, _______, _______,  _______,
    //└────────┴────────┴───────────┴─────┬────┴───────┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴───────────┘
                                              _______,  _______, _______,                   _______, _______, _______
                                       // └────────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


[_SETTINGS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬───────────┐
      RESET,  _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, TG(_GAMING),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼───────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼───────────┤
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼───────────┤
     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴───────────┘
                                    _______,  _______,_______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_GAMING] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────────┐
       _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,TD(ESC_GAMING),
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────┤
       KC_LALT, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────────┤
       KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,  _______,                            _______,   KC_J,    KC_K,    KC_L,  KC_SCLN,   KC_ENT,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────────┤
       KC_LCTL, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────────┘
                                      _______,  KC_NO,  KC_SPC,                    KC_SPC,   KC_NO,  _______
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SFT_F:
    case SFT_J:
      return TAPPING_TERM - 30;
    case GUI_SCLN:
    case GUI_A:
      return TAPPING_TERM + 70;
    case TD(SYM_FN_LAYER):
      return TAPPING_TERM * 3;
    default:
      return TAPPING_TERM;
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case SYMBOLS:
      if (record->event.pressed) {
        layer_on(_SYMBOLS);
        update_tri_layer(_SYMBOLS, _SETTINGS, _GAMING);
      } else {
        layer_off(_SYMBOLS);
        update_tri_layer(_SYMBOLS, _SETTINGS, _GAMING);
      }
      return false;
      break;

    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_NAV, _SETTINGS, _GAMING);
      } else {
        layer_off(_NAV);
        update_tri_layer(_NAV, _SETTINGS, _GAMING);
      }
      return false;
      break;

    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
        update_tri_layer(_MOUSE, _SETTINGS, _GAMING);
      } else {
        layer_off(_MOUSE);
        update_tri_layer(_MOUSE, _SETTINGS, _GAMING);
      }
      return false;
      break;

    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
      break;


    case SETTINGS:
      if (record->event.pressed) {
        layer_on(_SETTINGS);
      } else {
        layer_off(_SETTINGS);
      }
      return false;
      break;

    case GAMING:
      if (record->event.pressed) {
        layer_on(_GAMING);
      } else {
        layer_off(_GAMING);
      }
      return false;
      break;

    case NEXTWIN: // ALT+TAB
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    case PREVWIN: // ALT+SHIFT+TAB
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code16(S(KC_TAB));
      } else {
        unregister_code16(S(KC_TAB));
      }
      break;

    case REDO:
      if (record->event.pressed) {
        register_code16(S(LCTL(KC_Z)));
      } else {
        unregister_code16(S(LCTL(KC_Z)));
      }
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 600) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    return TD_SINGLE_HOLD;
  } else if (state->count == 2) {
    return TD_DOUBLE_HOLD;
  }
  else {
    return TD_UNKNOWN;
  }
}

// Initialize tap structure associated with example tap dance key
static td_tap_t sym_fn_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

// Functions that control what our tap dance key does
void sym_fn_finished(qk_tap_dance_state_t *state, void *user_data) {
  sym_fn_tap_state.state = cur_dance(state);
  switch (sym_fn_tap_state.state) {
    case TD_SINGLE_HOLD:
      layer_on(_SYMBOLS);
      break;
    case TD_DOUBLE_HOLD:
      layer_on(_FN);
      break;
    default:
      break;
  }
}

void sym_fn_reset(qk_tap_dance_state_t *state, void *user_data) {
  // If the key was held down and now is released then switch off the layer
  switch (sym_fn_tap_state.state)
  {
    case TD_SINGLE_HOLD:
      layer_off(_SYMBOLS);
      break;
    case TD_DOUBLE_HOLD:
      layer_off(_FN);
      break;
    default:
      break;
  }

  sym_fn_tap_state.state = TD_NONE;
}

void set_backlight(uint8_t colours[3])
{
  for (int i = 0; i < 6; i++) {
    rgb_matrix_set_color(underglowLED[i], colours[0], colours[1], colours[2]);
  }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {   //RGB
  if (host_keyboard_led_state().caps_lock) {                                 //caps lock backlight
    rgb_matrix_set_color(25, RGB_RED);
    rgb_matrix_set_color(12, RGB_RED);
  }

  for (uint8_t i = led_min; i <= led_max; i++) {
    switch(get_highest_layer(layer_state|default_layer_state)) { //layers underglow
      case _NUM:
//        for (int j = 0; j < 28; ++j) {
//          rgb_matrix_set_color(backlightLEDall[j], colourNum[0], colourNum[1], colourNum[2]);
//        }
        set_backlight(colourNum);
        break;
      case _SYMBOLS:
        set_backlight(colourSymbol);
        break;
      case _MOUSE:
        set_backlight(colourMouse);
        break;
      case _NAV:
        set_backlight(colourNav);
        break;
      case _FN:
        set_backlight(colourFn);
        break;
      case _SETTINGS:
        set_backlight(colourSettings);
        break;
      case _GAMING:
        set_backlight(colourGaming);
        break;
      default:
        set_backlight(colourDefault);
        break;
    }
  }
}