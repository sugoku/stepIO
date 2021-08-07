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
        uint8_t payload[32];
        uint8_t outbuf[32];
        const String manufacturer PROGMEM = STEPIO_MANUFACTURER;
        const String product PROGMEM = "PIU HID V1.00";
        const DeviceDescriptor ddescriptor PROGMEM = D_DEVICE(
            0x00,  // device class 0
            0x00,  // subclass 0
            0x00,  // device protocol 0
            0x08,  // max packet size 8 (USB_EP_SIZE is default which is 64)
            LXIO_VID,
            LXIO_PID,
            STEPIO_VERSION_USB,
            IMANUFACTURER,
            IPRODUCT,
            ISERIAL,
            1  // 1 configuration
        );


    public:
        void setup(uint8_t* config);
        void setConfig(uint8_t* config);
        void updateHost();
        void send(uint32_t* buf);
        uint32_t* const getLights() { return nullptr; };
};

#endif