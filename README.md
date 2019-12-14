# stepIO
This is a **st**age controller with **e**mulation of **P**IU**IO**, or in short, **stepIO**.
Originally based off racerxdl's PIUIO Clone, it is intended to be a foot PCB and IO replacement for dance pads. It focuses on customization and convenience, with several extra features, such as:

 - Support for Pump It Up and Dance Dance Revolution connectors
 - Full pad light support and outputs for cabinet lights
 - Analog sensor reading (meaning support for Velostat and FSRs)
 - USB flashing support for using and updating to different firmwares
 - Emulation of HID devices such as joystick, keyboard, and legacy PIUIO
 - Support for up to 8 multiplexed button inputs per board and 8 outputs per board (5V outputs, not for lights)
 - RGB LED support (?)

Note that to use two pads you need TWO stepIO boards, which are connected through a CAT-5 (Ethernet) cable and only one board is plugged into USB and DC 12V.

## FAQ
### Where can I get one?
I plan to stock up on them. I don't have a shop yet, but you'll be able to buy them on the Official Buy/Sell/Trade Group for Rhythm Games on Facebook.

### What about the GHETT-io/BARR-io?
stepIO is not intended to be a competitor to the GHETT-io or BARR-io, but rather a board with a separate focus. GHETT-io and BARR-io utilize hardware efficiently with the intent of sub-millisecond performance in dance games, and it does it very well. stepIO does not reach this level of performance.
*put benchmarks here*
However, stepIO is useful for all the other features that the GHETT-io lacks, providing a different space for it to be used. Games such as Pump It Up poll their IO boards at relatively slow rates.

### How do I switch modes/change settings/update firmware?
All of this can be done using the stepIO Configurator. Code is reflashed every time something is changed, but the process of flashing new code is made to be as simple and foolproof as possible with the configurator.

### How do I determine which board is player 1 or player 2?
On the board NOT connected to USB, wire COIN to GND for player 1 and TEST to GND for player 2. If neither pin is wired the board that isn't connected to USB is player 1.