#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

#define KC_MUND LGUI(KC_Z)
#define KC_MCUT LGUI(KC_X)
#define KC_MCPY LGUI(KC_C)
#define KC_MPST LGUI(KC_V)
#define KC_HESC MT(MOD_HYPR, KC_ESCAPE)
#define KC_NVSC LT(4,KC_SCOLON)
#define LWR_TAB LT(1,KC_TAB)
#define RS_ENT LT(2,KC_ENTER)

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  TD_BRC = 0,
  TD_CBRC,
  TD_ABRK,
  TD_DSUN,
  TD_GVTL,
  SCRSHT
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NAV,
  _NUMPAD,
};

qk_tap_dance_action_t tap_dance_actions[] = {

    [TD_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
   ,[TD_CBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR)
   ,[TD_ABRK] = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK)
   ,[TD_DSUN] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS)
   ,[TD_GVTL] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD)
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Lead |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc* |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;* |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift(|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |)Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NumPad| Ctrl | Alt  | GUI  |Lower*|    Space    |Raise*| Left | Down |  Up  | Right|
 * `-----------------------------------------------------------------------------------'
 * Esc* - Escape when tapped, Hyper when held
 * Lower* - Tab when tapped, lower when held
 * Raise* - Enter when tapped, raise when held
 * ;* - Semicolon when tapped, nav layer when held
 */

  [_BASE] = LAYOUT_planck_grid(
    KC_LEAD, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_HESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_NVSC, KC_QUOT,
    KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
    TG(5),   KC_LCTL, KC_LALT, KC_LGUI, LWR_TAB, KC_SPC,  KC_NO,   RS_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   -  |   =  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift(| Undo |  Cut | Copy | Paste|   (  |   )  | Enter|   ,  |   .  |   /  |)Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower*|  Backspace  |Raise*| Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 *
 */

  [_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_TRNS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_LSPO, KC_MUND, KC_MCUT, KC_MCPY, KC_MPST, KC_LPRN, KC_RPRN, KC_ENT,  KC_TRNS, KC_TRNS, KC_TRNS, KC_RSPC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, KC_NO,   KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |   +  |   _  |   {  |  }   |  F1  |  F2  |  F3  |  F4  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc* |      |ScrSht|   =  |   -  |   [  |  ]   |  F5  |  F6  |  F7  |  F8  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift(| Undo |  Cut | Copy | Paste|   <  |  >   |  F9  |  F10 |  F11 |  F12 |)Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Play | Ctrl | Alt  | GUI  |Lower*|   Delete    |Raise*| Prev | VolDn| VolUp| Next |
 * `-----------------------------------------------------------------------------------'
 * Esc* - Escape when tapped, Hyper when held
 * Lower* - Tab when tapped, lower when held
 * Raise* - Enter when tapped, raise when held
 * - _* - Tap Dance: dash when tapped once, underscore when tapped twice
 */

  [_RAISE] = LAYOUT_planck_grid(
    KC_TRNS, KC_NO,   KC_NO,   KC_PLUS, KC_UNDS, KC_LCBR, KC_RCBR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS,
    KC_TRNS, TD_DSUN, SCRSHT,  KC_EQL,  KC_MINS, KC_LBRC, KC_RBRC, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_ENT,
    KC_LSPO, KC_MUND, KC_MCUT, KC_MCPY, KC_MPST, KC_LABK, KC_RABK, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_RSPC,
    KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_NO,   KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |      |      | ClkOn|ClkOff|ClkTog|      |      | Sat- | Sat+ |      |      | Reset|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | AudOn|AudOff|AudTog|      |      | Val- | Val+ |RGBTog|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | MusOn|MusOff|MusTog|      |      | Hue- | Hue+ |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

  [_ADJUST] = LAYOUT_planck_grid(
    KC_TRNS, KC_TRNS, CK_ON,   CK_OFF,  CK_TOGG, KC_TRNS, KC_TRNS, RGB_SAD, RGB_SAI, KC_TRNS, KC_TRNS, RESET,
    KC_DEL,  KC_TRNS, AU_ON,   AU_OFF,  AU_TOG,  KC_TRNS, KC_TRNS, RGB_VAD, RGB_VAI, RGB_TOG, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, MU_ON,   MU_OFF,  MU_TOG,  KC_TRNS, KC_TRNS, RGB_HUD, RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

/* Nav
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |ScrLft|      |      |ScrRgt|      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Home | PgDn | PgUp |  End | Left | Down |  Up  | Right|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |CmdLft| CmdDn| CmdUp| CmdRt|AltLft| AltDn| AltUp| AltRt|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

  [_NAV] = LAYOUT_planck_grid(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_LEFT), KC_TRNS, KC_TRNS, RCTL(KC_RIGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RIGHT), LALT(KC_LEFT), LALT(KC_DOWN), LALT(KC_UP), LALT(KC_RIGHT),KC_TRNS,KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  Up  |      |NumLck|   7  |   8  |   9  |   *  |   /  |      | BkSp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  Tab | Left | Down | Right|  Tab |   4  |   5  |   6  |   +  |   -  |      |  Tab |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Enter|      |      |      | Enter|   1  |   2  |   3  |   ,  |   .  |  Up  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Base |      |      |      |      |      0      |   =  |      | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */

  [_NUMPAD] = LAYOUT_planck_grid(
    KC_TRNS, KC_NO,   KC_UP,   KC_NO,   KC_NLCK, KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, KC_PSLS, KC_NO,   KC_BSPC, 
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TAB,  KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_PMNS, KC_NO,   KC_TAB, 
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_ENT,  KC_KP_1, KC_KP_2, KC_KP_3, KC_COMM, KC_PDOT, KC_UP,   KC_ENT, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_NO,   KC_PEQL, KC_NO,   KC_LEFT, KC_DOWN, KC_RIGHT)

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { 
      {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {255,255,250},
      {141,255,233}, {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255}, 
      {141,255,233}, {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {141,255,233}, 
      {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233},           {0,0,255},          {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233} },

    [1] = { 
      {0,0,255},     {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {0,204,255},   {255,255,250},
      {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241},  {12,225,241}, 
      {141,255,233}, {243,222,234}, {243,222,234}, {243,222,234}, {243,222,234}, {180,150,255}, {180,150,255}, {12,225,241},  {0,0,255},     {0,0,255},     {0,0,255},     {141,255,233}, 
      {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233},           {0,0,255},          {141,255,233}, {32,255,234},  {32,255,234},  {32,255,234},  {32,255,234} },

    [2] = { 
      {0,0,255},     {0,0,0},       {0,0,0},       {10,225,255},  {10,225,255},  {134,255,213}, {134,255,213}, {85,203,158},  {85,203,158},  {85,203,158},  {85,203,158},  {255,255,250}, 
      {141,255,233}, {0,0,0},       {10,225,255},  {10,225,255},  {10,225,255},  {134,255,213}, {134,255,213}, {85,203,158},  {85,203,158},  {85,203,158},  {85,203,158},  {141,255,233}, 
      {141,255,233}, {243,222,234}, {243,222,234}, {243,222,234}, {243,222,234}, {134,255,213}, {134,255,213}, {85,203,158},  {85,203,158},  {85,203,158},  {85,203,158},  {141,255,233}, 
      {32,176,255},  {141,255,233}, {141,255,233}, {141,255,233}, {141,255,233},           {0,0,255},          {141,255,233}, {32,176,255},  {32,176,255},  {32,176,255},  {32,176,255} },

    [3] = { 
      {0,0,255},     {0,0,255},     {0,205,255},   {0,205,255},   {0,205,255},   {0,0,255},     {0,0,255},     {0,183,238},   {0,183,238},   {0,0,255},     {0,0,255},     {255,255,250},
      {0,0,255},     {0,0,255},     {0,205,255},   {0,205,255},   {0,205,255},   {0,0,255},     {0,0,255},     {0,183,238},   {0,183,238},   {0,183,238},   {0,0,255},     {0,0,255}, 
      {0,0,255},     {0,0,255},     {0,205,255},   {0,205,255},   {0,205,255},   {0,0,255},     {0,0,255},     {0,183,238},   {0,183,238},   {0,0,255},     {0,0,255},     {0,0,255}, 
      {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},               {0,0,255},          {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255},     {0,0,255} },

    [4] = { 
      {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {32,176,255},  {0,0,0},       {0,0,0},       {32,176,255},  {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0}, 
      {0,0,0},       {0,0,0},       {243,222,234}, {243,222,234}, {243,222,234}, {243,222,234}, {85,203,255},  {85,203,255},  {85,203,255},  {85,203,255},  {0,0,0},       {0,0,0},
      {0,0,0},       {0,0,0},       {10,225,255},  {10,225,255},  {10,225,255},  {10,225,255},  {134,255,213}, {134,255,213}, {134,255,213}, {134,255,213}, {0,0,0},       {0,0,0}, 
      {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},                  {0,0,0},           {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0} },

    [5] = { 
      {0,0,0},       {0,0,0},       {0,0,225},     {0,0,0},       {85,203,255},  {146,224,255}, {146,224,255}, {146,224,255}, {169,120,255}, {169,120,255}, {0,0,0},       {0,0,0}, 
      {0,0,0},       {0,0,225},     {0,0,225},     {0,0,225},     {12,225,241},  {146,224,255}, {146,224,255}, {146,224,255}, {169,120,255}, {169,120,255}, {0,0,0},       {12,225,241}, 
      {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},       {12,225,241},  {146,224,255}, {146,224,255}, {146,224,255}, {169,200,255}, {169,200,255}, {0,0,255},     {12,225,241}, 
      {255,255,250}, {0,0,0},       {0,0,0},       {0,0,0},       {0,0,0},                 {0,0,255},          {146,224,255}, {0,0,0},       {0,0,255},     {0,0,255},     {0,0,255} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SCRSHT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LCTL(SS_LSFT("4"))));
      } else {
        // when keycode is released
      }
      break;

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif

    LEADER_DICTIONARY() {
      leading = false;
      leader_end();

      SEQ_ONE_KEY(KC_T) {
        SEND_STRING(SS_LGUI("c") SS_LGUI("t") SS_LGUI("v") SS_TAP(X_ENTER));
      }

      SEQ_ONE_KEY(KC_Y) {
        SEND_STRING(":+1:");
      }
      
      SEQ_ONE_KEY(KC_N) {
        SEND_STRING(":-1:");
      }

      SEQ_ONE_KEY(KC_G) {
        SEND_STRING("/giphy ");
      }

      SEQ_TWO_KEYS(KC_S, KC_D) {
        SEND_STRING(SS_LGUI(SS_LSFT("4")));
      }

      SEQ_TWO_KEYS(KC_S, KC_C) {
        SEND_STRING(SS_LGUI(SS_LCTL(SS_LSFT("4"))));
      }
    }
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
