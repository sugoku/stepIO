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

#ifndef _INPUT_MUX4067_H
#define _INPUT_MUX4067_H

#include "Input.h"

class Input_MUX4067_Dual : public InputMUX
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
        uint32_t getP1andP2(uint8_t mux1, uint8_t mux2);
        const uint32_t* getMergedValues();
        const uint32_t* getValues();

};

#endif