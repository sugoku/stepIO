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

#ifndef _SERIALC_HANDLER_H
#define _SERIALC_HANDLER_H

#include "Config.h"

class SerialC
{
    private:
        PacketSerial ser;
        EEPROM_IO* ee;
        uint8_t* config;

    public:
        void setup(Stream* stream, EEPROM_IO* eepromio); 
        void parseCommand(const uint8_t* buf, size_t size);
        void sendPacket(uint8_t* buf);
        void sendConfig();
        void sendStatus(uint8_t status);  
        void loadEEPROM();
        void saveEEPROM();
        void overflow();

};

#endif