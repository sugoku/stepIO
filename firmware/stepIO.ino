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
#ifdef EEPROM_ENABLED
    #include "EEPROM/EEPROM_IO.h"
#endif

uint8_t status;
uint8_t* outmode;
uint32_t outbuf;
uint32_t* lightbuf;
uint32_t* inVals[4];
uint32_t* inMuxes[2];
uint8_t config[255];
uint32_t blocked;

// InputSensor in;
InputMUX in;  // should be Input eventually
Output out;
Lights lt;
Lights lightex;  // extra lights (RGB, etc.)
EEPROM_IO ee;
SerialC serialc;

uint8_t UpdateHost(Output* out) {
    if (out == NULL) return -1;
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

int UpdateExtraLights(Lights* le, uint32_t* buf) {
    if (le == NULL) return -1;
    return le->send(buf);
}


void HandleSerial(SerialC* ser) {
    ser->update();
    if (ser->overflow()) {
        ser->sendStatus(SerialMessages::ERROR_OVERFLOW);
    }
}

void FilterOutput(uint32_t* buf) {
    buf &= blocked;
}

uint8_t SendOutput(Output* out, uint32_t* buf) {
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
        version = ee.versionCheck();
        if (EEPROM_FIRST_TIME || version == 0xFF || version == 0x00) {
            ee.writeDefaults();
        }
        status = ee.readConfig(*config);
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
        lightsmode = &config[ConfigOptions::LIGHTS_MODE];
        extralightsmode = &config[ConfigOptions::EXTRA_LIGHTS_MODE];
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
    lightbuf = out.getLights();

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

        switch (*extralightsmode) {
            case LightsMode::FastLED:  // this takes up a LOT of RAM so not great for brokeIO
                lightex = Lights_FastLED();  // FastLED library
                break;
            case LightsMode::WS2812X:
                lightex = Lights_WS2812X();  // neopixel library probably
                break;
            case LightsMode::APA102:
                lightex = Lights_APA102();  // <APA102.h> probably
                break;
        }
        lightex.setup(&config[ConfigOptions::RGB_LED_COUNT]);
        if (&config[ConfigOptions::EXTRA_LED_TRIGGER] != 0xFF)
            lightrgb.setTrigger(&config[ConfigOptions::EXTRA_LED_TRIGGER]);
        
    #endif

    // get blocked inputs from the config
    blocked = (uint32_t)(&config[ConfigOptions::BLOCKED_INPUTS_3] << 24);
    blocked |= (uint32_t)(&config[ConfigOptions::BLOCKED_INPUTS_2] << 16);
    blocked |= (uint32_t)(&config[ConfigOptions::BLOCKED_INPUTS_1] << 8);
    blocked |= (uint32_t)(&config[ConfigOptions::BLOCKED_INPUTS_0]);

    EnableUSB(out.getUSBData());  // SetupEndpoints();

    Serial.begin(SERIAL_BAUD);
    serialc.setup(&Serial, &ee);

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

        UpdateLights(&lt, &lightbuf);  // this might need to be redone or split

        UpdateExtraLights(&lightex, &lightbuf);

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

    FilterOutput(&outbuf);

    SendOutput(&out, &outbuf);

    HandleSerial(&serialc);
}