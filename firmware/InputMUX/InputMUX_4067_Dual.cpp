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

#include "InputMUX_4067_Dual.h"

void InputMUX_4067_Dual::setup() {
    // set pinModes
    SETBIT(MUX_ENABLE_MODE, MUX_ENABLE_PIN);  // set to output

    CLRBIT(MUX1_IN_MODE, MUX1_IN_PIN);  // set to input
    CLRBIT(MUX2_IN_MODE, MUX2_IN_PIN);  // set to input
    #ifdef PULLUP_IN
        SETBIT(MUX1_IN_PORT, MUX1_IN_PIN);  // enable pull-up resistor
        SETBIT(MUX2_IN_PORT, MUX2_IN_PIN);  // enable pull-up resistor
    #endif

    SETBIT(MUX_S0_MODE, MUX_S0_PIN);  // set to output
    SETBIT(MUX_S1_MODE, MUX_S1_PIN);  // set to output
    SETBIT(MUX_S2_MODE, MUX_S2_PIN);  // set to output
    SETBIT(MUX_S3_MODE, MUX_S3_PIN);  // set to output

    // make sure everything is low
    this.reset();
    // enable MUXes
    this.enable();
}

void InputMUX_4067_Dual::enable() {
    CLRBIT(MUX_ENABLE_PORT, MUX_ENABLE_PIN);
}

void InputMUX_4067_Dual::disable() {
    SETBIT(MUX_ENABLE_PORT, MUX_ENABLE_PIN);
}

void InputMUX_4067_Dual::reset() {
    // set read inputs to 0
    this.vals = 0;

    // clear all selector pins
    CLRBIT(MUX_S0_PORT, MUX_S0_PIN);
    CLRBIT(MUX_S1_PORT, MUX_S1_PIN);
    CLRBIT(MUX_S2_PORT, MUX_S2_PIN);
    CLRBIT(MUX_S3_PORT, MUX_S3_PIN);

    // disable MUX until enabled again
    this.disable();
}

uint8_t InputMUX_4067_Dual::update(uint8_t mux=0) {
    for (uint8_t i = 15; i >= 0; i--) {
        // set the selector pins to the current value
        SETORCLRBIT(MUX_S3_PORT, MUX_S3_PIN, (i >> 3) & 1);
        SETORCLRBIT(MUX_S2_PORT, MUX_S2_PIN, (i >> 2) & 1);
        SETORCLRBIT(MUX_S1_PORT, MUX_S1_PIN, (i >> 1) & 1);
        SETORCLRBIT(MUX_S0_PORT, MUX_S0_PIN, i & 1);

        // read this value from BOTH muxes and store them in the ith bit and the (i+16)th bit respectively
        #ifdef PULLUP_IN
            SETORCLRBIT(this.vals[mux], i, !(GETBIT(MUX1_IN_READ, MUX1_IN_PIN)));
            SETORCLRBIT(this.vals[mux], i+16, !(GETBIT(MUX2_IN_READ, MUX2_IN_PIN)));
        #else
            SETORCLRBIT(this.vals[mux], i, GETBIT(MUX1_IN_READ, MUX1_IN_PIN));
            SETORCLRBIT(this.vals[mux], i+16, GETBIT(MUX2_IN_READ, MUX2_IN_PIN));
        #endif
    }

    return i*2;
}

static uint32_t InputMUX_4067_Dual::mergeValues(uint32_t* vals) {
    return vals[0] | vals[1] | vals[2] | vals[3];
}

uint32_t InputMUX_4067_Dual::getP1andP2(uint8_t mux1, uint8_t mux2) {
    if (mux1 == mux2)  // if they are the same there's no reason to try and merge something with itself
        return this.vals[mux1];

    uint32_t buf = this.vals[mux1];
    ORBIT(buf, PIUIO_InputPacket::P2_UPLEFT, GETBIT(this.vals[mux2], PIUIO_InputPacket:P2_UPLEFT));
    ORBIT(buf, PIUIO_InputPacket::P2_UPRIGHT, GETBIT(this.vals[mux2], PIUIO_InputPacket:P2_UPRIGHT));
    ORBIT(buf, PIUIO_InputPacket::P2_CENTER, GETBIT(this.vals[mux2], PIUIO_InputPacket:P2_CENTER));
    ORBIT(buf, PIUIO_InputPacket::P2_DOWNLEFT, GETBIT(this.vals[mux2], PIUIO_InputPacket:P2_DOWNLEFT));
    ORBIT(buf, PIUIO_InputPacket::P2_DOWNRIGHT, GETBIT(this.vals[mux2], PIUIO_InputPacket:P2_DOWNRIGHT));

    return buf;
}


const uint32_t* InputMUX_4067_Dual::getValues() {
    return &this.vals;
}