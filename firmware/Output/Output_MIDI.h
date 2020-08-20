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

#ifndef _OUTPUT_MIDI_H
#define _OUTPUT_MIDI_H

#include "Output.h"

class Output_MIDI : public Output
{
    protected:
        uint8_t* config;
        MIDI_* usbmidi;

    public:
        void setup(Config* config);
        void setConfig(Config* config);
        void updateHost();
        void send(uint16_t* buf);
        void sendAnalog(uint16_t* buf);  // buffer is an array
        void set(uint8_t midi0, uint8_t midi1, uint8_t midi2, bool on);
        const uint16_t* getLights();
        const uint8_t* getUSBData();
};

#endif