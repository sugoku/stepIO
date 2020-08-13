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

#ifndef _LIGHTS_LATCH32_H
#define _LIGHTS_LATCH32_H

#include "Lights.h"
#include <SPI.h>

class Lights_Latch32 : public Lights
{
    protected:
        uint32_t lights;

    public:
        virtual void setup() = 0;
        virtual uint32_t send() = 0;

};

#endif