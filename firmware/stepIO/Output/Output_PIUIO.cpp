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

#include "Output_PIUIO.h"

void Output_PIUIO::setup(uint8_t* config) {
    this->setConfig(config);
    vendorHandler = this->handleControl;
}

void Output_PIUIO::setConfig(uint8_t* config) {
    this->config = config;
}

void Output_PIUIO::updateHost() {
    // done when host updates USB instead
    return;
}

void Output_PIUIO::update(uint32_t buf) { 
    // i don't think you can loop through enums so this is the best i'll get for now
    // PIUIO uses negative logic hence the NOT operators
    SETORCLRBIT(this->lights, LightsPacket::P1_UPLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P1_UPLEFT)));
    SETORCLRBIT(this->lights, LightsPacket::P1_UPRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P1_UPRIGHT)));
    SETORCLRBIT(this->lights, LightsPacket::P1_CENTER, !(GETBIT(buf, PIUIO_LightsPacket::P1_CENTER)));
    SETORCLRBIT(this->lights, LightsPacket::P1_DOWNLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P1_DOWNLEFT)));
    SETORCLRBIT(this->lights, LightsPacket::P1_DOWNRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(this->lights, LightsPacket::P2_UPLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P2_UPLEFT)));
    SETORCLRBIT(this->lights, LightsPacket::P2_UPRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P2_UPRIGHT)));
    SETORCLRBIT(this->lights, LightsPacket::P2_CENTER, !(GETBIT(buf, PIUIO_LightsPacket::P2_CENTER)));
    SETORCLRBIT(this->lights, LightsPacket::P2_DOWNLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P2_DOWNLEFT)));
    SETORCLRBIT(this->lights, LightsPacket::P2_DOWNRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(this->lights, LightsPacket::MARQUEE_1, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_1)));
    SETORCLRBIT(this->lights, LightsPacket::MARQUEE_2, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_2)));
    SETORCLRBIT(this->lights, LightsPacket::MARQUEE_3, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_3)));
    SETORCLRBIT(this->lights, LightsPacket::MARQUEE_4, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_4)));
    SETORCLRBIT(this->lights, LightsPacket::SUB_LEFT, !(GETBIT(buf, PIUIO_LightsPacket::SUB_NEON)));
    SETORCLRBIT(this->lights, LightsPacket::SUB_RIGHT, !(GETBIT(buf, PIUIO_LightsPacket::SUB_NEON)));

    // set mux values
    SETORCLRBIT(this->mux[0], 0, GETBIT(buf, PIUIO_LightsPacket::P1_MUXER_0));
    SETORCLRBIT(this->mux[0], 1, GETBIT(buf, PIUIO_LightsPacket::P1_MUXER_1));
    SETORCLRBIT(this->mux[1], 0, GETBIT(buf, PIUIO_LightsPacket::P2_MUXER_0));
    SETORCLRBIT(this->mux[1], 1, GETBIT(buf, PIUIO_LightsPacket::P2_MUXER_1));
}

const uint16_t* Output_PIUIO::getLights() {
    return &this->lights;
}

const uint8_t* Output_PIUIO::getMuxes() {
    return &this->mux;
}

void Output_PIUIO::send(uint32_t* buf) {
    // doesn't actually send, just updates the data to send when it is requested by the host
    uint32_t tmp = 0xFFFFFFFF;
    
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_UPLEFT, !(GETBIT(*buf, InputPacket::P1_UPLEFT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_UPRIGHT, !(GETBIT(*buf, InputPacket::P1_UPRIGHT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_CENTER, !(GETBIT(*buf, InputPacket::P1_CENTER)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_DOWNLEFT, !(GETBIT(*buf, InputPacket::P1_DOWNLEFT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_DOWNRIGHT, !(GETBIT(*buf, InputPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P2_UPLEFT, !(GETBIT(*buf, InputPacket::P2_UPLEFT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P2_UPRIGHT, !(GETBIT(*buf, InputPacket::P2_UPRIGHT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P2_CENTER, !(GETBIT(*buf, InputPacket::P2_CENTER)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P2_DOWNLEFT, !(GETBIT(*buf, InputPacket::P2_DOWNLEFT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P2_DOWNRIGHT, !(GETBIT(*buf, InputPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_COIN, !(GETBIT(*buf, InputPacket::P1_COIN)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P2_COIN, !(GETBIT(*buf, InputPacket::P2_COIN)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_TEST, !(GETBIT(*buf, InputPacket::TEST_BUTTON)));
    // SETORCLRBIT(tmp, PIUIO_InputPacket::P2_TEST, !(GETBIT(*buf, InputPacket::TEST_BUTTON)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_SERVICE, !(GETBIT(*buf, InputPacket::SERVICE_BUTTON)));
    // SETORCLRBIT(tmp, PIUIO_InputPacket::P2_SERVICE, !(GETBIT(*buf, InputPacket::SERVICE_BUTTON)));
    SETORCLRBIT(tmp, PIUIO_InputPacket::P1_CLEAR, !(GETBIT(*buf, InputPacket::CLEAR_BUTTON)));
    // SETORCLRBIT(tmp, PIUIO_InputPacket::P2_CLEAR, !(GETBIT(*buf, InputPacket::CLEAR_BUTTON)));

    this->payload[3] = (tmp >> 24) & 0xFF;
    this->payload[2] = (tmp >> 16) & 0xFF;
    this->payload[1] = (tmp >> 8) & 0xFF;
    this->payload[0] = tmp & 0xFF;
}

void Output_PIUIO::handleControl(USBSetup setup) {
    uint8_t buf[USB_EP_SIZE];
    uint32_t tmp;

    if (setup.bRequest == PIUIO_ADDRESS) {
        if (setup.bmRequestType == REQUEST_DEVICETOHOST) {
            InitControl(sizeof(this->payload));
            USBD_SendControl(this->payload);
        } else if (setup.bmRequestType == REQUEST_HOSTTODEVICE) {
            // not sure if I need to InitControl
            if (USBD_RecvControl(buf, setup.wLength) != setup.wLength) {
                // return; ???
            }
            tmp |= buf[3] << 24;
            tmp |= buf[2] << 16;
            tmp |= buf[1] << 8;
            tmp |= buf[0];
            this->update(tmp);
        }
    }
}