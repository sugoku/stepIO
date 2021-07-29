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

void Output_LXIO::setup(Config* config) {
    this->setConfig(config);
    LXIO.begin();
}

void Output_LXIO::setConfig(Config* config) {
    this->config = config;
}

const uint16_t* Output_LXIO::getLights() {
    return nullptr;
}

void Output_LXIO::updateHost() {
    return;  // nothing needed here, no lights support
}

void Output_LXIO::send(uint16_t* buf) {
    uint32_t tmp[16] = {};
    memset(tmp[0xFFFFFFFF / 0x10], 0xFFFFFFFF % 0x10, 16);
    
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_UPLEFT_0 / 0x10], LXIO_InputPacket::P1_UPLEFT_0 % 0x10, !(GETBIT(*buf, InputPacket::P1_UPLEFT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_UPRIGHT_0 / 0x10], LXIO_InputPacket::P1_UPRIGHT_0 % 0x10, !(GETBIT(*buf, InputPacket::P1_UPRIGHT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_CENTER_0 / 0x10], LXIO_InputPacket::P1_CENTER_0 % 0x10, !(GETBIT(*buf, InputPacket::P1_CENTER)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_DOWNLEFT_0 / 0x10], LXIO_InputPacket::P1_DOWNLEFT_0 % 0x10, !(GETBIT(*buf, InputPacket::P1_DOWNLEFT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_DOWNRIGHT_0 / 0x10], LXIO_InputPacket::P1_DOWNRIGHT_0 % 0x10, !(GETBIT(*buf, InputPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P2_UPLEFT_0 / 0x10], LXIO_InputPacket::P2_UPLEFT_0 % 0x10, !(GETBIT(*buf, InputPacket::P2_UPLEFT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P2_UPRIGHT_0 / 0x10], LXIO_InputPacket::P2_UPRIGHT_0 % 0x10, !(GETBIT(*buf, InputPacket::P2_UPRIGHT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P2_CENTER_0 / 0x10], LXIO_InputPacket::P2_CENTER_0 % 0x10, !(GETBIT(*buf, InputPacket::P2_CENTER)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P2_DOWNLEFT_0 / 0x10], LXIO_InputPacket::P2_DOWNLEFT_0 % 0x10, !(GETBIT(*buf, InputPacket::P2_DOWNLEFT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P2_DOWNRIGHT_0 / 0x10], LXIO_InputPacket::P2_DOWNRIGHT_0 % 0x10, !(GETBIT(*buf, InputPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_COIN / 0x10], LXIO_InputPacket::P1_COIN % 0x10, !(GETBIT(*buf, InputPacket::P1_COIN)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P2_COIN / 0x10], LXIO_InputPacket::P2_COIN % 0x10, !(GETBIT(*buf, InputPacket::P2_COIN)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_TEST / 0x10], LXIO_InputPacket::P1_TEST % 0x10, !(GETBIT(*buf, InputPacket::TEST_BUTTON)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_SERVICE / 0x10], LXIO_InputPacket::P1_SERVICE % 0x10, !(GETBIT(*buf, InputPacket::SERVICE_BUTTON)));
    SETORCLRBIT(tmp[LXIO_InputPacket::P1_CLEAR / 0x10], LXIO_InputPacket::P1_CLEAR % 0x10, !(GETBIT(*buf, InputPacket::CLEAR_BUTTON)));

    this->payload[3] = (tmp >> 24) & 0xFF;
    this->payload[2] = (tmp >> 16) & 0xFF;
    this->payload[1] = (tmp >> 8) & 0xFF;
    this->payload[0] = tmp & 0xFF;

    LXIO.send();
}