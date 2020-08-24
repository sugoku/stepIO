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

#ifndef _OUTPUT_SWITCH_H
#define _OUTPUT_SWITCH_H

#include "Output.h"

class Output_Switch : public Output
{
    protected:
        uint8_t* config;
        const uint8_t manufacturer[] PROGMEM = STEPIO_MANUFACTURER;
        const uint8_t product[] PROGMEM = SWITCH_PRODUCT;
        const DeviceDescriptor ddescriptor PROGMEM = D_DEVICE(
            0xFF,  // vendor specific class
            0x00,
            0x00,
            USB_EP_SIZE,
            SWITCH_VID,
            SWITCH_PID,
            0x100,  // version 1
            IMANUFACTURER,
            IPRODUCT,
            ISERIAL,
            1  // 1 configuration
        );

    public:
        void setup(Config* config);
        void setConfig(Config* config);
        void updateHost();
        void send(uint16_t* buf);
        void sendAnalog(uint16_t* buf);  // buffer is an array
        const uint16_t* getLights();
        static uint8_t buttonToBit(uint8_t n);
};

#endif