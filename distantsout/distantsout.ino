const int out=12;
const int in=13;
const int motorPin = 5;
long int duration, distanceInches, distanceCm;
int limitCm = 60;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(out, OUTPUT);
  pinMode(in, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(out,LOW);
  delayMicroseconds(2);

  digitalWrite(out,HIGH);
  delayMicroseconds(10);
  digitalWrite(out,LOW);

  duration = pulseIn(in,HIGH);

  distanceCm = microsecondsToCentimeters(duration);
  char p[8];

  sprintf(p, "%4d cm", distanceCm);
  Serial.println(p);
  checkLimit();
  delay(100);
  
}

void checkLimit()
{

  if (distanceCm < limitCm) {
    digitalWrite(motorPin, HIGH);
  }else {
    digitalWrite(motorPin, LOW);
  }
  
}

long microsecondsToInches (long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}