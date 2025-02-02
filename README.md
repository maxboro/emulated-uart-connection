# Description
Device connection and data transmission via UART – a simple example. 
UART is emulated using socat. 

For Linux-based systems.

# How to run

### Create connection
To start connection run:
```bash
bash ./scripts/create_connection.sh
```
when connection no longer needed: Ctrl+C

## Communication simulation
### Python version
Start transmission:
```bash
 python ./transmission/python/transmitter.py --rate-hz=10
```

Start receiver in another terminal:
```bash
 python ./transmission/python/receiver.py
```

### C version (currently just a minimal example)
Compile code:
```bash
 cd ./transmission/c/
 gcc transmitter.c -o transmitter
 gcc receiver.c -o receiver
```
Start receiver:
```bash
 ./receiver
```
Start transmitter in another terminal:
```bash
 ./transmitter
```

# Example
### Python version
Transmitter terminal:
```terminal
Transmission started at 10 Hz rate
Devices: {'PTY_T': '/dev/pts/6', 'PTY_R': '/dev/pts/7'}
Payload size: 20 bytes
Header size: 2 bytes
Transmitter device: /dev/pts/6
{'n': 0, 'ts': 1738408736.2018816, 'val1': 79.66531579271519, 'val2': 8002.739455114154}
{'n': 1, 'ts': 1738408736.3031824, 'val1': 1142.7951800440528, 'val2': 9014.455197574267}
{'n': 2, 'ts': 1738408736.4045305, 'val1': 3146.0788074662705, 'val2': 2369.597081576965}
...
{'n': 94, 'ts': 1738408745.6603653, 'val1': 8316.69147879593, 'val2': 7361.872599472276}
{'n': 95, 'ts': 1738408745.7607894, 'val1': 5397.2207306205155, 'val2': 4051.730185618906}
{'n': 96, 'ts': 1738408745.8615575, 'val1': 1450.975641802117, 'val2': 9434.488074294803}
^CTransmitter is interrupted
N sent: 97. Session duration: 9.7s
Actual rate: 10.0 Hz
Transmitter serial is closed
```
Receiver terminal:
```terminal
Devices: {'PTY_T': '/dev/pts/6', 'PTY_R': '/dev/pts/7'}
Payload size: 20 bytes
Header size: 2 bytes
Receiver device: /dev/pts/7
{'n': 45, 'ts': 1738408740.7292933, 'val1': 6136.21044921875, 'val2': 9628.3828125}
{'n': 46, 'ts': 1738408740.8297496, 'val1': 7620.64599609375, 'val2': 3515.54443359375}
...
{'n': 88, 'ts': 1738408745.0570807, 'val1': 7096.373046875, 'val2': 4274.52197265625}
{'n': 89, 'ts': 1738408745.1576502, 'val1': 6489.908203125, 'val2': 6629.0810546875}
^CReceiver is interrupted
First package received: 45, last: 89
N received: 45, n sent 45.
Success rate: 100.0%
Receiver serial is closed
```
### C version
Transmitter terminal:
```terminal
Connection params:
/dev/pts/6
/dev/pts/7
main PTY_T: /dev/pts/6
main PTY_R: /dev/pts/7
Msg 0 is sent.
Msg 1 is sent.
Msg 2 is sent.
Msg 3 is sent.
Msg 4 is sent.
Msg 5 is sent.
Msg 6 is sent.
Msg 7 is sent.
Msg 8 is sent.
Msg 9 is sent.
```
Receiver terminal:
```terminal
Connection params:
/dev/pts/6
/dev/pts/7
main PTY_T: /dev/pts/6
main PTY_R: /dev/pts/7
Received: String send by C transmitter #0.
Received: String send by C transmitter #1.
Received: String send by C transmitter #2.
Received: String send by C transmitter #3.
Received: String send by C transmitter #4.
Received: String send by C transmitter #5.
Received: String send by C transmitter #6.
Received: String send by C transmitter #7.
Received: String send by C transmitter #8.
Received: String send by C transmitter #9.
```