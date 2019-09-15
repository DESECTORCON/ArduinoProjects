#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TimedAction.h>

static int buttonPin = 2;
static int timebuttonpin = 3;
int mode = 0;
int timemode = 0;
int sleeptime = 1;
int servodegrees = 10;

unsigned long lastmillis = millis();
boolean servo_direction = true;
boolean servoon = true;

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo servo;

void checkdegrees()
{
    if (digitalRead(buttonPin) == HIGH)
    {
        mode++;
        if (mode >= 5)
        {
            mode = 0;
        }
        servoon = true;
        switch (mode)
        {
        case 0:
            servodegrees = 20;
            break;
        case 1:
            servodegrees = 34;
            break;
        case 2:
            servodegrees = 60;
            break;
        case 3:
            servodegrees = 100;
            break;
        case 4:
            servoon = false;
            break;
        }
        lcd_print(sleeptime, servodegrees, servoon);
        delay(100);
    }
}

void checksleep()
{
    if (digitalRead(timebuttonpin) == HIGH)
    {
        sleeptime = sleeptime + 2;
        if (sleeptime > 100)
        {
            sleeptime = 10;
        }
        lcd_print(sleeptime, servodegrees, servoon);
        delay(100);
    }
}
TimedAction checkdegreesThread = TimedAction(110, checkdegrees);
TimedAction checksleepThread = TimedAction(110, checksleep);

void checkthread()
{
    checkdegreesThread.check();
    checksleepThread.check();
}

void setup()
{
    lcd.init();      // lcd를 사용을 시작합니다.
    lcd.backlight(); // backlight를 On 시킵니다.
    lcd.setCursor(0, 0);
    lcd.print("FanControl");

    pinMode(buttonPin, INPUT);
    pinMode(timebuttonpin, INPUT);
    servo.attach(12);
    servo.write(90);
    Serial.begin(9600);
}

void loop()
{
    checkthread();
    if (servoon)
    {
        if (servo_direction)
        {

            for (int i = 0; servodegrees >= i; i++)
            {
                checkthread();
                servo.write(servo.read() + 2);
                delay(sleeptime);
            }

            servo_direction = !servo_direction;
        }
        else
        {
            for (int i = 0; servodegrees >= i; i++)
            {
                checkthread();
                servo.write(servo.read() - 2);
                delay(sleeptime);
            }
            servo_direction = !servo_direction;
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
    lcd.setCursor(0, 1);
    lcd.print("                   ");
    lcd.setCursor(0, 1);
    lcd.print("Sleeptime:");
    lcd.print(sleeptime);

    lcd.setCursor(0, 2);
    lcd.print("                   ");
    lcd.setCursor(0, 2);
    lcd.print("ServoD:");
    lcd.print(servodegrees);

    lcd.setCursor(0, 3);
    lcd.print(" ServoOn:");
    lcd.print(servoon);
}