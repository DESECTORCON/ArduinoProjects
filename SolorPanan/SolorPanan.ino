// Project 21 - VU Meter

int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int switchPin = 12;


void setup()                 
{
  for (int i = 0; i < 10; i++)
  {
     pinMode(ledPins[i], OUTPUT); 
  }
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()                   
{
  int value = analogRead(A5);
  int topLED = map(value, 0, 1023, 0, 12) - 1;
  for (int i = 0; i < 10; i++)
  {
      digitalWrite(ledPins[i], (i <= topLED));
  }
  float voltage = value * (5.0 / 1024.0);
  // write the voltage value to the serial monitor:
  Serial.println(voltage);
//  Serial.println(value);
  delay(10);
}
