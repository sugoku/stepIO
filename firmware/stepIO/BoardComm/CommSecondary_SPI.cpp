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

void CommSecondary_SPI::setup() {
    SPISecondary.begin();

    return 0;
}

void CommPrimary_SPI::update() {
    uint8_t nextmsg = 0;

    if (player == PLAYER_1) {
        SETORCLRBIT(nextmsg, BoardCommInputPacket::UPLEFT, GETBIT(*inpkt, InputPacket::P1_UPLEFT));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::UPRIGHT, GETBIT(*inpkt, InputPacket::P1_UPRIGHT));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::CENTER, GETBIT(*inpkt, InputPacket::P1_CENTER));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::DOWNLEFT, GETBIT(*inpkt, InputPacket::P1_DOWNLEFT));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::DOWNRIGHT, GETBIT(*inpkt, InputPacket::P1_DOWNRIGHT));
    } else if (player == PLAYER_2) {
        SETORCLRBIT(nextmsg, BoardCommInputPacket::UPLEFT, GETBIT(*inpkt, InputPacket::P2_UPLEFT));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::UPRIGHT, GETBIT(*inpkt, InputPacket::P2_UPRIGHT));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::CENTER, GETBIT(*inpkt, InputPacket::P2_CENTER));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::DOWNLEFT, GETBIT(*inpkt, InputPacket::P2_DOWNLEFT));
        SETORCLRBIT(nextmsg, BoardCommInputPacket::DOWNRIGHT, GETBIT(*inpkt, InputPacket::P2_DOWNRIGHT));
    }

    if ((lastmsg >> 5) > 0) {
        this->parseCommand(lastmsg);
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
}