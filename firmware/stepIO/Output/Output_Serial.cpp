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

void Output_Serial::setup(Config* config, SerialC* serialc=nullptr) {
    this->setConfig(config);
    if (ser == nullptr) return;
    this->serialc = serialc;
}

void Output_Serial::setSerialC(SerialC* ser) {
    this->serialc = serialc;
}

void Output_Serial::setConfig(Config* config) {
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

const uint16_t* Output_Serial::getLights() {
    return &this.lights;
}

const uint8_t* Output_Serial::getMuxes() {
    return &this.mux;
}

void Output_Serial::send(uint16_t* buf) {
    if (this->serialc == nullptr) return;
    this->serialc->sendPacket({SerialCommands::SEND_INPUT, buf >> 4, buf & 0b1111});
}

void Output_Serial::sendAnalog(uint16_t* buf) {
    if (this->serialc == nullptr) return;
    uint8_t tmp = {
        SerialCommands::SEND_INPUT_ANALOG,
        // PLAYER 1
        buf[0],buf[1],buf[2],buf[3],buf[4],
        // PLAYER 2
        buf[5],buf[6],buf[7],buf[8],buf[9],
        // COIN BUTTONS
        buf[10],buf[11],
        // TEST, SERVICE, CLEAR
        buf[12],buf[13],buf[14],
        
        buf[15]
    };
    this->serialc->sendPacket(tmp);
}

// endpoint 0xAE
// sendControl()
// recvControl()