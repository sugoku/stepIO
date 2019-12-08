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

#ifndef __usbconfig_h_included__
#define __usbconfig_h_included__

/* ---------------------------- Hardware Config ---------------------------- */

#define USB_CFG_IOPORTNAME      D               //  We use PORT D for the USB port pins
#define USB_CFG_DMINUS_BIT      0               //  This is the USB D- line. PORTD.0
#define USB_CFG_DPLUS_BIT       1               //  This is the USB D+ line. PORTD.1
                                                //  The D+ from USB must be also connected to INT0, on ATMEGA328 it's PORTD.2
#define USB_CFG_CLOCK_KHZ       (F_CPU/1000)    //  This is the USB clock in kHz. we just use AVR Frequency / 1000;
                                                //  The good values for crystal: 12MHz, 12.8Mhz, 15MHz, 16Mhz, 16.5Mhz, 18Mhz, 20Mhz
                                                //  Our design uses 16MHz.
                                                //  The F_CPU is the definition of the clock, so you don't need to change anything here.
#define USB_CFG_CHECK_CRC       0               //  This makes the microcontroller calculate checksums for the USB packets. We don't want it, and plus it only works @ 18MHz

/* --------------------------- Functional Range ---------------------------- */

#define USB_CFG_HAVE_INTRIN_ENDPOINT    0       //  The PIUIO only uses one endpoint for control transfers, so this doesn't matter.
#define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
#define USB_CFG_EP3_NUMBER              3
#define USB_CFG_IMPLEMENT_HALT          0
#define USB_CFG_SUPPRESS_INTR_CODE      0       
#define USB_CFG_INTR_POLL_INTERVAL      10
#define USB_CFG_IS_SELF_POWERED         0
#define USB_CFG_MAX_BUS_POWER           1000    //  This is the maximum current in mA, it will be divided by two (1000mA / 2 = 500mA).
#define USB_CFG_IMPLEMENT_FN_WRITE      1       //  Used when game writes the lamp data.
#define USB_CFG_IMPLEMENT_FN_READ       0       //  Not needed for V-USB.
#define USB_CFG_IMPLEMENT_FN_WRITEOUT   0
#define USB_CFG_HAVE_FLOWCONTROL        0
#define USB_CFG_DRIVER_FLASH_PAGE       0
#define USB_CFG_LONG_TRANSFERS          0
#define USB_COUNT_SOF                   0
#define USB_CFG_CHECK_DATA_TOGGLING     0
#define USB_CFG_HAVE_MEASURE_FRAME_LENGTH   0
#define USB_USE_FAST_CRC                0

/* -------------------------- Device Description --------------------------- */

#define USB_CFG_VENDOR_ID       0x47, 0x05                              //  PIUIO vendor ID (Cypress, 0x0547)
#define USB_CFG_DEVICE_ID       0x02, 0x10                              //  PIUIO device ID (EZ-USB FX2, 0x1002)
#define USB_CFG_DEVICE_VERSION   0x01, 0x00                             //  Version 0.1
#define USB_CFG_VENDOR_NAME     'F', 'A', 'K', 'E'
#define USB_CFG_VENDOR_NAME_LEN 8
#define USB_CFG_DEVICE_NAME     'P', 'I', 'U', 'I', 'O'
#define USB_CFG_DEVICE_NAME_LEN 5
#define USB_CFG_DEVICE_CLASS        0xff                                //  0xFF is a vendor-specific class
#define USB_CFG_DEVICE_SUBCLASS     0
#define USB_CFG_INTERFACE_CLASS     0                                   
#define USB_CFG_INTERFACE_SUBCLASS  0
#define USB_CFG_INTERFACE_PROTOCOL  0

/* ------------------- Fine Control over USB Descriptors ------------------- */

#define USB_CFG_DESCR_PROPS_DEVICE                  0
#define USB_CFG_DESCR_PROPS_CONFIGURATION           0
#define USB_CFG_DESCR_PROPS_STRINGS                 0
#define USB_CFG_DESCR_PROPS_STRING_0                0
#define USB_CFG_DESCR_PROPS_STRING_VENDOR           0
#define USB_CFG_DESCR_PROPS_STRING_PRODUCT          0
#define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    0
#define USB_CFG_DESCR_PROPS_HID                     0
#define USB_CFG_DESCR_PROPS_HID_REPORT              0
#define USB_CFG_DESCR_PROPS_UNKNOWN                 0

#endif /* __usbconfig_h_included__ */
