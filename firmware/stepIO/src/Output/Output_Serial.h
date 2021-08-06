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

#ifndef _OUTPUT_SERIAL_H
#define _OUTPUT_SERIAL_H

#include "Output.h"
#include "../SerialConfig/SerialC_Handler.h"

class SerialC;

class Output_Serial : public Output
{
    protected:
        uint8_t* config;
        uint8_t mux[2] = {0, 0};  // from 0-3 inclusive, the sensor from each panel to read from the foot PCB (left, top, right, bottom) + for p1 and p2
        uint32_t lights = 0;
        SerialC* serialc;

    public:
        void setup(uint8_t* config, SerialC* serialc=nullptr);
        void setConfig(uint8_t* config);
        void setSerialC(SerialC* serialc);
        void update(uint32_t lightmux);
        void updateHost();
        void send(uint32_t* buf);
        void sendAnalog(uint32_t* buf);  // buffer is an array
        uint32_t* const getLights() { return &this->lights; };
        uint8_t* const getMuxes() { return &this->mux; };
};

#endif