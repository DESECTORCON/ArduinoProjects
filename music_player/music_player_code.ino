void setup() {
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:2
  if (digitalRead(11) == LOW) {
    Serial.print("S");
    delay(100);
  }
  if (digitalRead(12) == LOW) {
    Serial.print("P");
    delay(100);
  }
  if (digitalRead(10) == LOW) {
    Serial.print('Q');
    delay(100);
  }
  delay(50);
}