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

#include "Output_MIDI.h"

void Output_MIDI::setup(uint8_t* config, MIDI_* mid=nullptr) {
    this->setConfig(config);
    MIDIUSB.begin();
}

void Output_MIDI::setConfig(uint8_t* config) {
    this->config = config;
}

void Output_MIDI::updateHost() {
    return;  // to be implemented (CCs or something? or just sending notes back)
}

void Output_MIDI::set(uint8_t midi0, uint8_t midi1, uint8_t midi2, bool on) {
    midiEventPacket_t packet[4];

    if (this->config[(int)ConfigOptions::MIDI_USE_FIRST_BYTE]) {
        packet = {midi0 >> 4, midi0, midi1, midi2};
    } else {
        if (on) {
            packet = {MIDI_NOTE_ON >> 4, MIDI_NOTE_ON || (midi0 & 0b1111), midi1, midi2};
        } else {
            packet = {MIDI_NOTE_OFF >> 4, MIDI_NOTE_OFF || (midi0 & 0b1111), midi1, midi2};
        }
    }

    MIDIUSB.sendMIDI(packet);
}

void Output_MIDI::send(uint32_t* buf) {
    uint16_t diff = this->input ^ *buf;  // XOR the two to see where any differences have happened

    // if there is a change, set key on or off based on buf's state
    if GETBIT(diff, (int)InputPacket::P1_UPLEFT)
        this->set(this->config[(int)ConfigOptions::P1_UPLEFT_KEYCODE], GETBIT(*buf, (int)InputPacket::P1_UPLEFT));
    if GETBIT(diff, (int)InputPacket::P1_UPRIGHT)
        this->set(this->config[(int)ConfigOptions::P1_UPRIGHT_KEYCODE], GETBIT(*buf, (int)InputPacket::P1_UPRIGHT));
    if GETBIT(diff, (int)InputPacket::P1_CENTER)
        this->set(this->config[(int)ConfigOptions::P1_CENTER_KEYCODE], GETBIT(*buf, (int)InputPacket::P1_CENTER));
    if GETBIT(diff, (int)InputPacket::P1_DOWNLEFT)
        this->set(this->config[(int)ConfigOptions::P1_DOWNLEFT_KEYCODE], GETBIT(*buf, (int)InputPacket::P1_DOWNLEFT));
    if GETBIT(diff, (int)InputPacket::P1_DOWNRIGHT)
        this->set(this->config[(int)ConfigOptions::P1_DOWNRIGHT_KEYCODE], GETBIT(*buf, (int)InputPacket::P1_DOWNRIGHT));
    if GETBIT(diff, (int)InputPacket::P2_UPLEFT)
        this->set(this->config[(int)ConfigOptions::P2_UPLEFT_KEYCODE], GETBIT(*buf, (int)InputPacket::P2_UPLEFT));
    if GETBIT(diff, (int)InputPacket::P2_UPRIGHT)
        this->set(this->config[(int)ConfigOptions::P2_UPRIGHT_KEYCODE], GETBIT(*buf, (int)InputPacket::P2_UPRIGHT));
    if GETBIT(diff, (int)InputPacket::P2_CENTER)
        this->set(this->config[(int)ConfigOptions::P2_CENTER_KEYCODE], GETBIT(*buf, (int)InputPacket::P2_CENTER));
    if GETBIT(diff, (int)InputPacket::P2_DOWNLEFT)
        this->set(this->config[(int)ConfigOptions::P2_DOWNLEFT_KEYCODE], GETBIT(*buf, (int)InputPacket::P2_DOWNLEFT));
    if GETBIT(diff, (int)InputPacket::P2_DOWNRIGHT)
        this->set(this->config[(int)ConfigOptions::P2_DOWNRIGHT_KEYCODE], GETBIT(*buf, (int)InputPacket::P2_DOWNRIGHT));
    if GETBIT(diff, (int)InputPacket::P1_COIN)
        this->set(this->config[(int)ConfigOptions::P1_COIN_KEYCODE], GETBIT(*buf, (int)InputPacket::P1_COIN));
    if GETBIT(diff, (int)InputPacket::P2_COIN)
        this->set(this->config[(int)ConfigOptions::P2_COIN_KEYCODE], GETBIT(*buf, (int)InputPacket::P2_COIN));
    if GETBIT(diff, (int)InputPacket::TEST_BUTTON)
        this->set(this->config[(int)ConfigOptions::TEST_BUTTON_KEYCODE], GETBIT(*buf, (int)InputPacket::TEST_BUTTON));
    if GETBIT(diff, (int)InputPacket::SERVICE_BUTTON)
        this->set(this->config[(int)ConfigOptions::SERVICE_BUTTON_KEYCODE], GETBIT(*buf, (int)InputPacket::SERVICE_BUTTON));
    if GETBIT(diff, (int)InputPacket::CLEAR_BUTTON)
        this->set(this->config[(int)ConfigOptions::CLEAR_BUTTON_KEYCODE], GETBIT(*buf, (int)InputPacket::CLEAR_BUTTON));

    this->send();

    this->input = *buf;  // update input variable
}