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

#ifndef _INPUT_SIMPLE_H
#define _INPUT_SIMPLE_H

#include "Input.h"

class Input_Simple : public Input
{
    protected:
        uint32_t* vals = {0};  // no muxes

    public:
        void setup();  // setup any pins and any values, also any objects that are needed
        uint8_t update();  // return the amount of pins checked
        inline uint32_t getP1andP2(uint8_t mux1, uint8_t mux2) { return *getValues(); }
        inline uint32_t* getMergedValues() { return getValues(); }
        inline const uint32_t* getValues() { return vals; }
        static uint8_t muxToInputPacket(uint8_t mux_pin);

};

#endif