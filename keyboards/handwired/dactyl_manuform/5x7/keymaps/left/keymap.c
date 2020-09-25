#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LYR 1
#define _FN     1

// Some basic macros
#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED},       // Light 4 LEDs, starting with LED 6
    {9, 1, HSV_RED}       // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer
    // layers below this override layers above this
);

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x7(
          // left hand
          KC_ESC,    KC_Q,    KC_W,     KC_E,     KC_R,     KC_T,
          MO(_FN),    KC_A,    KC_S,     KC_D,     KC_F,     KC_G,
          OSM(MOD_LSFT), KC_Z, KC_X,    KC_C,     KC_V,     KC_B,
                              KC_LEFT, KC_RIGHT,
                                        KC_LCTL, OSL(_LYR), KC_LGUI,
                                        KC_SPC, KC_BSPC,
          // right hand
          KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,  KC_RALT,
          KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
          KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),
                           KC_DOWN, KC_UP,
          KC_ENT, KC_SPC, _______),

          // KC_LEFT, KC_UP,    KC_DOWN,  KC_RGHT,
          // KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),
          // TG(_NUMPAD), KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
          // KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
          // KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,
          // KC_BSPC, KC_ENT,
          // KC_PGUP, KC_PGDN,
          // KC_LCTL, KC_LALT),

    [_LYR] = LAYOUT_5x7(
          // left hand
          KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
          KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,
          KC_TAB, KC_TILD, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
                            KC_HOME,   KC_END,
                                       KC_LCTL, _______, KC_LGUI,
                                                KC_ENT, KC_DEL,
          // right hand
          KC_6,    KC_7,    KC_8,    KC_9,      KC_0, _______,
          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
          KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______, _______,
                            KC_PGDOWN, KC_PGUP,
          _______, _______, _______
                            ),

  [_FN] = LAYOUT_5x7(
          // left hand
           KC_F12,     KC_F1,     KC_F2,     KC_F3,     KC_F4,    KC_F5,
           _______,   _______,   _______,   _______,   _______,   RESET,
           _______, RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI,
                             _______, _______,
                                     _______, _______, _______,
                                              _______, _______,
          // right hand
           KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
           RESET,   _______,   _______,   _______,   RGB_MOD,   RGB_TOG,
           _______,   _______, _______,   RGB_SAI,   RGB_VAI,   RGB_HUI,
                               _______,   _______,
         _______, _______, _______
          )

  };
