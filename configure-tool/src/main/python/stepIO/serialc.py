from stepIO.constants import *
import serial

class SerialC:
    def __init__(self, com=None, baud=DEFAULT_BAUD):
        this.ser = serial.Serial(com)
