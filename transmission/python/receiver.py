import serial
import struct
from unit import Unit

class Receiver(Unit):
    def __init__(self):
        super().__init__()
        self._receiver_device = self.devices["PTY_R"]
        self.serial = serial.Serial(self._receiver_device)
        print(f"Receiver device: {self._receiver_device}")

    def _find_header(self):
        header_part = b""
        while True:
            header_part += self.serial.read(1)
            if len(header_part) > self.len_header:
                header_part = header_part[-self.len_header:]
            if header_part == self.msg_header:
                break

    @staticmethod
    def _process_data(data_received: list) -> dict:
        record = {
            "n": data_received[0],
            "ts": data_received[1],
            "val1": data_received[2],
            "val2": data_received[3],
        }
        return record

    def get_next_msg(self):
        self._find_header()
        payload = self.serial.read(self.payload_size)
        while len(payload) < self.payload_size:
            payload += self.serial.read(1)
        try:
            data_received = struct.unpack(self.msg_format, payload)
            data_processed = self._process_data(data_received)
        except Exception as exception:
            print(f"Msg lost, cannot be unpacked: {exception}")
            data_processed = None
        return data_processed

def start_receiving_transmission():
    receiver = Receiver()
    n_first_package = None
    n_last_package = None
    n_received_packages = 0
    try:
        while True:
            data = receiver.get_next_msg()
            if not data:
                continue
            n_received_packages += 1
            if not n_first_package:
                n_first_package = data["n"]
            n_last_package = data["n"]
            print(data)
    except KeyboardInterrupt:
        packs_sent = n_last_package - n_first_package + 1
        success_rate = n_received_packages / packs_sent
        stats = f"First package received: {n_first_package}, last: {n_last_package}\n"
        stats += f"N received: {n_received_packages}, n sent {packs_sent}.\n"
        stats += f"Success rate: {success_rate:.1%}"
        print("Receiver is interrupted")
        print(stats)
    finally:
        receiver.close()
        print("Receiver serial is closed")

if __name__ == "__main__":
    start_receiving_transmission()
