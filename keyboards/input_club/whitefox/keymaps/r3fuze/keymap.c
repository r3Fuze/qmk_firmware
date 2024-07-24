/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

#include "keymap_danish.h"

enum unicode_names {
    PLACEHOLDER
};
const uint32_t unicode_map[] PROGMEM = {};

// Prefixes:
//  SS -> send_string
//  CS -> custom
enum custom_keycodes {
    SS_HELLO = SAFE_RANGE,
    CS_RAND
};

bool handle_altgr(char custom[]) {
    const uint8_t mods = get_mods();

    if (mods & MOD_BIT(KC_RALT)) {
        unregister_mods(MOD_BIT(KC_RALT));

        send_unicode_string(custom);

        register_mods(mods);

        return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_C:
            if (record->event.pressed) {
                return handle_altgr("°");
            }
            return true;

        case KC_M:
            if (record->event.pressed) {
                return handle_altgr("μ");
            }
            return true;

        case KC_O:
            if (record->event.pressed) {
                return handle_altgr("Ω");
            }
            return true;

        case SS_HELLO:
            if (record->event.pressed) {
                send_string("Hello, world!\n");
            }
            return false;

        case CS_RAND:
            if (record->event.pressed) {
                tap_random_base64();
            }

            return false;
    }
    return true;
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case DK_AE:   // Æ
        case DK_OSTR: // Ø
        case DK_ARNG: // Å
        case DK_MINS: // -
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │ Backsp│ ½ │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O*│ P │ Å │ ¨ │     │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ Ent├───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Æ │ Ø │ ' │    │Hom│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Shft│ \ │ Z │ X │ C*│ V │ B │ N │ M*│ , │ . │ - │RShift│ ↑ │End│
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│Fn1 │Alt │                        │Alt│Win│Ctl│ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     *  AltGr+C -> °
     *  AltGr+M -> μ
     *  AltGr+O -> Ω
     */
    [0] = LAYOUT_65_iso(
        KC_ESC,     KC_1,       KC_2,       KC_3,   KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       DK_PLUS,    DK_ACUT,    KC_BSPC,    DK_HALF,
        KC_TAB,     KC_Q,       KC_W,       KC_E,   KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       DK_ARNG,    DK_DIAE,                KC_DEL,
        KC_CAPS,    KC_A,       KC_S,       KC_D,   KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       DK_AE,      DK_OSTR,    DK_QUOT,    KC_ENT,     KC_HOME,
        KC_LSFT,    DK_LABK,    KC_Z,       KC_X,   KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     DK_MINS,    KC_RSFT,    KC_UP,      KC_END,
        KC_LCTL,    MO(1),      KC_LALT,                                    KC_SPC,                             KC_RALT,    KC_LGUI,    KC_RCTL,    KC_LEFT,    KC_DOWN,    KC_RGHT
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │GRV│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│       │Mut│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │ ▽ │ ▽ │ ▽ │RND│ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │     │PrS│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐Play├───┤
     * │CapWrd│ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │    │PgU│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Lock│Fn2│ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │ ▽ │      │Vl+│PgD│
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │    │ ▽  │    │                        │   │Mnu│   │Prv│Vl-│Nxt│
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [1] = LAYOUT_65_iso(
        KC_GRV,  KC_F1,      KC_F2,      KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_MUTE,
        KC_NO,   _______,    _______,    _______, CS_RAND, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PSCR,
        CW_TOGG, _______,    _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_PGUP,
        QK_LOCK, MO(2),      _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO,   KC_VOLU, KC_PGDN,
        KC_NO,   _______,    KC_NO,                                 KC_NO,                     KC_NO,   KC_APP,  KC_NO,   KC_MPRV, KC_VOLD, KC_MNXT
    ),

    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │NKR│   │   │   │   │   │   │   │   │   │   │   │   │       │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │     │   │   │   │   │   │   │   │   │   │   │   │   │Bootl│   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
     * │      │   │   │   │   │   │ * │   │   │   │   │   │   │    │   │
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │    │ ▽ │   │   │   │   │ ▽ │   │   │   │   │   │      │BL+│   │
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │    │    │    │        BL Toggle       │   │   │   │BL/│BL-│BFX│
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [2] = LAYOUT_65_iso(
        NK_TOGG, KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,              KC_NO,
        KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO, KC_NO, SS_HELLO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     QK_BOOT, KC_NO,
        KC_NO,   _______, KC_NO, KC_NO,   KC_NO, KC_NO, _______,  KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,     BL_UP,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,                        BL_TOGG,                  KC_NO, KC_NO, KC_NO, BL_TOGG,   BL_DOWN, BL_STEP
    ),
};
