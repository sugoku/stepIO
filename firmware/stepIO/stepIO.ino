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

#include "Config.h"
#include "Defaults.h"
#include "Output/Output.h"
#include "Input/Input.h"
#ifdef EEPROM_ENABLED
    #include "EEPROM/EEPROM_IO.h"
#endif

uint8_t status = 0;
uint32_t outbuf = 0;
uint32_t* lightbuf;
uint32_t* inVals[];
// uint32_t* outMuxes[2];
uint8_t config[256];
uint32_t blocked = 0;

uint8_t inmode = 0;
uint8_t outmode = 0;
uint8_t lightsmode = 0;

uint8_t devicemode = 0;
bool boardcomm_on = false;

// InputSensor in;
Input in;
Output out;
Lights lt;
Lights lightex;  // extra lights (RGB, etc.)
EEPROM_IO ee;
SerialC serialc;
BoardComm boardcomm;

void UpdateHost(Output* out) {
    if (out == NULL) return;
    out->updateHost();
}

uint8_t UpdateInput(Input* in) {
    if (in == NULL) return -1;
    return in->update();
}

int UpdateLights(Lights* lt, uint32_t* buf) {
    if (lt == NULL) return -1;
    return lt->send(buf);
}

void HandleSerial(SerialC* ser) {
    ser->update();
    if (ser->overflow()) {
        ser->sendStatus(SerialMessages::ERROR_OVERFLOW);
    }
}

void HandleBoardComm(BoardComm* bc) {
    bc->update();
}

ISR (SPI_STC_vect)
{
    // if (devicemode == DEVICE_SECONDARY)
    boardcomm->lastmsg = SPDR;
    SPDR = boardcomm->nextmsg;
}

void GetOutput(Input *in, uint32_t* buf) {
    if (in == NULL) return;
    *buf = *inVals[0];
}

void FilterOutput(uint16_t* buf) {
    buf &= blocked;  // global blocks
    
    #ifdef DEBOUNCING
        // something
        // probably wait X ms before actually releasing if something is released
    #endif
}

void SendOutput(Output* out, uint32_t* buf) {
    if (out == NULL) return;
    out->send(buf);
}

int EnableUSB(Output* out) {
    STRING_MANUFACTURER = out->getManufacturer();
    STRING_PRODUCT = out->getProduct();
    USB_DeviceDescriptorIAD = out->getDeviceDescriptor();

    USBDevice_ USBDevice();  // comment this out in core and modify constructor so i can change VID and PID
    USBDevice.attach();  // connects device, needs to be commented out from main.cpp

    // alternatively, could detach, change constructor, then reattach (though pluggableusb might make that annoying?)
}

void setup() {

    #ifdef EEPROM_ENABLED
        version = ee.versionCheck();
        if (EEPROM_FIRST_TIME || version == 0xFF || version == 0x00) {
            ee.writeDefaults(&defaults);
        }
        status = ee.readConfig(&config);
        #ifndef SIMPLE_IO
            if (status < 0) {
                if (-readValue == EEPROM_ADDR_ERR) {
                    // Address was out of range
                }
                // put WireErrors here
            }
        #endif
    #else
        config = defaults;
    #endif

    inmode = config[ConfigOptions::INPUT_MODE];
    outmode = config[ConfigOptions::OUTPUT_MODE];
    lightsmode = config[ConfigOptions::LIGHTS_MODE];

    #ifdef PINCONFIG
        // CFG1-CFG4
        uint8_t pinconfig = 0;

        for (uint8_t i = 7; i >= 4; i--) {
            // set the selector pins to the current value
            SETORCLRBIT(MUX_S2_PORT, MUX_S2_PIN, (i >> 2) & 1);
            SETORCLRBIT(MUX_S1_PORT, MUX_S1_PIN, (i >> 1) & 1);
            SETORCLRBIT(MUX_S0_PORT, MUX_S0_PIN, i & 1);

            #ifdef PULLUP_IN
                SETORCLRBIT(pinconfig, i-4, !(GETBIT(MUX1_IN_READ, MUX1_IN_PIN)));
            #else
                SETORCLRBIT(pinconfig, i-4, GETBIT(MUX1_IN_READ, MUX1_IN_PIN));
            #endif
        }

        config[ConfigOptions::PLAYER] = (pinconfig & 1) ? PLAYER_1 : PLAYER_2;
        config[ConfigOptions::OUTPUT_MODE] = (pinconfig >> 1) & 0b111;
    #endif

    WATCHDOG_ENABLE;

    USBCON |= (1<<OTGPADE); // enable VBUS detection
    devicemode = (USBSTA & 1) ? DEVICE_PRIMARY : DEVICE_SECONDARY;  // set device mode based on if USB power is received

    in = Input_Simple();
    in.setup();

    if (devicemode == DEVICE_PRIMARY) {
        boardcomm = CommPrimary_SPI();

        switch (outmode) {
            case OutputMode::Joystick:
                out = Output_Joystick();
                break;
            case OutputMode::Keyboard:
                out = Output_Keyboard();
                break;
            case OutputMode::PIUIO:
                out = Output_PIUIO();
                break;
            case OutputMode::LXIO:
                out = Output_LXIO();
                break;
            case OutputMode::Switch:
                out = Output_Switch();
                break;
            case OutputMode::MIDI:
                out = Output_MIDI();
                break;
        }
        out.setup(&config);
        out.attach();
        lightbuf = out.getLights();
    } else {
        boardcomm = CommSecondary_SPI();
        lightbuf = nullptr;
    }

    #ifdef LIGHT_OUTPUT

        lt = Lights_Simple();
        lt.setup();
        
    #endif

    uint8_t err = boardcomm.setup();  // will hang for 2 seconds until connection is made, if no connection then board communication stays off
    if (!err)
        boardcomm_on = true;

    boardcomm.setPlayer(config[ConfigOptions::PLAYER]);
    boardcomm.attachInputPacket(*outbuf);

    // get blocked inputs from the config
    blocked = (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_3] << 24);
    blocked |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_2] << 16);
    blocked |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_1] << 8);
    blocked |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_0]);

    EnableUSB(&out);  // SetupEndpoints();

    #ifdef SERIAL_ENABLED
        SERIAL_CONFIG.begin(SERIAL_BAUD);
        serialc.setup(&config, &Serial, &ee);
        if (outmode == OutputMode::Serial)
            serialc.setOutput(&out);
    #endif

    inVals = in.getValues();
    // outMuxes = {0xFF, 0xFF};
}

void loop() {

    WATCHDOG_RESET;

    if (devicemode == DEVICE_PRIMARY)
        UpdateHost(&out);

    UpdateInput(&in);

    #ifdef LIGHT_OUTPUT

        UpdateLights(&lt, lightbuf);

    #endif

    GetOutput(&in, &outbuf);

    FilterOutput(&outbuf);

    if (devicemode == DEVICE_PRIMARY)
        SendOutput(&out, &outbuf);
    
    #ifdef SERIAL_ENABLED

        HandleSerial(&serialc);
        
    #endif

    if (boardcomm_on)
        HandleBoardComm(&boardcomm);
}