#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BME280.h>
#define ALTITUDE 216.0
#define USE_AVG

Adafruit_BME280 bme;
LiquidCrystal_I2C lcd(0x3F, 16, 4);

bool power_stat = true;

int temperature;
int humidity;
int pressure;

int index = 0;

const int sharpLEDPin = 8;   // Arduino digital pin 7 connect to sensor LED.
const int sharpVoPin = A7;
#ifdef USE_AVG
#define N 100
static unsigned long VoRawTotal = 0;
static int VoRawCount = 0;

int awake_time = 2500;
int cycle = 0;
const int lcd_backlight = 10;

#endif // USE_AVG

// Set the typical output voltage in Volts when there is zero dust.
static float Voc = 0.6;

// Use the typical sensitivity in units of V per 100ug/m3.
const float K = 0.5;

const int buttonup = 7;
const int buttondown = 12;
const int power = 11;

const int dustdigi = 8;
const int dustanal = A7;

const int led1 = 5;
const int led2 = 4;
const int led3 = 3;
const int led4 = 2;
const int led5 = A6;
const int led6 = A3;
const int led7 = A2;
const int led8 = A1;
const int led9 = A0;

int ledpins = {led1 ,led2,led3,led4,led5,led6,led7,led8,led9};


////////////////////////////////
// Helper functions to print a data value to the serial monitor.
void printValue(String text, unsigned int value, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  if (!isLast) {
    Serial.print(", ");
  }
}
void printFValue(String text, float value, String units, bool isLast = false) {
  Serial.print(text);
  Serial.print("=");
  Serial.print(value);
  Serial.print(units);
  if (!isLast) {
    Serial.print(", ");
  }
}

float dust_get() {
  // Turn on the dust sensor LED by setting digital pin LOW.
  digitalWrite(sharpLEDPin, LOW);

  // Wait 0.28ms before taking a reading of the output voltage as per spec.
  delayMicroseconds(280);

  // Record the output voltage. This operation takes around 100 microseconds.
  int VoRaw = analogRead(sharpVoPin);

  // Turn the dust sensor LED off by setting digital pin HIGH.
  digitalWrite(sharpLEDPin, HIGH);

  // Wait for remainder of the 10ms cycle = 10000 - 280 - 100 microseconds.
  delayMicroseconds(9620);

  // Print raw voltage value (number from 0 to 1023).
#ifdef PRINT_RAW_DATA
  printValue("VoRaw", VoRaw, true);
  Serial.println("");
#endif // PRINT_RAW_DATA

  // Use averaging if needed.
  float Vo = VoRaw;
#ifdef USE_AVG
  VoRawTotal += VoRaw;
  VoRawCount++;
  if ( VoRawCount >= N ) {
    Vo = 1.0 * VoRawTotal / N;
    VoRawCount = 0;
    VoRawTotal = 0;
  } else {
    return;
  }
#endif // USE_AVG

  // Compute the output voltage in Volts.
  Vo = Vo / 1024.0 * 5.0;
  printFValue("Vo", Vo * 1000.0, "mV");

  // Convert to Dust Density in units of ug/m3.
  float dV = Vo - Voc;
  if ( dV < 0 ) {
    dV = 0;
    Voc = Vo;
  }
  float dustDensity = dV / K * 100.0;
  printFValue("DustDensity", dustDensity, "ug/m3", true);
  return dustDensity;
}
///////////////////////////////

void led_con(bool one, bool two, bool three, int four, int five, int six, int seven, int eight, int nine){
  digitalWrite(one, HIGH);
  digitalWrite(two, HIGH);
  digitalWrite(three, HIGH);
  digitalWrite(, HIGH);
  digitalWrite(one, HIGH);
  digitalWrite(one, HIGH);
  digitalWrite(one, HIGH);
  digitalWrite(one, HIGH);
  digitalWrite(one, HIGH);

}


void setup()
{
    Serial.begin(9600);
        lcd.init();
    lcd.backlight();
    lcd.print("** ULTIDUINO **");
    bool status;
    status = bme.begin();
    if (!status) {
        Serial.println("failed to connect to bme sensor");
        lcd.setCursor(0, 1);
        lcd.print("failed to connect to bme sensor. PLEASE CHECK WIRING!");
    }
    pinMode(sharpLEDPin, OUTPUT);     // initalize LED as an output
    // pinMode(sensor, INPUT);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(led5, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(led7, OUTPUT);
    pinMode(led8, OUTPUT);
    pinMode(led9, OUTPUT);

    pinMode(buttondown, INPUT);
    pinMode(buttonup, INPUT);
    pinMode(power, INPUT);


}
void loop()
{
    if (power_stat){
        temperature = bme.readTemperature();
        humidity = bme.readHumidity();
        pressure = bme.readPressure();
        pressure = bme.seaLevelForAltitude(ALTITUDE, pressure);
        pressure = pressure / 100.0F;
        float dust = dust_get();

        lcd.setCursor(0,1);
        lcd.print(" humidity:");
        lcd.print(humidity);
        
        lcd.setCursor(0,2);
        lcd.print(" temperature:");
        lcd.print(temperature);

        lcd.setCursor(0,3);
        lcd.print(" dust:");
        lcd.print(dust);

        if (index == 1){
            lcd.setCursor(0,1);
            lcd.print("*");
            int val = map(humidity, 0, 1, 100, 9);
            Serial.println(val);

            for (int i = 0; i == 9; i++)
            {
              digitalWrite(ledpins[i], HIGH);
            }
            
            
        }

        if (index == 2){
            lcd.setCursor(0,2);
            lcd.print("*");
            int val = map(temperature, 0, 1, 100, 9);
            Serial.println(val);

            for (int i = 0; i == 9; i++)
            {
              digitalWrite(ledpins[i], HIGH);
            }
        }

        if (index == 3){
            lcd.setCursor(0,3);
            lcd.print("*");
            int val = map(dust, 0, 1, 250, 9);
            Serial.println(val);

            for (int i = 0; i == 9; i++)
            {
              digitalWrite(ledpins[i], HIGH);
            }
        }

        delay(50);
    }
    else {
      lcd.backlight();
      lcd.clear();
      
    }
    if (digitalRead(power) == HIGH){
        power_stat = !power_stat;
        delay(300);
    }
    if (digitalRead(buttonup) == HIGH){
        index = index + 1;
        if (index == 4 || index > 3){
            index = 3;
        }
        delay(200);
    }
    if (digitalRead(buttondown) == HIGH){
        index = index - 1;
        if (index == 0 || index < 1){
            index = 1;
        }
        delay(200);
    }
}