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

#ifndef _OUTPUT_JOYSTICK_H
#define _OUTPUT_JOYSTICK_H

#include "Output.h"

class Output_Joystick : public Output
{
    protected:
        uint8_t* config;

    public:
        void setup(Config* config);
        void setConfig(Config* config);
        void updateHost();
        void send(uint16_t* buf);
        void sendAnalog(uint16_t* buf);  // buffer is an array
        const uint16_t* getLights();
        const uint8_t* getUSBData();
};

#endif