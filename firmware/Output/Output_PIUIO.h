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

#ifndef _OUTPUT_PIUIO_H
#define _OUTPUT_PIUIO_H

#include "Output.h"

class Output_PIUIO : public Output
{
    protected:
        uint8_t* config;
        uint8_t mux[2] = {0, 0};  // from 0-3 inclusive, the sensor from each panel to read from the foot PCB (left, top, right, bottom) + for p1 and p2
        uint16_t lights = 0;
        uint8_t payload[4] = {[0 ... 3] = 0xFF};
        const uint8_t manufacturer[] PROGMEM = STEPIO_MANUFACTURER;
        const uint8_t product[] PROGMEM = "PIUIO";
        const DeviceDescriptor ddescriptor PROGMEM = D_DEVICE(
            0xFF,  // vendor specific class
            0x00,
            0x00,
            USB_EP_SIZE,
            PIUIO_VID,
            PIUIO_PID,
            STEPIO_VERSION_USB,
            IMANUFACTURER,
            IPRODUCT,
            ISERIAL,
            1  // 1 configuration
        );

    public:
        void setup(Config* config);
        void setConfig(Config* config);
        void updateHost();
        void update(uint32_t buf);
        void send(uint16_t* buf);
        void handleControl(USBSetup setup);
        const uint16_t* getLights();
        const uint8_t* getMuxes();
};

#endif