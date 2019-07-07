const int leftEchoPin = 3;
const int leftTriggerPin = 2;
const int middleEchoPin = 5;
const int middleTriggerPin = 4;
const int rightEchoPin = 7;
const int rightTriggerPin = 6;
const int leftLed = 10;
const int middleLed = 11;
const int rightLed = 12;
const int maxD = 20; //cm

void setup() {
    Serial.begin(9600);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(middleTriggerPin, OUTPUT);
  pinMode(middleEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  pinMode(leftLed, OUTPUT);
  pinMode(middleLed, OUTPUT);
  pinMode(rightLed, OUTPUT);

}

void loop() {
  ping(leftEchoPin, leftTriggerPin, leftLed);
  ping(middleEchoPin, middleTriggerPin, middleLed);
  ping(rightEchoPin, rightTriggerPin, rightLed);
  delay(50);

}

boolean ping(int echoPin, int pingPin, int ledPin)
{
  int d = getDistance(pingPin, echoPin);
  boolean pinActivated = false;
  if (d < maxD) {
    digitalWrite(ledPin, HIGH);
    pinActivated = true;
  } else {
    digitalWrite(ledPin, LOW);
    pinActivated = false;
  }
}

int getDistance(int pingPin, int echoPin)
{
  long duration, inches, cm;

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  return (cm);

}




long microsecondsToInches (long microseconds) {
  return (microseconds / 2) / 74;
}

long microsecondsToCentimeters(long microseconds) {
  return (microseconds / 2) / 29.1;
}
