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
/*                                                        */
/*  Adapted from Lucas Teske's PIUIO Clone (@racerxdl)    */
/**********************************************************/
/*                    License is GPLv3                    */
/*            https://github.com/sugoku/stepIO            */
/**********************************************************/

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h> 
#include <util/delay.h> 

#include <avr/pgmspace.h>   
#include "usbdrv.h"
#include "usbconfig.h"

#define REVISION 0x01  // revision 1

#define GETBIT(port,bit) ((port) & (0x01 << (bit)))     //    Get Byte bit
#define SETBIT(port,bit) ((port) |= (0x01 << (bit)))    //    Set Byte bit
#define CLRBIT(port,bit) ((port) &= ~(0x01 << (bit)))   //    Clr Byte bit

static unsigned char LampData[8];       //    The LampData buffer received
static unsigned char InputData[8];      //    The InputData buffer to send
static unsigned char datareceived = 0;  //    How many bytes we received
static unsigned char dataLength = 0;    //    Total to receive

// static unsigned char Input[2];          //    The actual 16 bits Input data
static unsigned char Output[2];         //    The actual 16 bits Output data

static unsigned char SlaveConfig[4];    //    Slave's configuration

// PIUIO Bytes

// This is for byte 1 of the player input
#define BTN_COIN      0x04
#define BTN_TEST      0x02
#define BTN_SERVICE   0x40
#define BTN_CLEAR     0x80

// This is for byte 0 and 2 of the input
#define SENSOR_LU     0x01
#define SENSOR_RU     0x02
#define SENSOR_CN     0x04
#define SENSOR_LD     0x08
#define SENSOR_RD     0x10

// This is for byte 0 and 2 of the output
#define SENSOR_LIGHT_LU     0x04
#define SENSOR_LIGHT_RU     0x08
#define SENSOR_LIGHT_CN     0x10
#define SENSOR_LIGHT_LD     0x20
#define SENSOR_LIGHT_RD     0x40

/*
    -----
    SPI IMPLEMENTATION

    initial:
    figure out who is slave based on who has USB power
    if slave:
        wait to receive
    master sends okay
    slave sends revision number as four bytes (in case)
    slave sends four byte message (in case) containing status of config based on four pins (coin, test, service, clear) like 00001111
    right now:
    - 1000 (coin) = player 1
    - 0100 (test) = player 2
    loops right to left so if 1100 then master chooses player 1 (edit: behavior still works but no right to left looping right now)
    by default 0000 is player 1 as slave, player 2 as master as power can go through the front of the pump pad (wiring harness)

    sending between would be like:
    master to slave:
    00011111 (last five digits are lights, first three are other things?)
    slave to master:
    00011111 (last five digits are pad inputs, first three are other things? maybe test and service buttons?)

    btw i didn't actually follow this i just send the PIUIO bytes directly
    -----
*/

/* 
    atmega328p pins:

    PB0 - MULTIPLEX SELECT 0
    PB1 - MULTIPLEX SELECT 1
    PB2 - SS
    PB3 - MOSI
    PB4 - MISO
    PB5 - SCK
    PC0 - SENSOR 1 (upper left)
    PC1 - SENSOR 2 (upper right)
    PC2 - SENSOR 3 (center)
    PC3 - SENSOR 4 (down left)
    PC4 - SENSOR 5 (down right)
    PC5 - MULTIPLEX IN
    PD0 - USB DATA (-)
    PD1 - USB DATA (+)
    PD2 - USB DATA (+)
    PD3 - LIGHT OUT 1 (upper left)
    PD4 - LIGHT OUT 2 (upper right)
    PD5 - LIGHT OUT 3 (center)
    PD6 - LIGHT OUT 4 (down left)
    PD7 - LIGHT OUT 5 (down right)
*/

#define PLAYER_1     0
#define PLAYER_2     2

// Pin Maps
#define GET_LU       GETBIT(PINC,0)         //  Upper left
#define GET_RU       GETBIT(PINC,1)         //  Upper right
#define GET_CN       GETBIT(PINC,2)         //  Center
#define GET_LD       GETBIT(PINC,3)         //  Down left
#define GET_RD       GETBIT(PINC,4)         //  Down right

#define SET_LU       SETBIT(PIND,3)
#define SET_RU       SETBIT(PIND,4)
#define SET_CN       SETBIT(PIND,5)
#define SET_LD       SETBIT(PIND,6)
#define SET_RD       SETBIT(PIND,7)

#define CLR_LU       CLRBIT(PIND,3)
#define CLR_RU       CLRBIT(PIND,4)
#define CLR_CN       CLRBIT(PIND,5)
#define CLR_LD       CLRBIT(PIND,6)
#define CLR_RD       CLRBIT(PIND,7)

#define GET_MP_IN    GETBIT(PINC,5)         //  Multiplexer input


int player = PLAYER_1;

static unsigned char NSAddresses[4] = {BTN_COIN, BTN_TEST, BTN_SERVICE, BTN_CLEAR};  // Non-sensor addresses

void read_mplex() {
    unsigned char i;
    for (i = 0; i < 4; i++) {
        if (i & 1) { SETBIT(PORTB, 0); } else { CLRBIT(PORTB, 0); };
        if (i & 2) { SETBIT(PORTB, 1); } else { CLRBIT(PORTB, 1); };
            
        if (GET_MP_IN) { InputData[1] |= NSAddresses[i]; } else { InputData[1] &= ~(NSAddresses[i]); };
    }
    CLRBIT(PORTB, 0);
    CLRBIT(PORTB, 1);
}

unsigned char spi_talk (unsigned char payload)
{
    SPDR = payload; // Data to send
    while (!(SPSR & (1 << SPIF)));
    return (SPDR); // Data received
}

void spi_slave_setup() {
    DDRB = (1<<6);     // Set MISO as output
    SPCR = (1<<SPE);   // Enable SPI

    // Set up multiplexer and read values
    read_mplex();

    // Wait for master okay
    while (!(spi_talk(0) == 0xBD));

    // Send REVISION
    spi_talk(REVISION);

    // Send InputData[1]
    spi_talk(InputData[1]);
    spi_talk(0);
    spi_talk(0);
    spi_talk(0);
}

void spi_master_setup() {
    DDRB = (1<<5) | (1<<3);                   // Set MOSI and SCK as outputs
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);  // Enable SPI and set as master, set to clock/16

    // Master sends okay
    spi_talk(0xBD);

    // Receive revision number
    unsigned char slaveRevision;
    slaveRevision = spi_talk(0);

    // Receive config status
    unsigned char i;
    for (i = 0; i < 4; i++)
        SlaveConfig[i] = spi_talk(0);

    if (SlaveConfig[0] & BTN_TEST) player = PLAYER_1; // Slave is player 2
    if (SlaveConfig[0] & BTN_COIN) player = PLAYER_2; // Slave is player 1
}

USB_PUBLIC uchar usbFunctionWrite(uchar *data, uchar len) {
    // This function will be only triggered when game writes to the lamps output.
    unsigned char i;

    for (i = 0; datareceived < 8 && i < len; i++, datareceived++)
        LampData[datareceived] = data[i];

    if (datareceived == dataLength) {      //    Time to set OUTPUT
        Output[0] = LampData[0];           //    AM uses unsigned shorts for those.
        Output[1] = LampData[2];           //    So we just skip one byte
    }                                      //    The other bytes are just 0xFF junk

    return (datareceived == dataLength);   //    1 if we received it all, 0 if not
}

USB_PUBLIC uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (void *)data;

    if (rq->bRequest == 0xAE) {                                 //    Access Game IO
        switch (rq->bmRequestType) {
            case 0x40:                                          //    Writing data to outputs
                datareceived = 0;
                dataLength = (unsigned char)rq->wLength.word;
                return USB_NO_MSG;                              //    Just tell we want a callback to usbFunctionWrite
                break;
            case 0xC0:                                          //    Reading input data
                usbMsgPtr = InputData;                          //    Just point to the buffer, and 
                return 8;                                       //    say to send 8 bytes to the PC
                break;
        }
    }
    return 0;                                                   //    We should never reach this point
}

void pollInputOutput() {
    InputData[0] = 0xFF;
    InputData[1] = 0xFF;
    InputData[2] = 0xFF;
    InputData[3] = 0xFF;

    if (GET_LD) { InputData[player] |= SENSOR_LD; } else { InputData[player] &= ~(SENSOR_LD); };
    if (GET_LU) { InputData[player] |= SENSOR_LU; } else { InputData[player] &= ~(SENSOR_LU); };
    if (GET_CN) { InputData[player] |= SENSOR_CN; } else { InputData[player] &= ~(SENSOR_CN); };
    if (GET_RU) { InputData[player] |= SENSOR_RU; } else { InputData[player] &= ~(SENSOR_RU); };
    if (GET_RD) { InputData[player] |= SENSOR_RD; } else { InputData[player] &= ~(SENSOR_RD); };

    read_mplex();

    if (Output[player >> 1] & SENSOR_LIGHT_LD) { SET_LD; } else { CLR_LD; };
    if (Output[player >> 1] & SENSOR_LIGHT_LU) { SET_LU; } else { CLR_LU; };
    if (Output[player >> 1] & SENSOR_LIGHT_CN) { SET_CN; } else { CLR_CN; };
    if (Output[player >> 1] & SENSOR_LIGHT_RU) { SET_RU; } else { CLR_RU; };
    if (Output[player >> 1] & SENSOR_LIGHT_RD) { SET_RD; } else { CLR_RD; };
}

int main() {
    unsigned char i;
    unsigned char msg;

    wdt_enable(WDTO_1S);

    DDRD |= 0b11111000;
    DDRB |= 0b00000011;
    PORTB = 0;

    for (i = 0; i < 8; i++)
        InputData[i] = 0xFF;
        
    usbInit();
    usbDeviceDisconnect();                      // Enforce re-enumeration
    for (i = 0; i < 250; i++) {                 // Wait 500 ms
        wdt_reset();                            // Keep the watchdog happy
        _delay_ms(1);
    }
    usbDeviceConnect();
    if (usbConfiguration != 0) {                // Master
        spi_master_setup();
        sei();                                  // Enable interrupts after re-enumeration
        while (1) {
            wdt_reset();                        // Keep the watchdog happy
            usbPoll();
            pollInputOutput();
            if (player == PLAYER_1) { 
                msg = spi_talk(Output[1]);
                InputData[PLAYER_2] = msg;
            } 
            else { 
                msg = spi_talk(Output[0]); 
                InputData[PLAYER_1] = msg;
            }
        }
    }
    else {                                      // Slave
        spi_slave_setup();
        while (1) {
            pollInputOutput();
            if (player == PLAYER_1) { 
                msg = spi_talk(InputData[PLAYER_1]); 
                Output[0] = msg;
            }
            else { 
                msg = spi_talk(InputData[PLAYER_2]); 
                Output[1] = msg;
            }
        }
    }

    return 0;
}
