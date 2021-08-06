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

#ifndef _OUTPUT_SWITCH_H
#define _OUTPUT_SWITCH_H

#include "Output.h"

class Output_Switch : public Output
{
    protected:
        uint8_t* config;
        const String product PROGMEM = SWITCH_PRODUCT;
        const DeviceDescriptor ddescriptor PROGMEM = D_DEVICE(
            0xFF,  // vendor specific class
            0x00,
            0x00,
            USB_EP_SIZE,
            SWITCH_VID,
            SWITCH_PID,
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
        void sendAnalog(uint32_t* buf);  // buffer is an array
        const uint32_t* getLights();
        static uint8_t buttonToBit(uint8_t n);
};

#endif