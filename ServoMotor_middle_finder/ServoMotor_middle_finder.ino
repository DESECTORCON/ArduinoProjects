#include <Servo.h>
Servo servo;
void setup() {
  // put your setup code here, to run once:
  servo.attach(10);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0;i<=180;i++) {
    servo.write(i);
    Serial.println(i);delay(150);
  }
}
