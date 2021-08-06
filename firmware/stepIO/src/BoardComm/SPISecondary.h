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

#ifndef _SPISECONDARY_H
#define _SPISECONDARY_H

#include "../Config.h"

class SPISecondary
{
    public:
        inline static void begin() {
            pinMode(MISO, OUTPUT);  // set MISO as output
            // SS, MOSI and SCK should all be inputs
            pinMode(SS, INPUT);  // unused currently
            pinMode(MOSI, INPUT);
            pinMode(SCK, INPUT);

            SPCR |= _BV(SPE);  // enable SPI in secondary mode
            SPCR |= _BV(SPIE);  // enable interrupts
        };
        // inline static void setClockDivider(uint8_t clockDiv) {
        //     SPI.setClockDivider(clockDiv);
        // };
        inline static uint8_t transfer(uint8_t data) {
            return SPI.transfer(data);
        };
        inline static uint16_t transfer16(uint16_t data) {
            return SPI.transfer16(data);
        };
        inline static void transfer(void* buf, size_t count) {
            SPI.transfer(buf, count);
        };
        inline static void end() {
            SPI.end();
        };
        // inline static void endTransaction() {
        //     SPI.endTransaction();
        // };
};

#endif