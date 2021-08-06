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

#ifndef _COMMPRIMARY_SPI_H
#define _COMMPRIMARY_SPI_H

#include "BoardComm.h"

class CommPrimary_SPI : public BoardComm
{
    protected:
        uint8_t lastmsg;
        uint8_t player;
        uint32_t* inpkt;

    public:
        uint8_t setup();
        inline void setPlayer(uint8_t player) { this->player = player; };
        inline void attachInputPacket(uint32_t* buf) { this->inpkt = buf; };
        void parseMessage(uint8_t msg);
        void update();
};

#endif