'''
    # stepIO Configuration Tool

    stage controller with
    emulation of PIUIO
    by BedrockSolid (@sugoku)

    SPDX-License-Identifier: GPL-3.0-or-later
    https://github.com/sugoku/stepIO
'''


from stepIO.constants import *
import serial
import struct
import cobs
import traceback


## host -> device packets

class ChangeInputModePacket:
    command = SerialCommands['CHANGE_INPUT_MODE']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack('BB', self.command, self.mode)

class ChangeOutputModePacket:
    command = SerialCommands['CHANGE_OUTPUT_MODE']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack('BB', self.command, self.mode)

class ChangeLightsModePacket:
    command = SerialCommands['CHANGE_LIGHTS_MODE']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack('BB', self.command, self.mode)

class LightsFromSensorsPacket:
    command = SerialCommands['LIGHTS_FROM_SENSORS']

    def __init__(self, state):
        self.state = state

    def toBytes(self):
        return struct.pack('BB', self.command, self.state)

class ChangeExtraLightsModePacket:
    command = SerialCommands['CHANGE_EXTRA_LIGHTS_MODE']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack('BB', self.command, self.mode)

class ChangeMuxPollingModePacket:
    command = SerialCommands['CHANGE_MUX_POLLING_MODE']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack('BB', self.command, self.mode)

class ChangeDebounceModePacket:
    command = SerialCommands['CHANGE_DEBOUNCE_MODE']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack('BB', self.command, self.mode)

class SetExtraLEDPacket:
    command = SerialCommands['SET_EXTRA_LED']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack()

class EditInputPacket:
    command = SerialCommands['EDIT_INPUT']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack()

class AnalogThresholdPacket:
    command = SerialCommands['ANALOG_THRESHOLD']

    def __init__(self, sensor, threshold):
        self.sensor = sensor
        self.threshold = threshold

    def toBytes(self):
        return struct.pack('BB<H', self.command, self.sensor, self.threshold)

class SaveToEEPROMPacket:  # 0 args
    command = SerialCommands['SAVE_TO_EEPROM']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class LoadFromEEPROMPacket:  # 0 args
    command = SerialCommands['LOAD_FROM_EEPROM']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class GetConfigPacket:  # 0 args
    command = SerialCommands['GET_CONFIG']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class SetConfigPacket:
    command = SerialCommands['SET_CONFIG']

    def __init__(self, config):
        self.config = config

    def toBytes(self):
        return struct.pack('Bs', self.command, bytearray(self.config))

class SendInputPacket:
    command = SerialCommands['SEND_INPUT']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack()

class SendInputAnalogPacket:
    command = SerialCommands['SEND_INPUT_ANALOG']

    def __init__(self, mode):
        self.mode = mode

    def toBytes(self):
        return struct.pack()

class GetLightsMuxPacket:  # 0 args
    command = SerialCommands['GET_LIGHTSMUX']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class SendLightsMuxPacket:
    command = SerialCommands['SEND_LIGHTSMUX']

    def __init__(self, lightsmux):
        self.lightsmux = lightsmux

    def toBytes(self):
        return struct.pack('B<L', self.command, self.lightsmux)

class ChangeBaudPacket:
    command = SerialCommands['CHANGE_BAUD']

    def __init__(self, baud):
        self.baud = baud

    def toBytes(self):
        return struct.pack('B<H', self.command, self.lightsmux)

class ResetPacket:  # 0 args
    command = SerialCommands['RESET']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class StatusGetPacket:  # 0 args
    command = SerialCommands['STATUS_GET']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class SetFactoryDefaultsPacket:  # 0 args
    command = SerialCommands['SET_FACTORY_DEFAULTS']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)

class GetDeviceInfoPacket:  # 0 args
    command = SerialCommands['GET_DEVICE_INFO']

    def __init__(self):
        pass

    def toBytes(self):
        return struct.pack('B', self.command)


## device -> host packets (which means there is no need to create these packets from the host)
# resp (the response) is the entire response
class ConfigPacket:
    msgtype = SerialMessageTypes['CONFIG']
    requestcmd = SerialCommands['GET_CONFIG']

    def __init__(self, resp):
        if resp[0] != self.msgtype:  # header must match
            raise
        self.requestcmd = resp[1]
        self.config = resp[2:]

class SensorPacket:
    msgtype = SerialMessageTypes['SENSOR']
    requestcmd = 0xFF

    def __init__(self, resp):
        if resp[0] != self.msgtype:  # header must match
            raise
        self.requestcmd = resp[1]
        self.sensorsraw = int.from_bytes(resp[2:], 'big')
        self.sensors = [255*(self.sensorsraw >> i & 1) for i in range(15, -1, -1)]  # 15 to 0 inclusive

class SensorAnalogPacket:
    msgtype = SerialMessageTypes['SENSOR_ANALOG']
    requestcmd = 0xFF

    def __init__(self, resp):
        if resp[0] != self.msgtype:  # header must match
            raise
        self.requestcmd = resp[1]
        self.sensors = [x for x in resp[2:]]  # convert to integers

class StatusPacket:
    msgtype = SerialMessageTypes['STATUS']
    requestcmd = None

    def __init__(self, resp):
        if resp[0] != self.msgtype:  # header must match
            raise
        self.requestcmd = resp[1]
        self.status = resp[2]

class LightsPacket:
    msgtype = SerialMessageTypes['LIGHTS']
    requestcmd = SerialCommands['GET_LIGHTSMUX']

    def __init__(self, resp):
        if resp[0] != self.msgtype:  # header must match
            raise
        self.requestcmd = resp[1]
        self.lightsraw = int.from_bytes(resp[2:], 'little')
        self.lights = [255*(self.sensorsraw >> i & 1) for i in range(31, -1, -1)]  # 31 to 0 inclusive

class DeviceInfoPacket:
    msgtype = SerialMessageTypes['DEVICE_INFO']
    requestcmd = SerialCommands['GET_DEVICE_INFO']

    def __init__(self, resp):
        if resp[0] != self.msgtype:  # header must match
            raise
        self.requestcmd = resp[1]
        self.info = resp[2:].decode('ascii')

## serial processor class
class SerialC:
    def __init__(self, com=None, baud=DEFAULT_BAUD, config=None):
        self.ser = serial.Serial(com, baudrate=baud)
        self.q = {}  # values should either be None or key should not exist if no pending command (.get() will return None)
        if config == None:
            self.config = [None for i in range(len(ConfigOptions))]

        self.map = {
            'STATUS': self.handleStatus,
            'SENSOR': self.handleSensor,
            'SENSOR_ANALOG': self.handleSensor,
            'CONFIG': self.handleConfig,
            'LIGHTS': self.handleLights,
            'DEVICE_INFO': self.handleDeviceInfo,
        }

        self.sensors = [
            [0, 0, 0, 0] for i in range(len(InputPacket))
        ]
        self.mux = [0, 0]
        self.lights = [0 for i in range(len(LightsPacket))]

    def SendConfigRequest(self):
        self.sendPacket()

    def loop(self):
        b = self.ser.inWaiting()
        if b > 0:
            buf = self.ser.read_until(b'\x00')
            if len(buf) > 0:
                resp = cobs.decode(buf[:-1])
                self.handlePacket(resp)

    def handlePacket(self, resp):
        if len(resp) < 1:
            return
        header = resp[0]
        cmd = SerialCommandsStr.get(header)  # get command name
        f = self.map.get(cmd)  # get function attached to said command
        if f is not None:
            f(resp)

    def handleConfig(self, resp):
        try:
            cfgpck = ConfigPacket(resp)
            self.config = cfgpck.config.copy()
            pck = self.q.get(cfgpck.requestcmd)
            if pck is not None:
                q[cfgpck.requestcmd] = None
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()

    def handleSensor(self, resp):
        try:
            # it should be SENSOR or SENSOR_ANALOG, will raise error in constructor if neither
            pck = SensorPacket(resp) if resp[0] == SerialMessageTypes['SENSOR'] else SensorAnalogPacket(resp)
            for i in range(len(pck.sensors)):
                if self.config['MUX_SIMPLE'] != EEPROM_FALSE:
                    self.sensors[i][self.mux[0]] = pck.sensors[i]
                else:
                    if 'P2' in InputPacketStr[i]:
                        self.sensors[i][self.mux[1]] = pck.sensors[i]
                    else:
                        self.sensors[i][self.mux[0]] = pck.sensors[i]
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()

    def handleStatus(self, resp):
        try:
            stpck = StatusPacket(resp)
            pck = self.q.get(stpck.command)
            if pck is not None:
                if stpck.status == SerialMessages['SUCCESS']:
                    q[stpck.command] = None
                pck.status = stpck.status
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()

    def handleLights(self, resp):
        try:
            ltpck = LightsPacket(resp)
            self.lights = ltpck.lights.copy()
            pck = self.q.get(ltpck.requestcmd)
            if pck is not None:
                q[ltpck.requestcmd] = None
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()

    def handleDeviceInfo(self, resp):
        try:
            dipck = DeviceInfoPacket(resp)
            self.info = dipck.info
            pck = self.q.get(dipck.requestcmd)
            if pck is not None:
                q[dipck.requestcmd] = None
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()
            
    def sendPacket(self, pck):
        self.q[pck.header] = pck
        buf = pck.toBytes()
        self.ser.write(cobs.encode(buf))