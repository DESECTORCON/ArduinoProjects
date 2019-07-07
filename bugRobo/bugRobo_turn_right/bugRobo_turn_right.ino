#include <Servo.h>

Servo frontServo;
Servo rearServo;

int centerTurnPos = 81;
int frontTurnRightUp = 63;
int frontTurnLeftUp = 117;
int backTurnRightForward = 66;
int backTurnLeftForward = 96;

void moveTurnLeft() {
  frontServo.write(frontTurnRightUp);
  rearServo.write(backTurnLeftForward);

  delay(125);

  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);

  delay(65);

  frontServo.write(frontTurnLeftUp);
  rearServo.write(backTurnRightForward);

  delay(125);

  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);

  delay(65);
}

void setup() {
  // put your setup code here, to run once:
  frontServo.attach(2);
  rearServo.attach(3);
  frontServo.write(90);
  rearServo.write(90);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  moveTurnLeft();
  delay(200);
}
