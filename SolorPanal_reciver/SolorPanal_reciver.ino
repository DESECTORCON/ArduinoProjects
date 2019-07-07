#include <SoftwareSerial.h>

SoftwareSerial No2Arduino(8, 9);
int segmentPins[] = {3, 2, A5, A2, A4, 4, 5, A3}; 
int displayPins[] = {A1, 6};

boolean onRoll = false;

int buttonPin = A0;

byte digits[10][8] = {
//  a  b  c  d  e  f  g  .
  { 1, 1, 1, 1, 1, 1, 0, 1},  // 0
  { 0, 1, 1, 0, 0, 0, 0, 1},  // 1
  { 1, 1, 0, 1, 1, 0, 1, 1},  // 2
  { 1, 1, 1, 1, 0, 0, 1, 1},  // 3
  { 0, 1, 1, 0, 0, 1, 1, 1},  // 4
  { 1, 0, 1, 1, 0, 1, 1, 1},  // 5
  { 1, 0, 1, 1, 1, 1, 1, 1},  // 6
  { 1, 1, 1, 0, 0, 0, 0, 1},  // 7
  { 1, 1, 1, 1, 1, 1, 1, 1},  // 8  
  { 1, 1, 1, 1, 0, 1, 1, 1}  // 9  
};
   
void setup() {
  // put your setup code here, to run once:
    for (int i=0; i < 8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
  No2Arduino.begin(9600);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int vol = round(No2Arduino.read());
  int x = (vol / 10);
  int y = (vol - ((vol / 10) * 10));
  updateDisplay(x, y);
  Serial.println(vol);
  delay(100);
}


void updateDisplay(int value1, int value2)
{
  digitalWrite(displayPins[0], HIGH);
  digitalWrite(displayPins[1], LOW);
  setSegments(value2);
  delay(5);
  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], HIGH);
  setSegments(value1);
  delay(5);

  digitalWrite(displayPins[0], LOW);
  digitalWrite(displayPins[1], LOW);
}

void setSegments(int n)
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(segmentPins[i], ! digits[n][i]);
  }
}
