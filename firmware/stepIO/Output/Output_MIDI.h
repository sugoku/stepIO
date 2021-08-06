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

#ifndef _OUTPUT_MIDI_H
#define _OUTPUT_MIDI_H

#include "Output.h"
#include <MIDIUSB.h>

class Output_MIDI : public Output
{
    protected:
        uint8_t* config;

    public:
        void setup(uint8_t* config);
        void setConfig(uint8_t* config);
        void updateHost();
        void send(uint32_t* buf);
        void sendAnalog(uint32_t* buf);  // buffer is an array
        void set(uint8_t midi0, uint8_t midi1, uint8_t midi2, bool on);
        inline uint32_t* const getLights() { return nullptr; };
};

#endif