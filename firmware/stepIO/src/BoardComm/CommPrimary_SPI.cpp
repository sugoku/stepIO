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

#include "CommPrimary_SPI.h"

uint8_t CommPrimary_SPI::setup() {
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);

    return 0;
}

void CommPrimary_SPI::parseMessage(uint8_t msg) {
    // no messages in use yet
}

void CommPrimary_SPI::update() {
    uint8_t payload = 0;

    if (player == PLAYER_1) {
        SETORCLRBIT(payload, (int)BoardCommInputPacket::UPLEFT, GETBIT(*this->inpkt, (int)InputPacket::P1_UPLEFT));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::UPRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P1_UPRIGHT));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::CENTER, GETBIT(*this->inpkt, (int)InputPacket::P1_CENTER));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::DOWNLEFT, GETBIT(*this->inpkt, (int)InputPacket::P1_DOWNLEFT));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::DOWNRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P1_DOWNRIGHT));
    } else if (player == PLAYER_2) {
        SETORCLRBIT(payload, (int)BoardCommInputPacket::UPLEFT, GETBIT(*this->inpkt, (int)InputPacket::P2_UPLEFT));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::UPRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P2_UPRIGHT));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::CENTER, GETBIT(*this->inpkt, (int)InputPacket::P2_CENTER));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::DOWNLEFT, GETBIT(*this->inpkt, (int)InputPacket::P2_DOWNLEFT));
        SETORCLRBIT(payload, (int)BoardCommInputPacket::DOWNRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P2_DOWNRIGHT));
    }
    
    lastmsg = SPI.transfer(payload);

    if ((lastmsg >> 5) > 0) {
        this->parseMessage(lastmsg);
    } else {
        // populate opposite pad
        if (player == PLAYER_1) {
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P2_UPLEFT, GETBIT(lastmsg, (int)BoardCommInputPacket::UPLEFT));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P2_UPRIGHT, GETBIT(lastmsg, (int)BoardCommInputPacket::UPRIGHT));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P2_CENTER, GETBIT(lastmsg, (int)BoardCommInputPacket::CENTER));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P2_DOWNLEFT, GETBIT(lastmsg, (int)BoardCommInputPacket::DOWNLEFT));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P2_DOWNRIGHT, GETBIT(lastmsg, (int)BoardCommInputPacket::DOWNRIGHT));
        } else if (player == PLAYER_2) {
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P1_UPLEFT, GETBIT(lastmsg, (int)BoardCommInputPacket::UPLEFT));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P1_UPRIGHT, GETBIT(lastmsg, (int)BoardCommInputPacket::UPRIGHT));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P1_CENTER, GETBIT(lastmsg, (int)BoardCommInputPacket::CENTER));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P1_DOWNLEFT, GETBIT(lastmsg, (int)BoardCommInputPacket::DOWNLEFT));
            SETORCLRBIT(*this->inpkt, (int)InputPacket::P1_DOWNRIGHT, GETBIT(lastmsg, (int)BoardCommInputPacket::DOWNRIGHT));
        }
    }    
}