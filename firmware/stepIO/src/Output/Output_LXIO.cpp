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

#include "Output_LXIO.h"

void Output_LXIO::setup(uint8_t* config) {
    memset(this->payload, 0xFF, 32);
    this->setConfig(config);
    LXHID.begin();
}

void Output_LXIO::setConfig(uint8_t* config) {
    this->config = config;
}

void Output_LXIO::updateHost() {
    return;  // nothing needed here, no lights support
}

void Output_LXIO::send(uint32_t* buf) {
    uint32_t tmp[16] = {};
    memset(tmp, 0xFF, 16);
    
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_UPLEFT_0 / 0x10], (int)LXIO_InputPacket::P1_UPLEFT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P1_UPLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_UPRIGHT_0 / 0x10], (int)LXIO_InputPacket::P1_UPRIGHT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P1_UPRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_CENTER_0 / 0x10], (int)LXIO_InputPacket::P1_CENTER_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P1_CENTER)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_DOWNLEFT_0 / 0x10], (int)LXIO_InputPacket::P1_DOWNLEFT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P1_DOWNLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_DOWNRIGHT_0 / 0x10], (int)LXIO_InputPacket::P1_DOWNRIGHT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_UPLEFT_0 / 0x10], (int)LXIO_InputPacket::P2_UPLEFT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P2_UPLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_UPRIGHT_0 / 0x10], (int)LXIO_InputPacket::P2_UPRIGHT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P2_UPRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_CENTER_0 / 0x10], (int)LXIO_InputPacket::P2_CENTER_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P2_CENTER)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_DOWNLEFT_0 / 0x10], (int)LXIO_InputPacket::P2_DOWNLEFT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P2_DOWNLEFT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_DOWNRIGHT_0 / 0x10], (int)LXIO_InputPacket::P2_DOWNRIGHT_0 % 0x10, !(GETBIT(*buf, (int)InputPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_COIN / 0x10], (int)LXIO_InputPacket::P1_COIN % 0x10, !(GETBIT(*buf, (int)InputPacket::P1_COIN)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P2_COIN / 0x10], (int)LXIO_InputPacket::P2_COIN % 0x10, !(GETBIT(*buf, (int)InputPacket::P2_COIN)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_TEST / 0x10], (int)LXIO_InputPacket::P1_TEST % 0x10, !(GETBIT(*buf, (int)InputPacket::TEST_BUTTON)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_SERVICE / 0x10], (int)LXIO_InputPacket::P1_SERVICE % 0x10, !(GETBIT(*buf, (int)InputPacket::SERVICE_BUTTON)));
    SETORCLRBIT(tmp[(int)LXIO_InputPacket::P1_CLEAR / 0x10], (int)LXIO_InputPacket::P1_CLEAR % 0x10, !(GETBIT(*buf, (int)InputPacket::CLEAR_BUTTON)));

    this->payload[3] = (tmp >> 24) & 0xFF;
    this->payload[2] = (tmp >> 16) & 0xFF;
    this->payload[1] = (tmp >> 8) & 0xFF;
    this->payload[0] = tmp & 0xFF;

    LXHID.send(this->payload);
}