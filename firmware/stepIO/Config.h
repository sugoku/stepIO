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

#ifndef _CONFIG_H
#define _CONFIG_H

#include <Arduino.h>

#include <USBAPI.h>
#include <USBCore.h>
#include <USBDesc.h>

#include <HID-Project.h>
#include <SPI.h>

// IF YOU ARE USING A SIMPLE_IO, UNCOMMENT THIS
#define SIMPLE_IO

#define PINCONFIG

// Configuration options, change if you need to reduce the program's size or fix things
// (all of this functionality can be configured and saved in real-time so don't remove unless you need to!)

// #define TREAT_AS_FIRST_BOOT  // Reload defaults if something isn't working for some reason

// #define SERIAL_ENABLED  // Not working yet, serial interface accessible through host to configure boards

#define ANALOG  // Support for load-cells, velostat, FSRs, etc.
#define ANALOG_AUTO_CALIBRATION

#define DEFAULT_ANALOG_VALUE 200  // Default analog threshold from 0-255

#define DEBOUNCING  // Prevents double-stepping and odd sensor behavior (not used in analog mode)
#ifndef SIMPLE_IO
    #define HARDWARE_DEBOUNCING  // Debounces directly through hardware for faster performance
#endif
// Below settings are for software debouncing ONLY (using Bounce2 library)
#define SW_DEBOUNCING_INTERVAL  // Interval in milliseconds to wait for stable signal
#define BOUNCE_LOCK_OUT // More responsive but does not wait for noise (ignores debouncing interval)

#define DMA_INPUT  // Direct memory access for faster performance

#define LIGHT_OUTPUT  // Enables light support
#ifndef SIMPLE_IO
    #define LIGHT_PAD_OUTPUT  // Enables pad lighting support
    #define LIGHT_LATCH_OUTPUT  // Enables support for cabinet light outputs using the 74HC595
#endif
#define LIGHT_RGB_OUTPUT  // Enables support for RGB lighting via FastLED

#define DEFAULT_RGB_LED_COUNT 288  // Default amount of RGB LEDs to use
#define DEFAULT_LED_COLORS {0, 230, 255};  // Default LED colors in RGB order (this is bright blue like the subwoofer neons)

// Advanced configuration options

#define SERIAL_CONFIG Serial  // This is the serial port used to send commands/access configuration.
// Serial usually refers to the USB serial connection while Serial1, Serial2, etc. are hardware serial ports with TX and RX pins.

#define SIMPLE_PIUIO_MUX  // Comment out if you want to request separate P1 and P2 multiplexer values in the same packet (no reason to normally do this)

#define SERIAL_BAUD 115200  // Change this to affect the speed at which data is sent on USB serial

#define EEPROM_ENABLED  // Comment out if you aren't using EEPROM (custom PCB maybe)
#define PULLUP_IN  // Comment out if you do not want to use pull-up resistors for digital inputs

#ifndef SIMPLE_IO
    #define EEPROM_EXTERNAL  // Use an external EEPROM (should be defaulted to for non-AVR microcontrollers)
#endif

#define EEPROM_DEFAULT_VALUE 0xFF  // The default value of all data in the EEPROM. For ATmega chips with built in EEPROM this is 0xFF.
// You would probably want this value to be correct to ensure that you don't waste write cycles when writing the initial configuration to EEPROM.

#define EEPROM_FIRST_TIME false  // Write defaults into EEPROM every time at startup (for debug only, this will shorten the lifespan of the EEPROM)
// Set this to a boolean and don't comment it out

// Don't edit anything below unless you know what you're doing!

// Let me know if you have a use for I2C which doesn't involve the EEPROM, in that case we can include Wire.h with a separate define.
#ifdef EEPROM_EXTERNAL
    #include <Wire.h>
    #include <extEEPROM.h>
#endif

#define CONFIG_SIZE 256  // size of config array

// PORT MANIPULATION MACROS

#define GETBIT(port,bit) ((port) & (1 << (bit)))     // get value at bit
#define SETBIT(port,bit) ((port) |= (1 << (bit)))    // set bit to 1
#define CLRBIT(port,bit) ((port) &= ~(1 << (bit)))   // set bit to 0 (clear bit)
#define SETORCLRBIT(port,bit,val) if (val) { SETBIT(port,bit); } else { CLRBIT(port,bit); }  // if true, set bit to 1, if false, clear bit to 0

#define ORBIT(port,bit,val) ((port) |= (val << (bit))
#define ANDBIT(port,bit,val) ((port) &= ~(!val << (bit))  // i think this makes sense?

// OTHER MACROS

#define LOOP_FOREVER for(;;){}  // useful to force a reset as long as watchdog is enabled

#define WATCHDOG_TIMEOUT 1000  // in milliseconds
#if defined(__SAM3X8E__)
    #define WATCHDOG_ENABLE watchdogEnable(WATCHDOG_TIMEOUT)
    #define WATCHDOG_RESET watchdogReset()
#elif defined(__AVR__)
    #include <avr/wdt.h>
    #define WATCHDOG_ENABLE wdt_enable(WATCHDOG_TIMEOUT)
    #define WATCHDOG_RESET wdt_reset()
#else
    #define WATCHDOG_ENABLE
    #define WATCHDOG_RESET
#endif


// STEPIO INFO

#define STEPIO_MANUFACTURER "sugoku"

// test PID, should not be used in production!
#define STEPIO_VID 0x1209
#define STEPIO_PID 0x0001

#define STEPIO_VERSION_GEN 0x02

#ifndef SIMPLE_IO

    #define STEPIO_VERSION_MODEL 0x01  // stepIO
    #define STEPIO_VERSION_MAJOR 0x00
    #define STEPIO_VERSION_MINOR 0x01
    #define STEPIO_VERSION_REVISION 0x01  // an alternate version number which must be greater than 0x00 and less than 0xFF, otherwise EEPROM resets

    #define STEPIO_PRODUCT "stepIO"

#else

    #define STEPIO_VERSION_MODEL 0x03  // susIO
    #define STEPIO_VERSION_MAJOR 0x00
    #define STEPIO_VERSION_MINOR 0x01
    #define STEPIO_VERSION_REVISION 0x01

    #define STEPIO_PRODUCT "susIO"

#endif

// #define REPORT_ACTUAL_VERSION

#ifdef REPORT_ACTUAL_VERSION
    #define STEPIO_VERSION_USB (STEPIO_VERSION_MAJOR << 2) | (STEPIO_VERSION_MINOR << 1)
#else
    #define STEPIO_VERSION_USB STEPIO_VERSION_MODEL << 2
#endif

#define STEPIO_DEVICE_DESCRIPTOR D_DEVICE(  \
    0xEF,   \
    0x02,   \
    0x01,   \
    USB_EP_SIZE,    \
    STEPIO_VID,     \
    STEPIO_PID,     \
    STEPIO_VERSION_USB,  \
    IMANUFACTURER,  \
    IPRODUCT,   \
    ISERIAL,    \
    1  \
)

// to use actual version under version, use 

// EF,02,01 are three magic bytes which indicate that the board has multiple IADs
// 1 at the end indicates one configuration




// DEVICE MODE

#define DEVICE_PRIMARY 0x01
#define DEVICE_SECONDARY 0x02

// PLAYERS

// this stuff is currently unused but if button board support is added it probably will matter more
#define PLAYER_1 0x0
#define PLAYER_2 0x1
#define DEFAULT_PLAYER PLAYER_1
#define DEFAULT_PLAYER_COUNT 2
#define PANELS_PER_PLAYER 5
#define PLAYER_1_BUTTONS 5  // p1 coin, left, right, select, back
#define PLAYER_2_BUTTONS 5  // p2 coin, left, right, select, back
#define OTHER_BUTTONS 3  // test, service, clear

// PINS

#ifndef SIMPLE_IO
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

    enum class MUX1 {
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

    enum class LIGHTOUT {
        LAMP_1,
        LAMP_2,
        LAMP_3,
        LAMP_4,
        SUB_LEFT,
        SUB_RIGHT
    };

// SIMPLE_IO PINS
#else

    #define MUX1_IN 13      // PC7
    #define MUX1_IN_READ PINC
    #define MUX1_IN_PORT PORTC
    #define MUX1_IN_MODE DDRC
    #define MUX1_IN_PIN 7

    #define MUX_S0 9        // PB5
    #define MUX_S0_READ PINB
    #define MUX_S0_PORT PORTB
    #define MUX_S0_MODE DDRB
    #define MUX_S0_PIN 5

    #define MUX_S1 10       // PB6
    #define MUX_S1_READ PINB
    #define MUX_S1_PORT PORTB
    #define MUX_S1_MODE DDRB
    #define MUX_S1_PIN 6

    #define MUX_S2 5        // PC6
    #define MUX_S2_READ PINC
    #define MUX_S2_PORT PORTC
    #define MUX_S2_MODE DDRC
    #define MUX_S2_PIN 6

    #define SENSOR_1 A1     // PF6
    #define SENSOR_1_READ PINF
    #define SENSOR_1_PORT PORTF
    #define SENSOR_1_MODE DDRF
    #define SENSOR_1_PIN 6

    #define SENSOR_2 A2     // PF5
    #define SENSOR_2_READ PINF
    #define SENSOR_2_PORT PORTF
    #define SENSOR_2_MODE DDRF
    #define SENSOR_2_PIN 5

    #define SENSOR_3 A3     // PF4
    #define SENSOR_3_READ PINF
    #define SENSOR_3_PORT PORTF
    #define SENSOR_3_MODE DDRF
    #define SENSOR_3_PIN 4

    #define SENSOR_4 A4     // PF1
    #define SENSOR_4_READ PINF
    #define SENSOR_4_PORT PORTF
    #define SENSOR_4_MODE DDRF
    #define SENSOR_4_PIN 1

    #define SENSOR_5 A5     // PF0
    #define SENSOR_5_READ PINF
    #define SENSOR_5_PORT PORTF
    #define SENSOR_5_MODE DDRF
    #define SENSOR_5_PIN 0

    #define LIGHTSIG_1 A5   // PD4
    #define LIGHTSIG_1_READ PIND
    #define LIGHTSIG_1_PORT PORTD
    #define LIGHTSIG_1_MODE DDRD
    #define LIGHTSIG_1_PIN 4

    #define LIGHTSIG_2 12   // PD6
    #define LIGHTSIG_2_READ PIND
    #define LIGHTSIG_2_PORT PORTD
    #define LIGHTSIG_2_MODE DDRD
    #define LIGHTSIG_2_PIN 6

    #define LIGHTSIG_3 6    // PD7
    #define LIGHTSIG_3_READ PIND
    #define LIGHTSIG_3_PORT PORTD
    #define LIGHTSIG_3_MODE DDRD
    #define LIGHTSIG_3_PIN 7

    #define LIGHTSIG_4 8    // PB4
    #define LIGHTSIG_4_READ PINB
    #define LIGHTSIG_4_PORT PORTB
    #define LIGHTSIG_4_MODE DDRB
    #define LIGHTSIG_4_PIN 4

    #define LIGHTSIG_5 A0   // PF7
    #define LIGHTSIG_5_READ PINF
    #define LIGHTSIG_5_PORT PORTF
    #define LIGHTSIG_5_MODE DDRF
    #define LIGHTSIG_5_PIN 7

    // according to pins_arduino.h, SS, MOSI, MISO and SCK are assigned pins already and SPI library should handle our worries too

    enum class SIMPLE_IO_MUX_IN {
        COIN,
        TEST,
        SERVICE,
        CLEAR,
        CFG1,
        CFG2,
        CFG3,
        CFG4
    };

#endif

// EEPROM
// for external EEPROM which is needed for stepIO but not SIMPLE_IO

#define EEPROM_TRUE 0x01
#define EEPROM_FALSE 0x00

#ifndef SIMPLE_IO
    #define EEPROM_SIZE kbits_256  // size of EEPROM
    #define EEPROM_MAX_ADDR 0x7D00
    #define EEPROM_COUNT 1  // how many EEPROM chips in I2C lane
    #define EEPROM_ADDRESS 0x50
    #define EEPROM_SPEED extEEPROM::twiClock100kHz  // more electrically stable which works considering we don't need fast speeds to read bytes of EEPROM
#endif

// CONFIG ENUM

// this is also the EEPROM mapping as well
// SIMPLE_IO has 0x400 bytes (1000)
// stepIO has 256Kb = 0x7D00 bytes

// not everything is used yet but eventually they should be used
enum class ConfigOptions {
    VERSION_MODEL, // 0x0000
    VERSION_MAJOR, 
    VERSION_MINOR,
    VERSION_REVISION,
    VERSION_GEN,
    
    UPDATE_STATUS, // 0x0005
    LAST_ERROR,

    INPUT_TYPE,  // InputMUX vs. InputSensor (should go unused soon)
    INPUT_MODE,
    MUX_POLLING_MODE,  // normal, merged, etc.
    MUX_SIMPLE,  // basically if SIMPLE_PIUIO_MUX is enabled

    OUTPUT_MODE,  
    LIGHTS_MODE,  // light output mode
    LIGHTS_FROM_SENSORS,  // read lights directly from the sensor inputs instead of from the host
    DEVICE_MODE,  // primary vs. secondary
    DEBOUNCE_MODE,

    PLAYER,  // which player is the main PCB hooked up to? (no longer needed)
    PANEL_COUNT,  // number of panels per player (anything from 1-5)
    P1BUTTON_COUNT,  // number of buttons for player 1
    P2BUTTON_COUNT,  // number of buttons for player 2
    OTHERBUTTON_COUNT,  // number of non-player-specific buttons

    BLOCKED_INPUTS_0,  // inputs based on InputPacket to filter out and prevent the user from using (potentially good for polling or disabling coin mode)
    BLOCKED_INPUTS_1,  // 1 is not blocked, 0 is blocked (because AND operation used)
    BLOCKED_INPUTS_2,
    BLOCKED_INPUTS_3,

    BLOCKED_INPUTS_MUX0_0,
    BLOCKED_INPUTS_MUX0_1,
    BLOCKED_INPUTS_MUX0_2,
    BLOCKED_INPUTS_MUX0_3,
    
    BLOCKED_INPUTS_MUX1_0,
    BLOCKED_INPUTS_MUX1_1,
    BLOCKED_INPUTS_MUX1_2,
    BLOCKED_INPUTS_MUX1_3,
    
    BLOCKED_INPUTS_MUX2_0,
    BLOCKED_INPUTS_MUX2_1,
    BLOCKED_INPUTS_MUX2_2,
    BLOCKED_INPUTS_MUX2_3,

    BLOCKED_INPUTS_MUX3_0,
    BLOCKED_INPUTS_MUX3_1,
    BLOCKED_INPUTS_MUX3_2,
    BLOCKED_INPUTS_MUX3_3,

    BLOCKED_LIGHTS_0,  // 1 is not blocked, 0 is blocked (because AND operation used)
    BLOCKED_LIGHTS_1,  
    BLOCKED_LIGHTS_2,
    BLOCKED_LIGHTS_3,

    // LSB
    SERIAL_BAUD_BYTE0,
    SERIAL_BAUD_BYTE1,
    SERIAL_BAUD_BYTE2,
    SERIAL_BAUD_BYTE3,

    RGB_LED_COUNT,
    EXTRA_LED_TRIGGER,  // 0xFF default, means disabled (based on nth bit of LightsPacket)

    LIGHT_P1_UPLEFT_REMAP,  // for remapping lights (their position in the LightsPacket)
    LIGHT_P1_UPRIGHT_REMAP,
    LIGHT_P1_CENTER_REMAP,
    LIGHT_P1_DOWNLEFT_REMAP,
    LIGHT_P1_DOWNRIGHT_REMAP,
    LIGHT_P2_UPLEFT_REMAP,
    LIGHT_P2_UPRIGHT_REMAP,
    LIGHT_P2_CENTER_REMAP,
    LIGHT_P2_DOWNLEFT_REMAP,
    LIGHT_P2_DOWNRIGHT_REMAP,
    LIGHT_MARQUEE_1_REMAP,
    LIGHT_MARQUEE_2_REMAP,
    LIGHT_MARQUEE_3_REMAP,
    LIGHT_MARQUEE_4_REMAP,
    LIGHT_SUB_LEFT_REMAP,
    LIGHT_SUB_RIGHT_REMAP,

    P1_UPLEFT_REMAP,  // for remapping to other input (their position in the InputPacket)
    P1_UPRIGHT_REMAP,
    P1_CENTER_REMAP,
    P1_DOWNLEFT_REMAP,
    P1_DOWNRIGHT_REMAP,
    P2_UPLEFT_REMAP,
    P2_UPRIGHT_REMAP,
    P2_CENTER_REMAP,
    P2_DOWNLEFT_REMAP,
    P2_DOWNRIGHT_REMAP,
    P1_COIN_REMAP,
    P2_COIN_REMAP,
    TEST_BUTTON_REMAP,
    SERVICE_BUTTON_REMAP,
    CLEAR_BUTTON_REMAP,

    P1_UPLEFT_KEYCODE,  // for keyboard
    P1_UPRIGHT_KEYCODE,
    P1_CENTER_KEYCODE,
    P1_DOWNLEFT_KEYCODE,
    P1_DOWNRIGHT_KEYCODE,
    P2_UPLEFT_KEYCODE,
    P2_UPRIGHT_KEYCODE,
    P2_CENTER_KEYCODE,
    P2_DOWNLEFT_KEYCODE,
    P2_DOWNRIGHT_KEYCODE,
    P1_COIN_KEYCODE,
    P2_COIN_KEYCODE,
    TEST_BUTTON_KEYCODE,
    SERVICE_BUTTON_KEYCODE,
    CLEAR_BUTTON_KEYCODE,

    P1_UPLEFT_GAMEPAD,  // for gamepad
    P1_UPRIGHT_GAMEPAD,
    P1_CENTER_GAMEPAD,
    P1_DOWNLEFT_GAMEPAD,
    P1_DOWNRIGHT_GAMEPAD,
    P2_UPLEFT_GAMEPAD,
    P2_UPRIGHT_GAMEPAD,
    P2_CENTER_GAMEPAD,
    P2_DOWNLEFT_GAMEPAD,
    P2_DOWNRIGHT_GAMEPAD,
    P1_COIN_GAMEPAD,
    P2_COIN_GAMEPAD,
    TEST_BUTTON_GAMEPAD,
    SERVICE_BUTTON_GAMEPAD,
    CLEAR_BUTTON_GAMEPAD,

    P1_UPLEFT_SWITCH,  // for switch
    P1_UPRIGHT_SWITCH,
    P1_CENTER_SWITCH,
    P1_DOWNLEFT_SWITCH,
    P1_DOWNRIGHT_SWITCH,
    P2_UPLEFT_SWITCH,
    P2_UPRIGHT_SWITCH,
    P2_CENTER_SWITCH,
    P2_DOWNLEFT_SWITCH,
    P2_DOWNRIGHT_SWITCH,
    P1_COIN_SWITCH,
    P2_COIN_SWITCH,
    TEST_BUTTON_SWITCH,
    SERVICE_BUTTON_SWITCH,
    CLEAR_BUTTON_SWITCH,

    MIDI_ANALOG,  // if using analog input, send analog values as note velocity
    MIDI_ANALOG_MIN,
    MIDI_ANALOG_MAX,
    MIDI_CHANNEL,
    
    MIDI_USE_FIRST_BYTE,  // first byte (MIDI0) contains note on or note off info, enabling this bypasses note on and off signals by pressing and releasing

    P1_UPLEFT_MIDI0,  // for MIDI, defining a MIDI event in order of header (byte1 >> 4), byte0, byte1, byte2
    P1_UPLEFT_MIDI1,
    P1_UPLEFT_MIDI2,
    P1_UPLEFT_CHANNEL,
    P1_UPRIGHT_MIDI0,
    P1_UPRIGHT_MIDI1,
    P1_UPRIGHT_MIDI2,
    P1_UPRIGHT_CHANNEL,
    P1_CENTER_MIDI0,
    P1_CENTER_MIDI1,
    P1_CENTER_MIDI2,
    P1_CENTER_CHANNEL,
    P1_DOWNLEFT_MIDI0,
    P1_DOWNLEFT_MIDI1,
    P1_DOWNLEFT_MIDI2,
    P1_DOWNLEFT_CHANNEL,
    P1_DOWNRIGHT_MIDI0,
    P1_DOWNRIGHT_MIDI1,
    P1_DOWNRIGHT_MIDI2,
    P1_DOWNRIGHT_CHANNEL,
    P2_UPLEFT_MIDI0,
    P2_UPLEFT_MIDI1,
    P2_UPLEFT_MIDI2,
    P2_UPLEFT_CHANNEL,
    P2_UPRIGHT_MIDI0,
    P2_UPRIGHT_MIDI1,
    P2_UPRIGHT_MIDI2,
    P2_UPRIGHT_CHANNEL,
    P2_CENTER_MIDI0,
    P2_CENTER_MIDI1,
    P2_CENTER_MIDI2,
    P2_CENTER_CHANNEL,
    P2_DOWNLEFT_MIDI0,
    P2_DOWNLEFT_MIDI1,
    P2_DOWNLEFT_MIDI2,
    P2_DOWNLEFT_CHANNEL,
    P2_DOWNRIGHT_MIDI0,
    P2_DOWNRIGHT_MIDI1,
    P2_DOWNRIGHT_MIDI2,
    P2_DOWNRIGHT_CHANNEL,
    P1_COIN_MIDI0,
    P1_COIN_MIDI1,
    P1_COIN_MIDI2,
    P1_COIN_CHANNEL,
    P2_COIN_MIDI0,
    P2_COIN_MIDI1,
    P2_COIN_MIDI2,
    P2_COIN_CHANNEL,
    TEST_BUTTON_MIDI0,
    TEST_BUTTON_MIDI1,
    TEST_BUTTON_MIDI2,
    TEST_BUTTON_CHANNEL,
    SERVICE_BUTTON_MIDI0,
    SERVICE_BUTTON_MIDI1,
    SERVICE_BUTTON_MIDI2,
    SERVICE_BUTTON_CHANNEL,
    CLEAR_BUTTON_MIDI0,
    CLEAR_BUTTON_MIDI1,
    CLEAR_BUTTON_MIDI2,
    CLEAR_BUTTON_CHANNEL,

    P1_UPLEFT_ANALOG,
    P1_UPRIGHT_ANALOG,
    P1_CENTER_ANALOG,
    P1_DOWNLEFT_ANALOG,
    P1_DOWNRIGHT_ANALOG,
    P2_UPLEFT_ANALOG,
    P2_UPRIGHT_ANALOG,
    P2_CENTER_ANALOG,
    P2_DOWNLEFT_ANALOG,
    P2_DOWNRIGHT_ANALOG,
    P1_COIN_ANALOG,
    P2_COIN_ANALOG,
    TEST_BUTTON_ANALOG,
    SERVICE_BUTTON_ANALOG,
    CLEAR_BUTTON_ANALOG,
    EXTRA_BUTTON_ANALOG,
};
// INPUT/OUTPUT CONSTANTS

enum class InputPacket {
    P1_UPLEFT,
    P1_UPRIGHT,
    P1_CENTER,
    P1_DOWNLEFT,
    P1_DOWNRIGHT,
    P2_UPLEFT,
    P2_UPRIGHT,
    P2_CENTER,
    P2_DOWNLEFT,
    P2_DOWNRIGHT,
    P1_COIN,
    P2_COIN,
    TEST_BUTTON,
    SERVICE_BUTTON,
    CLEAR_BUTTON
};

#define INPUT_COUNT 15

enum class BoardCommInputPacket {
    UPLEFT,
    UPRIGHT,
    CENTER,
    DOWNLEFT,
    DOWNRIGHT,
    CMD_1,
    CMD_2,
    CMD_3
};

/*
const uint8_t INPUT_LIST[] = {
    InputPacket::P1_UPLEFT,
    InputPacket::P1_UPRIGHT,
    InputPacket::P1_CENTER,
    InputPacket::P1_DOWNLEFT,
    InputPacket::P1_DOWNRIGHT,
    InputPacket::P2_UPLEFT,
    InputPacket::P2_UPRIGHT,
    InputPacket::P2_CENTER,
    InputPacket::P2_DOWNLEFT,
    InputPacket::P2_DOWNRIGHT,
    InputPacket::P1_COIN,
    InputPacket::P2_COIN,
    InputPacket::TEST_BUTTON,
    InputPacket::SERVICE_BUTTON,
    InputPacket::CLEAR_BUTTON
}
*/

#define ALL_INPUTS_ON 0xFF

#define DEFAULT_BLOCKED_INPUTS_0 ALL_INPUTS_ON
#define DEFAULT_BLOCKED_INPUTS_1 ALL_INPUTS_ON
#define DEFAULT_BLOCKED_INPUTS_2 ALL_INPUTS_ON
#define DEFAULT_BLOCKED_INPUTS_3 ALL_INPUTS_ON

#define ALL_LIGHTS_ON 0xFF

#define DEFAULT_BLOCKED_LIGHTS_0 ALL_LIGHTS_ON
#define DEFAULT_BLOCKED_LIGHTS_1 ALL_LIGHTS_ON
#define DEFAULT_BLOCKED_LIGHTS_2 ALL_LIGHTS_ON
#define DEFAULT_BLOCKED_LIGHTS_3 ALL_LIGHTS_ON


enum class LightsPacket {
    P1_UPLEFT,
    P1_UPRIGHT,
    P1_CENTER,
    P1_DOWNLEFT,
    P1_DOWNRIGHT,
    P2_UPLEFT,
    P2_UPRIGHT,
    P2_CENTER,
    P2_DOWNLEFT,
    P2_DOWNRIGHT,
    MARQUEE_1,
    MARQUEE_2,
    MARQUEE_3,
    MARQUEE_4,
    SUB_LEFT,
    SUB_RIGHT
};

// least to most significant bit
enum class PIUIO_InputPacket {
    NC_0,
    P2_TEST,
    P2_COIN,
    NC_3,
    NC_4,
    NC_5,
    P2_SERVICE,
    P2_CLEAR,
    P2_UPLEFT,
    P2_UPRIGHT,
    P2_CENTER,
    P2_DOWNLEFT,
    P2_DOWNRIGHT,
    NC_13,
    NC_14,
    NC_15,
    NC_16,
    P1_TEST,
    P1_COIN,
    NC_19,
    NC_20,
    NC_21,
    P1_SERVICE,
    P1_CLEAR,
    P1_UPLEFT,
    P1_UPRIGHT,
    P1_CENTER,
    P1_DOWNLEFT,
    P1_DOWNRIGHT,
    NC_29,
    NC_30,
    NC_31
};
enum class PIUIO_LightsPacket {
    MARQUEE_3,
    MARQUEE_2,
    MARQUEE_1,
    NC_3,
    NC_4,
    NC_5,
    NC_6,
    NC_7,
    P2_MUXER_0,
    P2_MUXER_1,
    P2_UPLEFT,
    P2_UPRIGHT,
    P2_CENTER,
    P2_DOWNLEFT,
    P2_DOWNRIGHT,
    MARQUEE_4,
    NC_16,
    NC_17,
    SUB_NEON,
    NC_19,
    NC_20,
    NC_21,
    NC_22,
    NC_23,
    P1_MUXER_0,
    P1_MUXER_1,
    P1_UPLEFT,
    P1_UPRIGHT,
    P1_CENTER,
    P1_DOWNLEFT,
    P1_DOWNRIGHT,
    NC_31
};

#define PIUIO_ENDPOINT 0x00  // control endpoint
#define PIUIO_ADDRESS 0xAE
#define PIUIO_INDEX 0x00
#define PIUIO_VALUE 0x00

#define PIUIO_VID 0x0547
#define PIUIO_PID 0x1002

// both input and lights packets are 16 bytes but any bit after the enums is unused
enum class LXIO_InputPacket {
    P1_UPLEFT_0,  // right sensor
    P1_UPRIGHT_0,
    P1_CENTER_0,
    P1_DOWNLEFT_0,
    P1_DOWNRIGHT_0,
    NC_5,
    NC_6,
    NC_7,
    P1_UPLEFT_1,  // left sensor
    P1_UPRIGHT_1,
    P1_CENTER_1,
    P1_DOWNLEFT_1,
    P1_DOWNRIGHT_1,
    NC_13,
    NC_14,
    NC_15,
    P1_UPLEFT_2,  // bottom sensor
    P1_UPRIGHT_2,
    P1_CENTER_2,
    P1_DOWNLEFT_2,
    P1_DOWNRIGHT_2,
    NC_21,
    NC_22,
    NC_23,
    P1_UPLEFT_3,  // top sensor
    P1_UPRIGHT_3,
    P1_CENTER_3,
    P1_DOWNLEFT_3,
    P1_DOWNRIGHT_3,
    NC_29,
    NC_30,
    NC_31,
    P2_UPLEFT_0,  // right sensor
    P2_UPRIGHT_0,
    P2_CENTER_0,
    P2_DOWNLEFT_0,
    P2_DOWNRIGHT_0,
    NC_37,
    NC_38,
    NC_39,
    P2_UPLEFT_1,  // left sensor
    P2_UPRIGHT_1,
    P2_CENTER_1,
    P2_DOWNLEFT_1,
    P2_DOWNRIGHT_1,
    NC_45,
    NC_46,
    NC_47,
    P2_UPLEFT_2,  // bottom sensor
    P2_UPRIGHT_2,
    P2_CENTER_2,
    P2_DOWNLEFT_2,
    P2_DOWNRIGHT_2,
    NC_53,
    NC_54,
    NC_55,
    P2_UPLEFT_3,  // top sensor
    P2_UPRIGHT_3,
    P2_CENTER_3,
    P2_DOWNLEFT_3,
    P2_DOWNRIGHT_3,
    NC_61,
    NC_62,
    NC_63,
    NC_64,
    P1_TEST,
    P1_COIN,
    NC_67,
    NC_68,
    NC_69,
    P1_SERVICE,
    P1_CLEAR,
    NC_72,
    P2_TEST,
    P2_COIN,
    NC_75,
    NC_76,
    NC_77,
    P2_SERVICE,
    P2_CLEAR,
    P1_MENU_UPLEFT,
    P1_MENU_UPRIGHT,
    P1_MENU_CENTER,
    P1_MENU_DOWNLEFT,
    P1_MENU_DOWNRIGHT,
    NC_85,
    NC_86,
    NC_87,
    P2_MENU_UPLEFT,
    P2_MENU_UPRIGHT,
    P2_MENU_CENTER,
    P2_MENU_DOWNLEFT,
    P2_MENU_DOWNRIGHT,
    NC_93,
    NC_94,
    NC_95,
};
enum class LXIO_LightsPacket {
    NC_0,
    NC_1,
    P1_UPLEFT,
    P1_UPRIGHT,
    P1_CENTER,
    P1_DOWNLEFT,
    P1_DOWNRIGHT,
    NC_7,
    NC_8,
    NC_9,
    SUB_NEON,
    NC_10,
    NC_11,
    NC_12,
    NC_13,
    NC_14,
    NC_15,
    NC_16,
    NC_17,
    P2_UPLEFT,
    P2_UPRIGHT,
    P2_CENTER,
    P2_DOWNLEFT,
    P2_DOWNRIGHT,
    MARQUEE_1,  // order may be wrong
    MARQUEE_2,
    MARQUEE_3,
    MARQUEE_4,
    P1_COIN_COUNT,
    P2_COIN_COUNT,  // usb enable? USB_28
    USB_29,
    USB_30,
    USB_31,
    P1_MENU_UPLEFT,
    P1_MENU_UPRIGHT,
    P1_MENU_CENTER,
    P1_MENU_DOWNLEFT,
    P1_MENU_DOWNRIGHT,
    NC_37,
    NC_38,
    NC_39,
    P2_MENU_UPLEFT,
    P2_MENU_UPRIGHT,
    P2_MENU_CENTER,
    P2_MENU_DOWNLEFT,
    P2_MENU_DOWNRIGHT,
    NC_45,
    NC_46,
    NC_47,
};

// NINTENDO SWITCH

// bitshift, check 2nd digit
#define EEPROM_SWITCH_BUTTON 0x0
#define EEPROM_SWITCH_HAT 0x1
#define EEPROM_SWITCH_STICK 0x2

#define EEPROM_SWITCH_BUTTON_Y 0x00
#define EEPROM_SWITCH_BUTTON_B 0x01
#define EEPROM_SWITCH_BUTTON_A 0x02
#define EEPROM_SWITCH_BUTTON_X 0x03
#define EEPROM_SWITCH_BUTTON_L 0x04
#define EEPROM_SWITCH_BUTTON_R 0x05
#define EEPROM_SWITCH_BUTTON_ZL 0x06
#define EEPROM_SWITCH_BUTTON_ZR 0x07
#define EEPROM_SWITCH_BUTTON_MINUS 0x08
#define EEPROM_SWITCH_BUTTON_PLUS 0x09
#define EEPROM_SWITCH_BUTTON_LCLICK 0x0A
#define EEPROM_SWITCH_BUTTON_RCLICK 0x0B
#define EEPROM_SWITCH_BUTTON_HOME 0x0C
#define EEPROM_SWITCH_BUTTON_CAPTURE 0x0D

#define EEPROM_SWITCH_HAT_TOP 0x10
#define EEPROM_SWITCH_HAT_TOP_RIGHT 0x11
#define EEPROM_SWITCH_HAT_RIGHT 0x12
#define EEPROM_SWITCH_HAT_BOTTOM_RIGHT 0x13
#define EEPROM_SWITCH_HAT_BOTTOM 0x14
#define EEPROM_SWITCH_HAT_BOTTOM_LEFT 0x15
#define EEPROM_SWITCH_HAT_LEFT 0x16
#define EEPROM_SWITCH_HAT_TOP_LEFT 0x17
#define EEPROM_SWITCH_HAT_CENTER 0x18

#define EEPROM_SWITCH_STICK_LX 0x20
#define EEPROM_SWITCH_STICK_LY 0x21
#define EEPROM_SWITCH_STICK_RX 0x22
#define EEPROM_SWITCH_STICK_RY 0x23

#define SWITCH_VID 0x0F0D
#define SWITCH_PID 0x0092
#define SWITCH_MANUFACTURER "HORI CO.,LTD."  // unused
#define SWITCH_PRODUCT "POKKEN CONTROLLER"

// MIDI

#define DEFAULT_MIDI_CHANNEL 0

#define MIDI_MIN_VELOCITY 0x00
#define MIDI_MAX_VELOCITY 0xFF
#define MIDI_STANDARD_VELOCITY 100
#define DEFAULT_MIDI_VELOCITY MIDI_STANDARD_VELOCITY

// headers are shifted left one bit but second byte has them like this so you can |= channel
// https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
#define MIDI_NOTE_ON 0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_POLYPHONIC_AFTERTOUCH 0xB0
#define MIDI_CONTROL_CHANGE 0xB0
#define MIDI_PROGRAM_CHANGE 0xC0
#define MIDI_CHANNEL_AFTERTOUCH 0xD0
#define MIDI_PITCH_BEND 0xE0
#define MIDI_SYSEX 0xF0
#define MIDI_TIME_CODE 0xF1
#define MIDI_SONG_POSITION 0xF2
#define MIDI_SONG_SELECT 0xF3
#define MIDI_TUNE_REQUEST 0xF6
#define MIDI_SYSEX_END 0xF7
#define MIDI_TIMING_CLOCK 0xF8
#define MIDI_START 0xFA
#define MIDI_CONTINUE 0xFB
#define MIDI_STOP 0xFC
#define MIDI_ACTIVE_SENSING 0xFE
#define MIDI_SYSTEM_RESET 0xFF


// SERIAL COMMANDS

enum class SerialCommands {
    CHANGE_INPUT_MODE,
    CHANGE_OUTPUT_MODE,
    CHANGE_LIGHTS_MODE,
    LIGHTS_FROM_SENSORS,
    CHANGE_EXTRA_LIGHTS_MODE,
    CHANGE_MUX_POLLING_MODE,
    CHANGE_DEBOUNCE_MODE,
    SET_EXTRA_LED,
    RESET_EXTRA_LEDS,
    EDIT_INPUT,  // anything that corresponds to InputPacket, uint32_t and nth byte
    ANALOG_THRESHOLD,  // global or per input
    SAVE_TO_EEPROM,
    LOAD_FROM_EEPROM,
    GET_CONFIG,
    SET_CONFIG,
    SEND_INPUT,
    SEND_INPUT_ANALOG,
    GET_LIGHTSMUX,
    SEND_LIGHTSMUX,
    CHANGE_BAUD,
    RESET,
    STATUS_GET,
    SET_FACTORY_DEFAULTS,
    GET_DEVICE_INFO,
};

// outgoing messages (device -> host)
enum class SerialMessageTypes {
    STATUS,
    SENSOR,
    SENSOR_ANALOG,
    CONFIG,
    LIGHTS,
    DEVICE_INFO,
};

enum class SerialMessages {
    SUCCESS,
    ALIVE,
    ERROR_OVERFLOW,
    ERROR_SHORT,
    ERROR_UNKNOWN,
    NOT_IMPLEMENTED,
    ERROR_NOT_ATTACHED,
    RESET,
};


// UPDATES
// for stepIO bootloader only (if applicable)

enum class UpdateStatus {
    SUCCESS,
    PENDING_FLASH,
    FLASH_ERROR,
    NOT_FLASHED = 0xFF
};

// ERRORS

enum class WireError {  // I2C errors, EEPROM
    DATA_TOO_LONG = 1,
    NACK_ON_ADDR,
    NACK_ON_DATA,
    OTHER_ERROR
};

enum class RuntimeError {
    NONE = 0xFF
};


#endif