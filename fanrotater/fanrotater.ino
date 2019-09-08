#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

static int buttonPin = 2;
static int timebuttonpin = 3;
int mode = 0;
int timemode = 0;
int sleeptime = 1000;
int servodegrees = 10;

int step1 = 0;
int step2 = 0;
int step3 = 0;
int step4 = 0;

unsigned long lastmillis = millis();
boolean servo_direction = true;
boolean servoon = true;

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo servo;

void setup()
{
    lcd.init();      // lcd를 사용을 시작합니다.
    lcd.backlight(); // backlight를 On 시킵니다.
    lcd.setCursor(0,0);
    lcd.print("FanControl");
    
    

    pinMode(buttonPin, INPUT);
    pinMode(timebuttonpin, INPUT);
    servo.attach(12);
    servo.write(90);
    Serial.begin(9600);
}

void loop()
{
    lcd_print(sleeptime, servodegrees, servoon);
    if (digitalRead(buttonPin) == HIGH)
    {
        mode++;
        if (mode >= 4)
        {
            mode = 0;
        }
        switch (mode)
        {
        case 0:
            servodegrees = 12;
            break;
        case 1:
            servodegrees = 48;
            break;
        case 2:
            servodegrees = 100;
            break;
        case 3:
            servodegrees = 160;
            break;
        }
        int divison_ = servodegrees / 4;
        step1 = division;
        setp2
        lcd_print(sleeptime, servodegrees, servoon);
        delay(100);
    }

    if (digitalRead(timebuttonpin) == HIGH)
    {
        timemode++;
        if (timemode >= 5)
        {
            timemode = 0;
        }
        servoon = true;
        switch (timemode)
        {
        case 0:
            sleeptime = 500;
            break;
        case 1:
            sleeptime = 1000;
            break;
        case 2:
            sleeptime = 1200;
            break;
        case 3:
            sleeptime = 1500;
            break;
        case 4:
            servoon = false;
            break;
        }
        lcd_print(sleeptime, servodegrees, servoon);
        delay(100);
    }

    // if ((millis() - lastmillis) >= sleeptime)
    // {
    //     Serial.println("Movment");
    //     Serial.print("--------------------");
    //     servo_direction = !servo_direction;
    //     lastmillis = millis();
    //     delay(sleeptime);
    // }
    if (servoon && (millis() - lastmillis) > sleeptime)
    {
        if (servo_direction)
        {
            servo.write(servodegrees);
            servo_direction = !servo_direction;
            lastmillis = millis();
        }
        else
        {
            servo.write(90);
            servo_direction = !servo_direction;
            lastmillis = millis();
        }
    }
    else
    {
        servo.write(servo.read());
    }

    Serial.print("sleeptime:::");

    Serial.println(sleeptime);
    Serial.print("servodegrees:::");
    Serial.println(servodegrees);

    // Serial.println((millis() - lastmillis));
}

void lcd_print(int sleeptime, int servodegrees, bool servoon)
{
    lcd.setCursor(0,1);
    lcd.print("Sleeptime:");
    lcd.print(sleeptime);

    lcd.setCursor(0,2);
    lcd.print("ServoD:");
    lcd.print(servodegrees);

    lcd.setCursor(0,3);
    lcd.print(" ServoOn:");
    lcd.print(servoon);
}