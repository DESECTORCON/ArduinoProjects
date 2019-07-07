#include <Servo.h>
#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

int lastmillis = 0;
boolean servo_wich = true;

Servo servo;
void setup() {
  Serial.begin(9600); // start the serial port
  pinMode(11, OUTPUT);
  servo.attach(5);
  servo.write(90);
}

void loop() {

  if ((millis() - lastmillis) > 5000){
    lastmillis = millis();
    if (servo_wich){
      servo.write(120);
    }else{
      servo.write(60);
    }
    servo_wich = !servo_wich;
  }
  
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(300); // slow down serial port 
  
    Serial.println(distance);   // print the distance

  if (distance < 13){
    analogWrite(11, 250);
  }else {
    analogWrite(11, 0);
  }
}
