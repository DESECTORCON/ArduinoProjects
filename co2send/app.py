import adafruit_dht as dht_sensor
import time
import board
from flask import Flask, Response
from prometheus_client import Counter, Gauge, start_http_server, generate_latest
import serial
co2 = 0
content_type = str('text/plain; version=0.0.4; charset=utf-8')

dht = dht_sensor.DHT22(board.D4)
temperature = 0
humidity =0

app = Flask(__name__)

current_humidity = Gauge(
        'current_humidity',
        'the current humidity percentage, this is a gauge as the value can increase or decrease',
        ['room']
)

current_temperature = Gauge(
        'current_temperature',
        'the current temperature in celsius, this is a gauge as the value can increase or decrease',
        ['room']
)

current_co2 = Gauge(
        'current_co2',
        'in ppm',
        ['room']
)

@app.route('/metrics')
def metrics():
    global s
    try:
        temperature = dht.temperature
        humidity = dht.humidity
        s.write(b"a")
        value = s.readlines()
        co2 = int(value[0].decode('ascii').strip('\r\n'))
    except Exception as e:
        return

    humidity = format(humidity, ".2f")
    temperature = format(temperature, ".2f")
    metrics = {"temperature": temperature, "humidity": humidity, "co2": co2}
    current_humidity.labels('study').set(metrics['humidity'])
    current_temperature.labels('study').set(metrics['temperature'])
    current_co2.labels('study').set(metrics['co2'])

    return Response(generate_latest(), mimetype=content_type)

if __name__ == '__main__':
    s = serial.Serial('/dev/ttyACM0', 9600, timeout=1) 
    app.run(host='172.17.0.1', port=5000)
