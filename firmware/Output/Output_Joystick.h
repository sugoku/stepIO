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

#ifndef _OUTPUT_JOYSTICK_H
#define _OUTPUT_JOYSTICK_H

#include "Output.h"
#include "HID-Project.h"

class Output_Joystick : public Output
{

    public:
        int setup();
        int updateIn();
        int updateInAnalog();  // allow the user to use analog input for X-Y axis joystick
        int updateHost();
        uint8_t* getLights() const;
        uint8_t* getUSBData() const;
};

#endif