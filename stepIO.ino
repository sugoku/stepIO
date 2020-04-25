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

void setup() {

#ifdef EEPROM_ENABLED

    status = EEPROM_VersionCheck();
    status = EEPROM_ReadConfig(*config);

    status = EEPROM_GetUSBInfo(*usbdata);

#else
    

#endif

    out = Output(*usbdata);
}

void loop() {
    
    SetupEndpoints();
    UpdateInput();
    SendOutput();

}