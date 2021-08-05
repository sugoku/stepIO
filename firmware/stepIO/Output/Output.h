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
        const uint8_t manufacturer[255] PROGMEM = STEPIO_MANUFACTURER;
        const uint8_t product[255] PROGMEM = STEPIO_PRODUCT;
        const DeviceDescriptor ddescriptor PROGMEM = STEPIO_DEVICE_DESCRIPTOR;

    public:
        virtual void setup(uint8_t* config) = 0;
        virtual void setConfig(uint8_t* config) = 0;
        virtual void send(uint32_t* buf) = 0;
        virtual void updateHost() = 0;
        virtual const uint32_t* getLights() = 0;
        inline const uint8_t* getManufacturer() { return manufacturer; };
        inline const uint8_t* getProduct() { return product; };
        inline const DeviceDescriptor* getDeviceDescriptor() { return &ddescriptor; };

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