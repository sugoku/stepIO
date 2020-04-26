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

#ifndef _OUTPUT_H
#define _OUTPUT_H

class Output
{
    public:
        virtual void setup() = 0;
        virtual void send() = 0;
        virtual void getLights() = 0;

};

enum OutputMode {
    Serial,
    Joystick,
    Keyboard,
    PIUIO,
    LXIO,
    Switch,
    MIDI  // not implemented
};

#endif