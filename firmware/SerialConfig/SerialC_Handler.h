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

#include "Config.h"

class SerialC
{
    protected:
        PacketSerial ser;
        EEPROM_IO* ee;
        Output_Serial* out;
        uint8_t* config;

    public:
        void setup(Config* config, Stream* stream=nullptr, EEPROM_IO* eepromio=nullptr); 
        void setConfig(Config* config);
        void parseCommand(const uint8_t* buf, size_t size);
        void sendPacket(uint8_t* buf);
        void sendConfig();
        void sendStatus(uint8_t status);  
        void setOutput(Output_Serial* out);  // Output object, SerialC actually takes input from it
        void loadEEPROM();
        void saveEEPROM();
        void overflow();

};

#endif