#include <Servo.h>
#define delay_time 500

Servo servo;
void setup() {
  servo.attach(12);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int coupler = analogRead(A5);
  Serial.print("Analog Input: ");
  Serial.println(coupler);
  if (coupler > 800) {
    //        delay(500);
    for (int i = 0; i < 3; i++) {
      if (analogRead(A5) < 60) {
        break;
      }
      Serial.print("LOOPSTATUS:::");
      Serial.println(i);
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    if (analogRead(A5) > 800) {
      Serial.println("ON");
      servo.write(180);
      delay(delay_time);
      servo.write(90);

      while (true) {
        int coupler = analogRead(A5);
        if (coupler < 40) {
          //          delay(5000); ---25
          for (int i = 0; i < 5; i++) {
            if (analogRead(A5) > 800) {
              break;
            }
            Serial.print("LOOPSTATUS:::");
            Serial.println(i);
            digitalWrite(13, HIGH);
            delay(100);
            digitalWrite(13, LOW);
            delay(100);
          }
          if (analogRead(A5) < 60) {
            Serial.println("OFF");
            servo.write(0);
            delay(delay_time);
            servo.write(90);
            break;
          }
        }
      }
    }
  }
  //  Serial.println(analogRead(A5));
  //  delay(10);
}
