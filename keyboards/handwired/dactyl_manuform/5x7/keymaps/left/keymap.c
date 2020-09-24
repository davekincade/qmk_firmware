#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2

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
        KC_ESC,    KC_1,    KC_2,    KC_3,      KC_4,     KC_5,
        KC_TAB,    KC_Q,    KC_W,     KC_E,     KC_R,     KC_T,
        KC_CAPS,   KC_A,    KC_S,     KC_D,     KC_F,     KC_G,
        OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B,
                         KC_LEFT, KC_RIGHT,
                KC_BSPC,
        KC_LCTL,
        KC_LGUI,
        // right hand
        KC_6,    KC_7,    KC_8,    KC_9,      KC_0,     KC_MINS,  KC_EQL,
        KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC, KC_RBRC,
        KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT, KC_BSLS,
        KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT), MO(_FN),
                         KC_DOWN, KC_UP,
        KC_ENT, KC_SPC,
        KC_RALT),

        // KC_LEFT, KC_UP,    KC_DOWN,  KC_RGHT,
        // KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  OSM(MOD_RSFT),
        // TG(_NUMPAD), KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        // KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
        // KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_GRV,
        // KC_BSPC, KC_ENT,
        // KC_PGUP, KC_PGDN,
        // KC_LCTL, KC_LALT),

[_FN] = LAYOUT_5x7(
        // left hand
         KC_GRV,     KC_F1,     KC_F2,     KC_F3,     KC_F4,    KC_F5,
         RESET,   _______,   _______,   _______,   _______,   _______,
         _______,   _______,   _______,   _______,   _______,   _______,
        _______, _______,   _______,   _______,   _______,   _______,
                                          KC_HOME,   KC_END,
        KC_DEL, _______,
        _______,
        // right hand
         KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,
         RESET,   _______,   _______,   _______,   _______,   RGB_MOD,   RGB_TOG,
         _______,   _______,   _______,   _______,   RGB_SAI,   RGB_VAI,   RGB_HUI,
        _______,     _______,   _______,   _______,   KC_GRV,   _______,   _______,
                                          KC_PGUP,   KC_PGUP,
       _______, _______,
        _______),

[_NUMPAD] = LAYOUT_5x7(
  // left hand
  _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,
  _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,
  _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,
  _______,   _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,
                                   KC_P0,     KC_PDOT,
 _______, _______,
_______,
        // right hand
                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                    _______,  _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                                      KC_P0,     KC_PDOT,
                    _______,
        KC_PENT,
        _______)

};
