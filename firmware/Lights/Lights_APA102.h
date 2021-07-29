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

#ifndef _LIGHTS_APA102_H
#define _LIGHTS_APA102_H

#include "Lights.h"

#include <FastGPIO.h>
#define APA102_USE_FAST_GPIO
#include <APA102.h>

class Lights_APA102 : public Lights
{
    protected:
        APA102* leds;
        uint8_t* color[3];  // red, green, blue
        int count = DEFAULT_RGB_LED_COUNT;  // how many LEDs we are controlling
        int triggerall = -1;  // whichever byte this is in LightsPacket will turn all the LEDs on, -1 ignores this behavior

    public:
        void setup(int n=0);
        uint32_t send(uint32_t* buf);
        void setColor(uint8_t* arr);
        void setCount(int n);
        void setTrigger(int n);
        int write(int start, int end, uint8_t* color=NULL);
        int write(int* list, uint8_t* color=NULL);
        void enable();
        void disable();
        void reset();

};

#endif