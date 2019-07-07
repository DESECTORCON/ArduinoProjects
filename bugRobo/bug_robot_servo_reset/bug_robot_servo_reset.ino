#include <Servo.h>

Servo frontServo;
Servo rearServo;

void setup() {
  // put your setup code here, to run once:
  frontServo.attach(2);
  rearServo.attach(3);
  frontServo.write(90);
  rearServo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
