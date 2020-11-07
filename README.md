# stepIO (Legacy)
This is the legacy branch for the **st**age controller with **e**mulation of **P**IU**IO**, or in short, **stepIO**.
The current iteration of the legacy board is called the PIUIO Stage PCB v2, since it is the second iteration of the legacy PIUIO clone board.
Based off of racerxdl's PIUIO Clone, it is intended to be a foot PCB and IO replacement for Pump dance pads.

 - Support for Pump It Up connectors
 - Full pad light support and outputs for cabinet lights
 - Analog sensor reading (meaning support for Velostat and FSRs)
 - USB flashing support for using and updating to different firmwares
 - PIUIO emulation
 - Can receive 12V power from a DC jack or directly from the machine (using the 6-pin Molex connector)
 - Support for up to 4 multiplexed button inputs per board (with 4 extra inputs per board, which are reserved for configuration but can be remapped in code)

Note that to use two pads you need TWO stepIO boards, which are connected through a CAT-5 (Ethernet) cable and only one board is plugged into USB and DC 12V.
I have not tested the connection between two boards, and I'm doubtful that it works in its current state. However, it does act as a PIUIO properly and I was able to play official mixes with it.

This board merges all four sensors in a panel to one signal, meaning that you will not be able to individually read each sensor.

The hardware has been recently adapted to use SMD parts but there is an earlier through-hole version of the PCB.

## FAQ
### Where can I get one?
I now plan to push forward these legacy PCBs to make up for the time it is taking to complete the main stepIO codebase. After some test runs, I plan to sell them.

### What about the GHETT-io/BARR-io?
The legacy stepIO is not intended to be a competitor to the GHETT-io or BARR-io, but rather a board with a separate focus. GHETT-io and BARR-io utilize hardware efficiently with the intent of sub-millisecond performance in dance games, and it does it very well. The board (probably) does not reach this level of performance.
However, stepIO is useful for all the other features that the GHETT-io lacks, providing a different space for it to be used. Games such as Pump It Up poll their IO boards at relatively slow rates (50Hz best case, 12.5Hz worst case) so there will be no noticeable difference in real gameplay.

### How do I switch modes/change settings/update firmware?
With this code, you'll have to modify it yourself and upload it to the ATmega328P chip using avrdude, connecting a programmer such as an Arduino to the ISP header of the PCB.

### How do I determine which board is player 1 or player 2?
On the board NOT connected to USB, wire CFG1 to GND for player 1 and CFG2 to GND for player 2. If neither pin is wired the board that isn't connected to USB is player 1.

## LICENSE NOTES
For the legacy branch, the firmware is licensed under GPL-3.0 and any schematics are licensed under CC BY-SA 3.0.

Copyright © 2020 sugoku
