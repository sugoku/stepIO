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

#include "Output_Keyboard.h"

void Output_Keyboard::setup(uint8_t* config) {
    this->setConfig(config);
    NKROKeyboard.begin();
}

void Output_Keyboard::setConfig(uint8_t* config) {
    this->config = config;
}

const uint16_t* Output_Keyboard::getLights() {
    return nullptr;
}

void Output_Keyboard::updateHost() {
    return;  // nothing needed here, no lights support
}

void Output_Keyboard::send(uint32_t* buf) {
    uint16_t diff = this->input ^ *buf;  // XOR the two to see where any differences have happened

    // if there is a change, set key on or off based on buf's state
    if GETBIT(diff, InputPacket::P1_UPLEFT)
        this->set(this->config[ConfigOptions::P1_UPLEFT_KEYCODE], GETBIT(*buf, InputPacket::P1_UPLEFT));
    if GETBIT(diff, InputPacket::P1_UPRIGHT)
        this->set(this->config[ConfigOptions::P1_UPRIGHT_KEYCODE], GETBIT(*buf, InputPacket::P1_UPRIGHT));
    if GETBIT(diff, InputPacket::P1_CENTER)
        this->set(this->config[ConfigOptions::P1_CENTER_KEYCODE], GETBIT(*buf, InputPacket::P1_CENTER));
    if GETBIT(diff, InputPacket::P1_DOWNLEFT)
        this->set(this->config[ConfigOptions::P1_DOWNLEFT_KEYCODE], GETBIT(*buf, InputPacket::P1_DOWNLEFT));
    if GETBIT(diff, InputPacket::P1_DOWNRIGHT)
        this->set(this->config[ConfigOptions::P1_DOWNRIGHT_KEYCODE], GETBIT(*buf, InputPacket::P1_DOWNRIGHT));
    if GETBIT(diff, InputPacket::P2_UPLEFT)
        this->set(this->config[ConfigOptions::P2_UPLEFT_KEYCODE], GETBIT(*buf, InputPacket::P2_UPLEFT));
    if GETBIT(diff, InputPacket::P2_UPRIGHT)
        this->set(this->config[ConfigOptions::P2_UPRIGHT_KEYCODE], GETBIT(*buf, InputPacket::P2_UPRIGHT));
    if GETBIT(diff, InputPacket::P2_CENTER)
        this->set(this->config[ConfigOptions::P2_CENTER_KEYCODE], GETBIT(*buf, InputPacket::P2_CENTER));
    if GETBIT(diff, InputPacket::P2_DOWNLEFT)
        this->set(this->config[ConfigOptions::P2_DOWNLEFT_KEYCODE], GETBIT(*buf, InputPacket::P2_DOWNLEFT));
    if GETBIT(diff, InputPacket::P2_DOWNRIGHT)
        this->set(this->config[ConfigOptions::P2_DOWNRIGHT_KEYCODE], GETBIT(*buf, InputPacket::P2_DOWNRIGHT));
    if GETBIT(diff, InputPacket::P1_COIN)
        this->set(this->config[ConfigOptions::P1_COIN_KEYCODE], GETBIT(*buf, InputPacket::P1_COIN));
    if GETBIT(diff, InputPacket::P2_COIN)
        this->set(this->config[ConfigOptions::P2_COIN_KEYCODE], GETBIT(*buf, InputPacket::P2_COIN));
    if GETBIT(diff, InputPacket::TEST_BUTTON)
        this->set(this->config[ConfigOptions::TEST_BUTTON_KEYCODE], GETBIT(*buf, InputPacket::TEST_BUTTON));
    if GETBIT(diff, InputPacket::SERVICE_BUTTON)
        this->set(this->config[ConfigOptions::SERVICE_BUTTON_KEYCODE], GETBIT(*buf, InputPacket::SERVICE_BUTTON));
    if GETBIT(diff, InputPacket::CLEAR_BUTTON)
        this->set(this->config[ConfigOptions::CLEAR_BUTTON_KEYCODE], GETBIT(*buf, InputPacket::CLEAR_BUTTON));

    NKROKeyboard.send();

    this->input = *buf;  // update input variable
}