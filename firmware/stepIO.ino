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

int status;
uint8_t usbdata[3];
uint8_t config[255];

int GetHostInput(Output out, uint8_t *lightbuf) {
    out.update();
    out.getLights(lightbuf);
}

int UpdateInput(Input in, uint8_t *buf) {
    in.read(buf);
}

int UpdateLights(Input in, uint8_t *buf) {
    in.read(buf);
}

int SendOutput(Output out, uint8_t *buf) {
    out.send(buf);
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

    status = EEPROM_GetUSBInfo(*usbdata);
    if (status < 0) {
        
    }

#else
    

#endif

    out = Output(*usbdata);

    watchdogEnable(WATCHDOG_TIMEOUT);

    EnableUSB();  // SetupEndpoints();

}

void loop() {

    watchdogReset();

    GetHostInput();
    UpdateInput();
    UpdateLights();
    SendOutput();

}