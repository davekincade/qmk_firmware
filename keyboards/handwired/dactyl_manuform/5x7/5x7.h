#pragma once

#include "dactyl_manuform.h"
#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avR/io.h>
  #include <avR/inteRRupt.h>
#endif
#endif

#define LAYOUT_5x7( \
    L11, L12, L13, L14, L15, L16,     \
    L21, L22, L23, L24, L25, L26,     \
    L31, L32, L33, L34, L35, L36,     \
              L41, L42, \
                        L43, L44, L45, \
                             L51, L52, \
        R11, R12, R13, R14, R15, R16, \
        R21, R22, R23, R24, R25, R26, \
        R31, R32, R33, R34, R35, R36, \
                       R44, R45, \
        R41, R42, R43                            \
  ) \
  { \
    { L11,   L12,   L13, L14, L15, L16,   KC_NO }, \
    { L21,   L22,   L23, L24, L25, L26,   KC_NO }, \
    { L31,   L32,   L33, L34, L35, L36,   KC_NO }, \
    { KC_NO, L41,   L42,   L43, L44, L45, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, L51, L52, KC_NO }, \
    { R11,   R12,   R13, R14, R15, R16,   KC_NO   }, \
    { R21,   R22,   R23, R24, R25, R26,   KC_NO   }, \
    { R31,   R32,   R33, R34, R35, R36,   KC_NO   }, \
    { R41,   R42,   R43, R44, R45, KC_NO,   KC_NO   }, \
    { KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO   }, \
}
