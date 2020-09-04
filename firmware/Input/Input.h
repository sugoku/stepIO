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

#ifndef _INPUTMUX_H
#define _INPUTMUX_H

#include "Config.h"

class Input
{

    public:
        virtual void setup() = 0;  // setup any pins and any values, also any objects that are needed
        virtual uint8_t update() = 0;  // return the amount of pins checked
        virtual uint32_t getP1andP2(uint8_t mux1, uint8_t mux2) = 0;  // if not applicable just return getValues();
        virtual const uint32_t* getMergedValues() = 0;  // if not applicable just return getValues();
        virtual const uint32_t* getValues() = 0;

};

enum InputMode {
    None,
    Software,
    Analog,
    DMA,
    MUX4067_Dual,
    MUX4067,
    MUX4051
};

enum MUXPollingMode {
    Normal,
    Merged,
    HalfMerged,
    One,
};

#endif