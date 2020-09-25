#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LYR 1
#define _FN     2

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
        {0, 1, HSV_RED},   // Light 4 LEDs, starting with LED 6
        {9, 1, HSV_RED}   // Light 4 LEDs, starting with LED 12
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

enum custom_keycodes {
        //   KC_INTE = SAFE_RANGE,
        //   KC_CURS,
        //   KC_SCRL,
        //   KC_CHRT,
        //   KC_SCLN_INV,
        // KC_BSPC_LCTL,
        // KC_DEL_ALT,
        // KC_ENT_LGUI,
        // KC_SPC_LSFT,
        KC_MO0 = SAFE_RANGE,
        KC_MO1,
        KC_MO2,
        KC_CPI_1,
        KC_CPI_2,
        KC_CPI_3,
        KC_INTE
};

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
                KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3),

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
                _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,
                KC_TAB, KC_TILD, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,
                KC_HOME,   KC_END,
                KC_LCTL, _______, KC_LGUI,
                KC_ENT, KC_DEL,
                // right hand
                KC_6,    KC_7,    KC_8,    KC_9,      KC_0, _______,
                KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
                KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, _______, _______,
                KC_PGDOWN, KC_PGUP,
                KC_CPI_1, KC_CPI_2, KC_CPI_3
                ),

        [_FN] = LAYOUT_5x7(
                // left hand
                KC_F12,     KC_F1,     KC_F2,     KC_F3,     KC_F4,    KC_F5,
                _______,   KC_INTE,   _______,   _______,   _______,   RESET,
                _______, RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI,
                _______, _______,
                _______, _______, _______,
                _______, _______,
                // right hand
                KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,
                RESET,   _______,   _______,   _______,   RGB_MOD,   RGB_TOG,
                _______,   _______, _______,   RGB_SAI,   RGB_VAI,   RGB_HUI,
                _______,   _______,
                KC_MO0, KC_MO1, KC_MO2
                )

};

#include "pointing_device.h"
#include "../../pmw3360/pmw3360.h"
#define SCROLL_DIVIDER 12
#define CPI_1 6000
#define CPI_2 10000
#define CPI_3 11000
#define CLAMP_HID(value) value < -127 ? -127 : value > 127 ? 127 : value

uint8_t trackMode = 0; // 0 Mousecursor; 1 arrowkeys/carret; 2 scrollwheel; 3 sound/brightness
uint8_t prev_trackMode = 0;
bool integrationMode = false;
int16_t cumi_x = 0;
int16_t cumi_y = 0;
uint8_t r_counter = 0;

// Triggers help to move only horizontal or vertical. When accumulated distance triggeres, only move one discrete value in direction with bigger delta.
uint16_t carret_trigger = 28;     // higher means slower
uint8_t scroll_trigger = 8;

float cursor_multiplier = 1.6;    // adjust cursor speed
uint8_t integration_divisor = 100; // slow down every mode in integration mode

void on_mouse_button(uint8_t mouse_button, bool pressed) {
        report_mouse_t report = pointing_device_get_report();

        if(pressed)
                report.buttons |= mouse_button;
        else
                report.buttons &= ~mouse_button;
        pointing_device_set_report(report);
        pointing_device_send();
}

void pointing_device_init(void){
        if(!is_keyboard_master())
                return;

        pmw_init();
}

int16_t cum_x = 0;
int16_t cum_y = 0;

void tap_tb(int16_t delta, uint16_t keycode0, uint16_t keycode1) {
        if(delta > 0) {
                tap_code(keycode0);
        } else if(delta < 0) {
                tap_code(keycode1);
        }
}

int16_t clamped_x;
int16_t clamped_y;
int sign(int x) {
        return (x > 0) - (x < 0);
}

void report_squal(int val) {
  char snum[5];
  itoa(val, snum, 10);
  SEND_STRING(" ");
  send_string(snum);
}

void pointing_device_task(void){
        if(!is_keyboard_master())
                return;

        report_mouse_t mouse_report = pointing_device_get_report();
        report_pmw_t pmw_report = pmw_get_report();

        if (integrationMode) {
                cumi_x += pmw_report.x;
                cumi_y += pmw_report.y;
                if (trackMode == 1) { //carret
            			clamped_x = CLAMP_HID(cumi_x / (integration_divisor / 20));
            			clamped_y = CLAMP_HID(cumi_y / (integration_divisor / 20));
            		} else if (trackMode == 2) { //scroll
            			clamped_x = CLAMP_HID(cumi_x / integration_divisor);
            			clamped_y = CLAMP_HID(cumi_y / integration_divisor);
            		} else { //cursor
            			clamped_x = CLAMP_HID(cumi_x / (integration_divisor));
            			clamped_y = CLAMP_HID(cumi_y / (integration_divisor));
            		}
        } else {
                clamped_x = CLAMP_HID(pmw_report.x);
                clamped_y = CLAMP_HID(pmw_report.y);
        }
        if (trackMode == 0) { //cursor (0)
                mouse_report.x = (int)( clamped_x * cursor_multiplier);
                mouse_report.y = (int)(-clamped_y * cursor_multiplier);
        } else if (trackMode == 1) { //carret (1)
                cum_x = cum_x + clamped_x;
                cum_y = cum_y + clamped_y;
                if(abs(cum_x) + abs(cum_y) >= carret_trigger) {
                        if(abs(cum_x) > abs(cum_y)) {
                                tap_tb(cum_x, KC_RIGHT, KC_LEFT);
                        } else {
                                tap_tb(cum_y,  KC_UP, KC_DOWN  );
                        }
                        cum_x = 0;
                        cum_y = 0;
                }
        } else if(trackMode == 2) { //scroll
                // accumulate scroll untill triggered
                cum_x = cum_x + clamped_x;
                cum_y = cum_y + clamped_y;
                if(abs(cum_x) + abs(cum_y) >= scroll_trigger) {
                        if(abs(cum_x) > abs(cum_y)) {
                                mouse_report.h = sign(cum_x);
                        } else {
                                mouse_report.v = sign(cum_y);
                        }
                        cum_x = 0;
                        cum_y = 0;
                }
        } else { // sound vol/brightness (3)
                cum_x = cum_x + clamped_x;
                cum_y = cum_y + clamped_y;
                if(abs(cum_x) + abs(cum_y) >= carret_trigger) {
                        if(abs(cum_x) > abs(cum_y)) {
                                tap_tb(cum_x, KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN);
                        } else {
                                tap_tb(cum_y, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN);
                        }
                        cum_x = 0;
                        cum_y = 0;
                }
        }

        // if (r_counter++ % 1000 == 0) {
        //   r_counter = 0;
        //   send_string("x");
        //   report_squal(mouse_report.x);
        //   send_string("y");
        //   report_squal(mouse_report.y);
        // }

        pointing_device_set_report(mouse_report);
        pointing_device_send();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
        if(!process_record_user(keycode, record)) {
                return false;
        }

        // handle mouse drag and scroll
        switch (keycode) {
        case KC_BTN1:
                on_mouse_button(MOUSE_BTN1, record->event.pressed);
                return false;

        case KC_BTN2:
                on_mouse_button(MOUSE_BTN2, record->event.pressed);
                return false;

        case KC_BTN3:
                on_mouse_button(MOUSE_BTN3, record->event.pressed);
                return false;

        case KC_BTN4:
                on_mouse_button(MOUSE_BTN4, record->event.pressed);
                return false;

        case KC_BTN5:
                on_mouse_button(MOUSE_BTN5, record->event.pressed);
                return false;

        case KC_CPI_1:
                if (cursor_multiplier > 0.2)
                      cursor_multiplier = cursor_multiplier - 0.2;

                return false;

        case KC_CPI_2:
                cursor_multiplier = 1.6;
                return false;

        case KC_CPI_3:
                cursor_multiplier = cursor_multiplier + 0.2;
                return false;

        case KC_MO0:
                prev_trackMode = trackMode;
                trackMode = 0;
                cumi_x = 0;
	  		        cumi_y = 0;
                return false;

        case KC_MO1:
                prev_trackMode = trackMode;
                trackMode = 1;
                cumi_x = 0;
	  		        cumi_y = 0;
                return false;

        case KC_MO2:
                prev_trackMode = trackMode;
                trackMode = 2;
                cumi_x = 0;
	  		        cumi_y = 0;
                return false;

        case KC_INTE:
                integrationMode = !integrationMode;
                cumi_x = 0;
	  		        cumi_y = 0;
                return false;

        default:
                return true;
        }
}

#ifndef POLLING
ISR(INT2_vect) {
        motion_time = timer_read32() + 50;
}
#endif
