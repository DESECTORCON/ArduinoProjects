const int out=12;
const int in=13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(out,OUTPUT);
  pinMode(in,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  long dur;
  long dis;

  digitalWrite(out,LOW);
  delayMicroseconds(2);

  digitalWrite(out,HIGH);
  delayMicroseconds(10);
  digitalWrite(out,LOW);

  dur=pulseIn(in,HIGH);

  Serial.print(microsecondsToCentimeters(dur));
  Serial.println();
  delay(1000);
}

long microsecondsToInches (long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
