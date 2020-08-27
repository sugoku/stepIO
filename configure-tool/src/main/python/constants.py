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
    'CLEAR_BUTTON_CHANNEL'
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
InputPacketDisplay = {s[1]: s[0] for s in _InputPacket}

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
PIUIO_InputPacket = {k: i for i, k in enumerate([
    'NC_0',
    'P2_TEST',
    'P2_COIN',
    'NC_3',
    'NC_4',
    'NC_5',
    'P2_SERVICE',
    'P2_CLEAR',
    'P2_UPLEFT',
    'P2_UPRIGHT',
    'P2_CENTER',
    'P2_DOWNLEFT',
    'P2_DOWNRIGHT',
    'NC_13',
    'NC_14',
    'NC_15',
    'NC_16',
    'P1_TEST',
    'P1_COIN',
    'NC_19',
    'NC_20',
    'NC_21',
    'P1_SERVICE',
    'P1_CLEAR',
    'P1_UPLEFT',
    'P1_UPRIGHT',
    'P1_CENTER',
    'P1_DOWNLEFT',
    'P1_DOWNRIGHT',
    'NC_29',
    'NC_30',
    'NC_31'
])}
PIUIO_LightsPacket = {k: i for i, k in enumerate([
    'MARQUEE_3',
    'MARQUEE_2',
    'MARQUEE_1',
    'NC_3',
    'NC_4',
    'NC_5',
    'NC_6',
    'NC_7',
    'P2_MUXER_0',
    'P2_MUXER_1',
    'P2_UPLEFT',
    'P2_UPRIGHT',
    'P2_CENTER',
    'P2_DOWNLEFT',
    'P2_DOWNRIGHT',
    'MARQUEE_4',
    'NC_16',
    'NC_17',
    'SUB_NEON',
    'NC_19',
    'NC_20',
    'NC_21',
    'NC_22',
    'NC_23',
    'P1_MUXER_0',
    'P1_MUXER_1',
    'P1_UPLEFT',
    'P1_UPRIGHT',
    'P1_CENTER',
    'P1_DOWNLEFT',
    'P1_DOWNRIGHT',
    'NC_31'
])}

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

# configuration-tool-specific constants

# for a 16 MHz 32u4 like brokeIO, 76800 is stable but 115200 is less, 250000 and its multiples are perfect, 230400 is really bad
BAUD_LIST = [300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76800, 115200, 230400, 250000, 500000, 1000000]
BAUD_LIST_STR = [str(x) for x in BAUD_LIST]
DEFAULT_BAUD = 115200  # consider 76800 as the default or even 250000 if it doesn't make the rest of the code suffer
DEFAULT_BAUD_INDEX = BAUD_LIST.index(DEFAULT_BAUD)