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

#ifndef _BOARDCOMM_H
#define _BOARDCOMM_H

#include "Config.h"

class BoardComm
{
    public:
        virtual void setup() = 0;
        virtual void setPlayer(uint8_t player) = 0;
        virtual void attachInputPacket(uint32_t* buf) = 0;  // read and written to
        virtual void parseMessage(uint8_t msg) = 0;
        virtual void update() = 0;

};

enum BoardCommMethod {
    None,
    SPI,
    I2C
};

#endif