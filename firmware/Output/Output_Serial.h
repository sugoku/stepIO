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

#ifndef _OUTPUT_SERIAL_H
#define _OUTPUT_SERIAL_H

#include "Output.h"

class Output_Serial : public Output
{
    protected:
        uint8_t* config;
        uint8_t mux[2] = {0, 0};  // from 0-3 inclusive, the sensor from each panel to read from the foot PCB (left, top, right, bottom) + for p1 and p2
        uint16_t lights = 0;
        SerialC* serialc;

    public:
        void setup(Config* config, SerialC* serialc=nullptr);
        void setConfig(Config* config);
        void setSerialC(SerialC* serialc);
        void update(uint32_t buf);
        void updateHost();
        void send(uint16_t* buf);
        void sendAnalog(uint16_t* buf);  // buffer is an array
        const uint16_t* getLights();
};

#endif