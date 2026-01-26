#include QMK_KEYBOARD_H
#include "layer_lock.h"

/* keymaps */

#undef LAYOUT
#define LAYOUT LAYOUT_split_3x6_3_ex2

enum layers {
    _BASE = 0,
    _NAV,
    _SYM,
    _CFG,
    _MS,
    _MS_WHL,
    _FN,
};

enum keycodes {
    OS_CLEAR = SAFE_RANGE,
    LLCK_OFF,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, TG(_MS),        OSL(_CFG), KC_Y, KC_U, KC_I, KC_O, KC_P, XXXXXXX,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, XXXXXXX,        XXXXXXX, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
        OS_CLEAR, KC_Z, KC_X, KC_C, KC_V, KC_B,        KC_N, KC_M, KC_SPC, OS_CLEAR, KC_BSPC, OSL(_FN),
        OS_LSFT, OS_LCTL, OSL(_NAV),        OSL(_SYM), OS_LGUI, OS_LALT
    ),

    [_NAV] = LAYOUT(
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, _______,        _______, KC_6, KC_7, KC_8, KC_9, KC_0, XXXXXXX,
        KC_ESC, KC_INS, KC_HOME, KC_PGUP, KC_PSCR, XXXXXXX, _______,        _______, KC_LEFT, KC_DOWN, KC_UP,KC_RIGHT, XXXXXXX, KC_ENT,
        OS_CLEAR, KC_DEL, KC_END, KC_PGDN, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, KC_SPC, OS_CLEAR, KC_BSPC, XXXXXXX,
        OS_LSFT, OS_LCTL, QK_LLCK,        XXXXXXX, OS_LGUI, OS_LALT
    ),

    [_SYM] = LAYOUT(
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, _______,        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
        KC_ESC, KC_LBRC, KC_RBRC, KC_MINS, KC_PLUS, KC_DQUO, _______,        _______, KC_BSLS, KC_SLSH, KC_PIPE, KC_LT, KC_GT, KC_ENT,
        OS_CLEAR, KC_LCBR, KC_RCBR, KC_UNDS, KC_EQL, KC_QUOT,        KC_COMM, KC_DOT, KC_SPC, OS_CLEAR, KC_BSPC, KC_QUES,
        OS_LSFT, OS_LCTL, XXXXXXX,        QK_LLCK, OS_LGUI, OS_LALT
    ),

    [_FN] = LAYOUT(
        KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, _______,        _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, XXXXXXX,
        KC_ESC, KC_F11, KC_F12, KC_BRIU, KC_VOLU, KC_MUTE, _______,        _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, XXXXXXX, KC_ENT,
        OS_CLEAR, XXXXXXX, XXXXXXX, KC_BRID, KC_VOLD, XXXXXXX,        XXXXXXX, XXXXXXX, KC_SPC, OS_CLEAR, KC_BSPC, QK_LLCK,
        OS_LSFT, OS_LCTL, XXXXXXX,        XXXXXXX, OS_LGUI, OS_LALT
    ),


    // TODO: thumbcluster mods
    [_MS] = LAYOUT(
        KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_MS),        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, OS_LALT,
        OS_LCTL, XXXXXXX, MS_BTN3, MS_BTN1, MS_BTN2, XXXXXXX, _______,        _______, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, XXXXXXX, OS_LCTL,
        OS_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, OS_LGUI, OS_LSFT,
        MS_ACL0, MS_ACL1, MS_ACL2,        XXXXXXX, MO(_MS_WHL), XXXXXXX
    ),
    [_MS_WHL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, _______, _______,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______,        _______, _______, _______
    ),

    // TODO:
    [_CFG] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, _______,        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LGUI, _______, KC_SPC,        KC_ENT, _______, KC_RALT
    )
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OS_CLEAR:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            clear_oneshot_mods();
            break;
        case LLCK_OFF:
            layer_lock_all_off();
            break;
        default:
            return true;
    }
    return false;
}

/* RGB indicators */

#define RGB_UNLOCKED RGB_ORANGE
#define RGB_LOCKED RGB_RED

#define SET_MOD_INDICATOR(row, col, mod_mask)      \
    if (g_led_config.matrix_co[row][col] == i) {   \
        if (get_oneshot_locked_mods() & mod_mask)  \
            rgb_matrix_set_color(i, RGB_LOCKED);   \
        else if (get_oneshot_mods() & mod_mask)    \
            rgb_matrix_set_color(i, RGB_UNLOCKED); \
        continue;                                  \
    }

// locked layer state isn't shared between splits
#define SET_LAYER_INDICATOR(row, col, layer)                              \
    if (g_led_config.matrix_co[row][col] == i && layer_state_is(layer)) { \
        if (is_layer_locked(layer))                                       \
            rgb_matrix_set_color(i, RGB_LOCKED);                          \
        else                                                              \
            rgb_matrix_set_color(i, RGB_UNLOCKED);                        \
        continue;                                                         \
    }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        SET_MOD_INDICATOR(3, 3, MOD_MASK_SHIFT);
        SET_MOD_INDICATOR(3, 4, MOD_MASK_CTRL);
        SET_MOD_INDICATOR(7, 4, MOD_MASK_GUI);
        SET_MOD_INDICATOR(7, 3, MOD_MASK_ALT);
        SET_LAYER_INDICATOR(0, 6, _MS);
        SET_LAYER_INDICATOR(3, 5, _NAV);
        SET_LAYER_INDICATOR(7, 5, _SYM);
        SET_LAYER_INDICATOR(6, 0, _FN);
    }
    return false;
}

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
// clang-format on
#endif
