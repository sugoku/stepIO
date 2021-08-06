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
/*  SPDX-License-Identifier: GPL-3.0-or-later             */
/*  https://github.com/sugoku/stepIO                      */
/**********************************************************/

#ifndef _DEFAULTS_H
#define _DEFAULTS_H

#include "Config.h"
#include "Output/Output.h"
#include "Input/Input.h"
#include "Lights/Lights.h"

// These are the default settings which will be loaded into stepIO/brokeIO on first boot, change as needed
const uint8_t defaults[256] PROGMEM = {
    [(int)ConfigOptions::VERSION_MODEL] = STEPIO_VERSION_MODEL,
    [(int)ConfigOptions::VERSION_MAJOR] = STEPIO_VERSION_MAJOR,
    [(int)ConfigOptions::VERSION_MINOR] = STEPIO_VERSION_MINOR,
    [(int)ConfigOptions::VERSION_REVISION] = STEPIO_VERSION_REVISION,
    [(int)ConfigOptions::VERSION_GEN] = STEPIO_VERSION_GEN,

    [(int)ConfigOptions::UPDATE_STATUS] = (int)UpdateStatus::SUCCESS,
    [(int)ConfigOptions::LAST_ERROR] = (int)RuntimeError::NONE,
    [(int)ConfigOptions::INPUT_TYPE] = EEPROM_DEFAULT_VALUE,  // unused
    #ifdef SIMPLE_IO
        [(int)ConfigOptions::INPUT_MODE] = (int)InputMode::MUX4067_Dual,
    #else
        [(int)ConfigOptions::INPUT_MODE] = InputMode::Software,
    #endif
    [(int)ConfigOptions::MUX_POLLING_MODE] = (int)MUXPollingMode::Normal,
    #ifdef SIMPLE_PIUIO_MUX
        [(int)ConfigOptions::MUX_SIMPLE] = EEPROM_TRUE,
    #else
        [(int)ConfigOptions::MUX_SIMPLE] = EEPROM_FALSE
    #endif

    [(int)ConfigOptions::OUTPUT_MODE] = (int)OutputMode::PIUIO,
    #ifdef SIMPLE_IO
        [(int)ConfigOptions::LIGHTS_MODE] = (int)LightsMode::Latch32,
    #else
        [(int)ConfigOptions::LIGHTS_MODE] = LightsMode::Signal,
    #endif
    [(int)ConfigOptions::LIGHTS_FROM_SENSORS] = EEPROM_FALSE,
    [(int)ConfigOptions::DEVICE_MODE] = DEVICE_PRIMARY,
    [(int)ConfigOptions::DEBOUNCE_MODE] = EEPROM_DEFAULT_VALUE,  // not implemented yet

    [(int)ConfigOptions::PLAYER] = DEFAULT_PLAYER,
    [(int)ConfigOptions::PANEL_COUNT] = PANELS_PER_PLAYER,
    [(int)ConfigOptions::P1BUTTON_COUNT] = PLAYER_1_BUTTONS,
    [(int)ConfigOptions::P2BUTTON_COUNT] = PLAYER_2_BUTTONS,
    [(int)ConfigOptions::OTHERBUTTON_COUNT] = OTHER_BUTTONS,

    [(int)ConfigOptions::BLOCKED_INPUTS_0] = DEFAULT_BLOCKED_INPUTS_0,
    [(int)ConfigOptions::BLOCKED_INPUTS_1] = DEFAULT_BLOCKED_INPUTS_1,
    [(int)ConfigOptions::BLOCKED_INPUTS_2] = DEFAULT_BLOCKED_INPUTS_2,
    [(int)ConfigOptions::BLOCKED_INPUTS_3] = DEFAULT_BLOCKED_INPUTS_3,

    [(int)ConfigOptions::BLOCKED_INPUTS_MUX0_0] = DEFAULT_BLOCKED_INPUTS_0,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX0_1] = DEFAULT_BLOCKED_INPUTS_1,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX0_2] = DEFAULT_BLOCKED_INPUTS_2,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX0_3] = DEFAULT_BLOCKED_INPUTS_3,

    [(int)ConfigOptions::BLOCKED_INPUTS_MUX1_0] = DEFAULT_BLOCKED_INPUTS_0,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX1_1] = DEFAULT_BLOCKED_INPUTS_1,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX1_2] = DEFAULT_BLOCKED_INPUTS_2,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX1_3] = DEFAULT_BLOCKED_INPUTS_3,

    [(int)ConfigOptions::BLOCKED_INPUTS_MUX2_0] = DEFAULT_BLOCKED_INPUTS_0,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX2_1] = DEFAULT_BLOCKED_INPUTS_1,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX2_2] = DEFAULT_BLOCKED_INPUTS_2,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX2_3] = DEFAULT_BLOCKED_INPUTS_3,

    [(int)ConfigOptions::BLOCKED_INPUTS_MUX3_0] = DEFAULT_BLOCKED_INPUTS_0,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX3_1] = DEFAULT_BLOCKED_INPUTS_1,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX3_2] = DEFAULT_BLOCKED_INPUTS_2,
    [(int)ConfigOptions::BLOCKED_INPUTS_MUX3_3] = DEFAULT_BLOCKED_INPUTS_3,

    [(int)ConfigOptions::BLOCKED_LIGHTS_0] = DEFAULT_BLOCKED_LIGHTS_0,
    [(int)ConfigOptions::BLOCKED_LIGHTS_1] = DEFAULT_BLOCKED_LIGHTS_1,
    [(int)ConfigOptions::BLOCKED_LIGHTS_2] = DEFAULT_BLOCKED_LIGHTS_2,
    [(int)ConfigOptions::BLOCKED_LIGHTS_3] = DEFAULT_BLOCKED_LIGHTS_3,

    // fix later
    [(int)ConfigOptions::SERIAL_BAUD_BYTE0] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::SERIAL_BAUD_BYTE1] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::SERIAL_BAUD_BYTE2] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::SERIAL_BAUD_BYTE3] = EEPROM_DEFAULT_VALUE,

    [(int)ConfigOptions::RGB_LED_COUNT] = DEFAULT_RGB_LED_COUNT,
    [(int)ConfigOptions::EXTRA_LED_TRIGGER] = EEPROM_DEFAULT_VALUE,

    [(int)ConfigOptions::LIGHT_P1_UPLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P1_UPRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P1_CENTER_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P1_DOWNLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P1_DOWNRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P2_UPLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P2_UPRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P2_CENTER_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P2_DOWNLEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_P2_DOWNRIGHT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_MARQUEE_1_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_MARQUEE_2_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_MARQUEE_3_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_MARQUEE_4_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_SUB_LEFT_REMAP] = EEPROM_DEFAULT_VALUE,
    [(int)ConfigOptions::LIGHT_SUB_RIGHT_REMAP] = EEPROM_DEFAULT_VALUE,

    [(int)ConfigOptions::P1_UPLEFT_REMAP] = (int)InputPacket::P1_UPLEFT,
    [(int)ConfigOptions::P1_UPRIGHT_REMAP] = (int)InputPacket::P1_UPRIGHT,
    [(int)ConfigOptions::P1_CENTER_REMAP] = (int)InputPacket::P1_CENTER,
    [(int)ConfigOptions::P1_DOWNLEFT_REMAP] = (int)InputPacket::P1_DOWNLEFT,
    [(int)ConfigOptions::P1_DOWNRIGHT_REMAP] = (int)InputPacket::P1_DOWNRIGHT,
    [(int)ConfigOptions::P2_UPLEFT_REMAP] = (int)InputPacket::P2_UPLEFT,
    [(int)ConfigOptions::P2_UPRIGHT_REMAP] = (int)InputPacket::P2_UPRIGHT,
    [(int)ConfigOptions::P2_CENTER_REMAP] = (int)InputPacket::P2_CENTER,
    [(int)ConfigOptions::P2_DOWNLEFT_REMAP] = (int)InputPacket::P2_DOWNLEFT,
    [(int)ConfigOptions::P2_DOWNRIGHT_REMAP] = (int)InputPacket::P2_DOWNRIGHT,
    [(int)ConfigOptions::P1_COIN_REMAP] = (int)InputPacket::P1_COIN,
    [(int)ConfigOptions::P2_COIN_REMAP] = (int)InputPacket::P2_COIN,
    [(int)ConfigOptions::TEST_BUTTON_REMAP] = (int)InputPacket::TEST_BUTTON,
    [(int)ConfigOptions::SERVICE_BUTTON_REMAP] = (int)InputPacket::SERVICE_BUTTON,
    [(int)ConfigOptions::CLEAR_BUTTON_REMAP] = (int)InputPacket::CLEAR_BUTTON,

    // keycodes from HID library
    [(int)ConfigOptions::P1_UPLEFT_KEYCODE] = (int)KeyboardKeycode::KEY_Q,
    [(int)ConfigOptions::P1_UPRIGHT_KEYCODE] = (int)KeyboardKeycode::KEY_E,
    [(int)ConfigOptions::P1_CENTER_KEYCODE] = (int)KeyboardKeycode::KEY_S,
    [(int)ConfigOptions::P1_DOWNLEFT_KEYCODE] = (int)KeyboardKeycode::KEY_Z,
    [(int)ConfigOptions::P1_DOWNRIGHT_KEYCODE] = (int)KeyboardKeycode::KEY_C,
    [(int)ConfigOptions::P2_UPLEFT_KEYCODE] = (int)KeyboardKeycode::KEYPAD_7,
    [(int)ConfigOptions::P2_UPRIGHT_KEYCODE] = (int)KeyboardKeycode::KEYPAD_9,
    [(int)ConfigOptions::P2_CENTER_KEYCODE] = (int)KeyboardKeycode::KEYPAD_5,
    [(int)ConfigOptions::P2_DOWNLEFT_KEYCODE] = (int)KeyboardKeycode::KEYPAD_1,
    [(int)ConfigOptions::P2_DOWNRIGHT_KEYCODE] = (int)KeyboardKeycode::KEYPAD_3,
    [(int)ConfigOptions::P1_COIN_KEYCODE] = (int)KeyboardKeycode::KEY_F1,
    [(int)ConfigOptions::P2_COIN_KEYCODE] = (int)KeyboardKeycode::KEY_F1,
    [(int)ConfigOptions::TEST_BUTTON_KEYCODE] = (int)KeyboardKeycode::KEY_SCROLL_LOCK,
    [(int)ConfigOptions::SERVICE_BUTTON_KEYCODE] = (int)KeyboardKeycode::KEY_ENTER,
    [(int)ConfigOptions::CLEAR_BUTTON_KEYCODE] = (int)KeyboardKeycode::KEY_ESC,

    // these are gamepad button numbers, there are 32 buttons total (0-31)
    [(int)ConfigOptions::P1_UPLEFT_GAMEPAD] = 0,
    [(int)ConfigOptions::P1_UPRIGHT_GAMEPAD] = 1,
    [(int)ConfigOptions::P1_CENTER_GAMEPAD] = 2,
    [(int)ConfigOptions::P1_DOWNLEFT_GAMEPAD] = 3,
    [(int)ConfigOptions::P1_DOWNRIGHT_GAMEPAD] = 4,
    [(int)ConfigOptions::P2_UPLEFT_GAMEPAD] = 5,
    [(int)ConfigOptions::P2_UPRIGHT_GAMEPAD] = 6,
    [(int)ConfigOptions::P2_CENTER_GAMEPAD] = 7,
    [(int)ConfigOptions::P2_DOWNLEFT_GAMEPAD] = 8,
    [(int)ConfigOptions::P2_DOWNRIGHT_GAMEPAD] = 9,
    [(int)ConfigOptions::P1_COIN_GAMEPAD] = 10,
    [(int)ConfigOptions::P2_COIN_GAMEPAD] = 11,
    [(int)ConfigOptions::TEST_BUTTON_GAMEPAD] = 12,
    [(int)ConfigOptions::SERVICE_BUTTON_GAMEPAD] = 13,
    [(int)ConfigOptions::CLEAR_BUTTON_GAMEPAD] = 14,

    // there are 14 buttons, 9 hat directions, also two sticks analog X and Y
    [(int)ConfigOptions::P1_UPLEFT_SWITCH] = EEPROM_SWITCH_HAT_TOP,
    [(int)ConfigOptions::P1_UPRIGHT_SWITCH] = EEPROM_SWITCH_HAT_RIGHT,
    [(int)ConfigOptions::P1_CENTER_SWITCH] = EEPROM_SWITCH_HAT_LEFT,
    [(int)ConfigOptions::P1_DOWNLEFT_SWITCH] = EEPROM_SWITCH_HAT_BOTTOM,
    [(int)ConfigOptions::P1_DOWNRIGHT_SWITCH] = EEPROM_SWITCH_BUTTON_L,
    [(int)ConfigOptions::P2_UPLEFT_SWITCH] = EEPROM_SWITCH_BUTTON_A,
    [(int)ConfigOptions::P2_UPRIGHT_SWITCH] = EEPROM_SWITCH_BUTTON_B,
    [(int)ConfigOptions::P2_CENTER_SWITCH] = EEPROM_SWITCH_BUTTON_X,
    [(int)ConfigOptions::P2_DOWNLEFT_SWITCH] = EEPROM_SWITCH_BUTTON_Y,
    [(int)ConfigOptions::P2_DOWNRIGHT_SWITCH] = EEPROM_SWITCH_BUTTON_R,
    [(int)ConfigOptions::P1_COIN_SWITCH] = EEPROM_SWITCH_BUTTON_MINUS,
    [(int)ConfigOptions::P2_COIN_SWITCH] = EEPROM_SWITCH_BUTTON_PLUS,
    [(int)ConfigOptions::TEST_BUTTON_SWITCH] = EEPROM_SWITCH_BUTTON_ZL,
    [(int)ConfigOptions::SERVICE_BUTTON_SWITCH] = EEPROM_SWITCH_BUTTON_ZR,
    [(int)ConfigOptions::CLEAR_BUTTON_SWITCH] = EEPROM_SWITCH_BUTTON_CAPTURE,

    [(int)ConfigOptions::MIDI_ANALOG] = EEPROM_TRUE,
    [(int)ConfigOptions::MIDI_ANALOG_MIN] = MIDI_MIN_VELOCITY,
    [(int)ConfigOptions::MIDI_ANALOG_MAX] = MIDI_MAX_VELOCITY,
    [(int)ConfigOptions::MIDI_CHANNEL] = DEFAULT_MIDI_CHANNEL,

    [(int)ConfigOptions::MIDI_USE_FIRST_BYTE] = EEPROM_FALSE,

    [(int)ConfigOptions::P1_UPLEFT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P1_UPLEFT_MIDI1] = 60,  // C5
    [(int)ConfigOptions::P1_UPLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P1_UPLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P1_UPRIGHT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P1_UPRIGHT_MIDI1] = 61,
    [(int)ConfigOptions::P1_UPRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P1_UPRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P1_CENTER_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P1_CENTER_MIDI1] = 62,
    [(int)ConfigOptions::P1_CENTER_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P1_CENTER_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P1_DOWNLEFT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P1_DOWNLEFT_MIDI1] = 63,
    [(int)ConfigOptions::P1_DOWNLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P1_DOWNLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P1_DOWNRIGHT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P1_DOWNRIGHT_MIDI1] = 64,
    [(int)ConfigOptions::P1_DOWNRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P1_DOWNRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P2_UPLEFT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P2_UPLEFT_MIDI1] = 65,
    [(int)ConfigOptions::P2_UPLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P2_UPLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P2_UPRIGHT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P2_UPRIGHT_MIDI1] = 66,
    [(int)ConfigOptions::P2_UPRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P2_UPRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P2_CENTER_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P2_CENTER_MIDI1] = 67,
    [(int)ConfigOptions::P2_CENTER_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P2_CENTER_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P2_DOWNLEFT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P2_DOWNLEFT_MIDI1] = 68,
    [(int)ConfigOptions::P2_DOWNLEFT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P2_DOWNLEFT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P2_DOWNRIGHT_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P2_DOWNRIGHT_MIDI1] = 69,
    [(int)ConfigOptions::P2_DOWNRIGHT_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P2_DOWNRIGHT_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P1_COIN_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P1_COIN_MIDI1] = 70,
    [(int)ConfigOptions::P1_COIN_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P1_COIN_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::P2_COIN_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::P2_COIN_MIDI1] = 71,
    [(int)ConfigOptions::P2_COIN_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::P2_COIN_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::TEST_BUTTON_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::TEST_BUTTON_MIDI1] = 72,
    [(int)ConfigOptions::TEST_BUTTON_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::TEST_BUTTON_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::SERVICE_BUTTON_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::SERVICE_BUTTON_MIDI1] = 73,
    [(int)ConfigOptions::SERVICE_BUTTON_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::SERVICE_BUTTON_CHANNEL] = DEFAULT_MIDI_CHANNEL,
    [(int)ConfigOptions::CLEAR_BUTTON_MIDI0] = MIDI_NOTE_ON,
    [(int)ConfigOptions::CLEAR_BUTTON_MIDI1] = 74,
    [(int)ConfigOptions::CLEAR_BUTTON_MIDI2] = MIDI_STANDARD_VELOCITY,
    [(int)ConfigOptions::CLEAR_BUTTON_CHANNEL] = DEFAULT_MIDI_CHANNEL,

    [(int)ConfigOptions::P1_UPLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P1_UPRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P1_CENTER_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P1_DOWNLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P1_DOWNRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P2_UPLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P2_UPRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P2_CENTER_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P2_DOWNLEFT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P2_DOWNRIGHT_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P1_COIN_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::P2_COIN_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::TEST_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::SERVICE_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::CLEAR_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
    [(int)ConfigOptions::EXTRA_BUTTON_ANALOG] = DEFAULT_ANALOG_VALUE,
};


#endif
