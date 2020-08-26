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
                if (this->out == nullptr) return;

                uint8_t tmp[size-1];
                for (int i = 1; i < size; i++) {
                    tmp[i-1] = buf[i];
                }

                this->out->update(tmp);
                break;
            case SerialCommands::CHANGE_BAUD:
                this->sendStatus(SerialMessages::NOT_IMPLEMENTED, buf[0]);
                break;
            case SerialCommands::SET_CONFIG:
                uint8_t tmp[size-1];
                for (int i = 1; i < size; i++) {
                    tmp[i-1] = buf[i];
                }

                if (size == 257)
                    this->setConfig(tmp, true);
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
                LOOP_FOREVER;
                break;
            case SerialCommands::STATUS_GET:
                this->sendStatus(SerialMessages::ALIVE, SerialCommands::STATUS_GET);
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

void SerialC::sendStatus(uint8_t status, uint8_t command) {
    pkt = {SerialMessageTypes::STATUS, command, status};
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

void SerialC::setConfig(const uint8_t* buf) {
    if (this->ee == nullptr) return;
    this->ee->updateConfig(buf);
}


bool SerialC::overflow() {
    return this->ser.overflow();
}