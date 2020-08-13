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

/*
notes:

how will we structure this code?
- any classes should have their own cpp
    - especially modular HID things
- provide serial interface with handlers and stuff in another cpp
- EEPROM config can be in another cpp

*/

#include "Config.h"
#include "Output/Output.h"
#include "InputMUX/InputMUX_4067_Dual.h"

uint8_t status;
uint8_t* outmode;
uint32_t* inVals[4];
uint32_t* inMuxes[2];
uint8_t config[255];

// InputSensor in;
InputMUX in;
Output out;
Lights lt;
LightsCustom lightc;

uint8_t UpdateHost(Output* out) {
    if (out == NULL) return -1;
    out->updateHost();
}

uint8_t UpdateInput(Input* in) {
    if (in == NULL) return -1;
    return in->update();
}

uint8_t UpdateLights(Lights* lt, uint8_t* buf) {
    if (lt == NULL) return -1;
    return lt->send(buf);
}

uint8_t SendOutput(Output* out, uint8_t* buf) {
    if (out == NULL) return -1;
    return out->send(buf);
}

int EnableUSB(uint8_t* usbdata) {
    // check *usbdata is valid

    USBDevice_ USBDevice(usbdata);  // comment this out in core and modify constructor so i can change VID and PID
    USBDevice.attach();  // connects device, needs to be commented out from main.cpp

    // alternatively, could detach, change constructor, then reattach (though pluggableusb might make that annoying?)
}

void setup() {

    #ifdef EEPROM_ENABLED
        version = EEPROM_VersionCheck();
        if (EEPROM_FIRST_TIME || version == 0xFF) {
            EEPROM_WriteDefaults();
        }
        status = EEPROM_ReadConfig(*config);
        #ifndef BROKEIO
            if (status < 0) {
                if (-readValue == EEPROM_ADDR_ERR) {
                    // Address was out of range
                }
                // put WireErrors here
            }
        #endif

        intype = &config[ConfigOptions::INPUT_TYPE];
        inmode = &config[ConfigOptions::INPUT_MODE];
        outmode = &config[ConfigOptions::OUTPUT_MODE];  // not sure if i need parentheses here
    #else
        config = defaults;
    #endif


    #if defined(__SAM3X8E__)
        watchdogEnable(WATCHDOG_TIMEOUT);
    #elif defined(__AVR__)
        wdt_enable(WATCHDOG_TIMEOUT);
    #endif

    // please merge InputMUX and InputSensor people can have multiple if they want
    switch (*intype) {
        /*
        case InputType::InputSensor:
            switch (*inmode) {
                case InputSensorMode::Analog:
                    in = Input_Analog();
                    break;
                case InputSensorMode::DMA:
                    in = Input_DMA();
                    break;
                case InputSensorMode::Software:
                    in = Input_Software();
                    break;
            }
            break;
        */
        case InputType::InputMUX:
            switch (*inmode) {
                case InputMUXMode::MUX4051:
                    in = InputMUX_4051();
                    break;
                case InputMUXMode::MUX4067:
                    in = InputMUX_4067();
                    break;
                case InputMUXMode::MUX4067_Dual:
                    in = InputMUX_4067_Dual();
                    break;
            }
            break;
    }
    

    switch (*outmode) {
        case OutputMode::Serial:
            out = Output_Serial();
            break;
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
    out.attach();

    #ifdef LIGHT_OUTPUT
        switch (*lightsmode) {
            case LightsMode::Latch:
                out = Lights_Latch();
                break;
            case LightsMode::WS2812X:
                out = Lights_WS2812X();
                break;
            case LightsMode::APA102:
                out = Lights_APA102();
                break;
            case LightsMode::Signal:
                out = Lights_Signal();
                break;
        }
        lt.setup();

        if (&config[ConfigOptions::EXTRA_LIGHTS]) {
            switch (*extralightsmode) {
                case LightsCustom::WS2812X:
                    lightc = LightsCustom_WS2812X();
                    break;
                case LightsCustom::APA102:
                    lightc = LightsCustom_APA102();
                    break;
            }
        }
        lightc.setPins(EXTRA_LIGHTS_DATA, EXTRA_LIGHTS_CLOCK);
    #endif

    EnableUSB(out.getUSBData());  // SetupEndpoints();

    inVals = &in.getValues();
    inMuxes = &in.getMuxes();

}

void loop() {

    #if defined(__SAM3X8E__)
        watchdogReset();
    #elif defined(__AVR__)
        wdt_reset();
    #endif

    UpdateHost(&out);

    UpdateInput(&in);  // if DMA this isn't needed

    #ifdef LIGHT_OUTPUT

        UpdateLights(&lt);  // this might need to be redone or split

        UpdateCustomLights(&lightc);

    #endif

    if (*outmode == OutputMode::PIUIO) {
        if !(&config[ConfigOptions::MERGED_INPUTS]) {
            #ifdef SIMPLE_PIUIO_MUX
                outbuf = &inVals[inMuxes[0]];
            #else
                outbuf = in.getP1andP2();  // get a buffer of the input values but OR operator done on the two muxes (for sensor pins)
            #endif
        } else {
            outbuf = InputMUX_4067_Dual.getMergedValues();  // make this part of Input instead or something
        }
    }
    SendOutput(&out, &outbuf);

}