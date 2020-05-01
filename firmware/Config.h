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

#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>
#include <Wire.h>
#include <extEEPROM.h>


// Configuration options, change if you need to reduce the program's size or fix things
// (all of this functionality can be configured and saved in real-time so don't remove unless you need to!)

// #define TREAT_AS_FIRST_BOOT  // Reload defaults if something isn't working for some reason

#define ANALOG  // Support for load-cells, velostat, FSRs, etc.
#define ANALOG_AUTO_CALIBRATION

#define DEBOUNCING  // Prevents double-stepping and odd sensor behavior (not used in analog mode)
#define HARDWARE_DEBOUNCING  // Debounces directly through hardware for faster performance
// Below settings are for software debouncing ONLY (using Bounce2 library)
#define SW_DEBOUNCING_INTERVAL  // Interval in milliseconds to wait for stable signal
#define BOUNCE_LOCK_OUT // More responsive but does not wait for noise (ignores debouncing interval)

#define DMA_INPUT  // Direct memory access for faster performance

#define LIGHT_OUTPUT  // Enables light support
#define LIGHT_PAD_OUTPUT  // Enables pad lighting support
#define LIGHT_LATCH_OUTPUT  // Enables support for cabinet light outputs using the 74HC595
#define LIGHT_RGB_OUTPUT  // Enables support for RGB lighting via FastLED


// Advanced configuration options

#define EEPROM_ENABLED  // Comment out if you aren't using EEPROM (custom PCB maybe)


// Don't edit anything below unless you know what you're doing!

// VERSION INFO

#define STEPIO_VERSION_MAJOR 0x00
#define STEPIO_VERSION_MINOR 0x01
#define STEPIO_VERSION_REVISION 0x01
#define STEPIO_VERSION_GEN 0x02

// PLAYERS

#define PLAYER_1 0x0
#define PLAYER_2 0x1

// PINS

#define SENSOR_1 54   // PA16, A0
#define SENSOR_2 55   // PA24, A1
#define SENSOR_3 56   // PA23, A2
#define SENSOR_4 57   // PA22, A3
#define SENSOR_5 58   // PA6, A4
#define SENSOR_6 59   // PA4, A5
#define SENSOR_7 60   // PA3, A6
#define SENSOR_8 61   // PA2, A7
#define SENSOR_9 62   // PB17, A8
#define SENSOR_10 63  // PB18, A9

int SensorArr[] = {SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6, SENSOR_7, SENSOR_8, SENSOR_9, SENSOR_10};

#define P1COIN 23     // PA14
#define P2COIN 24     // PA15
#define DI_2 3        // PC28
#define TEST 7        // PC23
#define SERVICE 8     // PC22
#define CLEAR 2       // PB25

#define LIGHTSIG_1 33   // PC1
#define LIGHTSIG_2 34   // PC2
#define LIGHTSIG_3 35   // PC3
#define LIGHTSIG_4 36   // PC4
#define LIGHTSIG_5 37   // PC5
#define LIGHTSIG_6 38   // PC6
#define LIGHTSIG_7 39   // PC7
#define LIGHTSIG_8 40   // PC8
#define LIGHTSIG_9 41   // PC9
#define LIGHTSIG_10 51  // PC12

int LightsArr[] = {LIGHTSIG_1, LIGHTSIG_2, LIGHTSIG_3, LIGHTSIG_4, LIGHTSIG_5, LIGHTSIG_6, LIGHTSIG_7, LIGHTSIG_8, LIGHTSIG_9, LIGHTSIG_10};

#define SHIFT_DATA 27   // PD2
#define SHIFT_CLOCK 26  // PD1
#define SHIFT_LATCH 25  // PD0

#define M2PLEXED_IN 64  // PB19
#define MSELECT_0 30    // PD9
#define MSELECT_1 12    // PD8
#define MSELECT_2 11    // PD7
#define MSELECT_3 29    // PD6

#define M2PLEXED_IN 65  // PB20
#define M2SELECT_0 44   // PC19
#define M2SELECT_1 45   // PC18
#define M2SELECT_2 46   // PC17
#define M2SELECT_3 47   // PC16

#define RGB_DATA 43     // PA20
#define RGB_CLK 42      // PA19

#define CANTX0 69       // PA0
#define CANRX0 68       // PA1

#define STATUS12V 48    // PC15

enum MUX1 {
    BB1LEFT,
    BB1RIGHT,
    BB1SELECT,
    BB1BACK,
    BB1UP,
    BB1DOWN,
    MI_06,
    MI_07,
    BB2LEFT,
    BB2RIGHT,
    BB2SELECT,
    BB2UP,
    BB2DOWN,
    BB2BACK,
    MI_14,
    MI_15
};

enum LIGHTOUT {
    LAMP_1,
    LAMP_2,
    LAMP_3,
    LAMP_4,
    SUB_LEFT,
    SUB_RIGHT
};

// EEPROM

#define EEPROM_SIZE kbits_256  // size of EEPROM
#define EEPROM_MAX_ADDR 0x7D00
#define EEPROM_COUNT 1  // how many EEPROM chips in I2C lane
#define EEPROM_ADDRESS 0x50
#define EEPROM_SPEED extEEPROM::twiClock100kHz  // more electrically stable which works considering we don't need fast speeds to read bytes of EEPROM

// CONFIG ENUM

enum ConfigOptions {
    VERSION_MAJOR, // 0x0000
    VERSION_MINOR,
    VERSION_REVISION,
    VERSION_GEN,
    
    UPDATE_STATUS, // 0x0004
    LAST_ERROR,

    OUTPUT_MODE,  // 0x0006
    LIGHTS_MODE,  // for example, getting lights from whatever's hooked to USB? or internally through what's being pressed? or SPI?
    LIGHT_LATCH_MODE,  // either outputs cabinet lights,
    RGB_LIGHTS,  // RGB lighting mode

    PLAYER,  // 0x000A, which player is the main PCB hooked up to?
    PANEL_COUNT,  // number of panels per player (anything from 1-5)
    P1BUTTON_COUNT,  // number of buttons for player 1
    P2BUTTON_COUNT,  // number of buttons for player 2
    BUTTON_COUNT,  // number of non-player-specific buttons
}

/* probably going to use enum as default mapping
// EEPROM MAPPING

// 256Kb = 0x7D00 bytes

#define EADDR_VERSION_MAJOR 0x0001
#define EADDR_VERSION_MINOR 0x0002
#define EADDR_VERSION_REVISION 0x0003
#define EADDR_VERSION_GEN 0x0004

#define EADDR_UPDATE_STATUS 0x0006
#define EADDR_LAST_ERROR 0x0008

#define EADDR_OUTPUT_MODE 0x000A
#define EADDR_LIGHTS_MODE 0x000B  // for example, getting lights from whatever's hooked to USB? or internally through what's being pressed? or SPI?

#define EADDR_PLAYER 0x001A  // which player is the main PCB hooked up to?
#define EADDR_PANEL_COUNT 0x001B  // number of panels per player (anything from 1-5)
#define EADDR_PBUTTON_COUNT 0x001C  // number of buttons per player
#define EADDR_BUTTON_COUNT 0x001D  // number of non-player-specific buttons
*/

// SERIAL COMMANDS

#define SERIAL_CONFIG_HEADER 0xA1
#define SERIAL_CONFIG_CHANGE_MODE 0x03

// RUNTIME

#define WATCHDOG_TIMEOUT 1000  // in milliseconds


#endif