# stepIO

This is the **stepIO** project, an open-source platform for arcade rhythm game input/output solutions, especially for dance games such as Pump It Up and Dance Dance Revolution.

It is designed around the Arduino ecosystem in order to encourage community development for both software and hardware, as well as to allow people to easily incorporate preexisting libraries into the codebase.

The firmware is made with many features in mind:

- Support for a multitude of input, lights, output, and other configurations in order to support many use cases
  - Inputs can be read directly through pins or through multiplexers (74HC4051, 74HC4067)
  - Lights can be controlled through pins, latches (74HC595), and RGB controllers (WS2812, APA102, etc.)
  - stepIO can act as multiple devices for outputs: joystick, keyboard, PIUIO, MIDI, serial, etc.
- Modularity so that it is easy for anyone to program support for their own configurations
- Custom button mappings for output modes
- Straightforward configuration through a serial connection, as well as a graphical tool to configure devices

## Devices

### stepIO

This is the **st**age controller with **e**mulation of **P**IU**IO**, or in short, **stepIO**.
Originally based off racerxdl's PIUIO Clone, it is intended to be a foot PCB and IO replacement for dance pads. It focuses on customization and convenience, with several extra features, such as:

- Support for Pump It Up and Dance Dance Revolution connectors, as well as header pins for everything else
- Full 12V pad light support with header pin outputs
- Analog sensor reading (meaning support for Velostat and FSRs)
- USB 2.0 High Speed support, enabling a maximum of 0.125ms polling (other boards aside from the official PIUIO are limited to 1ms as they only support USB 2.0 Full Speed)
- USB flashing support for using and updating to different firmwares
- Support for up to 16 multiplexed button inputs + multiplexer expansion breakout for another 16 inputs, as well as 8 cabinet light outputs per board (3.3V outputs, meant to connect to a light controller board)
- RGB LED support (4 pin and 3 pin)

You only need one stepIO board to control two pads, and the second pad is connected to an extension board through two CAT-5 (Ethernet) cables. The master board uses 5V converted 3.3V from the USB cable and 12V from either a 12V DC supply or a power cable from a Pump or DDR pad.

As of writing this, the PCB and schematics are finalized but the stepIO firmware currently is not equipped to support this board. Hopefully as traction builds up and there is more community support for this project we will be able to make the code fully compatible.

### brokeIO

This is the **brokeIO**, **B**edrock's **r**eplacement for **o**bsolete **K**orean hardwar**e** **IO** (in reference to the PIUIO and JAMMA).
The brokeIO is intended to be a cheap drop-in replacement for the PIUIO and is able to replace the JAMMA as well. The JAMMA edge pinout is broken out onto 2.54mm headers and can be connected to a external board to attach a JAMMA edge connector to. The 7-pin and 10-pin connectors for the pad and cabinet lights normally included on the JAMMA are also included on the brokeIO. There are also several extra pins which can be used to control additional multiplexers and RGB LEDs, if programmed to do so.

The stepIO codebase is currently focused on supporting brokeIO hardware.

More info on stepIO is available on the repository wiki.

## LICENSE NOTES

The firmware of stepIO is licensed under GPL-3.0, but the Arduino core is licensed under LGPL-2.1 and any schematics are licensed under CC BY-SA 3.0. The licenses are included in their respective folders.
