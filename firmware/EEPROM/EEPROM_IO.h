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

#ifndef _EEPROM_IO_H
#define _EEPROM_IO_H

#include "Config.h"
#include <EEPROM.h>

class EEPROM_ext
{
    #ifdef EEPROM_EXTERNAL 
        private:
            extEEPROM ee;
    #endif

    public: 
        uint8_t initialize();
        uint8_t read(int loc, uint8_t* buf[], size_t n=1);
        uint8_t readByte(int loc);
        uint8_t write(int loc, uint8_t* buf[], size_t n);
        uint8_t update(int loc, uint8_t* buf[], size_t n);
        uint8_t readConfig(uint8_t* config);
        uint8_t versionCheck(uint8_t* config);
    
}; 

#endif