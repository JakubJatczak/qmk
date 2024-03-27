// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H
#include "keycodes.h"

#define _DEFAULT 0
#define _SYMBOL_LEFT 1
#define _SYMBOL_RIGHT 2
#define _NAVIGATION 3
#define _NUMWORD 4
#define _I3 5

// Left-hand home row mods
#define HOME_A KC_A
#define HOME_R RALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I RALT_T(KC_I)
#define HOME_O KC_O

static uint16_t num_word_timer = 0;
static bool is_num_word_on = false;

enum userspace_custom_keycodes {
    NUMWORD=SAFE_RANGE,
    NC_0,    // empty keycodes to be able to add macro on unused keys
    NC_1,
    NC_2,
    NC_3,
};

enum combos {
    AltDot,
    apostrophe,
    delete,
    capsWord,
    numWord,
    bootloader,
    reset,
    f11,
    f12,
    dollar,
    symbol_space,
    symbol_return,
    backspace,
    esc,
    lock,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_DEFAULT] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
       * │ Q │ W │ F │ P │ B │       │ J │ L │ U │ Y │ : │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ A │ R │ S │ T │ G │       │ M │ N │ E │ I │ O │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ Z │ X │ C │ D │ V │       │ K │ H │ , │ . │ / │
       * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
       *           ┌───┐                   ┌───┐
       *           │   ├───┐           ┌───┤Alt│
       *           └───┤Bsp├───┐   ┌───┤Tab├───┘
       *               └───┤Spc│   │Ent├───┘
       *                   └───┘   └───┘
       */
                   KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B,     KC_J, KC_L, KC_U, KC_Y, KC_COLN, KC_NO,
                   KC_NO, HOME_A, HOME_R, HOME_S, HOME_T, KC_G, KC_M, HOME_N, HOME_E, HOME_I, HOME_O, KC_NO,
                   KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,     KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
         NC_3, LT(_NAVIGATION, KC_BSPC), LT(_SYMBOL_LEFT,KC_SPC),      LT(_SYMBOL_RIGHT, KC_ENT), LT(_I3, KC_TAB), MT(MOD_LALT, KC_ESC)),
  [_SYMBOL_LEFT] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
       * │   │   │   │   │   │       │   │ ! │ _ │ @ │   │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ 6 │ 4 │ 0 │ 2 │   │       │ * │ = │ | │ + │ - │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │   │   │   │ 8 │   │       │ & │ ' │ < │ > │ ? │
       * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
       *           ┌───┐                   ┌───┐
       *           │   ├───┐           ┌───┤   │
       *           └───┤   ├───┐   ┌───┤   ├───┘
       *               └───┤   │   │Ent├───┘
       *                   └───┘   └───┘
       */
                   KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO,   KC_EXLM, KC_UNDS, KC_AT, KC_NO, KC_NO,
                   KC_NO, KC_6, KC_4, KC_0, KC_2, KC_NO,            KC_ASTR, KC_EQUAL, KC_PIPE, KC_PLUS, KC_MINUS, KC_NO,
                   KC_NO, KC_NO, KC_NO, KC_NO, KC_8, KC_NO,         KC_AMPR, KC_GRAVE, KC_LABK, KC_RABK, KC_QUES, KC_NO,
                                          KC_NO, KC_NO, KC_NO,      KC_ENT, KC_NO, KC_NO),
  [_SYMBOL_RIGHT] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
       * │ $ │ { │ } │ " │   │       │   │   │   │   │   │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ # │ ( │ ) │ ; │ ~ │       │   │ 3 │ 1 │ 5 │ 7 │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ % │ [ │ ] │ ^ │ \ │       │   │ 9 │   │   │   │
       * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
       *           ┌───┐                   ┌───┐
       *           │   ├───┐           ┌───┤   │
       *           └───┤Del├───┐   ┌───┤   ├───┘
       *               └───┤Spc│   │   ├───┘
       *                   └───┘   └───┘
       */
                   KC_NO, KC_DLR,  KC_LCBR, KC_RCBR, KC_DQUO, KC_PIPE,    KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                   KC_NO, KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_TILD,    KC_NO, KC_3, KC_1, KC_5, KC_7, KC_TRANSPARENT,
                   KC_NO, KC_PERC, KC_LBRC, KC_RBRC, KC_CIRC, KC_BSLS,    KC_NO, KC_9, KC_NO, KC_NO, KC_NO, KC_NO,
                                                KC_NO, KC_DEL, KC_SPC,    KC_NO, KC_NO, KC_NO),

  [_NUMWORD] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
       * │   │   │   │   │   │       │   │   │   │   │   │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ 6 │ 4 │ 0 │ 2 │   │       │   │ 3 │ 1 │ 5 │ 7 │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │   │ x │   │ 8 │   │       │   │ 9 │ , │ . │   │
       * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
       *           ┌───┐                   ┌───┐
       *           │   ├───┐           ┌───┤   │
       *           └───┤   ├───┐   ┌───┤   ├───┘
       *               └───┤DEF│   │DEF├───┘
       *                   └───┘   └───┘
       */
      QK_BOOT, NC_0, KC_TRANSPARENT, KC_TRANSPARENT, NC_1, NC_2, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_RBT,
      KC_TRANSPARENT, KC_6, KC_4, KC_0, KC_2, KC_TRANSPARENT, KC_TRANSPARENT, KC_3, KC_1, KC_5, KC_7, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, KC_X, KC_TRANSPARENT, KC_8, KC_TRANSPARENT, KC_TRANSPARENT, KC_9, KC_COMM, KC_DOT, KC_TRANSPARENT, KC_TRANSPARENT,
      KC_TRANSPARENT, KC_TRANSPARENT, DF(_DEFAULT), DF(_DEFAULT), KC_TRANSPARENT, KC_TRANSPARENT),
  [_NAVIGATION] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
       * │ F1│ F2│ F3│ F4│ F5│       │ F6│ F7│ F8│ F9│F10│
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │Gui│Alt│Ctl│Sht│   │       │   │ ← │ ↓ │ ↑ │ → │
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │   │   │   │   │   │       │   │Hom│PgD│PgU│End│
       * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
       *           ┌───┐                   ┌───┐
       *           │   ├───┐           ┌───┤Alt│
       *           └───┤   ├───┐   ┌───┤   ├───┘
       *               └───┤   │   │   ├───┘
       *                   └───┘   └───┘
       */
      KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO,
      KC_NO, KC_RGUI, KC_RALT, KC_RCTL,  KC_RSFT, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RALT),
  [_I3] = LAYOUT_split_3x6_3(
      /*
       * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
       * │ 1 │ 2 │ 3 │ 4 │ 0 │       │ F6│ F7│ F8│ F9│F10│
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │ A │ R │ F │ T │Sh=│       │ F1│   │   │   │Lck│
       * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
       * │   │   │   │   │Sh │       │WQ │ / │ = │ - │ \ │
       * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
       *           ┌───┐                   ┌───┐
       *           │Esc├───┐           ┌───┤   │
       *           └───┤Spc├───┐   ┌───┤   ├───┘
       *               └───┤Ent│   │   ├───┘
       *                   └───┘   └───┘
       */
       RGUI(KC_BRK) , RGUI(KC_1) , RGUI(KC_2) , RGUI(KC_3) , RGUI(KC_4) , RGUI(KC_0) , RGUI(KC_F6) , RGUI(KC_F7) , RGUI(KC_F8) , RGUI(KC_F9) , RGUI(KC_F10) , KC_NO ,
       KC_NO , RGUI(KC_A), RGUI(KC_R), RGUI(KC_F) , MT((MOD_RSFT), RGUI(KC_T)) , RSFT(RGUI(KC_EQUAL)), RGUI(KC_F1) , KC_NO , KC_NO , KC_NO , RGUI(RSFT(KC_BRK)), KC_NO,
       RSFT(RGUI(KC_Q)), KC_NO , KC_NO , KC_NO , KC_NO , RSFT(RGUI(KC_SPC)), RGUI(RSFT(KC_Q)) , RGUI(KC_SLASH), RGUI(KC_EQUAL), RGUI(KC_MINUS), RGUI(KC_BSLS), KC_NO ,
       RGUI(KC_ESC), RGUI(KC_SPC), RGUI(KC_ENT), KC_NO , KC_NO , KC_NO
)};

__attribute__ ((weak))
bool process_record_user_kb(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool get_combo_must_tap(uint16_t index,combo_t *combo) {
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

void process_combo_event(uint16_t combo_index, bool pressed) {
    if(pressed) {
        switch(combo_index) {
            case capsWord:
                caps_word_on();
                break;
            case numWord:
                enable_num_word();
                break;
            default:
                // normal combo - no need to take any action
                return;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // This is just a hack to avoid problems with weak mod not being released when rolling ");"
    if(keycode == KC_RPRN)
    {
        if(record->event.pressed) {
            SEND_STRING(")");
        }
        return false;
    }
    else if(keycode == KC_PIPE)
    {
        if(record->event.pressed) {
            SEND_STRING("|");
        }
        return false;
    } else if (keycode == KC_PLUS) {
        if(record->event.pressed) {
            SEND_STRING("+");
        }
        return false;
    } else if (keycode == KC_LT) {
        if(record->event.pressed) {
            SEND_STRING("<");
        }
        return false;
    } else if (keycode == KC_GT) {
        if(record->event.pressed) {
            SEND_STRING(">");
        }
        return false;
    }

    // returns true if the QMK should handle the keycode normally and false if it is already handled
    if (!process_record_num_word(keycode, record)) {
        return false;
    }
    return process_record_user_kb(keycode, record);
}

const uint16_t PROGMEM altDot_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM apostrophe_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM delete_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM capsWord_combo[] = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM numWord_combo[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM bootloader_combo[]  = {NC_0, NC_1, COMBO_END};
const uint16_t PROGMEM reset_combo[]  = {NC_0, NC_2, COMBO_END};
const uint16_t PROGMEM f11_combo[] = {KC_F7, KC_F8, COMBO_END};
const uint16_t PROGMEM f12_combo[] = {KC_F8, KC_F9, COMBO_END};
const uint16_t PROGMEM dollar_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM symbol_space_combo[] = {KC_0, KC_4, COMBO_END};
const uint16_t PROGMEM symbol_return_combo[] = {KC_1, KC_5, COMBO_END};
const uint16_t PROGMEM backspace_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_Y, KC_COLN, COMBO_END};
const uint16_t PROGMEM lock_combo[] = {NC_3, KC_ESC, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(altDot_combo, LALT(KC_DOT)),
    COMBO(apostrophe_combo, KC_QUOTE),
    COMBO(delete_combo, KC_DEL),
    COMBO_ACTION(capsWord_combo),
    COMBO_ACTION(numWord_combo),
    COMBO(bootloader_combo, QK_BOOT),
    COMBO(reset_combo, QK_REBOOT),
    COMBO(f11_combo, KC_F11),
    COMBO(f12_combo, KC_F12),
    COMBO(dollar_combo, KC_DLR),
    COMBO(symbol_space_combo, KC_SPC),
    COMBO(symbol_return_combo, KC_ENT),
    COMBO(backspace_combo, KC_BSPC),
    COMBO(esc_combo, KC_ESC),
    COMBO(lock_combo, RGUI(KC_PAUS)),
};
