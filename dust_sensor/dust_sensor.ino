//#include "LowPower.h"
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

DS1302 rtc(4, 5, 6);
#define USE_AVG

int sensor = 8;              // the pin that the sensor is atteched to

// Arduino pin numbers.
const int sharpLEDPin = 7;   // Arduino digital pin 7 connect to sensor LED.
const int sharpVoPin = A5;
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

LiquidCrystal_I2C lcd(0x3F, 20, 4);

byte smile[] = {
  B00000,
  B01010,
  B10101,
  B00000,
  B10001,
  B01010,
  B00100,
  B00000
};

byte mod[] = {
  B00000,
  B01010,
  B10101,
  B01010,
  B00000,
  B11111,
  B00000,
  B00000
};

byte bad[] = {
  B00000,
  B01010,
  B10101,
  B01010,
  B00000,
  B01110,
  B10001,
  B00000
};

byte verybad[] = {
  B10001,
  B01010,
  B00100,
  B00100,
  B00100,
  B01010,
  B10001,
  B00000
};

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

/////////////////////////////////////////////////////////////////////////////

// Arduino setup function.
void setup() {
  // Set LED pin for output.
  pinMode(sharpLEDPin, OUTPUT);     // initalize LED as an output
  pinMode(sensor, INPUT);

  // Start the hardware serial port for the serial monitor.
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Wait two seconds for startup.
  delay(2000);
  Serial.println("");
  Serial.println("GP2Y1014AU0F Demo");
  Serial.println("=================");

  // init lcd
  lcd.init();
  lcd.createChar(0, smile);
  lcd.createChar(1, mod);
  lcd.createChar(2, bad);
  lcd.createChar(3, verybad);
  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.print(">Arduino dust sensor");
  lcd.setCursor(0, 1);
  lcd.print("DustDensity: ");

  rtc.halt(false);
  rtc.writeProtect(true);


}

// Arduino main loop.
void loop() {
  cycle ++;
  if (cycle > awake_time) {
    lcd.noDisplay();
    analogWrite(lcd_backlight, 0);
//    attachInterrupt(0, wake, HIGH);
//    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
//    detachInterrupt(0); 
//attachInterrupt(digitalPinToInterrupt(sensor), buttonPressed, RISING);
//LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF,TIMER1_OFF, TIMER0_OFF,SPI_OFF, USART0_OFF,TWI_OFF );
    

  }
  else {
    analogWrite(lcd_backlight, 170);
    lcd.display();
    lcd.setCursor(14, 1);
    float dust = dust_get();
    lcd.print(dust);

    if (dust < 30) {
      lcd.setCursor(0, 3);
      lcd.print("Dust: GOOD");
      lcd.setCursor(19, 3);
      lcd.write(0);
    }
    else if (30 < dust < 80) {
      lcd.setCursor(0, 3);
      lcd.print("Dust: MODRATE");
      lcd.setCursor(19, 3);
      lcd.write(1);
    }
    else if (81 < dust < 120) {
      lcd.setCursor(0, 3);
      lcd.print("Dust: BAD");
      lcd.setCursor(19, 3);
      lcd.write(2);
    }
    else if (121 < dust < 200) {
      lcd.setCursor(0, 3);
      lcd.print("Dust: VERY BAD");
      lcd.setCursor(19, 3);
      lcd.write(2);
    }
    else if (201 < dust) {
      lcd.setCursor(0, 3);
      lcd.print("Dust: DO NOT LIVE HERE!!!");
      lcd.setCursor(19, 3);
      lcd.write(3);
    }
    lcd.setCursor(15 , 3);
    lcd.print(cycle);
    lcd.setCursor(3, 2);
    lcd.print(rtc.getTimeStr());
    lcd.print(" ");
    lcd.print(rtc.getDOWStr(FORMAT_SHORT));

  }

  int val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    cycle = 0;
    lcd.setCursor(15 , 3);
    lcd.print("    ");
  }
  delay(1);
  Serial.print(cycle);
  Serial.print("  "); Serial.println(val);

  if (cycle < 0){
    cycle = awake_time;
  }



} 

//void wake() {
//  int val = digitalRead(sensor);
//}









// END PROGRAM
