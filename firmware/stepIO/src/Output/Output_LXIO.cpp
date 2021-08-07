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
/*  emulation of LXIO                                    */
/*  by BedrockSolid (@sugoku)                             */
/**********************************************************/
/*  SPDX-License-Identifier: GPL-3.0-or-later             */
/*  https://github.com/sugoku/stepIO                      */
/**********************************************************/

#include "Output_LXIO.h"

void Output_LXIO::setup(uint8_t* config) {
    memset(this->payload, 0xFF, 32);
    memset(this->lightbuf, 0xFF, 32);
    this->setConfig(config);
    LXHID.begin();
}

void Output_LXIO::setConfig(uint8_t* config) {
    this->config = config;
}

void Output_LXIO::updateHost() {
    LXHID.read(this->lightbuf);

    // LXIO uses negative logic hence the NOT operators
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_UPLEFT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P1_UPLEFT / 0x08], (int)LXIO_LightsPacket::P1_UPLEFT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_UPRIGHT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P1_UPRIGHT / 0x08], (int)LXIO_LightsPacket::P1_UPRIGHT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_CENTER, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P1_CENTER / 0x08], (int)LXIO_LightsPacket::P1_CENTER % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_DOWNLEFT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P1_DOWNLEFT / 0x08], (int)LXIO_LightsPacket::P1_DOWNLEFT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_DOWNRIGHT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P1_DOWNRIGHT / 0x08], (int)LXIO_LightsPacket::P1_DOWNRIGHT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_UPLEFT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P2_UPLEFT / 0x08], (int)LXIO_LightsPacket::P2_UPLEFT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_UPRIGHT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P2_UPRIGHT / 0x08], (int)LXIO_LightsPacket::P2_UPRIGHT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_CENTER, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P2_CENTER / 0x08], (int)LXIO_LightsPacket::P2_CENTER % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_DOWNLEFT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P2_DOWNLEFT / 0x08], (int)LXIO_LightsPacket::P2_DOWNLEFT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_DOWNRIGHT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::P2_DOWNRIGHT / 0x08], (int)LXIO_LightsPacket::P2_DOWNRIGHT % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_1, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::MARQUEE_1 / 0x08], (int)LXIO_LightsPacket::MARQUEE_1 % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_2, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::MARQUEE_2 / 0x08], (int)LXIO_LightsPacket::MARQUEE_2 % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_3, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::MARQUEE_3 / 0x08], (int)LXIO_LightsPacket::MARQUEE_3 % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_4, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::MARQUEE_4 / 0x08], (int)LXIO_LightsPacket::MARQUEE_4 % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::SUB_LEFT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::SUB_NEON / 0x08], (int)LXIO_LightsPacket::SUB_NEON % 0x08)));
    SETORCLRBIT(this->lights, (int)LightsPacket::SUB_RIGHT, !(GETBIT(this->lightbuf[(int)LXIO_LightsPacket::SUB_NEON / 0x08], (int)LXIO_LightsPacket::SUB_NEON % 0x08)));
    
}

void Output_LXIO::send(uint32_t* buf) {
    uint8_t tmp[16] = {};
    memset(tmp, 0xFF, 16);
    
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_UPLEFT_0 / 0x08], (int)LXIO_InputPacket::P1_UPLEFT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P1_UPLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_UPRIGHT_0 / 0x08], (int)LXIO_InputPacket::P1_UPRIGHT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P1_UPRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_CENTER_0 / 0x08], (int)LXIO_InputPacket::P1_CENTER_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P1_CENTER)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_DOWNLEFT_0 / 0x08], (int)LXIO_InputPacket::P1_DOWNLEFT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P1_DOWNLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_DOWNRIGHT_0 / 0x08], (int)LXIO_InputPacket::P1_DOWNRIGHT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_UPLEFT_0 / 0x08], (int)LXIO_InputPacket::P2_UPLEFT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P2_UPLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_UPRIGHT_0 / 0x08], (int)LXIO_InputPacket::P2_UPRIGHT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P2_UPRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_CENTER_0 / 0x08], (int)LXIO_InputPacket::P2_CENTER_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P2_CENTER)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_DOWNLEFT_0 / 0x08], (int)LXIO_InputPacket::P2_DOWNLEFT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P2_DOWNLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_DOWNRIGHT_0 / 0x08], (int)LXIO_InputPacket::P2_DOWNRIGHT_0 % 0x08, !(GETBIT(*buf, (int)InputPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_COIN / 0x08], (int)LXIO_InputPacket::P1_COIN % 0x08, !(GETBIT(*buf, (int)InputPacket::P1_COIN)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_COIN / 0x08], (int)LXIO_InputPacket::P2_COIN % 0x08, !(GETBIT(*buf, (int)InputPacket::P2_COIN)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_TEST / 0x08], (int)LXIO_InputPacket::P1_TEST % 0x08, !(GETBIT(*buf, (int)InputPacket::TEST_BUTTON)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_SERVICE / 0x08], (int)LXIO_InputPacket::P1_SERVICE % 0x08, !(GETBIT(*buf, (int)InputPacket::SERVICE_BUTTON)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_CLEAR / 0x08], (int)LXIO_InputPacket::P1_CLEAR % 0x08, !(GETBIT(*buf, (int)InputPacket::CLEAR_BUTTON)));

    for (int i = 0; i < 16; i++)
        this->payload[i] = tmp[i] & 0xFF;

    LXHID.write(this->payload);
}