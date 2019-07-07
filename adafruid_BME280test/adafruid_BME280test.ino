#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

float temperature;
float humidity;
float pressure;

#define ALTITUDE 216.0 // Altitude in Sparta, Greece

Adafruit_BME280 bme; // I2C

void setup(void) {

  Serial.begin(9600);
  Serial.println("Reading sensor");

  bool status;
    
    // default settings
    status = bme.begin(0x76);  //The I2C address of the sensor I use is 0x76
    if (!status) {
        Serial.println("Error. Check");
        Serial.println("connections");
        while (1);
    }
}

void loop() {
  
 delay(2000);

 getPressure();
 getHumidity();
 getTemperature();
 
 //printlning Temperature
 String temperatureString = String(temperature,1);
 Serial.println("T:"); 
 Serial.println(temperatureString);
 Serial.println((char)223);
 Serial.println("C ");
 
 //printlning Humidity
 String humidityString = String(humidity,0); 
 Serial.println("H: ");
 Serial.println(humidityString);
 Serial.println("%");
 
 //printlning Pressure
 Serial.println("P: ");
 String pressureString = String(pressure,2);
 Serial.println(pressureString);
 Serial.println(" hPa");
}

float getTemperature()
{
  temperature = bme.readTemperature();
}

float getHumidity()
{
  humidity = bme.readHumidity();
}

float getPressure()
{
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE,pressure);
  pressure = pressure/100.0F;
}
