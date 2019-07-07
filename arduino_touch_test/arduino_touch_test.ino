void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == LOW){
    Serial.println("touch");
    delay(1000);
  }else{
    Serial.println("not touch");
  }
  
}
