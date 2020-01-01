#include <Adafruit_BME280.h>
#include <UTFT.h>
#define ALTITUDE 216.0
// Declare which fonts we will be using
extern uint8_t SmallFont[];

int temperature;
int humidity;
int pressure;

// Declare an instance of the class
UTFT L(ITDB18SP,7,6,5,3,4); // Remember to change the model parameter to suit your display module!
Adafruit_BME280 bme;
void setup()
{
  Serial.begin(9600);
  L.InitLCD(PORTRAIT);
  L.setFont(SmallFont);
  L.setContrast(64);
  bool status;

  // default settings
  status = bme.begin(0x76);  //The I2C address of the sensor I use is 0x76
  Serial.println(status);
  
  L.print("Arduino Weather Center", 5, 50, 270);
}

void loop()
{
  L.setColor(VGA_SILVER);
  byte buf[126];  
    int x, x2;
  int y, y2;
  int r;
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure();
  pressure = bme.seaLevelForAltitude(ALTITUDE, pressure);
  pressure = pressure / 100.0F;

  //printlning Temperature
  String temperatureString = String(temperature, 1);
  // L.print("T:", 140, 20);
  L.print("T: " + temperatureString + " C", 140, 20, 270);
  // L.print(" C ");

  //printlning Humidity
  String humidityString = String(humidity, 0);
  // L.print("H: ", 140, 40);
  L.print("H: " + humidityString + " %", 140, 40, 270);
  // L.print("%");

  //printlning Pressure
  // L.print("P: ", 140, 60);
  String pressureString = String(pressure, 2);
  L.print("P: " + pressureString + "hPa", 140, 60, 270);
  // L.print(" hPa");
  delay(1000);
  Serial.println(temperatureString + "   " + humidityString + "   " +pressureString);
}
