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

#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "../Config.h"
#include <HID-Project.h>

class Output
{
    protected:
        // uint8_t* config;  // a link to a config
        // uint32_t lights;  // a LightsPacket (enum in Config.h)
        const String manufacturer PROGMEM = STEPIO_MANUFACTURER;
        const String product PROGMEM = STEPIO_PRODUCT;
        const DeviceDescriptor ddescriptor PROGMEM = STEPIO_DEVICE_DESCRIPTOR;

    public:
        virtual void setup(uint8_t* config) = 0;
        virtual void setConfig(uint8_t* config) = 0;
        virtual void send(uint32_t* buf) = 0;
        virtual void updateHost() = 0;
        virtual uint32_t* const getLights() = 0;
        const String* getManufacturer() { return &this->manufacturer; };
        const String* getProduct() { return &this->product; };
        const DeviceDescriptor* getDeviceDescriptor() { return &this->ddescriptor; };

};

enum class OutputMode {
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