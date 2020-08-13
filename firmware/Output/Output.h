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

#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "Config.h"

class Output
{
    protected:
        uint16_t* lights;  // a LightsPacket (enum in Config.h)

    public:
        virtual int setup() = 0;
        virtual int updateIn() = 0;
        virtual int updateHost() = 0;
        virtual uint8_t* getLights() const = 0;
        virtual uint8_t* getUSBData() const = 0;

};

enum OutputMode {
    None,
    Serial,
    Joystick,
    Keyboard,
    PIUIO,
    LXIO, // not implemented
    Switch,
    MIDI  // not implemented
};

#endif