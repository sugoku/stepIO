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

#include "Output_Serial.h"

#define U32_TO_U8(n) (n >> 24) % 0xFF, (n >> 16) % 0xFF, (n >> 8) % 0xFF, n % 0xFF

void Output_Serial::setup(uint8_t* config, SerialC* serialc=nullptr) {
    this->setConfig(config);
    if (serialc == nullptr) return;
    this->serialc = serialc;
}

void Output_Serial::setSerialC(SerialC* serialc) {
    this->serialc = serialc;
}

void Output_Serial::setConfig(uint8_t* config) {
    this->config = config;
}

void Output_Serial::updateHost() {
    return;  // not necessary, SerialC will call when necessary
}

void Output_Serial::update(uint32_t lightmux) {
    this->lights = (uint16_t)(lightmux & 0xFFFF);  // the first 16 bits (from right to left, LSB)
    this->mux[0] = (uint8_t)((lightmux >> 16) & 0b11);  // the two bits after that
    this->mux[1] = (uint8_t)((lightmux >> 18) & 0b11);  // the two bits after that
}

void Output_Serial::send(uint32_t* buf) {
    if (this->serialc == nullptr) return;
    uint8_t tmp[4] = {U32_TO_U8(buf[0])}
    this->serialc->sendPacket(this->serialc->makePacket((uint8_t)SerialMessageTypes::SENSOR, (uint8_t)SerialCommands::SEND_INPUT, );
}

void Output_Serial::sendAnalog(uint32_t* buf) {
    if (this->serialc == nullptr) return;
    uint8_t tmp[] = {
        (uint8_t)SerialMessageTypes::SENSOR_ANALOG,
        (uint8_t)SerialCommands::SEND_INPUT_ANALOG,
        // PLAYER 1
        U32_TO_U8(buf[0]),U32_TO_U8(buf[1]),U32_TO_U8(buf[2]),U32_TO_U8(buf[3]),U32_TO_U8(buf[4]),
        // PLAYER 2
        U32_TO_U8(buf[5]),U32_TO_U8(buf[6]),U32_TO_U8(buf[7]),U32_TO_U8(buf[8]),U32_TO_U8(buf[9]),
        // COIN BUTTONS
        U32_TO_U8(buf[10]),U32_TO_U8(buf[11]),
        // TEST, SERVICE, CLEAR
        U32_TO_U8(buf[12]),U32_TO_U8(buf[13]),U32_TO_U8(buf[14]),
        
        U32_TO_U8(buf[15])
    };
    this->serialc->sendPacket(tmp);
}

// endpoint 0xAE
// sendControl()
// recvControl()