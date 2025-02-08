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
or compile code with address sanitizer:
```bash
 cd ./transmission/c/
 gcc -fsanitize=address -g transmitter.c -o transmitter
 gcc -fsanitize=address -g receiver.c -o receiver
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
/dev/pts/4
/dev/pts/5
main PTY_T: /dev/pts/4
main PTY_R: /dev/pts/5
Msg '0 1738761153.432000 1804289.375000 846930.875000' is sent.
Msg '1 1738761154.433000 1681692.750000 1714636.875000' is sent.
Msg '2 1738761155.433000 1957747.875000 424238.343750' is sent.
Msg '3 1738761156.434000 719885.375000 1649760.500000' is sent.
Msg '4 1738761157.434000 596516.687500 1189641.500000' is sent.
Msg '5 1738761158.435000 1025202.375000 1350490.000000' is sent.
Msg '6 1738761159.436000 783368.687500 1102520.125000' is sent.
Msg '7 1738761160.437000 2044897.750000 1967514.000000' is sent.
Msg '8 1738761161.438000 1365180.500000 1540383.500000' is sent.
Msg '9 1738761162.438000 304089.187500 1303455.750000' is sent.
End of transmission signal is sent.
```
Receiver terminal:
```terminal
Connection params:
/dev/pts/4
/dev/pts/5
main PTY_T: /dev/pts/4
main PTY_R: /dev/pts/5
Received: 0 1738761153.432000 1804289.375000 846930.875000
Val sum: 2651220.250000
Received: 1 1738761154.433000 1681692.750000 1714636.875000
Val sum: 3396329.500000
Received: 2 1738761155.433000 1957747.875000 424238.343750
Val sum: 2381986.250000
Received: 3 1738761156.434000 719885.375000 1649760.500000
Val sum: 2369646.000000
Received: 4 1738761157.434000 596516.687500 1189641.500000
Val sum: 1786158.250000
Received: 5 1738761158.435000 1025202.375000 1350490.000000
Val sum: 2375692.500000
Received: 6 1738761159.436000 783368.687500 1102520.125000
Val sum: 1885888.750000
Received: 7 1738761160.437000 2044897.750000 1967514.000000
Val sum: 4012411.750000
Received: 8 1738761161.438000 1365180.500000 1540383.500000
Val sum: 2905564.000000
Received: 9 1738761162.438000 304089.187500 1303455.750000
Val sum: 1607545.000000
Received end of transmission signal
```
