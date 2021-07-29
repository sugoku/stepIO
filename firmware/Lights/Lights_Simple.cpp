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

#include "Lights_Simple.h"

void Lights_Simple::setup() {
    pinMode(LIGHTSIG_1, OUTPUT);
    pinMode(LIGHTSIG_2, OUTPUT);
    pinMode(LIGHTSIG_3, OUTPUT);
    pinMode(LIGHTSIG_4, OUTPUT);
    pinMode(LIGHTSIG_5, OUTPUT);
}

int Lights_Simple::send(uint32_t* buf) {
    if (player == PLAYER_1) {
        SETORCLRBIT(LIGHTSIG_1_PORT, LIGHTSIG_1_PIN, GETBIT(*buf, LightsPacket::P1_UPLEFT));
        SETORCLRBIT(LIGHTSIG_2_PORT, LIGHTSIG_2_PIN, GETBIT(*buf, LightsPacket::P1_UPRIGHT));
        SETORCLRBIT(LIGHTSIG_3_PORT, LIGHTSIG_3_PIN, GETBIT(*buf, LightsPacket::P1_CENTER));
        SETORCLRBIT(LIGHTSIG_4_PORT, LIGHTSIG_4_PIN, GETBIT(*buf, LightsPacket::P1_DOWNLEFT));
        SETORCLRBIT(LIGHTSIG_5_PORT, LIGHTSIG_5_PIN, GETBIT(*buf, LightsPacket::P1_DOWNRIGHT));
    } else if (player == PLAYER_2) {
        SETORCLRBIT(LIGHTSIG_1_PORT, LIGHTSIG_1_PIN, GETBIT(*buf, LightsPacket::P2_UPLEFT));
        SETORCLRBIT(LIGHTSIG_2_PORT, LIGHTSIG_2_PIN, GETBIT(*buf, LightsPacket::P2_UPRIGHT));
        SETORCLRBIT(LIGHTSIG_3_PORT, LIGHTSIG_3_PIN, GETBIT(*buf, LightsPacket::P2_CENTER));
        SETORCLRBIT(LIGHTSIG_4_PORT, LIGHTSIG_4_PIN, GETBIT(*buf, LightsPacket::P2_DOWNLEFT));
        SETORCLRBIT(LIGHTSIG_5_PORT, LIGHTSIG_5_PIN, GETBIT(*buf, LightsPacket::P2_DOWNRIGHT));
    }
}