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

#define U32_TO_U8(n) (n >> 24) % 0xFF, (n >> 16) % 0xFF, (n >> 8) % 0xFF, n % 0xFF

void SerialC::setup(uint8_t* config, Stream* stream=nullptr, EEPROM_IO* eepromio=nullptr) {
    this->setConfig(config);

    this->ser.setStream(stream);
    this->ser.setPacketHandler(&this->parseCommand);

    this->ee = eepromio;
}

void SerialC::setOutput(Output_Serial* out) {
    this->out = out;
}

void SerialC::setConfig(uint8_t* config) {
    this->config = config;
}

void SerialC::parseCommand(const uint8_t* buf, size_t size) {
    if (size == 0) { this->sendStatus((uint8_t)SerialMessages::ERROR_SHORT, 0xFF); }

    if (size > 1) {
        switch (buf[0]) {
            case (uint8_t)SerialCommands::CHANGE_INPUT_MODE:
                this->config[(uint8_t)ConfigOptions::INPUT_MODE] = buf[1];
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::CHANGE_OUTPUT_MODE:
                this->config[(uint8_t)ConfigOptions::OUTPUT_MODE] = buf[1];
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::CHANGE_LIGHTS_MODE:
                this->config[(uint8_t)ConfigOptions::LIGHTS_MODE] = buf[1];
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::CHANGE_EXTRA_LIGHTS_MODE:
                this->config[(uint8_t)ConfigOptions::EXTRA_LIGHTS_MODE] = buf[1];
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::CHANGE_MUX_POLLING_MODE:
                this->config[(uint8_t)ConfigOptions::MUX_POLLING_MODE] = buf[1];
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::CHANGE_DEBOUNCE_MODE:
                this->config[(uint8_t)ConfigOptions::DEBOUNCE_MODE] = buf[1];
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::ANALOG_THRESHOLD:
                this->sendStatus((uint8_t)SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case (uint8_t)SerialCommands::EDIT_INPUT:
                this->sendStatus((uint8_t)SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case (uint8_t)SerialCommands::SET_EXTRA_LED:
                this->sendStatus((uint8_t)SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case (uint8_t)SerialCommands::RESET_EXTRA_LEDS:
                this->sendStatus((uint8_t)SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case (uint8_t)SerialCommands::LIGHTS_FROM_SENSORS:
                this->config[(uint8_t)ConfigOptions::LIGHTS_FROM_SENSORS] = buf[1] & 1;
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::SEND_LIGHTSMUX:
                if (this->out == nullptr) {
                    this->sendStatus((uint8_t)SerialMessages::ERROR_NOT_ATTACHED, buf[0]);
                } else {
                    uint32_t tmp = 0;
                    for (int i = 1; i < size; i++)
                        tmp |= (buf[i] << (8 * (i-1)));
                        
                    this->out->update(tmp);
                }
                break;
            case (uint8_t)SerialCommands::CHANGE_BAUD:
                this->sendStatus((uint8_t)SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case (uint8_t)SerialCommands::SET_CONFIG:
                uint8_t tmp[size-1];
                for (int i = 1; i < size; i++)
                    tmp[i-1] = buf[i];

                if (size == 257)
                    this->saveConfig(tmp);
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            default:
                this->sendStatus((uint8_t)SerialMessages::ERROR_UNKNOWN, buf[0]);
                break;
        }
    } else {
        switch (buf[0]) {
            case (uint8_t)SerialCommands::LOAD_FROM_EEPROM:
                this->loadEEPROM();
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::SAVE_TO_EEPROM:
                this->saveEEPROM();
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::GET_CONFIG:
                this->sendConfig();
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
            case (uint8_t)SerialCommands::RESET:
                this->sendStatus((uint8_t)SerialMessages::RESET, buf[0]);
                LOOP_FOREVER;
                break;
            case (uint8_t)SerialCommands::STATUS_GET:
                this->sendStatus((uint8_t)SerialMessages::ALIVE, (uint8_t)SerialCommands::STATUS_GET);
                break;
            case (uint8_t)SerialCommands::GET_LIGHTSMUX:
                if (this->out == nullptr) {
                    this->sendStatus((uint8_t)SerialMessages::ERROR_NOT_ATTACHED, buf[0]);
                } else {
                    this->sendLights();
                    this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                }
                break;
            case (uint8_t)SerialCommands::SET_FACTORY_DEFAULTS:
                this->saveConfig(&defaults);
                this->sendStatus((uint8_t)SerialMessages::RESET, buf[0]);
                LOOP_FOREVER;
                break;
            case (uint8_t)SerialCommands::GET_DEVICE_INFO:
                this->sendDeviceInfo();
                this->sendStatus((uint8_t)SerialMessages::SUCCESS, buf[0]);
                break;
        }
    }
}

void SerialC::sendPacket(uint8_t* buf) {
    this->ser.send(buf, sizeof(buf));
}

void SerialC::sendConfig() {
    this->sendPacket(this->makePacket((uint8_t)SerialMessageTypes::CONFIG, (uint8_t)SerialCommands::GET_CONFIG, this->config));
}

void SerialC::sendDeviceInfo() {
    char buf[64];
    snprintf(buf, 64, "%s v%d.%d (rev %d)", STEPIO_PRODUCT, STEPIO_VERSION_MAJOR, STEPIO_VERSION_MINOR, STEPIO_VERSION_REVISION);
    this->sendPacket(this->makePacket((uint8_t)SerialMessageTypes::DEVICE_INFO, (uint8_t)SerialCommands::GET_DEVICE_INFO, buf));
}

uint8_t* SerialC::makePacket(uint8_t cmdtype, uint8_t requestcmd, uint8_t* buf) {
    uint8_t tmp[sizeof(buf)+2];

    tmp[0] = cmdtype;
    tmp[1] = requestcmd;
    for (int i = 0; i < sizeof(buf); i++)
        tmp[i+1] = buf[i];
    return tmp;
}

void SerialC::sendLights() {
    if (this->out == nullptr) this->sendStatus((uint8_t)SerialMessages::ERROR_NOT_ATTACHED, (uint8_t)SerialCommands::GET_LIGHTSMUX);
    uint32_t lpkt = *(this->out->getLights());
    uint8_t lights[] = {U32_TO_U8(lpkt)};
    uint8_t* pkt = this->makePacket((uint8_t)SerialMessageTypes::LIGHTS, (uint8_t)SerialCommands::GET_LIGHTSMUX, lights);
    this->sendPacket(pkt);
}

void SerialC::sendStatus(uint8_t status, uint8_t command) {
    uint8_t* pkt = this->makePacket((uint8_t)SerialMessageTypes::STATUS, command, &status);
    this->sendPacket(pkt);
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