# stepIO simple
This is the simple version of the firmware for the **st**age controller with **e**mulation of **P**IU**IO**, or in short, **stepIO**.
This branch is intended to be used with the **susIO**, **s**imple **U**SB **s**tage IO. susIO aims to be a stage PCB which allows one to directly connect Pump It Up pads to a computer as well as official games. It has:

- Support for Pump It Up and In the Groove connectors, as well as header pins for everything else
- Full 12V pad light support with header pin outputs
- Open-source firmware and USB flashing support for using and updating to different firmwares
- Emulation of HID and other USB devices such as joystick, keyboard, legacy PIUIO and LXIO
- Direct configuration of boards through jumpers
- Headers for coin, test, service and clear buttons
- Extremely small size using modern surface mounted parts

One susIO is required per pad, and two susIO boards may be connected through a CAT-5 cable. The primary board uses 5V from the USB cable and 12V from either a 12V DC supply or a Pump pad power cable, supplying power to the secondary board.

More info is available on the repository wiki.

LICENSE NOTES:
The firmware of stepIO is licensed under GPLv3, but the Arduino core is licensed under LGPLv2.1 and the schematics are licensed under CC BY-SA 3.0. The licenses are included in their respective folders.