// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "features/achordion.h"

#define _DEFAULT 0
#define _SYMBOL 1
#define _DIGITS 2
#define _NUMWORD 3
#define _I3 4

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)
// #define HOME_W RALT_T(KC_W)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)
// #define HOME_Y RALT_T(KC_Y)


static uint16_t num_word_timer = 0;
static bool is_num_word_on = false;

enum userspace_custom_keycodes {
    NUMWORD,
};

enum combos {
    CtrlR,
    CtrlP,
    AltDot,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_DEFAULT] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
       * │   │ Q │ W │ F │ P │ B │       │ J │ L │ U │ Y │ : │   │
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │   │ A │ R │ S │ T │ G │       │ M │ N │ E │ I │ O │   │
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │   │ Z │ X │ C │ D │ V │       │ K │ H │ , │ . │ / │   │
       * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
       *               ┌───┐                   ┌───┐
       *               │GUI├───┐           ┌───┤AlG│
       *               └───┤Spc├───┐   ┌───┤Ent├───┘
       *                   └───┤Bsp│   │Tab├───┘
       *                       └───┘   └───┘
       */
                   KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B,     KC_J, KC_L, KC_U, KC_Y, KC_COLN, KC_NO,
                   KC_NO, HOME_A, HOME_R, HOME_S, HOME_T, KC_G, KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_NO,
                   KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,     KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
         LT(_I3, KC_NO), LT(_DIGITS, KC_SPC), KC_BSPC,      KC_TAB, LT(_SYMBOL, KC_ENT), MT(MOD_RALT, KC_ESC)),
  [_SYMBOL] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
       * │   │ $ │ { │ } │ " │   │       │   │ ! │ _ │ @ │   │   │
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │   │ # │ ( │ ) │ ; │ ~ │       │ * │ = │ | │ + │ - │   │
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │   │ % │ [ │ ] │ ^ │ \ │       │ & │ ' │ < │ > │ ? │   │
       * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
       *               ┌───┐                   ┌───┐
       *               │   ├───┐           ┌───┤   │
       *               └───┤   ├───┐   ┌───┤   ├───┘
       *                   └───┤Del│   │   ├───┘
       *                       └───┘   └───┘
       */
                   KC_NO, KC_DLR,  KC_LCBR, KC_RCBR, KC_DQUO, KC_PIPE,    KC_NO,   KC_EXLM, KC_UNDS, KC_AT, KC_NO, KC_NO,
                   KC_NO, KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_TILD,    KC_ASTR, KC_EQUAL, KC_PIPE, KC_PLUS, KC_MINUS, KC_NO,
                   KC_NO, KC_PERC, KC_LBRC, KC_RBRC, KC_CIRC, KC_BSLS,    KC_AMPR, KC_GRAVE, KC_LABK, KC_RABK, KC_QUES, KC_NO,
                                                KC_NO, KC_NO, KC_DEL,     KC_NO, KC_NO, KC_NO),

  [_NUMWORD] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
       * │BOT│   │   │   │   │   │       │   │   │   │   │   │RST│
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │   │ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │   │
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │   │   │ x │   │   │   │       │   │   │ , │ . │   │   │
       * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
       *               ┌───┐                   ┌───┐
       *               │DEF├───┐           ┌───┤   │
       *               └───┤   ├───┐   ┌───┤   ├───┘
       *                   └───┤   │   │   ├───┘
       *                       └───┘   └───┘
       */
      QK_BOOT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_RBT,
      KC_TRANSPARENT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_X, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_COMM, KC_DOT, KC_TRANSPARENT, KC_TRANSPARENT,
      DF(_DEFAULT), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
  [_DIGITS] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
       * │   │ F1│ F2│ F3│ F4│ F5│       │ F6│ F7│ F8│ F9│F10│F11│
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │Shf│   │   │   │   │   │       │   │ ← │ ↓ │ ↑ │ → │F12│
       * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
       * │Ctl│ 1 │ 2 │ 3 │ 4 │ 5 │       │ 6 │ 7 │ 8 │ 9 │ 0 │Ctl│
       * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
       *               ┌───┐                   ┌───┐
       *               │   ├───┐           ┌───┤Alt│
       *               └───┤   ├───┐   ┌───┤   ├───┘
       *                   └───┤   │   │   ├───┘
       *                       └───┘   └───┘
       */
      KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
      KC_LSFT, KC_X, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F12,
      KC_LCTL, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_RCTL,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RALT),
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
       *               │   ├───┐           ┌───┤Esc│
       *               └───┤   ├───┐   ┌───┤Spc├───┘
       *                   └───┤   │   │Ent├───┘
       *                       └───┘   └───┘
       */
      LGUI(KC_BRK) , LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_0), LGUI(KC_F6), LGUI(KC_F7), LGUI(KC_F8), LGUI(KC_F9), LGUI(KC_F10), LGUI(KC_F11),
      KC_NO, LGUI(KC_A), LGUI(KC_R), LGUI(KC_F), MT((MOD_RSFT), LGUI(KC_T)), LGUI(RSFT(KC_EQUAL)), LGUI(KC_F1), LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RIGHT), LGUI(KC_F12),
      LGUI(RSFT(KC_Q)), LGUI(KC_X), KC_NO, KC_NO, KC_NO, LGUI(RSFT(KC_SPC)), KC_NO, LGUI(KC_SLASH), LGUI(KC_EQUAL), LGUI(KC_MINUS), LGUI(KC_BSLS), KC_NO, KC_NO, KC_NO, KC_NO, LGUI(KC_ENT), LGUI(KC_SPC), LGUI(KC_ESC)
)};
__attribute__ ((weak))
bool process_record_user_kb(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void enable_num_word(void) {
    if(is_num_word_on) 
    {
        return;
    }
    is_num_word_on = true;
    layer_on(_NUMWORD);
}

void disable_num_word(void) {
    if(!is_num_word_on) 
    {
        return;
    }
    is_num_word_on = false;
    layer_off(_NUMWORD);
}

void toggle_num_word(void) {
    if (is_num_word_on) {
        disable_num_word();
    }
    else {
        enable_num_word();
    }
}

bool should_terminate_num_word(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        case KC_1 ... KC_0:
        case KC_COMM:
        case KC_DOT:
        case KC_X:
            return false;
        default:
            return true;
    }

    // Should be unreachable
    return false;
}

bool process_record_num_word(uint16_t keycode, const keyrecord_t *record) {
    // Handle the custom keycodes that go with this feature
    if (keycode == NUMWORD) {
        if (record->event.pressed) {
            enable_num_word();
            num_word_timer = timer_read();
            return false;
        }
        else {
            if (timer_elapsed(num_word_timer) > TAPPING_TERM) {
                // If the user held the key longer than TAPPING_TERM,
                // consider it a hold, and disable the behavior on
                // key release.
                disable_num_word();
                return false;
            }
        }
    }

    // Other than the custom keycodes, nothing else in this feature will
    // activate if the behavior is not on, so allow QMK to handle the
    // event as usual
    if (!is_num_word_on) return true;

    // Nothing else acts on key release, either
    if (!record->event.pressed) {
        return true;
    }

    if (should_terminate_num_word(keycode, record)) {
        disable_num_word();
    }

    return true;
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record)
{
    switch(tap_hold_keycode)
    {
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        // case HOME_W:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
            break;
        // case HOME_Y:
            // special case for the apostropheCombo
            // if(other_keycode == KC_U)
            // {
            //     return false;
            // }
            // break;
        default:
            return true;
    }
    return achordion_opposite_hands(tap_hold_record, other_record);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(!process_achordion(keycode, record)) {
        return false;
    }
    switch(keycode) {
        case LT(_I3, KC_NO):
            if(record->tap.count && record->event.pressed) {
                enable_num_word();
                return false;
            }
    }
    // returns true if the QMK should handle the keycode normally and false if it is already handled
    if (!process_record_num_word(keycode, record)) {
        return false;
    }
    return process_record_user_kb(keycode, record);
}

void matrix_scan_user(void) {
  achordion_task();
}

const uint16_t PROGMEM ctrlR_combo[]  = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM ctrlP_combo[]  = {KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM altDot_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM ctrlShiftV_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM apostropheCombo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM deleteCombo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM altCombo[] = {KC_LCTL, KC_LSFT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(ctrlR_combo, RCTL(KC_R)),
    COMBO(ctrlP_combo, LCTL(KC_P)),
    COMBO(altDot_combo, LALT(KC_DOT)),
    COMBO(ctrlShiftV_combo, LSFT(LCTL(KC_V))),
    COMBO(apostropheCombo, KC_QUOTE),
    COMBO(deleteCombo, KC_DEL),
    COMBO(altCombo, OSM(MOD_LALT)),
};
