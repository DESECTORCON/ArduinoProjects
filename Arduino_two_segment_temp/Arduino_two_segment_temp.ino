// which analog pin to connect
#define THERMISTORPIN A6
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000
uint16_t samples[NUMSAMPLES];
#define piezoPin 7
#define left 11
#define right 12
#define blue 10
#define red 9

int segmentPins[] = {3, 2, A5, A2, A4, 4, 5, A3};
int displayPins[] = {A1, 6};
int settingTemp = 20;

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

void setup()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(displayPins[0], OUTPUT);
  pinMode(displayPins[1], OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(piezoPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
  //  analogReference(EXTERNAL);
}

void loop()
{
  static int digit1;
  static int digit2;
  int temp;
  int x;
  int y;
  temp = getTemp();
  x = (temp / 10);
  y = (temp - ((temp / 10) * 10));
  updateDisplay(x, y);

  if (digitalRead(buttonPin) == LOW) {
    tone(piezoPin, 1000, 500);
    delay(600);
    while (true) {
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      //      Serial.println("INLOOW");
      x = (settingTemp / 10);
      y = (settingTemp - ((settingTemp / 10) * 10));
      if (digitalRead(left) == LOW) {
        settingTemp = settingTemp - 1;
        delay(100);
      }
      if (digitalRead(right) == LOW) {
        settingTemp = settingTemp + 1;
        delay(100);
      }

      if (digitalRead(buttonPin) == LOW) {
        updateDisplay(8, 8);
        delay(500);
        tone(piezoPin, 1000, 500);
        delay(600);
        tone(piezoPin, 500, 500);
        delay(600);
        break;

      }

      updateDisplay(x, y);
    }
  }
  if (temp >= settingTemp) {
    digitalWrite(blue, HIGH);
    digitalWrite(red, LOW);
  } else {
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
  }



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


int getTemp() {
  uint8_t i;
  float average;

  // take N samples in a row, with a slight delay
  for (int i = 0; i < NUMSAMPLES; i++) {
    samples[i] = analogRead(THERMISTORPIN);
    delay(1);
  }

  // average all the samples out
  average = 0;
  for (int i = 0; i < NUMSAMPLES; i++) {
    average += samples[i];
  }
  average /= NUMSAMPLES;

  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  float steinhart;
  steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;
  // convert to C

  steinhart = round(steinhart);
  //  steinhart = steinhart * 100;

  Serial.print("Temperature ");
  Serial.print(steinhart);
  Serial.println(" *C");
  return steinhart;
}
