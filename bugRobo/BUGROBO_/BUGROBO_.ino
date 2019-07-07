#include <MsTimer2.h>
#include <Servo.h>

Servo frontServo;
Servo rearServo;

int centerPos = 90;
int frontRightUp = 72;
int frontLeftUp = 108;
int backRightForward = 75;
int backLeftForward = 105;
int walkSpeed = 100;
int centerTurnPos = 81;
int frontTurnRightUp = 63;
int frontTurnLeftUp = 117;
int backTurnRightForward = 66;
int backTurnLeftForward = 96;

const int trigPin = 8;
const int echoPin = 4;
const int statusLED = 13;
long int duration, distanceInches;
long distanceFront = 0;//cm
int startAvoidanceDistance = 25;//cm
bool isTurning = false;

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

long distanceCm(){
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distanceInches = microsecondsToInches(duration);

return microsecondsToCentimeters(duration);
}

void ledControler()
{
  if (isTurning) {
    digitalWrite(statusLED, HIGH);
    delay(200);
    digitalWrite(statusLED, LOW);
  }else {
    digitalWrite(statusLED, HIGH);
  }
}

void siybdControler()
{
  if (isTurning) {
    tone(11, 1000, 100);
  }else {
    tone(11, 0, 100);
  }
}


void conter() {
  frontServo.write(centerPos);
  rearServo.write(centerPos);
}

void moveForward()
{
  frontServo.write(frontRightUp);
  rearServo.write(backLeftForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  frontServo.write(frontLeftUp);
  rearServo.write(backRightForward);
  delay(125);

  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  
}

void moveBackRight()
{
  frontServo.write(frontRightUp);
  rearServo.write(backRightForward-6);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos-6);
  delay(65);
  frontServo.write(frontLeftUp+9);
  rearServo.write(backLeftForward-6);
  delay(125);
  
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);

  
}

void moveTurnLeft()
{
  frontServo.write(frontTurnRightUp);
  rearServo.write(backTurnLeftForward);
  delay(125);
  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);
  delay(65);
  frontServo.write(frontTurnLeftUp);
  rearServo.write(backTurnRightForward);
  delay(125);
  
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
}

void setup() {
  frontServo.attach(2);
  rearServo.attach(3);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(3000);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(statusLED, OUTPUT);

  MsTimer2::set(350,ledControler);
  MsTimer2::start();

}

void loop() {
  distanceFront = distanceCm();
  if (distanceFront > 1) {

    if (distanceFront<startAvoidanceDistance){
      isTurning = true;
      
      for (int i=0; i<=75; i++) {
        moveBackRight();
        delay(walkSpeed);
      }

      for (int i=0; i<=50; i++) {
        moveTurnLeft();
        delay(walkSpeed);
      }
      
    }else {
      isTurning = false;
      moveForward();
      digitalWrite(13, HIGH);
      delay(walkSpeed);
    }
    
  }

}
