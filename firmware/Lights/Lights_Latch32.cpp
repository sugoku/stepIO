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

#include "Lights_Latch32.h"

void Lights_Latch32::setup() {
    #ifndef SOFTWARE_LATCH
        // set pinModes for non-native SPI pins
        SETBIT(LATCH_ENABLE_MODE, LATCH_ENABLE_PIN);
        SETBIT(LATCH_RST_MODE, LATCH_RST_PIN);
        SETBIT(LATCH_RCLK_MODE, LATCH_RCLK_PIN);
        pinMode(SPIMODE, OUTPUT);  // is this necessary?

        SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    #else
        // something else with more pins set to output
    #endif

    CLRBIT(LATCH_ENABLE_PORT, LATCH_ENABLE_PIN);
    SETBIT(LATCH_RST_PORT, LATCH_RST_PIN);
    SETBIT(LATCH_RCLK_PORT, LATCH_RCLK_PIN);
}

uint32_t Lights_Latch32::send(uint32_t* buf) {
    // tell latch to receive from SPI
    CLRBIT(LATCH_RCLK_PORT, LATCH_RCLK_PIN);

    // worst case 10-15ns needed according to datasheet
    // delayMicroseconds(1);
    #ifndef SOFTWARE_LATCH
        SPI.transfer((uint8_t)((buf & 0xFF000000) >> 24));
        SPI.transfer((uint8_t)((buf & 0x00FF0000) >> 16));
        SPI.transfer((uint8_t)((buf & 0x0000FF00) >> 8));
        SPI.transfer((uint8_t)((buf & 0x000000FF)));
    #else
        shiftOut(SER, SRCLK, MSBFIRST, (uint8_t)((buf & 0xFF000000) >> 24));
        shiftOut(SER, SRCLK, MSBFIRST, (uint8_t)((buf & 0x00FF0000) >> 16));
        shiftOut(SER, SRCLK, MSBFIRST, (uint8_t)((buf & 0x0000FF00) >> 8));
        shiftOut(SER, SRCLK, MSBFIRST, (uint8_t)((buf & 0x000000FF)));
    #endif

    // tell latch to update values with what we just sent
    SETBIT(LATCH_RCLK_PORT, LATCH_RCLK_PIN);
}

void Lights_Latch32::enable() {
    CLRBIT(LATCH_ENABLE_PORT, LATCH_ENABLE_PIN);
}

void Lights_Latch32::disable() {
    SETBIT(LATCH_ENABLE_PORT, LATCH_ENABLE_PIN);
}

void Lights_Latch32::reset() {
    CLRBIT(LATCH_RST_PORT, LATCH_RST_PIN);
    delayMicroseconds(1);  // just in case the latch takes some time to notice and reset
    SETBIT(LATCH_RST_PORT, LATCH_RST_PIN);
}