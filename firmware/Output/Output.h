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
#include "HID-Project.h"

class Output
{
    protected:
        uint8_t* config;  // a link to a config
        // uint16_t lights;  // a LightsPacket (enum in Config.h)

    public:
        virtual void setup(Config* config) = 0;
        virtual void setConfig(Config* config) = 0;
        virtual void send() = 0;
        virtual void updateHost() = 0;
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