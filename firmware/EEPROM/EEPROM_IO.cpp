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

#include "EEPROM_IO.h"

uint8_t EEPROM_IO::initialize() {
    #ifdef EEPROM_EXTERNAL
        extEEPROM ee(EEPROM_SIZE, EEPROM_COUNT, EEPROM_ADDRESS);
        return ee.begin(EEPROM_SPEED);
    #else
        return 0;  // no initialization needed for standard EEPROM library
    #endif
}

int EEPROM_IO::read(int loc, uint8_t* buf[], size_t n=1) {
    loc += EEPROM_OFFSET
    #ifdef EEPROM_EXTERNAL
        return ee.read(loc, buf, n);
    #else
        for (int i = 0; i < n; i++)
            buf[i] = EEPROM.read(loc+i);
        return i;
    #endif
}

uint8_t EEPROM_IO::readByte(int loc) {
    loc += EEPROM_OFFSET
    #ifdef EEPROM_EXTERNAL
        return ee.read(loc);
    #else
        return EEPROM.read(loc);
    #endif
}

int EEPROM_IO::write(int loc, uint8_t* buf[], size_t n) {
    loc += EEPROM_OFFSET
    #ifdef EEPROM_EXTERNAL
        return ee.write(loc, buf, n);
    #else
        for (int i = 0; i < n; i++)
            EEPROM.write(loc+i, buf[i]);
        return i;
    #endif
}

int EEPROM_IO::update(int loc, uint8_t* buf[], size_t n) {
    loc += EEPROM_OFFSET
    #ifdef EEPROM_EXTERNAL
        // probably have some loop here to check first
        return ee.write(loc, buf, n);
    #else
        for (int i = 0; i < n; i++)
            EEPROM.update(loc+i, buf[i]);
        return i;
    #endif
}

int EEPROM_IO::readConfig(uint8_t* config) {
    return this->read(0, config, sizeof(config));
}

int EEPROM_IO::updateConfig(uint8_t* config) {
    return this->update(0, config, sizeof(config));
}

uint8_t EEPROM_IO::versionCheck(uint8_t* config) {
    return this->readByte(ConfigOptions::VERSION_REVISION);
}