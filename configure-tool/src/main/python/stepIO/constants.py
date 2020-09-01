CONFIGTOOL_VERSION = '0.0.1'
DEBUG_MODE = True

_SerialCommands = (
    ('CHANGE_INPUT_MODE', 'Change Input Mode'),
    ('CHANGE_OUTPUT_MODE', 'Change Output Mode'),
    ('CHANGE_LIGHTS_MODE', 'Change Lights Mode'),
    ('LIGHTS_FROM_SENSORS', 'Change Lights Based on Sensors'),
    ('CHANGE_EXTRA_LIGHTS_MODE', 'Change Extra Lights Mode'),
    ('CHANGE_MUX_POLLING_MODE', 'Change Mux Polling Mode'),
    ('CHANGE_DEBOUNCE_MODE', 'Change Debounce Mode'),
    ('SET_EXTRA_LED', 'Set Extra LED'),
    ('EDIT_INPUT', 'Edit Input'),
    ('ANALOG_THRESHOLD', 'Set Analog Threshold'),
    ('SAVE_TO_EEPROM', 'Save Config to EEPROM'),
    ('LOAD_FROM_EEPROM', 'Load Config from EEPROM'),
    ('GET_CONFIG', 'Get Config'),
    ('SET_CONFIG', 'Set Config'),
    ('SEND_INPUT', 'Send Input'),
    ('SEND_INPUT_ANALOG', 'Send Input (Analog)'),
    ('GET_LIGHTSMUX', 'Get Lights/Mux Packet'),
    ('SEND_LIGHTSMUX', 'Get Lights/Mux Packet'),
    ('CHANGE_BAUD', 'Change Serial Baud'),
    ('RESET', 'Reset Device'),
    ('STATUS_GET', 'Get Status'),
    ('SET_FACTORY_DEFAULTS', 'Restore Factory Defaults'),
    ('GET_DEVICE_INFO', 'Get Device Info'),
)

SerialCommands = {k[0]: i for i, k in enumerate(_SerialCommands)}
SerialCommandsStr = {i: k[0] for i, k in enumerate(_SerialCommands)}
SerialCommandsDisplay = {s[1]: s[0] for s in _SerialCommands}

SerialMessageTypes = {k: i for i, k in enumerate([
    'STATUS',
    'SENSOR',
    'SENSOR_ANALOG',
    'CONFIG'
])}

SerialMessages = {k: i for i, k in enumerate([
    'SUCCESS',
    'ALIVE',
    'ERROR_OVERFLOW',
    'ERROR_SHORT',
    'ERROR_UNKNOWN',
    'NOT_IMPLEMENTED',
    'ERROR_NOT_ATTACHED',
    'RESET'
])}

ConfigOptions = {k: i for i, k in enumerate([
    'VERSION_MODEL', # 0x0000
    'VERSION_MAJOR', 
    'VERSION_MINOR',
    'VERSION_REVISION',
    'VERSION_GEN',
    
    'UPDATE_STATUS', # 0x0005
    'LAST_ERROR',

    'INPUT_TYPE',  # InputMUX vs. InputSensor (should go unused soon)
    'INPUT_MODE',
    'MUX_POLLING_MODE',  # normal, merged, etc.
    'MUX_SIMPLE',

    'OUTPUT_MODE',  
    'LIGHTS_MODE',  # light output mode
    'LIGHTS_FROM_SENSORS',  # read lights directly from the sensor inputs instead of from the host
    'EXTRA_LIGHTS_MODE',  # programmable lights etc.
    'DEBOUNCE_MODE',

    'PLAYER',  # which player is the main PCB hooked up to? (no longer needed)
    'PANEL_COUNT',  # number of panels per player (anything from 1-5)
    'P1BUTTON_COUNT',  # number of buttons for player 1
    'P2BUTTON_COUNT',  # number of buttons for player 2
    'OTHERBUTTON_COUNT',  # number of non-player-specific buttons

    'BLOCKED_INPUTS_0',  # inputs based on InputPacket to filter out and prevent the user from using (potentially good for polling or disabling coin mode)
    'BLOCKED_INPUTS_1',  # 1 is not blocked, 0 is blocked (because AND operation used)
    'BLOCKED_INPUTS_2',
    'BLOCKED_INPUTS_3',

    'BLOCKED_INPUTS_MUX0_0',
    'BLOCKED_INPUTS_MUX0_1',
    'BLOCKED_INPUTS_MUX0_2',
    'BLOCKED_INPUTS_MUX0_3',
    
    'BLOCKED_INPUTS_MUX1_0',
    'BLOCKED_INPUTS_MUX1_1',
    'BLOCKED_INPUTS_MUX1_2',
    'BLOCKED_INPUTS_MUX1_3',
    
    'BLOCKED_INPUTS_MUX2_0',
    'BLOCKED_INPUTS_MUX2_1',
    'BLOCKED_INPUTS_MUX2_2',
    'BLOCKED_INPUTS_MUX2_3',

    'BLOCKED_INPUTS_MUX3_0',
    'BLOCKED_INPUTS_MUX3_1',
    'BLOCKED_INPUTS_MUX3_2',
    'BLOCKED_INPUTS_MUX3_3',

    # LSB
    'SERIAL_BAUD_BYTE0',
    'SERIAL_BAUD_BYTE1',
    'SERIAL_BAUD_BYTE2',
    'SERIAL_BAUD_BYTE3',

    'RGB_LED_COUNT',
    'EXTRA_LED_TRIGGER',  # 0xFF default, means disabled (based on nth bit of LightsPacket)

    'LIGHT_P1_UPLEFT_REMAP',  # for remapping lights (their position in the LightsPacket)
    'LIGHT_P1_UPRIGHT_REMAP',
    'LIGHT_P1_CENTER_REMAP',
    'LIGHT_P1_DOWNLEFT_REMAP',
    'LIGHT_P1_DOWNRIGHT_REMAP',
    'LIGHT_P2_UPLEFT_REMAP',
    'LIGHT_P2_UPRIGHT_REMAP',
    'LIGHT_P2_CENTER_REMAP',
    'LIGHT_P2_DOWNLEFT_REMAP',
    'LIGHT_P2_DOWNRIGHT_REMAP',
    'LIGHT_MARQUEE_1_REMAP',
    'LIGHT_MARQUEE_2_REMAP',
    'LIGHT_MARQUEE_3_REMAP',
    'LIGHT_MARQUEE_4_REMAP',
    'LIGHT_SUB_LEFT_REMAP',
    'LIGHT_SUB_RIGHT_REMAP',

    'P1_UPLEFT_REMAP',  # for remapping to other input (their position in the InputPacket)
    'P1_UPRIGHT_REMAP',
    'P1_CENTER_REMAP',
    'P1_DOWNLEFT_REMAP',
    'P1_DOWNRIGHT_REMAP',
    'P2_UPLEFT_REMAP',
    'P2_UPRIGHT_REMAP',
    'P2_CENTER_REMAP',
    'P2_DOWNLEFT_REMAP',
    'P2_DOWNRIGHT_REMAP',
    'P1_COIN_REMAP',
    'P2_COIN_REMAP',
    'TEST_BUTTON_REMAP',
    'SERVICE_BUTTON_REMAP',
    'CLEAR_BUTTON_REMAP',

    'P1_UPLEFT_KEYCODE',  # for keyboard
    'P1_UPRIGHT_KEYCODE',
    'P1_CENTER_KEYCODE',
    'P1_DOWNLEFT_KEYCODE',
    'P1_DOWNRIGHT_KEYCODE',
    'P2_UPLEFT_KEYCODE',
    'P2_UPRIGHT_KEYCODE',
    'P2_CENTER_KEYCODE',
    'P2_DOWNLEFT_KEYCODE',
    'P2_DOWNRIGHT_KEYCODE',
    'P1_COIN_KEYCODE',
    'P2_COIN_KEYCODE',
    'TEST_BUTTON_KEYCODE',
    'SERVICE_BUTTON_KEYCODE',
    'CLEAR_BUTTON_KEYCODE',

    'P1_UPLEFT_GAMEPAD',  # for gamepad
    'P1_UPRIGHT_GAMEPAD',
    'P1_CENTER_GAMEPAD',
    'P1_DOWNLEFT_GAMEPAD',
    'P1_DOWNRIGHT_GAMEPAD',
    'P2_UPLEFT_GAMEPAD',
    'P2_UPRIGHT_GAMEPAD',
    'P2_CENTER_GAMEPAD',
    'P2_DOWNLEFT_GAMEPAD',
    'P2_DOWNRIGHT_GAMEPAD',
    'P1_COIN_GAMEPAD',
    'P2_COIN_GAMEPAD',
    'TEST_BUTTON_GAMEPAD',
    'SERVICE_BUTTON_GAMEPAD',
    'CLEAR_BUTTON_GAMEPAD',

    'P1_UPLEFT_SWITCH',  # for switch
    'P1_UPRIGHT_SWITCH',
    'P1_CENTER_SWITCH',
    'P1_DOWNLEFT_SWITCH',
    'P1_DOWNRIGHT_SWITCH',
    'P2_UPLEFT_SWITCH',
    'P2_UPRIGHT_SWITCH',
    'P2_CENTER_SWITCH',
    'P2_DOWNLEFT_SWITCH',
    'P2_DOWNRIGHT_SWITCH',
    'P1_COIN_SWITCH',
    'P2_COIN_SWITCH',
    'TEST_BUTTON_SWITCH',
    'SERVICE_BUTTON_SWITCH',
    'CLEAR_BUTTON_SWITCH',

    'MIDI_ANALOG',  # if using analog input, send analog values as note velocity
    'MIDI_ANALOG_MIN',
    'MIDI_ANALOG_MAX',
    'MIDI_CHANNEL',
    
    'MIDI_USE_FIRST_BYTE',  # first byte (MIDI0) contains note on or note off info, enabling this bypasses note on and off signals by pressing and releasing

    'P1_UPLEFT_MIDI0',  # for MIDI, defining a MIDI event in order of header (byte1 >> 4), byte0, byte1, byte2
    'P1_UPLEFT_MIDI1',
    'P1_UPLEFT_MIDI2',
    'P1_UPLEFT_CHANNEL',
    'P1_UPRIGHT_MIDI0',
    'P1_UPRIGHT_MIDI1',
    'P1_UPRIGHT_MIDI2',
    'P1_UPRIGHT_CHANNEL',
    'P1_CENTER_MIDI0',
    'P1_CENTER_MIDI1',
    'P1_CENTER_MIDI2',
    'P1_CENTER_CHANNEL',
    'P1_DOWNLEFT_MIDI0',
    'P1_DOWNLEFT_MIDI1',
    'P1_DOWNLEFT_MIDI2',
    'P1_DOWNLEFT_CHANNEL',
    'P1_DOWNRIGHT_MIDI0',
    'P1_DOWNRIGHT_MIDI1',
    'P1_DOWNRIGHT_MIDI2',
    'P1_DOWNRIGHT_CHANNEL',
    'P2_UPLEFT_MIDI0',
    'P2_UPLEFT_MIDI1',
    'P2_UPLEFT_MIDI2',
    'P2_UPLEFT_CHANNEL',
    'P2_UPRIGHT_MIDI0',
    'P2_UPRIGHT_MIDI1',
    'P2_UPRIGHT_MIDI2',
    'P2_UPRIGHT_CHANNEL',
    'P2_CENTER_MIDI0',
    'P2_CENTER_MIDI1',
    'P2_CENTER_MIDI2',
    'P2_CENTER_CHANNEL',
    'P2_DOWNLEFT_MIDI0',
    'P2_DOWNLEFT_MIDI1',
    'P2_DOWNLEFT_MIDI2',
    'P2_DOWNLEFT_CHANNEL',
    'P2_DOWNRIGHT_MIDI0',
    'P2_DOWNRIGHT_MIDI1',
    'P2_DOWNRIGHT_MIDI2',
    'P2_DOWNRIGHT_CHANNEL',
    'P1_COIN_MIDI0',
    'P1_COIN_MIDI1',
    'P1_COIN_MIDI2',
    'P1_COIN_CHANNEL',
    'P2_COIN_MIDI0',
    'P2_COIN_MIDI1',
    'P2_COIN_MIDI2',
    'P2_COIN_CHANNEL',
    'TEST_BUTTON_MIDI0',
    'TEST_BUTTON_MIDI1',
    'TEST_BUTTON_MIDI2',
    'TEST_BUTTON_CHANNEL',
    'SERVICE_BUTTON_MIDI0',
    'SERVICE_BUTTON_MIDI1',
    'SERVICE_BUTTON_MIDI2',
    'SERVICE_BUTTON_CHANNEL',
    'CLEAR_BUTTON_MIDI0',
    'CLEAR_BUTTON_MIDI1',
    'CLEAR_BUTTON_MIDI2',
    'CLEAR_BUTTON_CHANNEL',

    'P1_UPLEFT_ANALOG',
    'P1_UPRIGHT_ANALOG',
    'P1_CENTER_ANALOG',
    'P1_DOWNLEFT_ANALOG',
    'P1_DOWNRIGHT_ANALOG',
    'P2_UPLEFT_ANALOG',
    'P2_UPRIGHT_ANALOG',
    'P2_CENTER_ANALOG',
    'P2_DOWNLEFT_ANALOG',
    'P2_DOWNRIGHT_ANALOG',
    'P1_COIN_ANALOG',
    'P2_COIN_ANALOG',
    'TEST_BUTTON_ANALOG',
    'SERVICE_BUTTON_ANALOG',
    'CLEAR_BUTTON_ANALOG',
    'EXTRA_BUTTON_ANALOG',
])}

# INPUT/OUTPUT CONSTANTS

_InputPacket = (
    ('P1_UPLEFT', 'P1 Up Left'),
    ('P1_UPRIGHT', 'P1 Up Right'),
    ('P1_CENTER', 'P1 Center'),
    ('P1_DOWNLEFT', 'P1 Down Left'),
    ('P1_DOWNRIGHT', 'P1 Down Right'),
    ('P2_UPLEFT', 'P2 Up Left'),
    ('P2_UPRIGHT', 'P2 Up Right'),
    ('P2_CENTER', 'P2 Center'),
    ('P2_DOWNLEFT', 'P2 Down Left'),
    ('P2_DOWNRIGHT', 'P2 Down Right'),
    ('P1_COIN', 'P1 Coin'),
    ('P2_COIN', 'P2 Coin'),
    ('TEST_BUTTON', 'Test Button'),
    ('SERVICE_BUTTON', 'Service Button'),
    ('CLEAR_BUTTON', 'Clear Button'),
)

InputPacket = {k[0]: i for i, k in enumerate(_InputPacket)}
InputPacketStr = {i: k[0] for i, k in enumerate(_InputPacket)}
InputPacketDisplay = {s[1]: s[0] for s in _InputPacket}
InputPacketNToDisplay = {i: k[1] for i, k in enumerate(_InputPacket)}

# 32 bits long
_LightsPacket = (
    ('P1_UPLEFT', 'P1 Up Left'),
    ('P1_UPRIGHT', 'P1 Up Right'),
    ('P1_CENTER', 'P1 Center'),
    ('P1_DOWNLEFT', 'P1 Down Left'),
    ('P1_DOWNRIGHT', 'P1 Down Right'),
    ('P2_UPLEFT', 'P2 Up Left'),
    ('P2_UPRIGHT', 'P2 Up Right'),
    ('P2_CENTER', 'P2 Center'),
    ('P2_DOWNLEFT', 'P2 Down Left'),
    ('P2_DOWNRIGHT', 'P2 Down Right'),
    ('MARQUEE_1', 'Marquee Light 1'),
    ('MARQUEE_2', 'Marquee Light 2'),
    ('MARQUEE_3', 'Marquee Light 3'),
    ('MARQUEE_4', 'Marquee Light 4'),
    ('SUB_LEFT', 'Subwoofer Neon Left'),
    ('SUB_RIGHT', 'Subwoofer Neon Right'),
    ('MUX0_S0', 'P1 Multiplexer Select Bit 0'),
    ('MUX0_S1', 'P1 Multiplexer Select Bit 1'),
    ('MUX1_S0', 'P2 Multiplexer Select Bit 0'),
    ('MUX1_S1', 'P2 Multiplexer Select Bit 1'),
)
_LightsPacketUsable = _LightsPacket[:16]
LightsPacket = {k[0]: i for i, k in enumerate(_LightsPacket)}
LightsPacketDisplay = {s[1]: s[0] for s in _LightsPacket}

# least to most significant bit
_PIUIO_InputPacket = {k: i for i, k in enumerate([
    ('NC_0', 'Not Connected 0'),
    ('P2_TEST', 'P2 Test Button'),
    ('P2_COIN', 'P2 Coin'),
    ('NC_3', 'Not Connected 3'),
    ('NC_4', 'Not Connected 4'),
    ('NC_5', 'Not Connected 5'),
    ('P2_SERVICE', 'P2 Service Button'),
    ('P2_CLEAR', 'P2 Clear Button'),
    ('P2_UPLEFT', 'P2 Up Left'),
    ('P2_UPRIGHT', 'P2 Up Right'),
    ('P2_CENTER', 'P2 Center'),
    ('P2_DOWNLEFT', 'P2 Down Left'),
    ('P2_DOWNRIGHT', 'P2 Down Right'),
    ('NC_13', 'Not Connected 13'),
    ('NC_14', 'Not Connected 14'),
    ('NC_15', 'Not Connected 15'),
    ('NC_16', 'Not Connected 16'),
    ('P1_TEST', 'P1 Test Button'),
    ('P1_COIN', 'P1 Coin'),
    ('NC_19', 'Not Connected 19'),
    ('NC_20', 'Not Connected 20'),
    ('NC_21', 'Not Connected 21'),
    ('P1_SERVICE', 'P1 Service Button'),
    ('P1_CLEAR', 'P1 Clear Button'),
    ('P1_UPLEFT', 'P1 Up Left'),
    ('P1_UPRIGHT', 'P1 Up Right'),
    ('P1_CENTER', 'P1 Center'),
    ('P1_DOWNLEFT', 'P1 Down Left'),
    ('P1_DOWNRIGHT', 'P1 Down Right'),
    ('NC_29', 'Not Connected 29'),
    ('NC_30', 'Not Connected 30'),
    ('NC_31', 'Not Connected 31'),
])}
PIUIO_InputPacket = {k[0]: i for i, k in enumerate(_PIUIO_InputPacket)}
PIUIO_InputPacketDisplay = {s[1]: s[0] for s in _PIUIO_InputPacket}
_PIUIO_LightsPacket = {k: i for i, k in enumerate([
    ('MARQUEE_3', 'Marquee Light 3'),
    ('MARQUEE_2', 'Marquee Light 2'),
    ('MARQUEE_1', 'Marquee Light 1'),
    ('NC_3', 'Not Connected 3'),
    ('NC_4', 'Not Connected 4'),
    ('NC_5', 'Not Connected 5'),
    ('NC_6', 'Not Connected 6'),
    ('NC_7', 'Not Connected 7'),
    ('P2_MUXER_0', 'P2 Multiplexer Select Bit 0'),
    ('P2_MUXER_1', 'P2 Multiplexer Select Bit 1'),
    ('P2_UPLEFT', 'P2 Up Left'),
    ('P2_UPRIGHT', 'P2 Up Right'),
    ('P2_CENTER', 'P2 Center'),
    ('P2_DOWNLEFT', 'P2 Down Left'),
    ('P2_DOWNRIGHT', 'P2 Down Right'),
    ('MARQUEE_4', 'Marquee Light 4'),
    ('NC_16', 'Not Connected 16'),
    ('NC_17', 'Not Connected 17'),
    ('SUB_LEFT', 'Subwoofer Neon'),
    ('NC_19', 'Not Connected 19'),
    ('NC_20', 'Not Connected 20'),
    ('NC_21', 'Not Connected 21'),
    ('NC_22', 'Not Connected 22'),
    ('NC_23', 'Not Connected 23'),
    ('P1_MUXER_0', 'P1 Multiplexer Select Bit 0'),
    ('P1_MUXER_1', 'P1 Multiplexer Select Bit 1'),
    ('P1_UPLEFT', 'P1 Up Left'),
    ('P1_UPRIGHT', 'P1 Up Right'),
    ('P1_CENTER', 'P1 Center'),
    ('P1_DOWNLEFT', 'P1 Down Left'),
    ('P1_DOWNRIGHT', 'P1 Down Right'),
    ('NC_31', 'Not Connected 31'),
])}
PIUIO_LightsPacket = {k[0]: i for i, k in enumerate(_PIUIO_LightsPacket)}
PIUIO_LightsPacketDisplay = {s[1]: s[0] for s in _PIUIO_LightsPacket}

_InputMode = (
    ('None', 'None'),
    ('Software', 'Software'),
    ('Analog', 'Analog'),
    ('DMA', 'DMA'),
    ('MUX4067_Dual', 'MUX4067 Dual'),
    ('MUX4067', 'MUX4067'),
    ('MUX4051', 'MUX4051'),
)
_InputModeUsable = {
    'stepIO': _InputMode[0:4],
    'brokeIO': _InputMode[0] + _InputMode[4:7],
}
InputMode = {k[0]: i for i, k in enumerate(_InputMode)}
InputModeDisplay = {s[1]: s[0] for s in _InputMode}

_MUXPollingMode = (
    ('Normal', 'Normal'),
    ('Merged', 'Merged'),
    ('HalfMerged', 'Half-Merged'),
    ('One', 'No Multiplexing'),
)
MUXPollingMode = {k[0]: i for i, k in enumerate(_MUXPollingMode)}
MUXPollingModeDisplay = {s[1]: s[0] for s in _MUXPollingMode}

_LightsMode = (
    ('None', 'None'),
    ('Latch32', 'Latch 32-out'),  # brokeIO
    ('Latch', 'Latch 8-out'),
    ('Signal', 'Direct Signal'),
    ('FastLED', 'FastLED'),
    ('WS281X', 'WS281X'),
    ('APA102', 'APA102'),
)
_LightsModeUsable = {
    'brokeIO': _InputMode[:2] + _InputMode[4:7],
}
LightsMode = {k[0]: i for i, k in enumerate(_LightsMode)}
LightsModeDisplay = {s[1]: s[0] for s in _LightsMode}

_OutputMode = (
    ('None', 'None'),
    ('Serial', 'Serial'),
    ('Joystick', 'Joystick'),
    ('Keyboard', 'Keyboard'),
    ('PIUIO', 'PIUIO'),
    ('PIUIO_ButtonBoard', 'PIUIO (Button Board)'),
    ('Switch', 'Switch Controller'),
    ('MIDI', 'MIDI'),
)
OutputMode = {k[0]: i for i, k in enumerate(_OutputMode)}
OutputModeDisplay = {s[1]: s[0] for s in _OutputMode}

_DebounceMode = (
)
DebounceMode = {k[0]: i for i, k in enumerate(_DebounceMode)}
DebounceModeDisplay = {s[1]: s[0] for s in _DebounceMode}


_UpdateStatus = (
    ('SUCCESS', 'Success'),
    ('PENDING_FLASH', 'Pending Flash'),
    ('FLASH_ERROR', 'Flash Error'),
    ('NOT_FLASHED', 'Not Flashed', 0xFF),
)

UpdateStatus = {k[0]: i if len(k) <= 2 else k[2] for i, k in enumerate(_UpdateStatus)}
UpdateStatusDisplay = {s[1]: s[0] for s in _UpdateStatus}

_WireError = ( # I2C errors, EEPROM
    ('NONE', 'None'),
    ('DATA_TOO_LONG', 'Data Too Long'),
    ('NACK_ON_ADDR', 'NACK on Address'),
    ('NACK_ON_DATA', 'NACK on Data'),
    ('OTHER_ERROR', 'Other Error'),
)

WireError = {k[0]: i for i, k in enumerate(_WireError)}
WireErrorDisplay = {s[1]: s[0] for s in _WireError}

_RuntimeErrors = (
    ('NONE', 'None', 0xFF),
)

RuntimeErrors = {k[0]: i if len(k) <= 2 else k[2] for i, k in enumerate(_RuntimeErrors)}
RuntimeErrorsDisplay = {s[1]: s[0] for s in _RuntimeErrors}

# CONFIG DEFINES

STEPIO_MANUFACTURER = "sugoku"

DEFAULT_ANALOG_VALUE = 200  # out of 255
EEPROM_DEFAULT_VALUE = 0xFF

# test PID, should not be used in production!
STEPIO_VID = 0x1209
STEPIO_PID = 0x0001

STEPIO_VERSION_GEN = 0x02

STEPIO_PRODUCT = "stepIO"
BROKEIO_PRODUCT = "brokeIO"

DEFAULT_RGB_LED_COUNT = 288  # Default amount of RGB LEDs to use
DEFAULT_LED_COLORS = [0, 230, 255]  # Default LED colors in RGB order (this is bright blue like the subwoofer neons)

# brokeIO
'''
MUX_ENABLE = A5   // PF0
MUX_ENABLE_READ = PINF
MUX_ENABLE_PORT = PORTF
MUX_ENABLE_MODE = DDRF
MUX_ENABLE_PIN = 0


MUX1_IN = 8       // PB4
MUX1_IN_READ = PINB
MUX1_IN_PORT = PORTB
MUX1_IN_MODE = DDRB
MUX1_IN_PIN = 4

MUX2_IN = A4      // PF1
MUX2_IN_READ = PINF
MUX2_IN_PORT = PORTF
MUX2_IN_MODE = DDRF
MUX2_IN_PIN = 1


MUX_S0 = A3       // PF4
MUX_S0_READ = PINF
MUX_S0_PORT = PORTF
MUX_S0_MODE = DDRF
MUX_S0_PIN = 4

MUX_S1 = A2       // PF5
MUX_S1_READ = PINF
MUX_S1_PORT = PORTF
MUX_S1_MODE = DDRF
MUX_S1_PIN = 5

MUX_S2 = A1       // PF6
MUX_S2_READ = PINF
MUX_S2_PORT = PORTF
MUX_S2_MODE = DDRF
MUX_S2_PIN = 6

MUX_S3 = A0       // PF7
MUX_S3_READ = PINF
MUX_S3_PORT = PORTF
MUX_S3_MODE = DDRF
MUX_S3_PIN = 7

# look into pins_arduino.h to disable TXLED and RXLED
#define LATCH_RCLK      // PD5, TXLED
LATCH_RCLK_READ = PIND
LATCH_RCLK_PORT = PORTD
LATCH_RCLK_MODE = DDRD
LATCH_RCLK_PIN = 5

LATCH_RST = 12    // PD6
LATCH_RST_READ = PIND
LATCH_RST_PORT = PORTD
LATCH_RST_MODE = DDRD
LATCH_RST_PIN = 6

LATCH_ENABLE = 6  // PD7
LATCH_ENABLE_READ = PIND
LATCH_ENABLE_PORT = PORTD
LATCH_ENABLE_MODE = DDRD
LATCH_ENABLE_PIN = 7

EXTRA_LIGHTS_DATA = 9  // PB5
EXTRA_LIGHTS_CLOCK = 10  // PB6
'''

# this stuff is currently unused but if button board support is added it probably will matter more
PLAYER_1 = 0x0
PLAYER_2 = 0x1
DEFAULT_PLAYER = PLAYER_1
DEFAULT_PLAYER_COUNT = 2
PANELS_PER_PLAYER = 5
PLAYER_1_BUTTONS = 5  # p1 coin, left, right, select, back
PLAYER_2_BUTTONS = 5  # p2 coin, left, right, select, back
OTHER_BUTTONS = 3  # test, service, clear

EEPROM_OFFSET = 0x00  # needs to be implemented

EEPROM_TRUE = 0x01
EEPROM_FALSE = 0x00

EEPROM_SIZE = 1000  # bytes

'''
EEPROM_SIZE = kbits_256  # size of EEPROM
EEPROM_MAX_ADDR = 0x7D00
EEPROM_COUNT = 1  # how many EEPROM chips in I2C lane
EEPROM_ADDRESS = 0x50
EEPROM_SPEED = extEEPROM::twiClock100kHz  # more electrically stable which works considering we don't need fast speeds to read bytes of EEPROM
'''

INPUT_COUNT = 15

DEFAULT_BLOCKED_INPUTS_0 = EEPROM_DEFAULT_VALUE
DEFAULT_BLOCKED_INPUTS_1 = EEPROM_DEFAULT_VALUE
DEFAULT_BLOCKED_INPUTS_2 = EEPROM_DEFAULT_VALUE
DEFAULT_BLOCKED_INPUTS_3 = EEPROM_DEFAULT_VALUE

PIUIO_ENDPOINT = 0x00  # control endpoint
PIUIO_ADDRESS = 0xAE
PIUIO_INDEX = 0x00
PIUIO_VALUE = 0x00

PIUIO_VID = 0x0547
PIUIO_PID = 0x1002

# NINTENDO SWITCH

# bitshift, check 2nd digit

EEPROM_SWITCH_BUTTON = 0x0
EEPROM_SWITCH_HAT = 0x1
EEPROM_SWITCH_STICK = 0x2

EEPROM_SWITCH_BUTTON_Y = 0x00
EEPROM_SWITCH_BUTTON_B = 0x01
EEPROM_SWITCH_BUTTON_A = 0x02
EEPROM_SWITCH_BUTTON_X = 0x03
EEPROM_SWITCH_BUTTON_L = 0x04
EEPROM_SWITCH_BUTTON_R = 0x05
EEPROM_SWITCH_BUTTON_ZL = 0x06
EEPROM_SWITCH_BUTTON_ZR = 0x07
EEPROM_SWITCH_BUTTON_MINUS = 0x08
EEPROM_SWITCH_BUTTON_PLUS = 0x09
EEPROM_SWITCH_BUTTON_LCLICK = 0x0A
EEPROM_SWITCH_BUTTON_RCLICK = 0x0B
EEPROM_SWITCH_BUTTON_HOME = 0x0C
EEPROM_SWITCH_BUTTON_CAPTURE = 0x0D

EEPROM_SWITCH_HAT_TOP = 0x10
EEPROM_SWITCH_HAT_TOP_RIGHT = 0x11
EEPROM_SWITCH_HAT_RIGHT = 0x12
EEPROM_SWITCH_HAT_BOTTOM_RIGHT = 0x13
EEPROM_SWITCH_HAT_BOTTOM = 0x14
EEPROM_SWITCH_HAT_BOTTOM_LEFT = 0x15
EEPROM_SWITCH_HAT_LEFT = 0x16
EEPROM_SWITCH_HAT_TOP_LEFT = 0x17
EEPROM_SWITCH_HAT_CENTER = 0x18

EEPROM_SWITCH_STICK_LX = 0x20
EEPROM_SWITCH_STICK_LY = 0x21
EEPROM_SWITCH_STICK_RX = 0x22
EEPROM_SWITCH_STICK_RY = 0x23

SWITCH_VID = 0x0F0D
SWITCH_PID = 0x0092
SWITCH_MANUFACTURER = "HORI CO.,LTD."
SWITCH_PRODUCT = "POKKEN CONTROLLER"

# MIDI

DEFAULT_MIDI_CHANNEL = 0

MIDI_MIN_VELOCITY = 0x00
MIDI_MAX_VELOCITY = 0xFF
MIDI_STANDARD_VELOCITY = 100
DEFAULT_MIDI_VELOCITY = MIDI_STANDARD_VELOCITY

# headers are shifted left one bit but second byte has them like this so you can |= channel
# https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
MIDI_NOTE_ON = 0x90
MIDI_NOTE_OFF = 0x80
MIDI_POLYPHONIC_AFTERTOUCH = 0xB0
MIDI_CONTROL_CHANGE = 0xB0
MIDI_PROGRAM_CHANGE = 0xC0
MIDI_CHANNEL_AFTERTOUCH = 0xD0
MIDI_PITCH_BEND = 0xE0
MIDI_SYSEX = 0xF0
MIDI_TIME_CODE = 0xF1
MIDI_SONG_POSITION = 0xF2
MIDI_SONG_SELECT = 0xF3
MIDI_TUNE_REQUEST = 0xF6
MIDI_SYSEX_END = 0xF7
MIDI_TIMING_CLOCK = 0xF8
MIDI_START = 0xFA
MIDI_CONTINUE = 0xFB
MIDI_STOP = 0xFC
MIDI_ACTIVE_SENSING = 0xFE
MIDI_SYSTEM_RESET = 0xFF

defaults = [0xFF for i in range(256)]

'''
defaults[ConfigOptions['VERSION_MODEL']] = STEPIO_VERSION_MODEL
defaults[ConfigOptions['VERSION_MAJOR']] = STEPIO_VERSION_MAJOR
defaults[ConfigOptions['VERSION_MINOR']] = STEPIO_VERSION_MINOR
defaults[ConfigOptions['VERSION_REVISION'] = STEPIO_VERSION_REVISION
'''
# versions should be handled in a different way

defaults[ConfigOptions['UPDATE_STATUS']] = UpdateStatus['SUCCESS']
defaults[ConfigOptions['LAST_ERROR']] = RuntimeErrors['NONE']
defaults[ConfigOptions['INPUT_TYPE']] = EEPROM_DEFAULT_VALUE,  # unused
defaults[ConfigOptions['INPUT_MODE']] = InputMode['MUX4067_Dual']

defaults[ConfigOptions['MUX_POLLING_MODE']] = MUXPollingMode['Normal']
defaults[ConfigOptions['SIMPLE_MUX']] = EEPROM_TRUE

defaults[ConfigOptions['OUTPUT_MODE']] = OutputMode['PIUIO']
defaults[ConfigOptions['LIGHTS_MODE']] = LightsMode['Latch32']
defaults[ConfigOptions['LIGHTS_FROM_SENSORS']] = EEPROM_FALSE
defaults[ConfigOptions['EXTRA_LIGHTS_MODE']] = LightsMode['None']
defaults[ConfigOptions['DEBOUNCE_MODE']] = EEPROM_DEFAULT_VALUE,  # not implemented yet

defaults[ConfigOptions['PLAYER']] = DEFAULT_PLAYER
defaults[ConfigOptions['PANEL_COUNT']] = PANELS_PER_PLAYER
defaults[ConfigOptions['P1BUTTON_COUNT']] = PLAYER_1_BUTTONS
defaults[ConfigOptions['P2BUTTON_COUNT']] = PLAYER_2_BUTTONS
defaults[ConfigOptions['OTHERBUTTON_COUNT']] = OTHER_BUTTONS

defaults[ConfigOptions['BLOCKED_INPUTS_0']] = DEFAULT_BLOCKED_INPUTS_0
defaults[ConfigOptions['BLOCKED_INPUTS_1']] = DEFAULT_BLOCKED_INPUTS_1
defaults[ConfigOptions['BLOCKED_INPUTS_2']] = DEFAULT_BLOCKED_INPUTS_2
defaults[ConfigOptions['BLOCKED_INPUTS_3']] = DEFAULT_BLOCKED_INPUTS_3

defaults[ConfigOptions['BLOCKED_INPUTS_MUX0_0']] = DEFAULT_BLOCKED_INPUTS_0
defaults[ConfigOptions['BLOCKED_INPUTS_MUX0_1']] = DEFAULT_BLOCKED_INPUTS_1
defaults[ConfigOptions['BLOCKED_INPUTS_MUX0_2']] = DEFAULT_BLOCKED_INPUTS_2
defaults[ConfigOptions['BLOCKED_INPUTS_MUX0_3']] = DEFAULT_BLOCKED_INPUTS_3

defaults[ConfigOptions['BLOCKED_INPUTS_MUX1_0']] = DEFAULT_BLOCKED_INPUTS_0
defaults[ConfigOptions['BLOCKED_INPUTS_MUX1_1']] = DEFAULT_BLOCKED_INPUTS_1
defaults[ConfigOptions['BLOCKED_INPUTS_MUX1_2']] = DEFAULT_BLOCKED_INPUTS_2
defaults[ConfigOptions['BLOCKED_INPUTS_MUX1_3']] = DEFAULT_BLOCKED_INPUTS_3

defaults[ConfigOptions['BLOCKED_INPUTS_MUX2_0']] = DEFAULT_BLOCKED_INPUTS_0
defaults[ConfigOptions['BLOCKED_INPUTS_MUX2_1']] = DEFAULT_BLOCKED_INPUTS_1
defaults[ConfigOptions['BLOCKED_INPUTS_MUX2_2']] = DEFAULT_BLOCKED_INPUTS_2
defaults[ConfigOptions['BLOCKED_INPUTS_MUX2_3']] = DEFAULT_BLOCKED_INPUTS_3

defaults[ConfigOptions['BLOCKED_INPUTS_MUX3_0']] = DEFAULT_BLOCKED_INPUTS_0
defaults[ConfigOptions['BLOCKED_INPUTS_MUX3_1']] = DEFAULT_BLOCKED_INPUTS_1
defaults[ConfigOptions['BLOCKED_INPUTS_MUX3_2']] = DEFAULT_BLOCKED_INPUTS_2
defaults[ConfigOptions['BLOCKED_INPUTS_MUX3_3']] = DEFAULT_BLOCKED_INPUTS_3

defaults[ConfigOptions['RGB_LED_COUNT']] = DEFAULT_RGB_LED_COUNT
defaults[ConfigOptions['EXTRA_LED_TRIGGER']] = EEPROM_DEFAULT_VALUE

defaults[ConfigOptions['LIGHT_P1_UPLEFT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P1_UPRIGHT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P1_CENTER_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P1_DOWNLEFT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P1_DOWNRIGHT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P2_UPLEFT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P2_UPRIGHT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P2_CENTER_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P2_DOWNLEFT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_P2_DOWNRIGHT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_MARQUEE_1_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_MARQUEE_2_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_MARQUEE_3_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_MARQUEE_4_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_SUB_LEFT_REMAP']] = EEPROM_DEFAULT_VALUE
defaults[ConfigOptions['LIGHT_SUB_RIGHT_REMAP']] = EEPROM_DEFAULT_VALUE

defaults[ConfigOptions['P1_UPLEFT_REMAP']] = InputPacket['P1_UPLEFT']
defaults[ConfigOptions['P1_UPRIGHT_REMAP']] = InputPacket['P1_UPRIGHT']
defaults[ConfigOptions['P1_CENTER_REMAP']] = InputPacket['P1_CENTER']
defaults[ConfigOptions['P1_DOWNLEFT_REMAP']] = InputPacket['P1_DOWNLEFT']
defaults[ConfigOptions['P1_DOWNRIGHT_REMAP']] = InputPacket['P1_DOWNRIGHT']
defaults[ConfigOptions['P2_UPLEFT_REMAP']] = InputPacket['P2_UPLEFT']
defaults[ConfigOptions['P2_UPRIGHT_REMAP']] = InputPacket['P2_UPRIGHT']
defaults[ConfigOptions['P2_CENTER_REMAP']] = InputPacket['P2_CENTER']
defaults[ConfigOptions['P2_DOWNLEFT_REMAP']] = InputPacket['P2_DOWNLEFT']
defaults[ConfigOptions['P2_DOWNRIGHT_REMAP']] = InputPacket['P2_DOWNRIGHT']
defaults[ConfigOptions['P1_COIN_REMAP']] = InputPacket['P1_COIN']
defaults[ConfigOptions['P2_COIN_REMAP']] = InputPacket['P2_COIN']
defaults[ConfigOptions['TEST_BUTTON_REMAP']] = InputPacket['TEST_BUTTON']
defaults[ConfigOptions['SERVICE_BUTTON_REMAP']] = InputPacket['SERVICE_BUTTON']
defaults[ConfigOptions['CLEAR_BUTTON_REMAP']] = InputPacket['CLEAR_BUTTON']

# thanks @willwade
KeyboardKeycode = {"KEY_MOD_LCTRL": 0x01,"KEY_MOD_LSHIFT": 0x02,"KEY_MOD_LALT": 0x04,"KEY_MOD_LMETA": 0x08,"KEY_MOD_RCTRL": 0x10,"KEY_MOD_RSHIFT": 0x20,"KEY_MOD_RALT": 0x40,"KEY_MOD_RMETA": 0x80,"KEY_NONE": 0x00,"KEY_ERR_OVF": 0x01,"KEY_A": 0x04,"KEY_B": 0x05,"KEY_C": 0x06,"KEY_D": 0x07,"KEY_E": 0x08,"KEY_F": 0x09,"KEY_G": 0x0a,"KEY_H": 0x0b,"KEY_I": 0x0c,"KEY_J": 0x0d,"KEY_K": 0x0e,"KEY_L": 0x0f,"KEY_M": 0x10,"KEY_N": 0x11,"KEY_O": 0x12,"KEY_P": 0x13,"KEY_Q": 0x14,"KEY_R": 0x15,"KEY_S": 0x16,"KEY_T": 0x17,"KEY_U": 0x18,"KEY_V": 0x19,"KEY_W": 0x1a,"KEY_X": 0x1b,"KEY_Y": 0x1c,"KEY_Z": 0x1d,"KEY_1": 0x1e,"KEY_2": 0x1f,"KEY_3": 0x20,"KEY_4": 0x21,"KEY_5": 0x22,"KEY_6": 0x23,"KEY_7": 0x24,"KEY_8": 0x25,"KEY_9": 0x26,"KEY_0": 0x27,"KEY_ENTER": 0x28,"KEY_ESC": 0x29,"KEY_BACKSPACE": 0x2a,"KEY_TAB": 0x2b,"KEY_SPACE": 0x2c,"KEY_MINUS": 0x2d,"KEY_EQUAL": 0x2e,"KEY_LEFTBRACE": 0x2f,"KEY_RIGHTBRACE": 0x30,"KEY_BACKSLASH": 0x31,"KEY_HASHTILDE": 0x32,"KEY_SEMICOLON": 0x33,"KEY_APOSTROPHE": 0x34,"KEY_GRAVE": 0x35,"KEY_COMMA": 0x36,"KEY_DOT": 0x37,"KEY_SLASH": 0x38,"KEY_CAPSLOCK": 0x39,"KEY_F1": 0x3a,"KEY_F2": 0x3b,"KEY_F3": 0x3c,"KEY_F4": 0x3d,"KEY_F5": 0x3e,"KEY_F6": 0x3f,"KEY_F7": 0x40,"KEY_F8": 0x41,"KEY_F9": 0x42,"KEY_F10": 0x43,"KEY_F11": 0x44,"KEY_F12": 0x45,"KEY_SYSRQ": 0x46,"KEY_SCROLL_LOCK": 0x47,"KEY_PAUSE": 0x48,"KEY_INSERT": 0x49,"KEY_HOME": 0x4a,"KEY_PAGEUP": 0x4b,"KEY_DELETE": 0x4c,"KEY_END": 0x4d,"KEY_PAGEDOWN": 0x4e,"KEY_RIGHT": 0x4f,"KEY_LEFT": 0x50,"KEY_DOWN": 0x51,"KEY_UP": 0x52,"KEY_NUMLOCK": 0x53,"KEYPAD_SLASH": 0x54,"KEYPAD_ASTERISK": 0x55,"KEYPAD_MINUS": 0x56,"KEYPAD_PLUS": 0x57,"KEYPAD_ENTER": 0x58,"KEYPAD_1": 0x59,"KEYPAD_2": 0x5a,"KEYPAD_3": 0x5b,"KEYPAD_4": 0x5c,"KEYPAD_5": 0x5d,"KEYPAD_6": 0x5e,"KEYPAD_7": 0x5f,"KEYPAD_8": 0x60,"KEYPAD_9": 0x61,"KEYPAD_0": 0x62,"KEYPAD_DOT": 0x63,"KEY_102ND": 0x64,"KEY_COMPOSE": 0x65,"KEY_POWER": 0x66,"KEYPAD_EQUAL": 0x67,"KEY_F13": 0x68,"KEY_F14": 0x69,"KEY_F15": 0x6a,"KEY_F16": 0x6b,"KEY_F17": 0x6c,"KEY_F18": 0x6d,"KEY_F19": 0x6e,"KEY_F20": 0x6f,"KEY_F21": 0x70,"KEY_F22": 0x71,"KEY_F23": 0x72,"KEY_F24": 0x73,"KEY_OPEN": 0x74,"KEY_HELP": 0x75,"KEY_PROPS": 0x76,"KEY_FRONT": 0x77,"KEY_STOP": 0x78,"KEY_AGAIN": 0x79,"KEY_UNDO": 0x7a,"KEY_CUT": 0x7b,"KEY_COPY": 0x7c,"KEY_PASTE": 0x7d,"KEY_FIND": 0x7e,"KEY_MUTE": 0x7f,"KEY_VOLUMEUP": 0x80,"KEY_VOLUMEDOWN": 0x81,"KEYPAD_COMMA": 0x85,"KEY_RO": 0x87,"KEY_KATAKANAHIRAGANA": 0x88,"KEY_YEN": 0x89,"KEY_HENKAN": 0x8a,"KEY_MUHENKAN": 0x8b,"KEYPAD_JPCOMMA": 0x8c,"KEY_HANGEUL": 0x90,"KEY_HANJA": 0x91,"KEY_KATAKANA": 0x92,"KEY_HIRAGANA": 0x93,"KEY_ZENKAKUHANKAKU": 0x94,"KEYPAD_LEFTPAREN": 0xb6,"KEYPAD_RIGHTPAREN": 0xb7,"KEY_LEFTCTRL": 0xe0,"KEY_LEFTSHIFT": 0xe1,"KEY_LEFTALT": 0xe2,"KEY_LEFTWINDOWS": 0xe3,"KEY_RIGHTCTRL": 0xe4,"KEY_RIGHTSHIFT": 0xe5,"KEY_RIGHTALT": 0xe6,"KEY_RIGHTMETA": 0xe7,"KEY_MEDIA_PLAYPAUSE": 0xe8,"KEY_MEDIA_STOPCD": 0xe9,"KEY_MEDIA_PREVIOUSSONG": 0xea,"KEY_MEDIA_NEXTSONG": 0xeb,"KEY_MEDIA_EJECTCD": 0xec,"KEY_MEDIA_VOLUMEUP": 0xed,"KEY_MEDIA_VOLUMEDOWN": 0xee,"KEY_MEDIA_MUTE": 0xef,"KEY_MEDIA_WWW": 0xf0,"KEY_MEDIA_BACK": 0xf1,"KEY_MEDIA_FORWARD": 0xf2,"KEY_MEDIA_STOP": 0xf3,"KEY_MEDIA_FIND": 0xf4,"KEY_MEDIA_SCROLLUP": 0xf5,"KEY_MEDIA_SCROLLDOWN": 0xf6,"KEY_MEDIA_EDIT": 0xf7,"KEY_MEDIA_SLEEP": 0xf8,"KEY_MEDIA_COFFEE": 0xf9,"KEY_MEDIA_REFRESH": 0xfa,"KEY_MEDIA_CALC": 0xfb}

# keycodes from HID library
defaults[ConfigOptions['P1_UPLEFT_KEYCODE']] = KeyboardKeycode['KEY_Q']
defaults[ConfigOptions['P1_UPRIGHT_KEYCODE']] = KeyboardKeycode['KEY_E']
defaults[ConfigOptions['P1_CENTER_KEYCODE']] = KeyboardKeycode['KEY_S']
defaults[ConfigOptions['P1_DOWNLEFT_KEYCODE']] = KeyboardKeycode['KEY_Z']
defaults[ConfigOptions['P1_DOWNRIGHT_KEYCODE']] = KeyboardKeycode['KEY_C']
defaults[ConfigOptions['P2_UPLEFT_KEYCODE']] = KeyboardKeycode['KEYPAD_7']
defaults[ConfigOptions['P2_UPRIGHT_KEYCODE']] = KeyboardKeycode['KEYPAD_9']
defaults[ConfigOptions['P2_CENTER_KEYCODE']] = KeyboardKeycode['KEYPAD_5']
defaults[ConfigOptions['P2_DOWNLEFT_KEYCODE']] = KeyboardKeycode['KEYPAD_1']
defaults[ConfigOptions['P2_DOWNRIGHT_KEYCODE']] = KeyboardKeycode['KEYPAD_3']
defaults[ConfigOptions['P1_COIN_KEYCODE']] = KeyboardKeycode['KEY_F1']
defaults[ConfigOptions['P2_COIN_KEYCODE']] = KeyboardKeycode['KEY_F1']
defaults[ConfigOptions['TEST_BUTTON_KEYCODE']] = KeyboardKeycode['KEY_SCROLL_LOCK']
defaults[ConfigOptions['SERVICE_BUTTON_KEYCODE']] = KeyboardKeycode['KEY_ENTER']
defaults[ConfigOptions['CLEAR_BUTTON_KEYCODE']] = KeyboardKeycode['KEY_ESC']

# these are gamepad button numbers, there are 32 buttons total (0-31)
defaults[ConfigOptions['P1_UPLEFT_GAMEPAD']] = 0
defaults[ConfigOptions['P1_UPRIGHT_GAMEPAD']] = 1
defaults[ConfigOptions['P1_CENTER_GAMEPAD']] = 2
defaults[ConfigOptions['P1_DOWNLEFT_GAMEPAD']] = 3
defaults[ConfigOptions['P1_DOWNRIGHT_GAMEPAD']] = 4
defaults[ConfigOptions['P2_UPLEFT_GAMEPAD']] = 5
defaults[ConfigOptions['P2_UPRIGHT_GAMEPAD']] = 6
defaults[ConfigOptions['P2_CENTER_GAMEPAD']] = 7
defaults[ConfigOptions['P2_DOWNLEFT_GAMEPAD']] = 8
defaults[ConfigOptions['P2_DOWNRIGHT_GAMEPAD']] = 9
defaults[ConfigOptions['P1_COIN_GAMEPAD']] = 10
defaults[ConfigOptions['P2_COIN_GAMEPAD']] = 11
defaults[ConfigOptions['TEST_BUTTON_GAMEPAD']] = 12
defaults[ConfigOptions['SERVICE_BUTTON_GAMEPAD']] = 13
defaults[ConfigOptions['CLEAR_BUTTON_GAMEPAD']] = 14

# there are 14 buttons, 9 hat directions, also two sticks analog X and Y
defaults[ConfigOptions['P1_UPLEFT_SWITCH']] = EEPROM_SWITCH_HAT_TOP
defaults[ConfigOptions['P1_UPRIGHT_SWITCH']] = EEPROM_SWITCH_HAT_RIGHT
defaults[ConfigOptions['P1_CENTER_SWITCH']] = EEPROM_SWITCH_HAT_LEFT
defaults[ConfigOptions['P1_DOWNLEFT_SWITCH']] = EEPROM_SWITCH_HAT_BOTTOM
defaults[ConfigOptions['P1_DOWNRIGHT_SWITCH']] = EEPROM_SWITCH_BUTTON_L
defaults[ConfigOptions['P2_UPLEFT_SWITCH']] = EEPROM_SWITCH_BUTTON_A
defaults[ConfigOptions['P2_UPRIGHT_SWITCH']] = EEPROM_SWITCH_BUTTON_B
defaults[ConfigOptions['P2_CENTER_SWITCH']] = EEPROM_SWITCH_BUTTON_X
defaults[ConfigOptions['P2_DOWNLEFT_SWITCH']] = EEPROM_SWITCH_BUTTON_Y
defaults[ConfigOptions['P2_DOWNRIGHT_SWITCH']] = EEPROM_SWITCH_BUTTON_R
defaults[ConfigOptions['P1_COIN_SWITCH']] = EEPROM_SWITCH_BUTTON_MINUS
defaults[ConfigOptions['P2_COIN_SWITCH']] = EEPROM_SWITCH_BUTTON_PLUS
defaults[ConfigOptions['TEST_BUTTON_SWITCH']] = EEPROM_SWITCH_BUTTON_ZL
defaults[ConfigOptions['SERVICE_BUTTON_SWITCH']] = EEPROM_SWITCH_BUTTON_ZR
defaults[ConfigOptions['CLEAR_BUTTON_SWITCH']] = EEPROM_SWITCH_BUTTON_CAPTURE

defaults[ConfigOptions['MIDI_ANALOG']] = EEPROM_TRUE
defaults[ConfigOptions['MIDI_ANALOG_MIN']] = MIDI_MIN_VELOCITY
defaults[ConfigOptions['MIDI_ANALOG_MAX']] = MIDI_MAX_VELOCITY
defaults[ConfigOptions['MIDI_CHANNEL']] = DEFAULT_MIDI_CHANNEL

defaults[ConfigOptions['MIDI_USE_FIRST_BYTE']] = EEPROM_FALSE

defaults[ConfigOptions['P1_UPLEFT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P1_UPLEFT_MIDI1']] = 60  # C5
defaults[ConfigOptions['P1_UPLEFT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P1_UPLEFT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P1_UPRIGHT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P1_UPRIGHT_MIDI1']] = 61
defaults[ConfigOptions['P1_UPRIGHT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P1_UPRIGHT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P1_CENTER_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P1_CENTER_MIDI1']] = 62
defaults[ConfigOptions['P1_CENTER_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P1_CENTER_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P1_DOWNLEFT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P1_DOWNLEFT_MIDI1']] = 63
defaults[ConfigOptions['P1_DOWNLEFT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P1_DOWNLEFT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P1_DOWNRIGHT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P1_DOWNRIGHT_MIDI1']] = 64
defaults[ConfigOptions['P1_DOWNRIGHT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P1_DOWNRIGHT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P2_UPLEFT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P2_UPLEFT_MIDI1']] = 65
defaults[ConfigOptions['P2_UPLEFT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P2_UPLEFT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P2_UPRIGHT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P2_UPRIGHT_MIDI1']] = 66
defaults[ConfigOptions['P2_UPRIGHT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P2_UPRIGHT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P2_CENTER_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P2_CENTER_MIDI1']] = 67
defaults[ConfigOptions['P2_CENTER_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P2_CENTER_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P2_DOWNLEFT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P2_DOWNLEFT_MIDI1']] = 68
defaults[ConfigOptions['P2_DOWNLEFT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P2_DOWNLEFT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P2_DOWNRIGHT_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P2_DOWNRIGHT_MIDI1']] = 69
defaults[ConfigOptions['P2_DOWNRIGHT_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P2_DOWNRIGHT_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P1_COIN_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P1_COIN_MIDI1']] = 70
defaults[ConfigOptions['P1_COIN_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P1_COIN_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['P2_COIN_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['P2_COIN_MIDI1']] = 71
defaults[ConfigOptions['P2_COIN_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['P2_COIN_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['TEST_BUTTON_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['TEST_BUTTON_MIDI1']] = 72
defaults[ConfigOptions['TEST_BUTTON_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['TEST_BUTTON_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['SERVICE_BUTTON_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['SERVICE_BUTTON_MIDI1']] = 73
defaults[ConfigOptions['SERVICE_BUTTON_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['SERVICE_BUTTON_CHANNEL']] = DEFAULT_MIDI_CHANNEL
defaults[ConfigOptions['CLEAR_BUTTON_MIDI0']] = MIDI_NOTE_ON
defaults[ConfigOptions['CLEAR_BUTTON_MIDI1']] = 74
defaults[ConfigOptions['CLEAR_BUTTON_MIDI2']] = MIDI_STANDARD_VELOCITY
defaults[ConfigOptions['CLEAR_BUTTON_CHANNEL']] = DEFAULT_MIDI_CHANNEL

defaults[ConfigOptions['P1_UPLEFT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P1_UPRIGHT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P1_CENTER_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P1_DOWNLEFT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P1_DOWNRIGHT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P2_UPLEFT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P2_UPRIGHT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P2_CENTER_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P2_DOWNLEFT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P2_DOWNRIGHT_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P1_COIN_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['P2_COIN_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['TEST_BUTTON_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['SERVICE_BUTTON_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['CLEAR_BUTTON_ANALOG']] = DEFAULT_ANALOG_VALUE
defaults[ConfigOptions['EXTRA_BUTTON_ANALOG']] = DEFAULT_ANALOG_VALUE

# configuration-tool-specific constants

# for a 16 MHz 32u4 like brokeIO, 76800 is stable but 115200 is less, 250000 and its multiples are perfect, 230400 is really bad
BAUD_LIST = [300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76800, 115200, 230400, 250000, 500000, 1000000]
BAUD_LIST_STR = [str(x) for x in BAUD_LIST]
DEFAULT_BAUD = 115200  # consider 76800 as the default or even 250000 if it doesn't make the rest of the code suffer
DEFAULT_BAUD_INDEX = BAUD_LIST.index(DEFAULT_BAUD)