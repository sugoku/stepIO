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

void SerialC::sendConfig(uint8_t *config) {
    // check if config exists here
    
    for (int i = 0; i < EEPROM_MAX_ADDR; i++) {
        this->sendByte((uint8_t)(config[i]));
    }
    
}

int SerialC::sendEEPROM(EEPROM_IO *e) {  // Same as sendConfig for most purposes but reads EEPROM directly
    int tmp;

    for (uint16_t i = 0; i < EEPROM_MAX_ADDR; i++) {

        tmp = e.readInt(i);

        if (tmp < 0) {
            return tmp;
        }

        this->sendByte((uint8_t)tmp);

    }
    
    return 0;
}