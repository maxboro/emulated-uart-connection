import argparse
import struct
import serial
import time
from utils import DataSynthGenerator
from unit import Unit

class Transmitter(Unit):

    def __init__(self):
        super().__init__()
        self._transmitter_device = self.devices["PTY_T"]
        self.serial = serial.Serial(self._transmitter_device)
        print(f"Transmitter device: {self._transmitter_device}")

    def _compose_msg(self, data: dict):
        payload_bytes = struct.pack(self.msg_format, data["n"], data["ts"],  data["val1"], data["val2"])
        composed_msg = self.msg_header + payload_bytes
        return composed_msg

    def send(self, data: dict):
        composed_msg = self._compose_msg(data)
        self.serial.write(composed_msg)

def start_simulated_transmission(args: argparse.Namespace):
    print(f"Transmission started at {args.rate_hz} Hz rate")
    interval_s = 1 / args.rate_hz
    last_n_send = None
    ts_start = None
    ts_last = None

    synt_data_gen = DataSynthGenerator()
    transmitter = Transmitter()
    try:
        while True:
            data = synt_data_gen.get_simulated_record()
            print(data)
            transmitter.send(data)
            if not ts_start:
                ts_start = data["ts"]
            ts_last = data["ts"]
            last_n_send = data["n"]
            time.sleep(interval_s)
    except KeyboardInterrupt:
        session_duration = ts_last - ts_start
        actual_updates_per_sec = (last_n_send + 1) / session_duration
        stats = f"N sent: {last_n_send + 1}. Session duration: {session_duration:.1f}s\n"
        stats += f"Actual rate: {actual_updates_per_sec:.1f} Hz"
        print("Transmitter is interrupted")
        print(stats)
    finally:
        transmitter.close()
        print("Transmitter serial is closed")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog='Transmitter',
    )
    parser.add_argument(
        '--rate-hz', 
        default=10,
        type=int,
        help = 'Rate of transmission in Hz'
    )
    args = parser.parse_args()
    start_simulated_transmission(args)
