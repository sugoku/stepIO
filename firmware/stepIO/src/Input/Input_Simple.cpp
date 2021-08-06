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

#include "Input_Simple.h"

#ifdef PULLUP_IN
    #define PULLUP_INV(x) !x
#else
    #define PULLUP_INV(x) x
#endif

void Input_Simple::setup() {
    #ifdef PULLUP_IN
        uint32_t mode = INPUT_PULLUP;
    #else
        uint32_t mode = INPUT;
    #endif

    pinMode(SENSOR_1, mode);
    pinMode(SENSOR_2, mode);
    pinMode(SENSOR_3, mode);
    pinMode(SENSOR_4, mode);
    pinMode(SENSOR_5, mode);

    pinMode(MUX1_IN, mode);
    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_S2, OUTPUT);
}

 uint8_t Input_Simple::muxToInputPacket(uint8_t mux_pin) {
    switch (mux_pin) {
        case (int)SIMPLE_IO_MUX_IN::COIN: 
            if (player == PLAYER_1) {
                return (int)InputPacket::P1_COIN;
            } else if (player == PLAYER_2) {
                return (int)InputPacket::P2_COIN;
            };
        case (int)SIMPLE_IO_MUX_IN::TEST: return (int)InputPacket::TEST_BUTTON;
        case (int)SIMPLE_IO_MUX_IN::SERVICE: return (int)InputPacket::SERVICE_BUTTON;
        case (int)SIMPLE_IO_MUX_IN::CLEAR: return (int)InputPacket::CLEAR_BUTTON;

    }
}

uint8_t Input_Simple::update() {
    if (player == PLAYER_1) {
        SETORCLRBIT(this->vals[0], (int)InputPacket::P1_UPLEFT, PULLUP_INV(GETBIT(SENSOR_1_READ, SENSOR_1_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P1_UPRIGHT, PULLUP_INV(GETBIT(SENSOR_2_READ, SENSOR_2_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P1_CENTER, PULLUP_INV(GETBIT(SENSOR_3_READ, SENSOR_3_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P1_DOWNLEFT, PULLUP_INV(GETBIT(SENSOR_4_READ, SENSOR_4_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P1_DOWNRIGHT, PULLUP_INV(GETBIT(SENSOR_5_READ, SENSOR_5_PIN)));
    } else if (player == PLAYER_2) {
        SETORCLRBIT(this->vals[0], (int)InputPacket::P2_UPLEFT, PULLUP_INV(GETBIT(SENSOR_1_READ, SENSOR_1_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P2_UPRIGHT, PULLUP_INV(GETBIT(SENSOR_2_READ, SENSOR_2_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P2_CENTER, PULLUP_INV(GETBIT(SENSOR_3_READ, SENSOR_3_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P2_DOWNLEFT, PULLUP_INV(GETBIT(SENSOR_4_READ, SENSOR_4_PIN)));
        SETORCLRBIT(this->vals[0], (int)InputPacket::P2_DOWNRIGHT, PULLUP_INV(GETBIT(SENSOR_5_READ, SENSOR_5_PIN)));
    }

    // read mux
    for (uint8_t i = 3; i >= 0; i--) {
        SETORCLRBIT(MUX_S2_PORT, MUX_S2_PIN, (i >> 2) & 1);
        SETORCLRBIT(MUX_S1_PORT, MUX_S1_PIN, (i >> 1) & 1);
        SETORCLRBIT(MUX_S0_PORT, MUX_S0_PIN, i & 1);

        SETORCLRBIT(this->vals[0], this->muxToInputPacket(i), PULLUP_INV(GETBIT(MUX1_IN_READ, MUX1_IN_PIN)));
    }

    return 8;
}