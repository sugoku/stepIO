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
        SETORCLRBIT(payload, BoardCommInputPacket::UPLEFT, GETBIT(*inpkt, InputPacket::P1_UPLEFT));
        SETORCLRBIT(payload, BoardCommInputPacket::UPRIGHT, GETBIT(*inpkt, InputPacket::P1_UPRIGHT));
        SETORCLRBIT(payload, BoardCommInputPacket::CENTER, GETBIT(*inpkt, InputPacket::P1_CENTER));
        SETORCLRBIT(payload, BoardCommInputPacket::DOWNLEFT, GETBIT(*inpkt, InputPacket::P1_DOWNLEFT));
        SETORCLRBIT(payload, BoardCommInputPacket::DOWNRIGHT, GETBIT(*inpkt, InputPacket::P1_DOWNRIGHT));
    } else if (player == PLAYER_2) {
        SETORCLRBIT(payload, BoardCommInputPacket::UPLEFT, GETBIT(*inpkt, InputPacket::P2_UPLEFT));
        SETORCLRBIT(payload, BoardCommInputPacket::UPRIGHT, GETBIT(*inpkt, InputPacket::P2_UPRIGHT));
        SETORCLRBIT(payload, BoardCommInputPacket::CENTER, GETBIT(*inpkt, InputPacket::P2_CENTER));
        SETORCLRBIT(payload, BoardCommInputPacket::DOWNLEFT, GETBIT(*inpkt, InputPacket::P2_DOWNLEFT));
        SETORCLRBIT(payload, BoardCommInputPacket::DOWNRIGHT, GETBIT(*inpkt, InputPacket::P2_DOWNRIGHT));
    }
    
    lastmsg = SPI.transfer(payload);

    if ((lastmsg >> 5) > 0) {
        this->parseMessage(lastmsg);
    } else {
        // populate opposite pad
        if (player == PLAYER_1) {
            SETORCLRBIT(*inpkt, InputPacket::P2_UPLEFT, GETBIT(lastmsg, BoardCommInputPacket::UPLEFT));
            SETORCLRBIT(*inpkt, InputPacket::P2_UPRIGHT, GETBIT(lastmsg, BoardCommInputPacket::UPRIGHT));
            SETORCLRBIT(*inpkt, InputPacket::P2_CENTER, GETBIT(lastmsg, BoardCommInputPacket::CENTER));
            SETORCLRBIT(*inpkt, InputPacket::P2_DOWNLEFT, GETBIT(lastmsg, BoardCommInputPacket::DOWNLEFT));
            SETORCLRBIT(*inpkt, InputPacket::P2_DOWNRIGHT, GETBIT(lastmsg, BoardCommInputPacket::DOWNRIGHT));
        } else if (player == PLAYER_2) {
            SETORCLRBIT(*inpkt, InputPacket::P1_UPLEFT, GETBIT(lastmsg, BoardCommInputPacket::UPLEFT));
            SETORCLRBIT(*inpkt, InputPacket::P1_UPRIGHT, GETBIT(lastmsg, BoardCommInputPacket::UPRIGHT));
            SETORCLRBIT(*inpkt, InputPacket::P1_CENTER, GETBIT(lastmsg, BoardCommInputPacket::CENTER));
            SETORCLRBIT(*inpkt, InputPacket::P1_DOWNLEFT, GETBIT(lastmsg, BoardCommInputPacket::DOWNLEFT));
            SETORCLRBIT(*inpkt, InputPacket::P1_DOWNRIGHT, GETBIT(lastmsg, BoardCommInputPacket::DOWNRIGHT));
        }
    }    
}