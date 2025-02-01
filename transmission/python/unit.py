import struct
from abc import ABC
from utils import get_devices

class Unit(ABC):
    msg_header = b"\x55\xAA"
    msg_format = "<Idff" # integer, double precision float, float, float

    def __init__(self):
        self.devices = get_devices()
        self.len_header = len(self.msg_header)
        self.payload_size = struct.calcsize(self.msg_format)
        self.serial = None
        print(f"Devices: {self.devices}")
        print(f"Payload size: {self.payload_size} bytes")
        print(f"Header size: {self.len_header} bytes")

    def close(self):
        if self.serial and self.serial.is_open:
            self.serial.close()

