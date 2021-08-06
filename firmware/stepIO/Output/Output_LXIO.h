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

#ifndef _OUTPUT_LXIO_H
#define _OUTPUT_LXIO_H

#include "Output.h"

class Output_LXIO : public Output
{
    protected:
        uint8_t* config;
        const String manufacturer PROGMEM = STEPIO_MANUFACTURER;
        const String product PROGMEM = "PIUIO";

    public:
        void setup(uint8_t* config);
        void setConfig(uint8_t* config);
        void updateHost();
        void send(uint32_t* buf);
        const uint32_t* getLights();
};

#endif