#include <Servo.h>

static int buttonPin = 2;
static int timebuttonpin = 3;
int mode = 0;
int timemode = 0;
int sleeptime = 1000;
int delaytime = 1000;
unsigned long lastmillis = millis();
boolean servo_direction = true;

Servo servo;

void setup()
{
    pinMode(buttonPin, INPUT);
    pinMode(timebuttonpin, INPUT);
    servo.attach(12);
    servo.write(90);
    Serial.begin(9600);
}

void loop()
{
    if (digitalRead(buttonPin) == HIGH)
    {
        mode++;
        if (mode >= 3)
        {
            mode = 0;
        }
        switch (mode)
        {
        case 0:
            delaytime = 500;
            break;
        case 1:
            delaytime = 800;
            break;
        case 2:
            delaytime = 1000;
            break;
        case 3:
            delaytime = 1200;
            break;
        default:
            delaytime = 0;
            break;
        }
        delay(500);
    }

    if (digitalRead(timebuttonpin) == HIGH)
    {
        timemode++;
        if (timemode >= 3)
        {
            timemode = 0;
        }
        switch (timemode)
        {
        case 0:
            sleeptime = 300;
            break;
        case 1:
            sleeptime = 500;
            break;
        case 2:
            sleeptime = 700;
            break;
        case 3:
            sleeptime = 1500;
            break;
        }
        delay(500);
    }

    if ((millis() - lastmillis) >= delaytime)
    {
        Serial.println("Movment");
        Serial.print("--------------------");
        servo_direction = !servo_direction;
        // servo.write(180);
        lastmillis = millis();
        // Serial.println("asdf");
        servo.write(90);
        delay(sleeptime);
    }
    // else
    // {
    //     servo_direction = !servo_direction;
    //     // servo.write(0);
    //     // Serial.println("ASDF");
    //     delay(100);ƒ
    // }

    if (servo_direction){
        servo.write(180);
    }else {
        servo.write(0);
    }
    Serial.print("sleeptime:::");

    Serial.println(sleeptime);
    Serial.print("delaytime:::");
    Serial.println(delaytime);

    // Serial.println((millis() - lastmillis));
}