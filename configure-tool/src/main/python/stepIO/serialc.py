from stepIO.constants import *
import serial
import struct
import cobs

if DEBUG_MODE:
    import traceback


class SerialC:
    def __init__(self, com=None, baud=DEFAULT_BAUD, config=None):
        self.ser = serial.Serial(com, baudrate=baud)
        self.q = {}  # values should either be None or key should not exist if no pending command (.get() will return None)
        if config == None:
            self.config = [None for i in range(len(ConfigOptions))]

        self.map = {
            'STATUS': self.handleStatus,
            'SENSOR': self.handleSensor,
            'SENSOR_ANALOG': self.handleSensorAnalog,
            'CONFIG': self.handleConfig,
        }

        self.sensors = [
            [0, 0, 0, 0] for i in range(len(InputPacket))
        ]
        self.mux = [0, 0]

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
            pck = ConfigPacket(resp)
            self.config = pck.config.copy()
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()

    def handleSensor(self, resp):
        try:
            pck = SensorPacket(resp)
            for i in range(len(pck.sensors)):
                if self.config['MUX_SIMPLE'] != EEPROM_FALSE:
                    self.sensors[i][self.mux[0]] = int(pck.sensors[i])
                else:
                    if 'P2' in InputPacketStr[i]:
                        self.sensors[i][self.mux[1]] = int(pck.sensors[i])
                    else:
                        self.sensors[i][self.mux[0]] = int(pck.sensors[i])
        except Exception:
            if DEBUG_MODE:
                traceback.print_exc()

    def handleSensorAnalog(self, resp):
        try:
            pck = SensorAnalogPacket(resp)
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
            
    def sendPacket(self, pck):
        self.q[pck.header] = pck
        buf = pck.toBinary()
        self.ser.write(cobs.encode(buf))