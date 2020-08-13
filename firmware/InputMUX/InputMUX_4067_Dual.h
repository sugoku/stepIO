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

#ifndef _INPUTMUX_4067_H
#define _INPUTMUX_4067_H

#include "InputMUX.h"

class InputMUX_4067_Dual : public InputMUX
{
    protected:
        uint32_t vals[4] = {0, 0, 0, 0};  // 1 for each MUX state, we are caching them so we can poll faster even when the PC isn't asking

    public:
        void setup();
        uint8_t update(uint8_t mux=0);  // read from multiplexers and take in a value `mux` which determines which sensor we are reading from
        void enable();  // enable the multiplexer
        void disable();  // disable the multiplexer
        void reset();  // set all read inputs to an off state, reset all selector pins, disable the multiplexer
        static uint32_t mergeValues(uint32_t* vals);
        const uint32_t* getMergedValues();
        const uint32_t* getValues();

};

#endif