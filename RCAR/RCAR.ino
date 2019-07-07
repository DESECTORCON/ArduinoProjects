#include <Servo.h>

int status_ok_led = 5;
int status_nk_led = 4;


int trigPin = 3;
int echoPin = 2;
long duration, distance;

Servo servoL;
Servo servoR;

void setup() {
  Serial.begin(9600);
  Serial.println("sys starting");
  servoR.attach(8);
  servoL.attach(7);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(status_ok_led, OUTPUT);
  pinMode(status_nk_led, OUTPUT); servoL.write(80);
  servoR.write(100);
  Serial.println("sys starting - sucess");
}
void loop() {
  //   put your main code here, to run repeatedly:

  Serial.println("sys getting distance");
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println("sys distance complete");

  if (distance <= 30) {
    Serial.println("sys object dected");
    servoL.write(100);
    servoR.write(80);
    Serial.println("sys backing up");
    delay(1000);
    Serial.println("sys wait complete");
    servoL.write(100);
    servoR.write(100);
    delay(1000);
    Serial.println("sys complete backing up");
    servoL.write(80);
    servoR.write(100);
  }


}
