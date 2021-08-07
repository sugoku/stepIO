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

#include "CommSecondary_SPI.h"

uint8_t CommSecondary_SPI::setup() {
    SPISecondary.begin();

    unsigned long start = millis();

    // try to receive 0x72 for 1 second; return 0 if success and 1 if failure
    while ((millis() - start) < 1000 && SPISecondary.transfer(0x07) != 0x72);

    return (uint8_t)((millis() - start) >= 1000);
}

void CommSecondary_SPI::parseMessage(uint8_t msg) {
    // no messages in use yet
}

void CommSecondary_SPI::update() {
    uint8_t nextmsg = 0;

    if (player == PLAYER_1) {
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::UPLEFT, GETBIT(*this->inpkt, (int)InputPacket::P1_UPLEFT));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::UPRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P1_UPRIGHT));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::CENTER, GETBIT(*this->inpkt, (int)InputPacket::P1_CENTER));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::DOWNLEFT, GETBIT(*this->inpkt, (int)InputPacket::P1_DOWNLEFT));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::DOWNRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P1_DOWNRIGHT));
    } else if (player == PLAYER_2) {
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::UPLEFT, GETBIT(*this->inpkt, (int)InputPacket::P2_UPLEFT));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::UPRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P2_UPRIGHT));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::CENTER, GETBIT(*this->inpkt, (int)InputPacket::P2_CENTER));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::DOWNLEFT, GETBIT(*this->inpkt, (int)InputPacket::P2_DOWNLEFT));
        SETORCLRBIT(nextmsg, (int)BoardCommInputPacket::DOWNRIGHT, GETBIT(*this->inpkt, (int)InputPacket::P2_DOWNRIGHT));
    }

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
