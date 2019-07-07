#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 9, 10, 11, 12);

int left = A0;
int right = A3;
int up = A2;
int down = A1;

int trigPin = 5;    // Trigger
int echoPin = 6;    // Echo
long duration, cm, inches;
int count = 0;

int lastCm;
int obj = 10;

Servo LR;
Servo UD;

void setup() {
  // put your setup code here, to run once:
  LR.attach(8);
  UD.attach(7);

  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  lcd.begin(4, 16);
  lcd.clear();
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  if (digitalRead(left) == LOW) {
    LR.write(180);
    Serial.print("BTLEFT");
  }
  if (digitalRead(right) == LOW) {
    LR.write(0);
    Serial.print("BTLEFT");
  }
  if (digitalRead(up) == LOW) {
    UD.write(180);
    Serial.print("BTLEFT");
  }
  if (digitalRead(down) == LOW) {
    UD.write(0);
    Serial.print("BTLEFT");
  }
  if ((digitalRead(left) != LOW) &  (digitalRead(right) != LOW) & (digitalRead(up) != LOW) & (digitalRead(down) != LOW)) {
    Serial.print("BTSTOP");
    UD.write(90); LR.write(90);
  }


  if (count >= 2) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
    

    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    lcd.setCursor(0, 1);
    lcd.print("Dist: ");
    lcd.print(cm);
    lcd.print("  Cm");

    if (((lastCm - cm) > obj )|| ((cm-lastCm) > obj )){
      lcd.setCursor(1,2);
      lcd.print("OBJ dected!");
      tone(13, 1000);
    }else {
      lcd.setCursor(1,2);
      lcd.print("                ");
      noTone(13);
    }
    lastCm = cm;
    count = 0;
  }
  delay(50);
  count ++;

}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
