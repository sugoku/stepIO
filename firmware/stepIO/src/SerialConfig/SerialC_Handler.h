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

#ifndef _SERIALC_HANDLER_H
#define _SERIALC_HANDLER_H

#include "../Config.h"
#include "../EEPROM/EEPROM_IO.h"
#include "../Output/Output_Serial.h"

class SerialC
{
    protected:
        PacketSerial ser;
        EEPROM_IO* ee;
        Output_Serial* out;
        uint8_t* config;

    public:
        void setup(uint8_t* config, Stream* stream=nullptr, EEPROM_IO* eepromio=nullptr); 
        void setConfig(uint8_t* config);
        void parseCommand(const uint8_t* buf, size_t size);
        void sendPacket(uint8_t* buf);
        uint8_t makePacket(uint8_t command, uint8_t* buf);
        void sendConfig();
        void sendDeviceInfo();
        void sendStatus(uint8_t status, uint8_t command);  
        void setOutput(Output_Serial* out);  // Output object, SerialC actually takes input from it
        void loadEEPROM();
        void saveEEPROM();
        void saveConfig(uint8_t* buf);
        void overflow();

};

#endif