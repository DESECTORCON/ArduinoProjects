#include <Servo.h>
Servo myServo;
void setup() {
  myServo.attach(2);
  myServo.write(90);

}

void loop() {
  delay(100);
}
