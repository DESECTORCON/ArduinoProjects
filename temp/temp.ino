#include <DHT11.h>
// Project 13 - Temperature Logger
#include <EEPROM.h>
#include <LiquidCrystal.h>

#define analogPin 1
#define gndPin A0
#define plusPin A2
#define maxReadings 1000
#define logStartStop 9

int lastReading = 0;
int backLight = 8;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

dht11 DHT11;
const int QRD1114_PIN = A3;

#define DHT11PIN 10

long current_temp;

boolean loggingOn;
//long period = 300;
long period = 10000; // 10 seconds
long lastLoggingTime = 0;
char mode = 'C';

void setup()
{
  pinMode(gndPin, OUTPUT);
  pinMode(plusPin, OUTPUT);
  pinMode(logStartStop, INPUT_PULLUP);
  digitalWrite(gndPin, LOW);
  digitalWrite(plusPin, HIGH);
  pinMode(QRD1114_PIN, INPUT);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);

  Serial.begin(9600);
  Serial.println("Ready");
  lcd.begin(20, 4);
  lcd.print("===Temp Master==");
  lcd.setCursor(0, 1);
  lcd.print("Current Temp:");

  lastReading = EEPROM.read(0); // First byte is reading position
  char sampleCh = (char)EEPROM.read(1);// Second is logging period '0' to'9'
  if (sampleCh > '0' && sampleCh <= '9')
  {
    setPeriod(sampleCh);
  }
  loggingOn = true;            // start logging on turn on
}

void loop()
{
  if (digitalRead(logStartStop) == LOW) {

    if (loggingOn == true) {

      loggingOn = false;
      delay(200);
    } else {

      loggingOn = true;
      delay(200);
    }

  }
  if (Serial.available())
  {
    char ch = Serial.read();


    if (ch == 'r' || ch == 'R')
    {
      sendBackdata();
    }
    else if (ch == 'x' || ch == 'X')
    {
      lastReading = 0;
      EEPROM.write(0, 0);
      Serial.println("Data cleared");
    }
    else if (ch == 'g' || ch == 'G')
    {
      loggingOn = true;
      Serial.println("Logging started");
    }
    else if (ch > '0' && ch <= '9')
    {
      setPeriod(ch);
    }
    else if (ch == 'c' or ch == 'C')
    {
      Serial.println("Mode set to deg C");
      mode = 'C';
    }
    else if (ch == 'f' or ch == 'F')
    {
      Serial.println("Mode set to deg F");
      mode = 'F';
    }
    else if (ch == '?')
    {
      reportStatus();
    }
  }
  long now = millis();
  if (loggingOn && (now > lastLoggingTime + period))
  {
    logReading();
    lastLoggingTime = now;
    current_temp = measureTemp();
    Serial.println("----------------");
    Serial.print("Current Temp C");
    Serial.println(current_temp);
    Serial.println("----------------");

  }


  int proximityADC = analogRead(QRD1114_PIN);
  float proximityV = (float)proximityADC * 5.0 / 1023.0;
//  Serial.println(proximityV);
  if (proximityV < 2) {
    digitalWrite(backLight, HIGH);
    lcd.display();
    updateLCD();
  } else {
    digitalWrite(backLight, LOW);
    lcd.noDisplay();
  }


  //  lcd.setCursor(10, 2);

  delay(350);

}

void sendBackdata()
{
  loggingOn = false;
  Serial.println("Logging stopped");
  Serial.println("------ cut here ---------");
  Serial.print("Time (min)\tTemp (");
  Serial.print(mode);
  Serial.println(")");
  for (int i = 0; i < lastReading + 2; i++)
  {
    Serial.print((period * i) / 60000);
    Serial.print("\t");
    float temp = getReading(i);
    if (mode == 'F')
    {
      temp = (temp * 9) / 5 + 32;
    }
    Serial.println(temp);
  }
  Serial.println("------ cut here ---------");
}

void setPeriod(char ch)
{
  EEPROM.write(1, ch);
  long periodMins = ch - '0';
  Serial.print("Sample period set to: ");
  Serial.print(periodMins);
  Serial.println(" mins");
  period = periodMins * 60000;
}

void logReading()
{
  if (lastReading < maxReadings)
  {
    storeReading(measureTemp(), lastReading);
    lastReading++;
  }
  else
  {
    Serial.println("Full! logging stopped");
    loggingOn = false;
  }
}

float measureTemp()
{
  int a = analogRead(analogPin);
  float volts = a / 205.0;
  float temp = (volts - 0.5) * 100;
  return temp;
}

void storeReading(float reading, int index)
{
  EEPROM.write(0, (byte)index); // store the number of samples in byte 0
  byte compressedReading = (byte)((reading + 20.0) * 4);
  EEPROM.write(index + 2, compressedReading);
  reportStatus();
}

float getReading(int index)
{
  lastReading = EEPROM.read(0);
  byte compressedReading = EEPROM.read(index + 2);
  float uncompressesReading = (compressedReading / 4.0) - 20.0;
  return uncompressesReading;
}

void reportStatus()
{
  Serial.println("----------------");
  Serial.println("Status");
  Serial.print("Current Temp C");
  Serial.println(measureTemp());
  Serial.print("Sample period (s)\t");
  Serial.println(period / 1000);
  Serial.print("Num readings\t");
  Serial.println(lastReading);
  Serial.print("Mode degrees\t");
  Serial.println(mode);
  Serial.println("----------------");
}

int s = 0;
int sec = 0;
int hrs = 0;
int minutes = 0;
int initialHours = 00;//variable to initiate hours
int initialMins = 0;//variable to initiate minutes
int initialSecs = 00;//variable to initiate seconds

//this method is for seconds
int seconds()
{
  s = initialHours * 3600;
  s = s + (initialMins * 60);
  s = s + initialSecs;
  s = s + (millis() / 1000);
  return s;
}
//this method is for hours
int hours()
{
  hrs = seconds();
  hrs = hrs / 3600;
  hrs = hrs % 24;
  return hrs;
}
//this method is for minutes
int mins()
{
  minutes = seconds();
  minutes = minutes / 60;
  minutes = minutes % 60;
  return minutes;
}

int secs()
{
  sec = seconds();
  sec = sec % 60;
  return sec;
}

void printDigits(byte digits) {
  if (digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
char sep()
{
  s = millis() / 1000;
  if (s % 2 == 0)
  {
    lcd.print(":");
  }
  else {
    lcd.print(" ");
  }
}
void digitalClockDisplay() {
  lcd.setCursor(5, 3);
  printDigits(
    hours());
  sep();
  printDigits(mins());
  sep();
  printDigits(secs());
}


void updateLCD() {
  int chk = DHT11.read(DHT11PIN);
  lcd.clear();
  digitalClockDisplay();
  //            col row
  lcd.setCursor(0, 0);
  lcd.print("=====Temp Master====");
  lcd.setCursor(0, 1);
  lcd.print("====Current Temp:");
  lcd.setCursor(2, 2);
  lcd.print(measureTemp());
  lcd.setCursor(10, 2);
  lcd.print(DHT11.humidity);
  //  Serial.println(DHT11.humidity);
  lcd.print("%");
  lcd.setCursor(13, 2);
  if (loggingOn) {

    lcd.print("log ON");
  } else {
    lcd.print("log OFF");
  }
}
