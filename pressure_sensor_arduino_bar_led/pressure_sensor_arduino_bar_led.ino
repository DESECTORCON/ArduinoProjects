int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int led1 = 13;
int led2 = 10;
int led3 = 9;
int led4 = 8;
int led5 = 7;
int led6 = 6;
int led7 = 5;
int led8 = 4;
int led9 = 3;
int numleds;
int ledArray[9] = {led1 ,led2 ,led3 ,led4 ,led5 ,led6 ,led7 ,led8 ,led9};
int brightness_sensor = A1;
int lamp = 11;
int laston = 0;

 
void setup(void) {
  // We'll send debugging information via the //Serial monitor
  Serial.begin(9600);   
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(lamp, OUTPUT);
}
 
void loop(void) {
  int fsrReading = analogRead(fsrPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (fsrReading < 10) {
    Serial.println(" - No pressure");
  } else if (fsrReading < 50){
    ledCrontol(1,0,0,0,0,0,0,0,0);
//    digitalWrite(ledArray[0], HIGH);
  }
  else if (fsrReading < 100){
//    digitalWrite(ledArray[1], HIGH);
    ledCrontol(1,1,0,0,0,0,0,0,0);
  }
  else if (fsrReading < 150){
//    digitalWrite(ledArray[2], HIGH);
    ledCrontol(1,1,1,0,0,0,0,0,0);
  }
  else if (fsrReading < 200) {
    Serial.println(" - Light touch");
    ledCrontol(1,1,1,1,0,0,0,0,0);
    
//    digitalWrite(ledArray[3], HIGH);
  }
  else if (fsrReading < 300){
//    digitalWrite(ledArray[4], HIGH);
      ledCrontol(1,1,1,1,1,0,0,0,0);
      analogWrite(lamp, 200);
  }
  else if (fsrReading < 400) {
//    digitalWrite(ledArray[5], HIGH);
    ledCrontol(1,1,1,1,1,1,1,0,0);
  }
  else if (fsrReading < 500) {
    Serial.println(" - Light squeeze");
//    digitalWrite(ledArray[6], HIGH);
    ledCrontol(1,1,1,1,1,1,1,1,0);
  }
  else if (fsrReading < 700){
    digitalWrite(ledArray[7], HIGH);
  }
  else if (fsrReading < 800) {
    Serial.println(" - Medium squeeze");
//    digitalWrite(ledArray[8], HIGH);
    ledCrontol(1,1,1,1,1,1,1,1,1);
  } 
  else {
    Serial.println(" - Big squeeze");
//    digitalWrite(ledArray[9], HIGH);
    ledCrontol(1,1,1,1,1,1,1,1,1);
  }
  if (fsrReading > 150){
      int laston = millis();
      int value = analogRead(A2);
      value = map(value, 0, 1023, 0, 255);
      analogWrite(lamp, value);
  }
  if (laston + 100000 < millis()) {
    analogWrite(lamp, 0);
  }
  delay(10);
  Serial.println(millis());
  Serial.println(laston);
} 

void ledCrontol(int l1, int l2, int l3, int l4, int l5, int l6, int l7, int l8, int l9){
  
  digitalWrite(ledArray[0], l1);
  digitalWrite(ledArray[1], l2);
  digitalWrite(ledArray[2], l3);
  digitalWrite(ledArray[3], l4);
  digitalWrite(ledArray[4], l5);
  digitalWrite(ledArray[5], l6);
  digitalWrite(ledArray[6], l7);
  digitalWrite(ledArray[7], l8);
  digitalWrite(ledArray[8], l9);
}
