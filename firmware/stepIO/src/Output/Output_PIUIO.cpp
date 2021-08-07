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
    USBDevice.setControlHandler(this, Output_PIUIO::control);
    this->mux = this->mux_arr;
}

void Output_PIUIO::setConfig(uint8_t* config) {
    this->config = config;
}

void Output_PIUIO::updateHost() {
    // done when host updates USB instead
    return;
}

uint8_t* const Output_PIUIO::getMuxes() { 
    return this->mux;
}

void Output_PIUIO::update(uint32_t buf) { 
    // i don't think you can loop through enums so this is the best i'll get for now
    // PIUIO uses negative logic hence the NOT operators
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_UPLEFT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P1_UPLEFT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_UPRIGHT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P1_UPRIGHT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_CENTER, !(GETBIT(buf, (int)PIUIO_LightsPacket::P1_CENTER)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_DOWNLEFT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P1_DOWNLEFT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P1_DOWNRIGHT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_UPLEFT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P2_UPLEFT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_UPRIGHT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P2_UPRIGHT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_CENTER, !(GETBIT(buf, (int)PIUIO_LightsPacket::P2_CENTER)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_DOWNLEFT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P2_DOWNLEFT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::P2_DOWNRIGHT, !(GETBIT(buf, (int)PIUIO_LightsPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_1, !(GETBIT(buf, (int)PIUIO_LightsPacket::MARQUEE_1)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_2, !(GETBIT(buf, (int)PIUIO_LightsPacket::MARQUEE_2)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_3, !(GETBIT(buf, (int)PIUIO_LightsPacket::MARQUEE_3)));
    SETORCLRBIT(this->lights, (int)LightsPacket::MARQUEE_4, !(GETBIT(buf, (int)PIUIO_LightsPacket::MARQUEE_4)));
    SETORCLRBIT(this->lights, (int)LightsPacket::SUB_LEFT, !(GETBIT(buf, (int)PIUIO_LightsPacket::SUB_NEON)));
    SETORCLRBIT(this->lights, (int)LightsPacket::SUB_RIGHT, !(GETBIT(buf, (int)PIUIO_LightsPacket::SUB_NEON)));

    // set mux values
    SETORCLRBIT(this->mux[0], 0, GETBIT(buf, (int)PIUIO_LightsPacket::P1_MUXER_0));
    SETORCLRBIT(this->mux[0], 1, GETBIT(buf, (int)PIUIO_LightsPacket::P1_MUXER_1));
    SETORCLRBIT(this->mux[1], 0, GETBIT(buf, (int)PIUIO_LightsPacket::P2_MUXER_0));
    SETORCLRBIT(this->mux[1], 1, GETBIT(buf, (int)PIUIO_LightsPacket::P2_MUXER_1));
}

void Output_PIUIO::send(uint32_t* buf) {
    // doesn't actually send, just updates the data to send when it is requested by the host
    uint32_t tmp = 0xFFFFFFFF;
    
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_UPLEFT, !(GETBIT(*buf, (int)InputPacket::P1_UPLEFT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_UPRIGHT, !(GETBIT(*buf, (int)InputPacket::P1_UPRIGHT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_CENTER, !(GETBIT(*buf, (int)InputPacket::P1_CENTER)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_DOWNLEFT, !(GETBIT(*buf, (int)InputPacket::P1_DOWNLEFT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_DOWNRIGHT, !(GETBIT(*buf, (int)InputPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_UPLEFT, !(GETBIT(*buf, (int)InputPacket::P2_UPLEFT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_UPRIGHT, !(GETBIT(*buf, (int)InputPacket::P2_UPRIGHT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_CENTER, !(GETBIT(*buf, (int)InputPacket::P2_CENTER)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_DOWNLEFT, !(GETBIT(*buf, (int)InputPacket::P2_DOWNLEFT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_DOWNRIGHT, !(GETBIT(*buf, (int)InputPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_COIN, !(GETBIT(*buf, (int)InputPacket::P1_COIN)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_COIN, !(GETBIT(*buf, (int)InputPacket::P2_COIN)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_TEST, !(GETBIT(*buf, (int)InputPacket::TEST_BUTTON)));
    // SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_TEST, !(GETBIT(*buf, (int)InputPacket::TEST_BUTTON)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_SERVICE, !(GETBIT(*buf, (int)InputPacket::SERVICE_BUTTON)));
    // SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_SERVICE, !(GETBIT(*buf, (int)InputPacket::SERVICE_BUTTON)));
    SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P1_CLEAR, !(GETBIT(*buf, (int)InputPacket::CLEAR_BUTTON)));
    // SETORCLRBIT(tmp, (int)PIUIO_InputPacket::P2_CLEAR, !(GETBIT(*buf, (int)InputPacket::CLEAR_BUTTON)));

    this->payload[3] = (tmp >> 24) & 0xFF;
    this->payload[2] = (tmp >> 16) & 0xFF;
    this->payload[1] = (tmp >> 8) & 0xFF;
    this->payload[0] = tmp & 0xFF;
}

static void Output_PIUIO::control(void* obj, USBSetup setup) {
    static_cast<Output_PIUIO*>(obj)->handleControl(setup);
}

void Output_PIUIO::handleControl(USBSetup setup) {
    uint8_t buf[USB_EP_SIZE];
    uint32_t tmp;

    if (setup.bRequest == PIUIO_ADDRESS) {
        if (setup.bmRequestType == REQUEST_DEVICETOHOST) {
            InitControl(sizeof(this->payload));
            #if defined(__SAM3X8E__)
                USBD_SendControl(this->payload);
            #elif defined(__AVR__)
                USB_SendControl(0, this->payload, sizeof(this->payload));
            #endif
            
        } else if (setup.bmRequestType == REQUEST_HOSTTODEVICE) {
            // not sure if I need to InitControl
            if (
                #if defined(__SAM3X8E__)
                    USBD_RecvControl(buf, setup.wLength)
                #elif defined(__AVR__)
                    USB_RecvControl(buf, setup.wLength)
                #endif
                            != setup.wLength) {
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