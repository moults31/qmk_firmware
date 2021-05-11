/* Copyright 2020 MrT1ddl3s
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_CTRL_MASK  (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTRL))
#define MODS_ALT_MASK  (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_GUI_MASK  (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))

#define CHECK_OBS_MODS_MASK(mods) ((mods & MODS_SHIFT_MASK) && (mods & MODS_CTRL_MASK) && (mods & MODS_ALT_MASK) && (mods & MODS_GUI_MASK))

enum custom_keycodes {
    M_TERMFOCUS = SAFE_RANGE,
    M_TEAMSCODEBLOCK,
    M_OBS_BRB,
    M_OBS_GAME,
    M_OBS_JSTCHT,
    M_OBS_DSKT_MUTE,
    M_OBS_DSKT_UNMUTE,
    M_OBS_VOICE_MUTE,
    M_OBS_VOICE_UNMUTE,
    M_OBS_MOOSIC_MUTE,
    M_OBS_MOOSIC_UNMUTE,
};

// Handle OBS-specific custom keycodes
bool process_record_user_obs(uint16_t keycode, keyrecord_t *record) {
    // Apply all 4 mods for custom OBS macros
    register_code(KC_LSHIFT);
    register_code(KC_LCTL);
    register_code(KC_LALT);
    register_code(KC_LGUI);

    switch (keycode) {
        case M_OBS_BRB:
            SEND_STRING("1");
            break;
        case M_OBS_GAME:
            SEND_STRING("2");
            break;
        case M_OBS_JSTCHT:
            SEND_STRING("3");
            break;
        case M_OBS_DSKT_MUTE:
            SEND_STRING("4");
            break;
        case M_OBS_DSKT_UNMUTE:
            SEND_STRING("5");
            break;
        case M_OBS_VOICE_MUTE:
            SEND_STRING("6");
            break;
        case M_OBS_VOICE_UNMUTE:
            SEND_STRING("7");
            break;
        case M_OBS_MOOSIC_MUTE:
            SEND_STRING("8");
            break;
        case M_OBS_MOOSIC_UNMUTE:
            SEND_STRING("9");
            break;
    }

    // Unpress all 4 mods for custom OBS macros
    unregister_code(KC_LSHIFT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);

    return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool rv = true;
    switch (keycode) {
        case M_TERMFOCUS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTRL("`"));
            }
            break;
        case M_TEAMSCODEBLOCK:
            if (record->event.pressed) {
                SEND_STRING("```");
            }
            break;
        case M_OBS_BRB:
        case M_OBS_GAME:
        case M_OBS_JSTCHT:
        case M_OBS_DSKT_MUTE:
        case M_OBS_DSKT_UNMUTE:
        case M_OBS_VOICE_MUTE:
        case M_OBS_VOICE_UNMUTE:
        case M_OBS_MOOSIC_MUTE:
        case M_OBS_MOOSIC_UNMUTE:
            rv = process_record_user_obs(keycode, record);
            break;
    }
    return rv;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho(
                  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
                  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
                  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
         KC_MPLY, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
         KC_MUTE, MO(3),  KC_P0,   KC_PDOT, KC_PENT
				 ),

	[1] = LAYOUT_ortho(
                  KC_1,         KC_TRNS,          KC_TRNS, KC_TRNS,
                  KC_TRNS,      KC_TRNS,          KC_TRNS, KC_TRNS,
                  KC_TRNS,      KC_TRNS,          KC_TRNS, KC_TRNS,
         KC_TRNS, M_TERMFOCUS,  M_TEAMSCODEBLOCK, KC_TRNS, KC_TRNS,
         KC_TRNS, MO(3),        KC_TRNS,          KC_TRNS, KC_TRNS
				 ),

	[2] = LAYOUT_ortho(
                  KC_8,               KC_TRNS,           KC_TRNS,             KC_TRNS,
                  M_OBS_VOICE_UNMUTE, M_OBS_MOOSIC_MUTE, M_OBS_MOOSIC_UNMUTE, KC_TRNS,
                  M_OBS_DSKT_MUTE,    M_OBS_DSKT_UNMUTE, M_OBS_VOICE_MUTE,    KC_TRNS,
         KC_TRNS, M_OBS_BRB,          M_OBS_GAME,        M_OBS_JSTCHT,        KC_TRNS,
         KC_TRNS, MO(3),              KC_TRNS,           KC_TRNS,             KC_TRNS
				 ),

	[3] = LAYOUT_ortho(
                  RESET,    KC_TRNS,    KC_TRNS, KC_TRNS,
                  KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,
                  KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,
         KC_TRNS, TO(1),    TO(2),      TO(3),   KC_TRNS,
         KC_TRNS, KC_TRNS,  TO(0),      KC_TRNS, KC_TRNS
				 )

};
