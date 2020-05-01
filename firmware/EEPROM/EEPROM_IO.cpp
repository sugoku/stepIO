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

#include "EEPROM_IO.h"

uint8_t EEPROM_IO::initialize() {
    extEEPROM ee(EEPROM_SIZE, EEPROM_COUNT, EEPROM_ADDRESS);
    return ee.begin(EEPROM_SPEED);
}

uint8_t EEPROM_IO::read(int loc, uint8_t* buf[], int n) {
    return ee.read(loc, buf, n);
}

int EEPROM_IO::readInt(int loc) {
    return ee.read(loc);
}

uint8_t EEPROM_IO::write(int loc, uint8_t* buf[], int n) {
    return ee.write(loc, buf, n);
}