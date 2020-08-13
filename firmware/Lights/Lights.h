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

#ifndef _LIGHTS_H
#define _LIGHTS_H

#include "Config.h"

class Lights
{
    protected:
        uint8_t* lights;

    public:
        virtual int setup() = 0;
        virtual int send() = 0;

};

enum LightsMode {
    Latch32,  // brokeIO
    Latch,
    RGB,
    Signal
};

#endif