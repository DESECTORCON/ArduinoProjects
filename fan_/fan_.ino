#include <Servo.h>
int ThermistorPin = 3;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

// Project 23 - Computer Controlled Fan
int motorPin = 11;
int motorPin2 = 3;

int fanMode = 0;

int servoPin = 10;
Servo servo;

int aPin = A1;
int bPin = A2;
int buttonPin = A0;

int histeresis = 5;

int servoM = 0;

int speed, lastSpeed;
void setup()
{
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
  pinMode(motorPin2, OUTPUT);
  analogWrite(motorPin2, 0);
  Serial.begin(9600);

  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  servo.attach(10);
  servo.write(90);
  randomSeed(A5);
}

void loop()
{

  //  if (Serial.available())
  //  {
  //    char ch = Serial.read();
  //    if (ch >= '0' && ch <= '9')
  //    {
  //      speed = ch - '0';
  //      if (speed == 0)
  //      {
  //        analogWrite(motorPin, 0);
  //      }
  //      else
  //      {
  //        analogWrite(motorPin, 600 + speed * 20);
  //      }
  //    }
  //    Serial.println("SEIR");
  //  }
  //  Serial.println(speed);

  fanTemp();
  int change = getEncoderTurn();
  Serial.println(change);
  if (servoM == 0) {
    int value = servo.read();
    servo.write(value - (change * 5));
  } if (servoM == 1) {
    //    Serial.println(change);
    speed = speed + change;

    if (speed < 0)
    {
      speed = 0;
    }

    if (speed > 8)
    {
      speed = 8;
    }

    if (speed != lastSpeed)
    {

      if (speed == 0)
      {
        analogWrite(motorPin, 0);
      }
      else
      {
        analogWrite(motorPin, 600 + speed * 20);
        lastSpeed = speed;
      }
    }

  }

  if (servoM == 3) {
    while (digitalRead(buttonPin) != LOW) {
      fanTemp();
      int value = servo.read();
      Serial.println(value);
      servo.write(value + 1);
      delay(100);
      if (value > 160) {
        while (digitalRead(buttonPin) != LOW) {
          fanTemp();
          Serial.println(servoM);
          int value = servo.read();
          servo.write(value - 1);
          if (value < 20) {
            break;
          }
          delay(100);
        }
      }
    }
  }

  if (servoM == 4) {
    speed = 150;
    servo.write(90);
    while (digitalRead(buttonPin) != LOW) {
      fanTemp();
      int value = servo.read();
      Serial.println(value);
      servo.write(value + 3);
      delay(100);
      if (value > 160) {
        while (digitalRead(buttonPin) != LOW) {
          fanTemp();
          Serial.println(servoM);
          int value = servo.read();
          servo.write(value - 3);
          if (value < 20) {
            break;
          }
          delay(100);
          if (random(1, 3) == 2) {
            analogWrite(motorPin, speed + random(-100, 100));
          }
        }
      }
      if (random(1, 3) == 2) {
        analogWrite(motorPin, speed + random(-80, 80));
      }
      delay(random(10 , 500));

    }
  }

  if (digitalRead(buttonPin) == LOW) {
    servoM = servoM + 1;

    if (servoM > 4) {
      servoM = 0;
    }

    delay(300);
  }
  Serial.println(servoM);
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
  Serial.print(oldA);
  Serial.print(oldB);
  return result;

}

void fanTemp() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  Tc = T - 273.15;
  //  Tf = (Tc * 9.0) / 5.0 + 32.0;

  //  Serial.print("Temperature: ");
  //  //  Serial.print(Tf);
  //  //  Serial.print(" F; ");
  //  Serial.print(Tc);
  //  Serial.println(" C");

  if (Tc > 100) {
    if (fanMode != 1) {
      analogWrite(3, 255);
      delay(10);
    }
    fanMode = 1;
    analogWrite(3, 100);
  } if (Tc > 103) {
    if (fanMode != 2) {
      analogWrite(3, 255);
      delay(10);
    }
    fanMode = 2;
    analogWrite(3, 255);
    delay(10);
    analogWrite(3, 150);
  } if (Tc > 110) {
    if (fanMode != 3) {
      analogWrite(3, 255);
      delay(10);
    }
    fanMode = 3;
    analogWrite(3, 255);
    delay(10);
    analogWrite(3, 250);
  }

  if (Tc < 95) {
    fanMode = 0;
    analogWrite(3, 0);
  }
}
