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
#include "Defaults.h"
#include "Output/Output.h"
#include "Input/Input_MUX4067_Dual.h"
#ifdef EEPROM_ENABLED
    #include "EEPROM/EEPROM_IO.h"
#endif

uint8_t status = 0;
uint32_t outbuf = 0;
uint32_t* lightbuf;
uint32_t* inVals[];
uint8_t* outMuxes[2];
uint8_t config[256];
uint32_t blocked[5] = {0, 0, 0, 0, 0};  // 5th is a global block

uint8_t inmode = 0;
uint8_t outmode = 0;
uint8_t lightsmode = 0;
uint8_t extralightsmode = 0;

// InputSensor in;
Input in;
Output out;
Lights lt;
Lights lightex;  // extra lights (RGB, etc.)
EEPROM_IO ee;
SerialC serialc;

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

void GetOutput(Input *in, uint32_t* buf) {
    if (in == NULL) return;
    if (outmode == OutputMode::PIUIO) {
        if (config[ConfigOptions::MUX_POLLING_MODE] == MUXPollingMode::Normal) {
            #ifdef SIMPLE_PIUIO_MUX
                *buf = *inVals[outMuxes[0]];
            #else
                *buf = in.getP1andP2(outMuxes[0], outMuxes[1]);  // get a buffer of the input values but OR operator done on the two muxes (for sensor pins)
            #endif
        } else if (config[ConfigOptions::MUX_POLLING_MODE] == MUXPollingMode::Merged) {
            *buf = *in.getMergedValues();
        }
    } else {
        *buf = *inVals[0];
    }
}

void FilterOutput(uint32_t* buf) {
    // mux blocks
    if (outmuxes[0] != 0xFF) {
        buf &= (blocked[outMuxes[0]] & 0xFFFF0000);  // player 1
        buf &= (blocked[outMuxes[1]] & 0x0000FFFF);  // player 2
    }

    buf &= blocked[5];  // global blocks
    
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
        #ifndef BROKEIO
            if (status < 0) {
                if (-readValue == EEPROM_ADDR_ERR) {
                    // Address was out of range
                }
                // put WireErrors here
            }
        #endif

        inmode = config[ConfigOptions::INPUT_MODE];
        outmode = config[ConfigOptions::OUTPUT_MODE];
        lightsmode = config[ConfigOptions::LIGHTS_MODE];
        extralightsmode = config[ConfigOptions::EXTRA_LIGHTS_MODE];
    #else
        config = defaults;
    #endif

    WATCHDOG_ENABLE;

    switch (inmode) {
        case InputMode::MUX4051:
            // to be implemented in stepIO
            // in = InputMUX_4051();
            break;
        case InputMode::MUX4067:
            // to be implemented
            // in = InputMUX_4067();
            break;
        case InputMode::MUX4067_Dual:
            in = Input_MUX4067_Dual();
            break;
    }
    in.setup();
    

    switch (outmode) {
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
            vendorHandler = out.handleControl;  // allow us to handle vendor control transfers
            break;
        case OutputMode::Switch:
            // todo: add modified HID library and SwitchJoystick in order to use
            // out = Output_Switch();
            break;
        case OutputMode::MIDI:
            // todo: modify MIDIUSB to not instantly initialize in order to use
            // out = Output_MIDI();
            break;
    }
    out.setup(&config);
    out.attach();
    lightbuf = out.getLights();

    #ifdef LIGHT_OUTPUT

        switch (lightsmode) {
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

        switch (extralightsmode) {
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
        lightex.setup(config[ConfigOptions::RGB_LED_COUNT]);
        if (config[ConfigOptions::EXTRA_LED_TRIGGER] != 0xFF)
            lightrgb.setTrigger(config[ConfigOptions::EXTRA_LED_TRIGGER]);
        
    #endif

    // get blocked inputs from the config
    blocked[5] = (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_3] << 24);
    blocked[5] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_2] << 16);
    blocked[5] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_1] << 8);
    blocked[5] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_0]);

    blocked[0] = (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX0_3] << 24);
    blocked[0] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX0_2] << 16);
    blocked[0] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX0_1] << 8);
    blocked[0] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX0_0]);

    blocked[1] = (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX1_3] << 24);
    blocked[1] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX1_2] << 16);
    blocked[1] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX1_1] << 8);
    blocked[1] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX1_0]);

    blocked[2] = (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX2_3] << 24);
    blocked[2] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX2_2] << 16);
    blocked[2] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX2_1] << 8);
    blocked[2] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX2_0]);

    blocked[3] = (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX3_3] << 24);
    blocked[3] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX3_2] << 16);
    blocked[3] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX3_1] << 8);
    blocked[3] |= (uint32_t)(config[ConfigOptions::BLOCKED_INPUTS_MUX3_0]);

    EnableUSB(&out);  // SetupEndpoints();

    SERIAL_CONFIG.begin(SERIAL_BAUD);
    serialc.setup(&config, &Serial, &ee);
    if (outmode == OutputMode::Serial)
        serialc.setOutput(&out);

    inVals = in.getValues();
    if (outmode == OutputMode::Serial || outmode == OutputMode::PIUIO) {
        outMuxes = out.getMuxes();
    } else {
        outMuxes = {0xFF, 0xFF};
    }
        

}

void loop() {

    WATCHDOG_RESET;

    UpdateHost(&out);

    UpdateInput(&in);  // if DMA this isn't needed

    #ifdef LIGHT_OUTPUT

        UpdateLights(&lt, lightbuf);

        // extra lights
        UpdateLights(&lightex, lightbuf);

    #endif

    GetOutput(&in, &outbuf);

    FilterOutput(&outbuf);

    SendOutput(&out, &outbuf);

    HandleSerial(&serialc);
}