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
/*                    License is GPLv3                    */
/*            https://github.com/sugoku/stepIO            */
/**********************************************************/

#include "Output_Switch.h"

void Output_Switch::setup(Config* config) {
    this->setConfig(config);
    SwitchJoystick.begin();
}

void Output_Switch::setConfig(Config* config) {
    this->config = config;
}

const uint16_t* Output_Switch::getLights() {
    return nullptr;
}

void Output_Switch::updateHost() {
    return;  // nothing needed here, no lights support
}

static uint8_t Output_Switch::buttonToBit(uint8_t n) {
    return EEPROM_SWITCH_BUTTON - n;
}

void Output_Switch::send(uint16_t* buf) {
    uint32_t tmp = 0x0000;
    
    // need to parse switch defs first (probably in config)
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P1_UPLEFT_GAMEPAD]), GETBIT(*buf, InputPacket::P1_UPLEFT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P1_UPRIGHT_GAMEPAD]), GETBIT(*buf, InputPacket::P1_UPRIGHT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P1_CENTER_GAMEPAD]), GETBIT(*buf, InputPacket::P1_CENTER));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P1_DOWNLEFT_GAMEPAD]), GETBIT(*buf, InputPacket::P1_DOWNLEFT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P1_DOWNRIGHT_GAMEPAD]), GETBIT(*buf, InputPacket::P1_DOWNRIGHT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P2_UPLEFT_GAMEPAD]), GETBIT(*buf, InputPacket::P2_UPLEFT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P2_UPRIGHT_GAMEPAD]), GETBIT(*buf, InputPacket::P2_UPRIGHT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P2_CENTER_GAMEPAD]), GETBIT(*buf, InputPacket::P2_CENTER));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P2_DOWNLEFT_GAMEPAD]), GETBIT(*buf, InputPacket::P2_DOWNLEFT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P2_DOWNRIGHT_GAMEPAD]), GETBIT(*buf, InputPacket::P2_DOWNRIGHT));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P1_COIN_GAMEPAD]), GETBIT(*buf, InputPacket::P1_COIN));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::P2_COIN_GAMEPAD]), GETBIT(*buf, InputPacket::P2_COIN));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::TEST_BUTTON_GAMEPAD]), GETBIT(*buf, InputPacket::TEST_BUTTON));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::SERVICE_BUTTON_GAMEPAD]), GETBIT(*buf, InputPacket::SERVICE_BUTTON));
    SETORCLRBIT(tmp, Output_Switch::buttonToBit(this->config[ConfigOptions::CLEAR_BUTTON_GAMEPAD]), GETBIT(*buf, InputPacket::CLEAR_BUTTON));

    SwitchJoystick.buttons(tmp);
    SwitchJoystick.write();
}

void Output_Switch::sendAnalog(uint16_t* buf) {
    // not implemented yet
    // xAxis, yAxis, zAxis, rxAxis, ryAxis, rzAxis
}

// for reference
// https://github.com/LuiCat/ArduinoTaikoController/tree/master/taiko_controller