import random
import time

class DataSynthGenerator:
    def __init__(self):
        self.msg_n = 0

    @staticmethod
    def get_random_float() -> float:
        return random.random() * 10000

    @staticmethod
    def get_timestamp() -> float:
        return time.time()

    def get_simulated_record(self) -> dict:
        record = {
            "n": self.msg_n,
            "ts": self.get_timestamp(),
            "val1": self.get_random_float(),
            "val2": self.get_random_float(),
        }
        self.msg_n += 1
        return record

def get_devices() -> dict:
    with open("connection_params.txt", "r") as connection_params:
        connection_params_data = connection_params.read().split("\n")
    pts = {}
    for pts_data in connection_params_data:
        if pts_data:
            pts_name, pts_n = pts_data.split("=")
            pts[pts_name] = pts_n

    return pts
