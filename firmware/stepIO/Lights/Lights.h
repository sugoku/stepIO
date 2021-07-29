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

#ifndef _LIGHTS_H
#define _LIGHTS_H

#include "Config.h"

class Lights
{
    public:
        virtual void setup() = 0;
        virtual int send(uint32_t* buf) = 0;

};

enum LightsMode {
    None,
    Latch32,  // SIMPLE_IO
    Latch,
    Signal,
    FastLED,
    WS281X,
    APA102
};

#endif