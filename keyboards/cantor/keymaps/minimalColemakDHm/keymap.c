// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _SYMBOL  1
#define _DIGITS  2
#define _NUMWORD 3
#define _I3 4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_split_3x6_3(
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │ Q │ W │ F │ P │ B │       │ J │ L │ U │ Y │ : │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sht│ A │ R │ S │ T │ G │       │ M │ N │ E │ I │ O │Sft│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ Z │ X │ C │ D │ V │       │ K │ H │ , │ . │ / │Ctl│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤AlG│
      *               └───┤Spc├───┐   ┌───┤Ent├───┘
      *                   └───┤Bsp│   │Tab├───┘
      *                       └───┘   └───┘
      */
        KC_TAB,        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,     KC_J,    KC_L,    KC_U,    KC_Y,    KC_COLN, KC_QUOTE,
        OSM(MOD_LSFT), KC_A,    KC_R,    KC_S,    KC_T,    KC_G,     KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    OSM(MOD_RSFT),
        KC_LCTL,       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,     KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                                     LM(_I3, MOD_LGUI), LT(_DIGITS, KC_SPC),  KC_BSPC,    KC_TAB, LT(_SYMBOL, KC_ENT), MT(MOD_RALT, KC_ESC)
    ),
    [_SYMBOL] = LAYOUT_split_3x6_3(
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │ $ │ { │ } │ " │ | │       │ ' │ ! │ _ │ @ │ : │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │ # │ ( │ ) │ ; │ ~ │       │ * │ = │ / │ + │ - │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │ % │ [ │ ] │ ^ │ \ │       │ & │ ' │ < │ > │ ? │   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤Del│   │   ├───┘
      *                       └───┘   └───┘
      */
         KC_NO, KC_DLR,  KC_LCBR, KC_RCBR, KC_DQUO, KC_PIPE,    KC_QUOTE,    KC_EXLM,  KC_UNDS,  KC_AT,   KC_COLN,  KC_NO,
         KC_NO, KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_TILD,    KC_ASTR,     KC_EQUAL, KC_SLASH, KC_PLUS, KC_MINUS, KC_NO,
         KC_NO, KC_PERC, KC_LBRC, KC_RBRC, KC_CIRC, KC_BSLS,    KC_AMPR,     KC_GRAVE, KC_LABK,  KC_RABK, KC_QUES,  KC_NO,
                                    KC_NO,   KC_NO,  KC_DEL,    KC_NO,    KC_NO,    KC_NO
    ),
    [_NUMWORD] = LAYOUT_split_3x6_3(
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │BOT│   │   │   │   │   │       │   │   │   │   │   │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │   │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │   │ x │   │   │   │       │   │   │ , │ . │   │   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
         QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO,   KC_NO,  KC_NO, KC_NO,
         KC_NO, KC_1,  KC_2,  KC_3,  KC_4,  KC_5,     KC_6,  KC_7,  KC_8,    KC_9,   KC_0,  KC_NO,
         KC_NO, KC_X,  KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_COMM, KC_DOT, KC_NO, KC_NO,
                              KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO
    ),
    [_DIGITS] = LAYOUT_split_3x6_3(
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │   │ F1│ F2│ F3│ F4│ F5│       │ F6│ F7│ F8│ F9│F10│F11│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │F12│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │   │   │   │   │   │       │   │ ← │ ↓ │ ↑ │ → │   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤   │   │   ├───┘
      *                       └───┘   └───┘
      */
         KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,    KC_F6, KC_F7,   KC_F8,   KC_F9, KC_F10,    KC_F11,
         KC_NO, KC_1,  KC_2,  KC_3,  KC_4,  KC_5,     KC_6,  KC_7,    KC_8,    KC_9,  KC_0,      KC_F12,
         KC_NO, KC_X,  KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,  KC_NO,
                              KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO
    ),
    [_I3] = LAYOUT_split_3x6_3(
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Pus│ 1 │ 2 │ 3 │ 4 │ 0 │       │ F6│ F7│ F8│ F9│F10│F11│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │   │ A │ R │ F │ T │Sh=│       │ F1│ ← │ ↓ │ ↑ │ → │F12│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │ShQ│   │   │   │   │Sh │       │   │ / │ = │ - │ \ │   │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │   ├───┐           ┌───┤   │
      *               └───┤   ├───┐   ┌───┤Spc├───┘
      *                   └───┤   │   │Ent├───┘
      *                       └───┘   └───┘
      */
         KC_PAUS,    KC_1, KC_2,  KC_3,  KC_4,  KC_0,           KC_F6, KC_F7,    KC_F8,   KC_F9,    KC_F10,   KC_F11,
         KC_NO,      KC_A, KC_R,  KC_F,  MT(MOD_RSFT, KC_T),  RSFT(KC_EQUAL),    KC_F1, MT(MOD_LSFT, KC_LEFT),  KC_DOWN, KC_UP,    KC_RIGHT, KC_F12,
         RSFT(KC_Q), KC_X, KC_NO, KC_NO, KC_NO, RSFT(KC_SPC),   KC_NO, KC_SLASH, KC_EQUAL,   KC_MINUS, KC_BSLS,  KC_NO,
                                  KC_NO, KC_NO, KC_NO,          KC_ENT,   KC_SPC, KC_NO
 )
};

enum combos {
 CtrlR,
 CtrlP,
 AltDot,
};

const uint16_t PROGMEM ctrlR_combo[] = { KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM ctrlP_combo[] = { KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM altDot_combo[] = { KC_COMMA, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(ctrlR_combo, RCTL(KC_R)),
    COMBO(ctrlP_combo, LCTL(KC_P)),
    COMBO(altDot_combo, LALT(KC_DOT)),
};

