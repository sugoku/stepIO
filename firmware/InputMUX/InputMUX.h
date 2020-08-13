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

#ifndef _INPUTMUX_H
#define _INPUTMUX_H

#include "Config.h"

class InputMUX
{

    public:
        virtual void setup() = 0;  // setup any pins and any values, also any objects that are needed
        virtual uint8_t update() = 0;  // return the amount of pins checked

};

enum InputMUXMode {
    None,
    MUX4067_Dual,
    MUX4067,
    MUX4051
};

#endif