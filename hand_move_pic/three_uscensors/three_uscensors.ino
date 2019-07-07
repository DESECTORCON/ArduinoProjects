const int leftEchoPin = 3;
const int leftTriggerPin = 2;
const int middleEchoPin = 5;
const int middleTriggerPin = 4;
const int rightEchoPin = 7;
const int rightTriggerPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(middleTriggerPin, OUTPUT);
  pinMode(middleEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Left: ");
  Serial.println(getDistance(leftTriggerPin, leftEchoPin));
  Serial.print("Middle: ");
  Serial.println(getDistance(middleTriggerPin, middleEchoPin));
  Serial.print("Right: ");
  Serial.println(getDistance(rightTriggerPin, rightEchoPin));
  Serial.println();
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
