# stepIO
This is the firmware for the **st**age controller with **e**mulation of **P**IU**IO**, or in short, **stepIO**.
Originally based off racerxdl's PIUIO Clone, it is intended to be a foot PCB and IO replacement for dance pads. It focuses on customization and convenience, with several extra features, such as:

- Support for Pump It Up and Dance Dance Revolution connectors, as well as header pins for everything else
- Full 12V pad light support with header pin outputs
- Analog sensor reading (meaning support for Velostat and FSRs)
- USB flashing support for using and updating to different firmwares
- Configuration through serial connection
- Emulation of HID and other USB devices such as joystick, keyboard, and legacy PIUIO
- Support for up to 16 multiplexed button inputs + multiplexer expansion for another 16 inputs, as well as 8 cabinet light outputs per board (5V outputs, meant to connect to a light controller board)
- RGB LED support (4 pin but 3 pin possible)

As of the latest iteration, you now only need one stepIO board to control two pads, and the second pad is connected to an extension board through two CAT-5 (Ethernet) cables. The master board uses 5V converted 3.3V from the USB cable and 12V from either a 12V DC supply or a Pump pad power cable.

In addition, this is also the firmware for the **brokeIO**, **B**edrock's **r**eplacement for **o**bsolete **K**orean hardwar**e** **IO** (in reference to the PIUIO and JAMMA).
The brokeIO is intended to be a cheap drop-in replacement for the PIUIO and can replace the JAMMA as well. The JAMMA edge pinout is broken out onto 2.54mm headers and can be connected to a external converter board. The 7-pin and 10-pin connectors for the pad and cabinet lights normally included on the JAMMA are also included on the brokeIO. There are also several extra pins which can be used to control additional multiplexers and RGB LEDs.

More info is available on the repository wiki.

LICENSE NOTES:
The firmware of stepIO is licensed under GPLv3, but the Arduino core is licensed under LGPLv2.1 and the schematics are licensed under CC BY-SA 3.0. The licenses are included in their respective folders.