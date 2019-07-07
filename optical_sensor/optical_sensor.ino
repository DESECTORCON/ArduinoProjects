#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht.h>

#define RT0 10000   // Ω
#define B 3977
#define VCC 5    //Supply voltage
#define R 10000  //R=10KΩ
float RT, VR, ln, TX, T0, VRT;

#define DHT11_PIN A0
#define blue 12
#define green 11
#define red 10

#define Pointer 1
#define Logo 0
#define barOne 2
#define barTwo 3
#define barThree 4
#define barFour 5
#define barFive 6

#define thermoster A1

int aPin = 3;
int bPin = 4;
int buttonPin = 7;

LiquidCrystal_I2C lcd(0x3F, 20, 4);
dht DHT;

char mode = 'L';
int menuNum = 0;
int cursor_ = 0;

bool otherLED = true;

int count = 0;

int temp = 0;
int humidity = 0;
int set_humidity = 0;

byte customChar[] = {
  B00100,
  B01010,
  B10101,
  B10101,
  B10101,
  B11011,
  B10001,
  B10101
};

byte pointer[] = {
  B01000,
  B00100,
  B00010,
  B11111,
  B11111,
  B00010,
  B00100,
  B01000
};

byte five[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte four[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};
byte three[] = {B11100, B11100, B11100, B11100, B11100, B11100, B11100, B11100};
byte two[] = {B11000, B11000, B11000, B11000, B11000, B11000, B11000, B11000};
byte one[] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B10000};

void setup() {
  lcd.init(); lcd.init(); lcd.backlight(); lcd.createChar(0, customChar); lcd.createChar(1, pointer); lcd.createChar(2, one); lcd.createChar(3, two); lcd.createChar(4, three);
  lcd.createChar(5, four); lcd.createChar(6, five);

  pinMode(aPin, INPUT_PULLUP); pinMode(bPin, INPUT_PULLUP); pinMode(buttonPin, INPUT_PULLUP);
  pinMode(red, OUTPUT); pinMode(green, OUTPUT); pinMode(blue, OUTPUT); pinMode(thermoster, INPUT); Serial.begin(9600);
  digitalWrite(blue, HIGH); digitalWrite(green, HIGH); digitalWrite(red, HIGH);
}

void loop() {
  int turn = getEncoderTurn();
  Serial.println(mode);
  lcd.setCursor(16, 3);
  lcd.print(count);

  if (mode == 'L' && menuNum == 0)
  {
    if (otherLED)
    {
      digitalWrite(green, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
    }
    lcd.setCursor(0, 0); lcd.write(0);
    lcd.setCursor(1, 0); lcd.print(">>Arduino Sensors<<");
    lcd.setCursor(1, 1); lcd.print("Temperature");
    lcd.setCursor(1, 2); lcd.print("Humidity");
    lcd.setCursor(1, 3); lcd.print("Sound");

    if (turn != 0)
    {
      cursor_ = cursor_ + turn;

      if (cursor_ == 3) {
        cursor_ = 2;
      } if (cursor_ == -1) {
        cursor_ = 0;
      }

      if (cursor_ == 0)
      {
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(0, 2); lcd.print(" ");
        lcd.setCursor(0, 3); lcd.print(" ");
      }
      if (cursor_ == 1)
      {
        lcd.setCursor(0, 1); lcd.print(" ");
        lcd.setCursor(0, 2); lcd.write(1);
        lcd.setCursor(0, 3); lcd.print(" ");
      }
      if (cursor_ == 2)
      {
        lcd.setCursor(0, 1); lcd.print(" ");
        lcd.setCursor(0, 2); lcd.print(" ");
        lcd.setCursor(0, 3); lcd.write(1);
      }
    }

    if (digitalRead(buttonPin) == LOW)
    {

      if (cursor_ == 0)
      {
        menuNum = 1;
      }
      if (cursor_ == 1)
      {
        menuNum = 2;
      }
      if (cursor_ == 2)
      {
        menuNum = 3;
      }
      delay(300);
      cursor_ = 0;
      lcd.clear();
    }

  }


  if (mode == 'L' && menuNum == 1)
  {
    if (otherLED) {
      analogWrite(green, 50);
      analogWrite(red, 150);
      digitalWrite(blue, HIGH);
    }

    lcd.setCursor(0, 0); lcd.write(Logo);
    lcd.setCursor(1, 0); lcd.print("Lobby>Temperature");
    lcd.setCursor(1, 1); lcd.print("DHT11");
    lcd.setCursor(1, 2); lcd.print("Thermistor");
    lcd.setCursor(1, 3); lcd.print("back");

    if (turn != 0)
    {

      cursor_ = cursor_ + turn;

      if (cursor_ == 3) {
        cursor_ = 2;
      } if (cursor_ == -1) {
        cursor_ = 0;
      }

      if (cursor_ == 0)
      {
        lcd.setCursor(0, 1); lcd.write(1);
        lcd.setCursor(0, 2); lcd.print(" ");
        lcd.setCursor(0, 3); lcd.print(" ");
      }
      if (cursor_ == 1)
      {
        lcd.setCursor(0, 1); lcd.print(" ");
        lcd.setCursor(0, 2); lcd.write(1);
        lcd.setCursor(0, 3); lcd.print(" ");
      }
      if (cursor_ == 2)
      {
        lcd.setCursor(0, 2); lcd.print(" ");
        lcd.setCursor(0, 1); lcd.print(" ");
        lcd.setCursor(0, 3); lcd.write(1);
      }

    }
    if (digitalRead(buttonPin) == LOW)
    {
      if (cursor_ == 0) {
        mode = 'T';
      }
      if (cursor_ == 1) {
        mode = 'I';
      }
      if (cursor_ == 2)
      {
        mode = 'L';
        menuNum = 0;
      }
      lcd.clear();
      delay(300);
      cursor_ = 0 ;
    }

  }

  if (mode == 'T')
  {
    if (otherLED)
    {
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      digitalWrite(blue, HIGH);
    }

    if (count >= 100) {
      int chk = DHT.read11(DHT11_PIN);

      //      resetDisplay(0,0);

      lcd.setCursor(0, 0);
      lcd.print("     Tempture     ");
      //            col, row
      lcd.setCursor(5, 1);
      lcd.print(DHT.temperature);
      count = 0;
    } if (count >= 80) {
      //      resetDisplay(0,0);
      lcd.setCursor(0, 0);
      lcd.print(">>Getting Value...<<");
    }

    lcd.setCursor(1, 2); lcd.print("back");
    lcd.setCursor(10, 2); lcd.print("refresh");

    if (turn != 0)
    {

      cursor_ = cursor_ + turn;

      if (cursor_ == 2)
      {
        cursor_ == 0;
      }
      if (cursor_ == -1)
      {
        cursor_ == 0;
      }

    }

    if (cursor_ == 0)
    {
      lcd.setCursor(0, 2);
      lcd.write(1);
      lcd.setCursor(9, 2);
      lcd.print(" ");
    }

    if (cursor_ == 1) {
      lcd.setCursor(9, 2);
      lcd.write(1);
      lcd.setCursor(0, 2);
      lcd.print(" ");
    }

    if (digitalRead(buttonPin) == LOW) {
      if (cursor_ == 0) {
        lcd.clear();
        mode = 'L';
        cursor_ = 0;
        delay(300);
      }
      if (cursor_ == 1) {
        int chk = DHT.read11(DHT11_PIN);

        //      resetDisplay(0,0);

        lcd.setCursor(0, 0);
        lcd.print("     Tempture     ");
        //            col, row
        lcd.setCursor(5, 1);
        lcd.print(DHT.temperature);
        delay(300);
        count = 0;
      }
    }

    if (mode == 'I')
    {
      if (otherLED)
      {
        digitalWrite(green, LOW);
        digitalWrite(red, LOW);
        digitalWrite(blue, HIGH);
      }

      VRT = analogRead(thermoster);              //Acquisition analog value of VRT
      VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
      VR = VCC - VRT;
      RT = VRT / (VR / R);               //Resistance of RT

      ln = log(RT / RT0);
      TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

      TX = TX - 273.15;                 //Conversion to Celsius

      Serial.print("AAA");

      //      resetDisplay(0,0);

      lcd.setCursor(0, 0);
      lcd.print("     Tempture     ");
      //            col, row
      lcd.setCursor(5, 1);
      lcd.print(TX);
      count = 0;
      lcd.setCursor(1, 2); lcd.print("back");

      if (cursor_ == 0)
      {
        lcd.setCursor(0, 2);
        lcd.write(1);
      }

      if (digitalRead(buttonPin) == LOW) {
        lcd.clear();
        mode = 'L';
        cursor_ = 0;
        delay(300);
      }

    }
    if (mode == 'H')
    {
      if (otherLED)
      {
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        digitalWrite(blue, LOW);
      }

      if (count >= 100) {
        int chk = DHT.read11(DHT11_PIN);

        //      resetDisplay(0,0);

        lcd.setCursor(0, 0);
        lcd.print("     humidity     ");
        //            col, row
        lcd.setCursor(5, 1);
        lcd.print(DHT.humidity); lcd.print("%");
        count = 0;
      } if (count >= 80) {
        //      resetDisplay(0,0);
        lcd.setCursor(0, 0);
        lcd.print(">>Getting Value...<<");
      }

      lcd.setCursor(1, 2);
      lcd.print("back");

      if (cursor_ == 0)
      {
        lcd.setCursor(0, 2);
        lcd.write(1);
      }
      if (digitalRead(buttonPin) == LOW) {
        lcd.clear();
        mode = 'L';
        cursor_ = 0;
        delay(300);
      }

    }
    if (mode == 'S')
    {
      if (otherLED) {
        analogWrite(green, 200);
        analogWrite(red, 100);
        digitalWrite(blue, LOW);
      }

      lcd.setCursor(5, 0);
      lcd.print("set humidity");

      lcd.setCursor(5, 1);
      lcd.print(set_humidity); lcd.print("%");

      if (turn != 0)
      {

        set_humidity = turn + set_humidity;

      }


      if (cursor_ == 0)
      {
        lcd.setCursor(0, 2);
        lcd.print("*");
      }
      if (digitalRead(buttonPin) == LOW) {
        lcd.clear();
        mode = 'L';
        cursor_ = 0;
        delay(300);
      }

    }
    if (count >= 1000) {
      int chk = DHT.read11(DHT11_PIN);
      if (DHT.humidity < set_humidity) {
        otherLED = false;
        digitalWrite(red, HIGH);
        digitalWrite(blue, LOW);
        digitalWrite(green, LOW);
      } else {
        otherLED = true;
      }
      count = 0;
    }
    count ++;
  }
}


int getEncoderTurn()
{
  // return -1, 0, or +1
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;
  int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  if (newA != oldA || newB != oldB)
  {
    // something has changed
    if (oldA == LOW && newA == HIGH)
    {
      result = -(oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}


void resetDisplay(int row, int colon)
{

  lcd.setCursor(colon, row);
  lcd.print("            ");

}


double Thermister(int RawADC) {
  double Temp;
  // See http://en.wikipedia.org/wiki/Thermistor for explanation of formula
  Temp = log(((10240000 / RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;           // Convert Kelvin to Celcius
  return Temp;
}
