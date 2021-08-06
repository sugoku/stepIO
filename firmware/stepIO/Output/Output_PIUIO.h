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
        uint32_t lights = 0;
        uint8_t payload[4] = {0xFF, 0xFF, 0xFF, 0xFF};
        const String manufacturer PROGMEM = STEPIO_MANUFACTURER;
        const String product PROGMEM = "PIUIO";
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
        void setup(uint8_t* config);
        void setConfig(uint8_t* config);
        void updateHost();
        void update(uint32_t buf);
        void send(uint32_t* buf);
        void handleControl(USBSetup setup);
        inline uint32_t* const getLights() { return &this->lights; };
        uint8_t* const getMuxes();
        // const uint8_t* getUSBData();
};

#endif