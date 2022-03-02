#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _SYMBOLS 1
#define _NAV 2
#define _SETTINGS 3
#define _GAMING 4

#define GUI_HOME MT(MOD_LGUI, KC_HOME)
#define ALT_PGDN MT(MOD_LALT, KC_PGDN)
#define SFT_END  MT(MOD_LSFT, KC_END)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOLS, // PROGRAMMING SYMBOLS
  NAV,
  SETTINGS,
  GAMING,
  PREVWIN,
  NEXTWIN
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌───────────────────────┬────────────────────┬───────────────────┬───────────────────┬───────────────────┬────────────┐                              ┌───────────┬───────────────────────┬───────────────────┬───────────────────┬──────────────────────┬─────────┐
        KC_GRV,              KC_1,                     KC_2,                KC_3,            KC_4,            KC_5,                                          KC_6,            KC_7,               KC_8,                KC_9,               KC_0,              KC_ESC,
  //├───────────────────────┼────────────────────┼───────────────────┼───────────────────┼───────────────────┼────────────┤                              ├───────────┼───────────────────────┼───────────────────┼───────────────────┼──────────────────────┼─────────┼
     KC_LBRC,                  KC_Q,                     KC_W,                KC_E,            KC_R,            KC_T,                                          KC_Y,            KC_U,                KC_I,                KC_O,               KC_P,            KC_BSPC,
  //├───────────────────────┼────────────────────┼───────────────────┼───────────────────┼───────────────────┼────────────┤                              ├───────────┼───────────────────────┼───────────────────┼───────────────────┼───────────────────────┼────────┼
     KC_LCBR,                  MT(MOD_LGUI, KC_A), MT(MOD_LALT, KC_S), MT(MOD_LCTL, KC_D), MT(MOD_LSFT, KC_F),  KC_G,                                          KC_H,      MT(MOD_RSFT, KC_J),  MT(MOD_RCTL, KC_K), MT(MOD_LALT, KC_L), MT(MOD_RGUI, KC_SCLN),  KC_QUOT,
  //├───────────────────────┼────────────────────┼───────────────────┼───────────────────┼───────────────────┼────────────┼─────────┐           ┌────────┴───────────┼───────────────────────┼───────────────────┼───────────────────┼───────────────────────┼────────┼
     KC_TAB,                  KC_Z,                   KC_X,                 KC_C,                KC_V,         KC_B,        KC_MINUS,            KC_EQL,     KC_N,          KC_M,               KC_COMM,              KC_DOT,              KC_SLSH,           KC_BSLS,
  //└───────────────────────┴────────────────────┴───────────────────┴───────────────────┬───────────────────┴────────────┴─────────┘           └────────┴───────────┴───────────────────────┴───────────────────┴───────────────────┴───────────────────────┴────────┘
                                                                                                PREVWIN,      MO(_MISSING),  KC_ENT,              KC_SPC,  TT(_MOUSE),  NEXTWIN
                                               //                                        └───────────────────┴────────────┴─────────┘           └────────┴────────────┴────────┘
  ),

  [_SYMBOLS] = LAYOUT(
        //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
           KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_HASH, KC_PIPE, KC_AMPR, KC_EXLM, _______,                            _______, KC_LBRC, KC_RBRC, KC_LT,    KC_GT, _______,
        //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
           _______, KC_MINS, KC_UNDS, KC_PLUS, KC_EQL,  _______,                            _______, KC_RCBR, KC_LPRN, KC_RPRN, KC_LBRC, _______
        //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
            _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        //└────────┴────────┴────────┴────────┴───┬────────────┼─────────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                       _______,  MO(_SETTINGS), _______,               _______, _______, _______
                                  // └────────────┴────────────┴─────────┘            └────────┴────────┴────────┘
  ),


[_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────────┬─────────┬────────┬──────────┬───────────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______,      _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────────┼─────────┼────────┼──────────┼───────────────┼────────┤
     _______, _______, _______, KC_PGUP, _______, _______,                             KC_WH_L,     KC_WH_U,  KC_UP,    KC_WH_D,     KC_WH_R,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────────┼─────────┼────────┼──────────┼───────────────┼────────┤
     _______, _______, GUI_HOME,ALT_PGDN, SFT_END, _______,                           LCTL(KC_LEFT),KC_LEFT,  KC_DOWN, KC_RIGHT, LCTL(KC_RIGHT), _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────────┼─────────┼────────┼──────────┼───────────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______,   _______,    _______,  _______, _______,    _______,       _______,
  //└────────┴────────┴────────┴┬────┴───┬────┴───────┬───┴────┬───┘        └───┬─────────────────┴─────────┴────────┴──────────┴───────────────┴────────┴
                                 _______,    _______,   _______,                    _______,     MO(_SETTINGS), TG(_GAMING)
                            //  └────────┴────────────┴────────┘                 └─────────────┴──────────────┴────────────┘
  ),

  [_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_MS_U, _______, _______,                            _______, _______, KC_WH_U, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                            _______, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴────────┴───┬────────────┼─────────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                _______,     MO(_SETTINGS), _______,             KC_BTN1, KC_BTN2, _______
                            // └────────────┴────────────┴─────────┘            └────────┴────────┴────────┘
  ),

  [_SETTINGS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
      RESET,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  _______,_______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

    [_GAMING] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______,   KC_A,    KC_S,    KC_D,    KC_F,  _______,                            _______,   KC_J,    KC_K,    KC_L,  KC_SCLN, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______, _______,_______,                   _______, _______,TG(_GAMING)
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case MISSING:
      if (record->event.pressed) {
        layer_on(_MISSING);
        update_tri_layer(_MISSING, _MOUSE, _SETTINGS);
      } else {
        layer_off(_MISSING);
        update_tri_layer(_MISSING, _MOUSE, _SETTINGS);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
        update_tri_layer(_MISSING, _MOUSE, _SETTINGS);
      } else {
        layer_off(_MOUSE);
        update_tri_layer(_MISSING, _MOUSE, _SETTINGS);
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
