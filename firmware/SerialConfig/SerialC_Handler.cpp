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

#include "SerialC_Handler.h"

void SerialC::setup(Stream* stream, EEPROM_IO* eepromio) {
    this->ser.setStream(stream);
    this->ser.setPacketHandler(&this.parseCommand);

    this->ee = eepromio;
}

void SerialC::parseCommand(const uint8_t* buf, size_t size) {
    if (size == 0) { sendStatus(SerialMessages::ERROR_SHORT); }

    if (size > 1) {
        switch (buf[0]) {
            case SerialCommands::CHANGE_INPUT_MODE:
                this->config[ConfigOptions::INPUT_MODE] = buf[1];
                break;
            case SerialCommands::CHANGE_OUTPUT_MODE:
                this->config[ConfigOptions::OUTPUT_MODE] = buf[1];
                break;
            case SerialCommands::CHANGE_LIGHTS_MODE:
                this->config[ConfigOptions::LIGHTS_MODE] = buf[1];
                break;
            case SerialCommands::CHANGE_EXTRA_LIGHTS_MODE:
                this->config[ConfigOptions::EXTRA_LIGHTS_MODE] = buf[1];
                break;
            case SerialCommands::CHANGE_MUX_POLLING_MODE:
                this->config[ConfigOptions::MUX_POLLING_MODE] = buf[1];
                break;
            case SerialCommands::CHANGE_DEBOUNCE_MODE:
                this->config[ConfigOptions::DEBOUNCE_MODE] = buf[1];
                break;
            case SerialCommands::ANALOG_THRESHOLD:
                break;
            case SerialCommands::EDIT_INPUT:
                break;
            case SerialCommands::SET_EXTRA_LED:
                break;
            case SerialCommands::LIGHTS_FROM_SENSORS:
                this->config[ConfigOptions::LIGHTS_FROM_SENSORS] = buf[1] & 1;
                break;
            default:
                sendStatus(SerialMessages::ERROR_UNKNOWN);
                break;
        }
    } else {
        switch (buf[0]) {
            case SerialCommands::LOAD_FROM_EEPROM:
                this->loadEEPROM();
                break;
            case SerialCommands::SAVE_TO_EEPROM:
                this->saveEEPROM();
                break;
            case SerialCommands::GET_CONFIG:
                this->sendConfig();
                break;
        }
    }
}

void SerialC::sendPacket(uint8_t* buf) {
    this->ser.send(buf, sizeof(buf));
}

void SerialC::sendConfig() {
    this->sendPacket(this->config);
}

void SerialC::sendStatus(uint8_t status) {
    pkt = {SerialMessageTypes::STATUS, status};
    this->sendPacket(&pkt);
}

void SerialC::loadEEPROM() {
    this->ee->readConfig(this->config);
}

void SerialC::saveEEPROM() {
    this->ee->updateConfig(this->config);
}

bool SerialC::overflow() {
    return this->ser.overflow();
}