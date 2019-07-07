const int echoPing = 3;
const int triggerPing = 2;

void setup() {
  Serial.begin(9600);
  pinMode(echoPing, INPUT);
  pinMode(triggerPing, OUTPUT);
}

void loop() {
  long duration, inches, cm;

  digitalWrite(triggerPing, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(triggerPing, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPing, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPing, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(10);

}

long microsecondsToInches (long microseconds) {
  return (microseconds / 2) / 74;
}

long microsecondsToCentimeters(long microseconds) {
  return (microseconds / 2) / 29.1;
}
