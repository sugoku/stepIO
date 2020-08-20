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

#ifndef _OUTPUT_KEYBOARD_H
#define _OUTPUT_KEYBOARD_H

#include "Output.h"

class Output_Keyboard : public Output
{
    protected:
        uint8_t* config;
        uint16_t input = 0;  // we need to actually keep track of what we've pressed and what we haven't

    public:
        void setup(Config* config);
        void setConfig(Config* config);
        void updateHost();
        void send(uint16_t* buf);
        const uint16_t* getLights();
        const uint8_t* getUSBData();
};

#endif