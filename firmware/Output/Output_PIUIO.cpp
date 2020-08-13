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

#include "Output_PIUIO.h"

void Output_PIUIO::updateHost() {
    uint32_t buf = recvControl(PIUIO_ENDPOINT) >> 16;

    // i don't think you can loop through enums so this is the best i'll get for now
    // PIUIO uses negative logic hence the NOT operators
    SETORCLRBIT(this.lights, LightsPacket::P1_UPLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P1_UPLEFT)));
    SETORCLRBIT(this.lights, LightsPacket::P1_UPRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P1_UPRIGHT)));
    SETORCLRBIT(this.lights, LightsPacket::P1_CENTER, !(GETBIT(buf, PIUIO_LightsPacket::P1_CENTER)));
    SETORCLRBIT(this.lights, LightsPacket::P1_DOWNLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P1_DOWNLEFT)));
    SETORCLRBIT(this.lights, LightsPacket::P1_DOWNRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(this.lights, LightsPacket::P2_UPLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P2_UPLEFT)));
    SETORCLRBIT(this.lights, LightsPacket::P2_UPRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P2_UPRIGHT)));
    SETORCLRBIT(this.lights, LightsPacket::P2_CENTER, !(GETBIT(buf, PIUIO_LightsPacket::P2_CENTER)));
    SETORCLRBIT(this.lights, LightsPacket::P2_DOWNLEFT, !(GETBIT(buf, PIUIO_LightsPacket::P2_DOWNLEFT)));
    SETORCLRBIT(this.lights, LightsPacket::P2_DOWNRIGHT, !(GETBIT(buf, PIUIO_LightsPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(this.lights, LightsPacket::MARQUEE_1, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_1)));
    SETORCLRBIT(this.lights, LightsPacket::MARQUEE_2, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_2)));
    SETORCLRBIT(this.lights, LightsPacket::MARQUEE_3, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_3)));
    SETORCLRBIT(this.lights, LightsPacket::MARQUEE_4, !(GETBIT(buf, PIUIO_LightsPacket::MARQUEE_4)));
    SETORCLRBIT(this.lights, LightsPacket::SUB_LEFT, !(GETBIT(buf, PIUIO_LightsPacket::SUB_NEON)));
    SETORCLRBIT(this.lights, LightsPacket::SUB_RIGHT, !(GETBIT(buf, PIUIO_LightsPacket::SUB_NEON)));

    // set mux values
    SETORCLRBIT(this.mux[0], 0, GETBIT(buf, PIUIO_LightsPacket::P1_MUXER_0));
    SETORCLRBIT(this.mux[0], 1, GETBIT(buf, PIUIO_LightsPacket::P1_MUXER_1));
    SETORCLRBIT(this.mux[1], 0, GETBIT(buf, PIUIO_LightsPacket::P2_MUXER_0));
    SETORCLRBIT(this.mux[1], 1, GETBIT(buf, PIUIO_LightsPacket::P2_MUXER_1));
}

const uint16_t* Output_PIUIO::getLights() {
    return &this.lights;
}

const uint8_t* Output_PIUIO::getMuxes() {
    return &this.mux;
}


void Output_PIUIO::send(uint16_t* inp) {
    uint64_t buf = 0xFFFFFFFF;
    
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_UPLEFT, !(GETBIT(inp, InputPacket::P1_UPLEFT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_UPRIGHT, !(GETBIT(inp, InputPacket::P1_UPRIGHT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_CENTER, !(GETBIT(inp, InputPacket::P1_CENTER)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_DOWNLEFT, !(GETBIT(inp, InputPacket::P1_DOWNLEFT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_DOWNRIGHT, !(GETBIT(inp, InputPacket::P1_DOWNRIGHT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P2_UPLEFT, !(GETBIT(inp, InputPacket::P2_UPLEFT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P2_UPRIGHT, !(GETBIT(inp, InputPacket::P2_UPRIGHT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P2_CENTER, !(GETBIT(inp, InputPacket::P2_CENTER)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P2_DOWNLEFT, !(GETBIT(inp, InputPacket::P2_DOWNLEFT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P2_DOWNRIGHT, !(GETBIT(inp, InputPacket::P2_DOWNRIGHT)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_COIN, !(GETBIT(inp, InputPacket::P1_COIN)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P2_COIN, !(GETBIT(inp, InputPacket::P2_COIN)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_TEST, !(GETBIT(inp, InputPacket::TEST_BUTTON)));
    // SETORCLRBIT(buf, PIUIO_InputPacket::P2_TEST, !(GETBIT(inp, InputPacket::TEST_BUTTON)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_SERVICE, !(GETBIT(inp, InputPacket::SERVICE_BUTTON)));
    // SETORCLRBIT(buf, PIUIO_InputPacket::P2_SERVICE, !(GETBIT(inp, InputPacket::SERVICE_BUTTON)));
    SETORCLRBIT(buf, PIUIO_InputPacket::P1_CLEAR, !(GETBIT(inp, InputPacket::CLEAR_BUTTON)));
    // SETORCLRBIT(buf, PIUIO_InputPacket::P2_CLEAR, !(GETBIT(inp, InputPacket::CLEAR_BUTTON)));

    sendControl(PIUIO_ENDPOINT, buf);
}

// endpoint 0xAE
// sendControl()
// recvControl()