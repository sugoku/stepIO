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

#include "SerialC_Handler.h"

void SerialC::setup(Config* config, Stream* stream=nullptr, EEPROM_IO* eepromio=nullptr, Output_Serial* out=nullptr) {
    this->setConfig(config);

    this->ser.setStream(stream);
    this->ser.setPacketHandler(&this->parseCommand);

    this->ee = eepromio;
    this->setOutput(out);
    
}

void SerialC::setOutput(Output_Serial* out) {
    this->out = out;
}

void SerialC::setConfig(Config* config) {
    this->config = config;
}

void SerialC::parseCommand(const uint8_t* buf, size_t size) {
    if (size == 0) { this->sendStatus(SerialMessages::ERROR_SHORT); }

    if (size > 1) {
        switch (buf[0]) {
            case SerialCommands::CHANGE_INPUT_MODE:
                this->config[ConfigOptions::INPUT_MODE] = buf[1];
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::CHANGE_OUTPUT_MODE:
                this->config[ConfigOptions::OUTPUT_MODE] = buf[1];
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::CHANGE_LIGHTS_MODE:
                this->config[ConfigOptions::LIGHTS_MODE] = buf[1];
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::CHANGE_EXTRA_LIGHTS_MODE:
                this->config[ConfigOptions::EXTRA_LIGHTS_MODE] = buf[1];
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::CHANGE_MUX_POLLING_MODE:
                this->config[ConfigOptions::MUX_POLLING_MODE] = buf[1];
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::CHANGE_DEBOUNCE_MODE:
                this->config[ConfigOptions::DEBOUNCE_MODE] = buf[1];
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::ANALOG_THRESHOLD:
                this->sendStatus(SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case SerialCommands::EDIT_INPUT:
                this->sendStatus(SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case SerialCommands::SET_EXTRA_LED:
                this->sendStatus(SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case SerialCommands::LIGHTS_FROM_SENSORS:
                this->config[ConfigOptions::LIGHTS_FROM_SENSORS] = buf[1] & 1;
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::SEND_LIGHTSMUX:
                if (this->out == nullptr) {
                    this->sendStatus(SerialMessages::ERROR_NOT_ATTACHED, buf[0]);
                } else {
                    uint8_t tmp[size-1];
                    for (int i = 1; i < size; i++)
                        tmp[i-1] = buf[i];

                    this->out->update(tmp);
                }
                break;
            case SerialCommands::CHANGE_BAUD:
                this->sendStatus(SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case SerialCommands::SET_CONFIG:
                uint8_t tmp[size-1];
                for (int i = 1; i < size; i++)
                    tmp[i-1] = buf[i];

                if (size == 257)
                    this->saveConfig(tmp);
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            default:
                this->sendStatus(SerialMessages::ERROR_UNKNOWN, buf[0]);
                break;
        }
    } else {
        switch (buf[0]) {
            case SerialCommands::LOAD_FROM_EEPROM:
                this->loadEEPROM();
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::SAVE_TO_EEPROM:
                this->saveEEPROM();
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::GET_CONFIG:
                this->sendConfig();
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
            case SerialCommands::RESET:
                this->sendStatus(SerialMessages::RESET, buf[0]);
                LOOP_FOREVER;
                break;
            case SerialCommands::STATUS_GET:
                this->sendStatus(SerialMessages::ALIVE, SerialCommands::STATUS_GET);
                break;
            case SerialCommands::GET_LIGHTSMUX:
                if (this->out == nullptr) {
                    this->sendStatus(SerialMessages::ERROR_NOT_ATTACHED, buf[0]);
                } else {
                    this->sendLights();
                    this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                }
                break;
            case SerialCommands::SET_FACTORY_DEFAULTS:
                this->saveConfig(&defaults);
                this->sendStatus(SerialMessages::RESET, buf[0]);
                LOOP_FOREVER;
                break;
            case SerialCommands::GET_DEVICE_INFO:
                this->sendDeviceInfo();
                this->sendStatus(SerialMessages::SUCCESS, buf[0]);
                break;
        }
    }
}

void SerialC::sendPacket(uint8_t* buf) {
    this->ser.send(buf, sizeof(buf));
}

void SerialC::sendConfig() {
    this->sendPacket(this->makePacket(SerialMessageTypes::CONFIG, SerialCommands::GET_CONFIG, this->config));
}

void SerialC::sendDeviceInfo() {
    char buf[64];
    snprintf(buf, 64, "%s v%d.%d (rev %d)", STEPIO_PRODUCT, STEPIO_VERSION_MAJOR, STEPIO_VERSION_MINOR, STEPIO_VERSION_REVISION);
    this->sendPacket(this->makePacket(SerialMessageTypes::DEVICE_INFO, SerialCommands::GET_DEVICE_INFO, buf));
}

uint8_t* SerialC::makePacket(uint8_t cmdtype, uint8_t requestcmd, uint8_t* buf) {
    uint8_t tmp[sizeof(buf)+2];

    tmp[0] = cmdtype;
    tmp[1] = requestcmd;
    for (int i = 0; i < sizeof(buf), i++)
        tmp[i+1] = buf[i];
    return tmp;
}

void SerialC::sendLights() {
    if (this->out == nullptr) this->sendStatus(SerialMessages::ERROR_NOT_ATTACHED, SerialCommands::GET_LIGHTSMUX);
    uint8_t pkt[] = this->makePacket(SerialMessageTypes::LIGHTS, SerialCommands::GET_LIGHTSMUX, this->out->getLights())
    this->sendPacket(&pkt);
}

void SerialC::sendStatus(uint8_t status, uint8_t command) {
    uint8_t pkt[] = this->makePacket(SerialMessageTypes::STATUS, command, &status);
    this->sendPacket(&pkt);
}

void SerialC::loadEEPROM() {
    if (this->ee == nullptr) return;
    this->ee->readConfig(this->config);
}

void SerialC::saveEEPROM() {
    if (this->ee == nullptr) return;
    this->ee->updateConfig(this->config);
}

void SerialC::saveConfig(uint8_t* buf) {
    if (this->ee == nullptr) return;
    this->ee->updateConfig(buf);
}


bool SerialC::overflow() {
    return this->ser.overflow();
}