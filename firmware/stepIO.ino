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

int status;
int* outmode;
uint8_t config[255];

int GetHostInput(Output out, uint8_t *lightbuf) {
    out.updateHost();
    out.getLights(lightbuf);
}

int UpdateInput(Input in, uint8_t *buf) {
    in.updateIn(buf);
}

int UpdateLights(Lights lt, uint8_t *buf) {
    lt.read(buf);
}

int SendOutput(Output out, uint8_t *buf) {
    out.send(buf);
}

int EnableUSB(uint8_t *usbdata) {
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
    if (status < 0) {
        if (-readValue == EEPROM_ADDR_ERR) {
            // Address was out of range
        }
        // put WireErrors here
    }

    outmode = &config[ConfigOptions::OUTPUT_MODE];  // not sure if i need parentheses here

#else
    

#endif

    watchdogEnable(WATCHDOG_TIMEOUT);

    switch (*outmode) {
        case OutputMode::Serial:
            Output out = Output_Serial();
        break;
        case OutputMode::Joystick:
            Output out = Output_Joystick();
        break;
        case OutputMode::Keyboard:
            Output out = Output_Keyboard();
        break;
        case OutputMode::PIUIO:
            Output out = Output_PIUIO();
        break;
        case OutputMode::LXIO:
            Output out = Output_LXIO();
        break;
        case OutputMode::Switch:
            Output out = Output_Switch();
        break;
        case OutputMode::MIDI:
            Output out = Output_MIDI();
        break;
    }
    out.attach();

    EnableUSB(out.getUSBData());  // SetupEndpoints();

}

void loop() {

    watchdogReset();

    GetHostInput();
    UpdateInput();  // if DMA this isn't needed
    UpdateLights();  // this might need to be redone or split
    SendOutput();

}