import serial
from time import sleep
co2 = 0
with serial.Serial('/dev/ttyACM0', 9600, timeout=1) as s:
    while True:
        s.write(b"a")
        value = s.readlines()
        co2 = int(value[0].decode('ascii').strip('\r\n'))
        print(co2)
        sleep(1)
