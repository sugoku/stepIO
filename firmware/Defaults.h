/**********************************************************/
/*                  _            _____ ____               */
/*                 | |          |_   _/ __ \              */
/*              ___| |_ ___ _ __  | || |  | |             */
/*             / __| __/ _ \ '_ \ | || |  | |             */
/*             \__ \ ||  __/ |_) || || |__| |             */
/*             |___/\__\___| .__/_____\____/              */
/*                         | |                            */
/*                         |_|                            */
/*                                                        */
/*  stage controller with                                 */
/*  emulation of PIUIO                                    */
/*  by BedrockSolid (@sugoku)                             */
/**********************************************************/
/*                    License is GPLv3                    */
/*            https://github.com/sugoku/stepIO            */
/**********************************************************/

#ifndef _DEFAULTS_H
#define _DEFAULTS_H

#include "Config.h"

// These are the default settings which will be loaded into stepIO/brokeIO on first boot, change as needed
const uint8_t defaults[256] PROGMEM = {
    [ConfigOptions::VERSION_MODEL] = STEPIO_VERSION_MODEL,
    [ConfigOptions::VERSION_MAJOR] = STEPIO_VERSION_MAJOR,
    [ConfigOptions::VERSION_MINOR] = STEPIO_VERSION_MINOR,
    [ConfigOptions::VERSION_REVISION] = STEPIO_VERSION_REVISION,

    [ConfigOptions::UPDATE_STATUS] = UpdateStatus::SUCCESS,
    [ConfigOptions::LAST_ERROR] = RuntimeError::NONE,
    [ConfigOptions::INPUT_TYPE] = EEPROM_DEFAULT_VALUE,  // unused
    #ifdef BROKEIO
        [ConfigOptions::INPUT_MODE] = InputMode::MUX4067_Dual,
    #else
        [ConfigOptions::INPUT_MODE] = InputMode::Software,
    #endif
    [ConfigOptions::MUX_POLLING_MODE] = MUXPollingMode::Normal,
    #ifdef SIMPLE_PIUIO_MUX
        [ConfigOptions::MUX_SIMPLE] = EEPROM_TRUE
    #else
        [ConfigOptions::MUX_SIMPLE] = EEPROM_FALSE
    #endif

    [ConfigOptions::OUTPUT_MODE] = OutputMode::PIUIO,
    #ifdef BROKEIO
        [ConfigOptions::LIGHTS_MODE] = LightsMode::Latch32,
    #else
        [ConfigOptions::LIGHTS_MODE] = LightsMode::Signal,
    #endif
    [ConfigOptions::LIGHTS_FROM_SENSORS] = EEPROM_FALSE,
    [ConfigOptions::EXTRA_LIGHTS_MODE] = LightsMode::None,
    [ConfigOptions::DEBOUNCE_MODE] = EEPROM_DEFAULT_VALUE,  // not implemented yet

    [ConfigOptions::PLAYER] = DEFAULT_PLAYER,
    [ConfigOptions::PANEL_COUNT] = PANELS_PER_PLAYER,
    [ConfigOptions::P1BUTTON_COUNT] = PLAYER_1_BUTTONS,
    [ConfigOptions::P2BUTTON_COUNT] = PLAYER_2_BUTTONS,
    [ConfigOptions::OTHERBUTTON_COUNT] = OTHER_BUTTONS,

    [ConfigOptions::BLOCKED_INPUTS_0] = DEFAULT_BLOCKED_INPUTS_0,
    [ConfigOptions::BLOCKED_INPUTS_1] = DEFAULT_BLOCKED_INPUTS_1,
    [ConfigOptions::BLOCKED_INPUTS_2] = DEFAULT_BLOCKED_INPUTS_2,
    [ConfigOptions::BLOCKED_INPUTS_3] = DEFAULT_BLOCKED_INPUTS_3,

    [ConfigOptions::BLOCKED_INPUTS_MUX0_0] = DEFAULT_BLOCKED_INPUTS_0,
    [ConfigOptions::BLOCKED_INPUTS_MUX0_1] = DEFAULT_BLOCKED_INPUTS_1,
    [ConfigOptions::BLOCKED_INPUTS_MUX0_2] = DEFAULT_BLOCKED_INPUTS_2,
    [ConfigOptions::BLOCKED_INPUTS_MUX0_3] = DEFAULT_BLOCKED_INPUTS_3,

    [ConfigOptions::BLOCKED_INPUTS_MUX1_0] = DEFAULT_BLOCKED_INPUTS_0,
    [ConfigOptions::BLOCKED_INPUTS_MUX1_1] = DEFAULT_BLOCKED_INPUTS_1,
    [ConfigOptions::BLOCKED_INPUTS_MUX1_2] = DEFAULT_BLOCKED_INPUTS_2,
    [ConfigOptions::BLOCKED_INPUTS_MUX1_3] = DEFAULT_BLOCKED_INPUTS_3,

    [ConfigOptions::BLOCKED_INPUTS_MUX2_0] = DEFAULT_BLOCKED_INPUTS_0,
    [ConfigOptions::BLOCKED_INPUTS_MUX2_1] = DEFAULT_BLOCKED_INPUTS_1,
    [ConfigOptions::BLOCKED_INPUTS_MUX2_2] = DEFAULT_BLOCKED_INPUTS_2,
    [ConfigOptions::BLOCKED_INPUTS_MUX2_3] = DEFAULT_BLOCKED_INPUTS_3,

    [ConfigOptions::BLOCKED_INPUTS_MUX3_0] = DEFAULT_BLOCKED_INPUTS_0,
    [ConfigOptions::BLOCKED_INPUTS_MUX3_1] = DEFAULT_BLOCKED_INPUTS_1,
    [ConfigOptions::BLOCKED_INPUTS_MUX3_2] = DEFAULT_BLOCKED_INPUTS_2,
    [ConfigOptions::BLOCKED_INPUTS_MUX3_3] = DEFAULT_BLOCKED_INPUTS_3,

    [ConfigOptions::RGB_LED_COUNT] = DEFAULT_RGB_LED_COUNT,
    [ConfigOptions::EXTRA_LED_TRIGGER] = EEPROM_DEFAULT_VALUE,

    [ConfigOptions::LIGHT_P1_UPLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P1_UPRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P1_CENTER_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P1_DOWNLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P1_DOWNRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P2_UPLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P2_UPRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P2_CENTER_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P2_DOWNLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_P2_DOWNRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_MARQUEE_1_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_MARQUEE_2_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_MARQUEE_3_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_MARQUEE_4_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_SUB_LEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [ConfigOptions::LIGHT_SUB_RIGHT_REMAP] = EEPROM_DEFAULT_VALUE,

    [ConfigOptions::P1_UPLEFT_REMAP] = InputPacket::P1_UPLEFT,
    [ConfigOptions::P1_UPRIGHT_REMAP] = InputPacket::P1_UPRIGHT,
    [ConfigOptions::P1_CENTER_REMAP] = InputPacket::P1_CENTER,
    [ConfigOptions::P1_DOWNLEFT_REMAP] = InputPacket::P1_DOWNLEFT,
    [ConfigOptions::P1_DOWNRIGHT_REMAP] = InputPacket::P1_DOWNRIGHT,
    [ConfigOptions::P2_UPLEFT_REMAP] = InputPacket::P2_UPLEFT,
    [ConfigOptions::P2_UPRIGHT_REMAP] = InputPacket::P2_UPRIGHT,
    [ConfigOptions::P2_CENTER_REMAP] = InputPacket::P2_CENTER,
    [ConfigOptions::P2_DOWNLEFT_REMAP] = InputPacket::P2_DOWNLEFT,
    [ConfigOptions::P2_DOWNRIGHT_REMAP] = InputPacket::P2_DOWNRIGHT,
    [ConfigOptions::P1_COIN_REMAP] = InputPacket::P1_COIN,
    [ConfigOptions::P2_COIN_REMAP] = InputPacket::P2_COIN,
    [ConfigOptions::TEST_BUTTON_REMAP] = InputPacket::TEST_BUTTON,
    [ConfigOptions::SERVICE_BUTTON_REMAP] = InputPacket::SERVICE_BUTTON,
    [ConfigOptions::CLEAR_BUTTON_REMAP] = InputPacket::CLEAR_BUTTON,

    // keycodes from HID library
    [ConfigOptions::P1_UPLEFT_KEYCODE] = KeyboardKeycode::KEY_Q,
    [ConfigOptions::P1_UPRIGHT_KEYCODE] = KeyboardKeycode::KEY_E,
    [ConfigOptions::P1_CENTER_KEYCODE] = KeyboardKeycode::KEY_S,
    [ConfigOptions::P1_DOWNLEFT_KEYCODE] = KeyboardKeycode::KEY_Z,
    [ConfigOptions::P1_DOWNRIGHT_KEYCODE] = KeyboardKeycode::KEY_C,
    [ConfigOptions::P2_UPLEFT_KEYCODE] = KeyboardKeycode::KEYPAD_7,
    [ConfigOptions::P2_UPRIGHT_KEYCODE] = KeyboardKeycode::KEYPAD_9,
    [ConfigOptions::P2_CENTER_KEYCODE] = KeyboardKeycode::KEYPAD_5,
    [ConfigOptions::P2_DOWNLEFT_KEYCODE] = KeyboardKeycode::KEYPAD_1,
    [ConfigOptions::P2_DOWNRIGHT_KEYCODE] = KeyboardKeycode::KEYPAD_3,
    [ConfigOptions::P1_COIN_KEYCODE] = KeyboardKeycode::KEY_F1,
    [ConfigOptions::P2_COIN_KEYCODE] = KeyboardKeycode::KEY_F1,
    [ConfigOptions::TEST_BUTTON_KEYCODE] = KeyboardKeycode::KEY_SCROLL_LOCK,
    [ConfigOptions::SERVICE_BUTTON_KEYCODE] = KeyboardKeycode::KEY_ENTER,
    [ConfigOptions::CLEAR_BUTTON_KEYCODE] = KeyboardKeycode::KEY_ESC,

    // these are gamepad button numbers, there are 32 buttons total (0-31)
    [ConfigOptions::P1_UPLEFT_GAMEPAD] = 0,
    [ConfigOptions::P1_UPRIGHT_GAMEPAD] = 1,
    [ConfigOptions::P1_CENTER_GAMEPAD] = 2,
    [ConfigOptions::P1_DOWNLEFT_GAMEPAD] = 3,
    [ConfigOptions::P1_DOWNRIGHT_GAMEPAD] = 4,
    [ConfigOptions::P2_UPLEFT_GAMEPAD] = 5,
    [ConfigOptions::P2_UPRIGHT_GAMEPAD] = 6,
    [ConfigOptions::P2_CENTER_GAMEPAD] = 7,
    [ConfigOptions::P2_DOWNLEFT_GAMEPAD] = 8,
    [ConfigOptions::P2_DOWNRIGHT_GAMEPAD] = 9,
    [ConfigOptions::P1_COIN_GAMEPAD] = 10,
    [ConfigOptions::P2_COIN_GAMEPAD] = 11,
    [ConfigOptions::TEST_BUTTON_GAMEPAD] = 12,
    [ConfigOptions::SERVICE_BUTTON_GAMEPAD] = 13,
    [ConfigOptions::CLEAR_BUTTON_GAMEPAD] = 14,

    // there are 14 buttons, 9 hat directions, also two sticks analog X and Y
    [ConfigOptions::P1_UPLEFT_SWITCH] = EEPROM_SWITCH_HAT_TOP,
    [ConfigOptions::P1_UPRIGHT_SWITCH] = EEPROM_SWITCH_HAT_RIGHT,
    [ConfigOptions::P1_CENTER_SWITCH] = EEPROM_SWITCH_HAT_LEFT,
    [ConfigOptions::P1_DOWNLEFT_SWITCH] = EEPROM_SWITCH_HAT_BOTTOM,
    [ConfigOptions::P1_DOWNRIGHT_SWITCH] = EEPROM_SWITCH_BUTTON_L,
    [ConfigOptions::P2_UPLEFT_SWITCH] = EEPROM_SWITCH_BUTTON_A,
    [ConfigOptions::P2_UPRIGHT_SWITCH] = EEPROM_SWITCH_BUTTON_B,
    [ConfigOptions::P2_CENTER_SWITCH] = EEPROM_SWITCH_BUTTON_X,
    [ConfigOptions::P2_DOWNLEFT_SWITCH] = EEPROM_SWITCH_BUTTON_Y,
    [ConfigOptions::P2_DOWNRIGHT_SWITCH] = EEPROM_SWITCH_BUTTON_R,
    [ConfigOptions::P1_COIN_SWITCH] = EEPROM_SWITCH_BUTTON_MINUS,
    [ConfigOptions::P2_COIN_SWITCH] = EEPROM_SWITCH_BUTTON_PLUS,
    [ConfigOptions::TEST_BUTTON_SWITCH] = EEPROM_SWITCH_BUTTON_ZL,
    [ConfigOptions::SERVICE_BUTTON_SWITCH] = EEPROM_SWITCH_BUTTON_ZR,
    [ConfigOptions::CLEAR_BUTTON_SWITCH] = EEPROM_SWITCH_BUTTON_CAPTURE,

    [ConfigOptions::MIDI_ANALOG] = EEPROM_TRUE,
    [ConfigOptions::MIDI_ANALOG_MIN] = MIDI_MIN_VELOCITY,
    [ConfigOptions::MIDI_ANALOG_MAX] = MIDI_MAX_VELOCITY,
    [ConfigOptions::MIDI_CHANNEL] = DEFAULT_MIDI_CHANNEL,

    [ConfigOptions::MIDI_USE_FIRST_BYTE] = EEPROM_FALSE,

    [ConfigOptions::P1_UPLEFT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P1_UPLEFT_MIDI1] = 60,  // C5
    [ConfigOptions::P1_UPLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P1_UPLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P1_UPRIGHT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P1_UPRIGHT_MIDI1] = 61,
    [ConfigOptions::P1_UPRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P1_UPRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P1_CENTER_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P1_CENTER_MIDI1] = 62,
    [ConfigOptions::P1_CENTER_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P1_CENTER_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P1_DOWNLEFT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P1_DOWNLEFT_MIDI1] = 63,
    [ConfigOptions::P1_DOWNLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P1_DOWNLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P1_DOWNRIGHT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P1_DOWNRIGHT_MIDI1] = 64,
    [ConfigOptions::P1_DOWNRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P1_DOWNRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P2_UPLEFT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P2_UPLEFT_MIDI1] = 65,
    [ConfigOptions::P2_UPLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P2_UPLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P2_UPRIGHT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P2_UPRIGHT_MIDI1] = 66,
    [ConfigOptions::P2_UPRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P2_UPRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P2_CENTER_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P2_CENTER_MIDI1] = 67,
    [ConfigOptions::P2_CENTER_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P2_CENTER_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P2_DOWNLEFT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P2_DOWNLEFT_MIDI1] = 68,
    [ConfigOptions::P2_DOWNLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P2_DOWNLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P2_DOWNRIGHT_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P2_DOWNRIGHT_MIDI1] = 69,
    [ConfigOptions::P2_DOWNRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P2_DOWNRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P1_COIN_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P1_COIN_MIDI1] = 70,
    [ConfigOptions::P1_COIN_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P1_COIN_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::P2_COIN_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::P2_COIN_MIDI1] = 71,
    [ConfigOptions::P2_COIN_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::P2_COIN_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::TEST_BUTTON_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::TEST_BUTTON_MIDI1] = 72,
    [ConfigOptions::TEST_BUTTON_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::TEST_BUTTON_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::SERVICE_BUTTON_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::SERVICE_BUTTON_MIDI1] = 73,
    [ConfigOptions::SERVICE_BUTTON_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::SERVICE_BUTTON_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [ConfigOptions::CLEAR_BUTTON_MIDI0] = MIDI_NOTE_ON,
    [ConfigOptions::CLEAR_BUTTON_MIDI1] = 74,
    [ConfigOptions::CLEAR_BUTTON_MIDI2] = MIDI_STANDARD_VELOCITY,
    [ConfigOptions::CLEAR_BUTTON_CHANNEL] = DEFAULT_MIDI_CHANNEL,

    [ConfigOptions::P1_UPLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P1_UPRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P1_CENTER_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P1_DOWNLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P1_DOWNRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P2_UPLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P2_UPRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P2_CENTER_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P2_DOWNLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P2_DOWNRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P1_COIN_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::P2_COIN_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::TEST_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::SERVICE_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::CLEAR_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
    [ConfigOptions::EXTRA_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
};


#endif