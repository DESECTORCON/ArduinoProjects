#include <DS1302.h>
#include <Time.h>
#include <TimeLib.h>
#include <TimerFreeTone.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

Adafruit_7segment display = Adafruit_7segment();

int times[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 100, 130, 200, 230, 300, 330, 400, 430, 500, 530, 600, 700, 800, 900, 1000, 1500, 2000, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500};
int numTimes = 35;

int buzzerPin = 11;
int aPin = 2;
int bPin = 4;
int buttonPin = 3;
unsigned long lastMillis1;

int change = 0;

int alarm_hour = 0;
int alarm_minute = 0;
int alarm_on = false;

int brightness = 3;

int time_mode = 0;

boolean stopped = true;

int selectedTimeIndex = 12;
int timerMinute;
int timerSecond;

int col = 1;

int button = 5;
int mode = 0;

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  display.begin(0x70);
  reset();
  display.setBrightness(brightness);
  display.print(0xCCEE, HEX);
  tone(buzzerPin , 779, 100);
  delay(200);

  attachInterrupt(digitalPinToInterrupt(aPin), getEncoderTurn, CHANGE);
}

void loop()
{
  //  int change = getEncoderTurn();
//  getEncoderTurn();
  Serial.println(change);
  if (digitalRead(button) == LOW) {
    noTone(buzzerPin);
    timerSecond = 0;
    timerMinute = 0;
    mode ++;
    stopped = false;
    if (mode > 5) {
      mode = 0;
    } else {

    }


    display.print(0xC, HEX);
    display.writeDigitNum(1, mode);
    display.writeDisplay();
    tone(buzzerPin , 220, 100);
    delay(500);
    display.writeDigitNum(1, 0);
    display.writeDigitNum(2, 0);
    display.writeDigitNum(3, 0);
    display.writeDigitNum(4, 0);
    display.blinkRate(0);
    display.drawColon(true);
    display.writeDisplay();
    noTone(buzzerPin);
    stopped = true;
    //
    //
    //    delay(200);
  }

  if (mode == 0) {
    updateCountingTime();
    updateDisplay();
    if (timerMinute == 0 && timerSecond == 0 && ! stopped)
    {
      tone(buzzerPin, 400);
    }
    else
    {
      noTone(buzzerPin);
    }
    if (digitalRead(buttonPin) == LOW)
    {
      stopped = ! stopped;
      while (digitalRead(buttonPin) == LOW);
    }
//    int change = getEncoderTurn();
    if (change != 0)
    {
      changeSetTime(change);
    }
  } if (mode == 1 ) {


    if (digitalRead(buttonPin) == LOW) {
      stopped = !stopped;
      delay(300);
    }
    //    Serial.println(stopped);
    if (stopped) {

      static unsigned long lastMillis;
      unsigned long m = millis();
      if (m > (lastMillis + 1000))
      {

        if (timerSecond == 59)
        {
          timerSecond = 0;
          timerMinute ++;
        }
        else
        {
          timerSecond ++;
        }
        lastMillis = m;
        if (col == 1) {
          col = 0;
        } else {
          col = 1;
        }
      }
      int timeRemaining =  timerMinute * 100 + timerSecond;
      display.print(timeRemaining, DEC);
      display.drawColon(true);
      display.writeDisplay();
    } else {

    }
  }


  if (mode == 2) {
    unsigned int CTime = 0;
    CTime = CTime + hour() * 100;
    CTime = CTime + minute();

    display.print(CTime, DEC);
    if ((second() % 2) == 0) {
      display.drawColon(true);
    } else {
      display.drawColon(false);
    }
    display.writeDisplay();

    if (change != 0) {
      if (time_mode == 0) {
        setTime(hour(), minute() + change, second(), day(), month(), year());
      } if (time_mode == 1)
        setTime(hour() + change, minute(), second(), day(), month(), year());
    }

    if (digitalRead(buttonPin) == LOW) {
      if (time_mode >= 1) {
        time_mode = 0;
      } else {
        time_mode ++;
      }
      delay(200);
    }

  }

  if (mode == 3)
  {

    if (change != 0)
    {
      brightness = brightness + change;

      if (brightness >= 15) {
        brightness = 15;
      }
      if (brightness <= 0) {
        brightness = 0;
      }

      display.setBrightness(brightness);
      display.print(brightness, DEC);

      display.writeDisplay();


    }
  }


  if (mode == 4) {
    if (digitalRead(buttonPin) == LOW) {
      if (time_mode >= 1) {
        time_mode = 0;
      } else {
        time_mode ++;
      }
      delay(200);
    }
    if (change != 0)
    {

      if (alarm_minute >= 60)
      {
        alarm_minute = 0;
        alarm_hour ++;
      }

      if (alarm_hour >= 24)
      {
        alarm_hour = 0;
      }

      if (alarm_hour < 0)
      {
        alarm_hour = 0;
      }

      if (alarm_minute < 0)
      {
        alarm_minute = 0;
      }

      if (time_mode == 1) {
        alarm_minute  = alarm_minute + change;
      }
      if (time_mode == 0) {
        alarm_hour = alarm_hour + change;
      }

    }
    display.print(alarm_minute + alarm_hour * 100, DEC);
    display.drawColon(true);
    display.writeDisplay();
  }

  if (mode == 5) {

    if (digitalRead(buttonPin) == LOW)
    {
      alarm_on = !alarm_on;
      if (alarm_on) {
        display.print(0xE1, HEX);
      }
      else {
        display.print(0xF0, HEX);
      }
      display.writeDisplay();
      delay(300);
    }

  }

  if ( alarm_minute == minute() && alarm_hour == hour() && alarm_on)
  {
    if (digitalRead(buttonPin) == LOW) {
      alarm_on = false;
    }
    tone(buzzerPin, 1000, 1000);
    mode = 5;
    display.print(0xEFEF, HEX);
    display.drawColon(true);
    display.writeDisplay();
    delay(500);
  }

  //  Serial.println(brightness);
  //  Serial.println(col);
}

void reset()
{
  timerMinute = times[selectedTimeIndex] / 100;
  timerSecond = times[selectedTimeIndex] % 100;
  stopped = true;
  noTone(buzzerPin);
}

void updateDisplay() // mmss
{
  // update I2C display
  int timeRemaining =  timerMinute * 100 + timerSecond;
  if (timeRemaining == 0) {
    display.print(0xFEFE, HEX);
    display.drawColon(true);
  } else {
    display.print(timeRemaining, DEC);
    if (timeRemaining < 1000) {
      display.writeDigitNum(0, 0);
    }
    if (timeRemaining < 100) {
      display.writeDigitNum(0, 0);
      display.writeDigitNum(1, 0);
    }
    if (timeRemaining < 10) {
      display.writeDigitNum(0, 0);
      display.writeDigitNum(1, 0);
      display.writeDigitNum(3, 0);
    }

    if (col == 1) {
      display.drawColon(false);
    } else {
      display.drawColon(true);
    }

    if (timeRemaining < 60 && !stopped) {
      display.blinkRate(2);
    } else {
      display.blinkRate(0);
    }



    if (timeRemaining < 15 && !stopped && !(timeRemaining < 10) && (millis() - lastMillis1 > 1000) && col == 1) {
      TimerFreeTone(buzzerPin, 600, 500);
      lastMillis1 = millis();
      display.writeDigitNum(5, 0, true);
    }
    if (timeRemaining < 10 && !stopped && col == 1 && (millis() - lastMillis1 > 1000)) {
      TimerFreeTone(buzzerPin, 700, 500);
      lastMillis1 = millis();
      display.writeDigitNum(6, 0, true);
    }
    else {
      noTone(buzzerPin);
    }
  }



  //  Serial.println(lastMillis1);
  display.writeDisplay();
}

void updateCountingTime()
{
  if (stopped) return;

  static unsigned long lastMillis;
  unsigned long m = millis();
  if (m > (lastMillis + 1000) && (timerSecond > 0 || timerMinute > 0))
  {

    if (timerSecond == 0)
    {
      timerSecond = 59;
      timerMinute --;
    }
    else
    {
      timerSecond --;
    }
    lastMillis = m;
    if (col == 1) {
      col = 0;
    } else {
      col = 1;
    }
  }
}


void changeSetTime(int change)
{
  selectedTimeIndex += change;
  if (selectedTimeIndex < 0)
  {
    selectedTimeIndex = numTimes;
  }
  else if (selectedTimeIndex > numTimes)
  {
    selectedTimeIndex = 0;
  }
  timerMinute = times[selectedTimeIndex] / 100;
  timerSecond = times[selectedTimeIndex] % 100;
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
  change = change + result;
  return result;
}
