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

#include "Lights_APA102.h"

void Lights_APA102::setup(int n=0) {
    this->leds = APA102<EXTRA_LIGHTS_DATA, EXTRA_LIGHTS_CLOCK>();
    this->color = DEFAULT_LED_COLORS;
    if (n > 0)
        this->count = n;
}

void Lights_APA102::setColor(uint8_t* arr) {
    // red, green, blue
    memcpy(&this->leds, arr, 3);
}

void Lights_APA102::setCount(int n) {
    this->count = n;
}

void Lights_APA102::setTrigger(int n) {
    this->triggerall = n;
}

int Lights_APA102::send(uint32_t* buf) {
    if (this->triggerall >= 0) {
        if ((buf >> this->triggerall) & 1) {  // if triggered bit is on
            return this->write(0, this->count);
        }
    } else {
        return this->write(buf);
    }
}

int Lights_APA102::write(int start, int end, uint8_t* color=nullptr) {
    this->leds->startFrame();
    if (color != nullptr) {
        for (int i = start; i < end; i++)
            this->leds->sendColor(i, color[0], color[1], color[2]);
    } else {
        for (int i = start; i < end; i++)
            this->leds->sendColor(i, this->color[0], this->color[1], this->color[2]);
    }
    this->leds->endFrame(end-start);
    return end-start;
}

int Lights_APA102::write(uint32* buf, uint8_t* color=nullptr) {
    this->leds->startFrame();
    if (color != nullptr) {
        for (int i = 0; i < 32; i++) {
            if (GETBIT(buf, i)) {
                this->leds->sendColor(i, color[0], color[1], color[2]);
            }
        }
    } else {
        for (int i = 0; i < 32; i++) {
            if (GETBIT(buf, i)) {
                this->leds->sendColor(i, this->color[0], this->color[1], this->color[2]);
            }
        }
    }
    this->leds->endFrame(end-start);
    return end-start;
}

void Lights_APA102::reset() {
    this->write(0, this->count-1, {0, 0, 0});
}