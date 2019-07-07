int slide = 0;

boolean left = false;
boolean middle = false;
boolean right = false;

const int leftEchoPin = 3;
const int leftTriggerPin = 2;
const int middleEchoPin = 5;
const int middleTriggerPin = 4;
const int rightEchoPin = 7;
const int rightTriggerPin = 6;

const int ledPin = 13;
const int leftLed = 10;
const int middleLed = 11;
const int rightLed = 12;

const int maxD = 20; //cm

long int lastTouch = -1;
int resetAfter = 2000;
int afterSlideDelay = 500;
int afterSlideOppositeDelay = 1500;

int SLIDELEFT_BEGIN = -1;
int SLIDELEFT_TO_CENTER = -2;

int SLIDENONE = 0;

int SLIDERIGHT_BEGIN = 1;
int SLIDERIGHT_TO_CENTER = 2;


void setup() {
      Serial.begin(9600);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(middleTriggerPin, OUTPUT);
  pinMode(middleEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  pinMode(leftLed, OUTPUT);
  pinMode(middleLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  left = ping(leftEchoPin, leftTriggerPin, leftLed);
  middle = ping(middleEchoPin, middleTriggerPin, middleLed);
  right = ping(rightEchoPin, rightTriggerPin, rightLed);
  if (left || middle || right) {
    lastTouch=millis();
  }

  if (millis()-lastTouch>resetAfter ) {
    slide=0;
    digitalWrite(ledPin, LOW);
    // Serial.println("Reset slide and timer. ");
  }

  if (slide >= SLIDENONE) { // only if we are not already in opposite move
    if ( (left) && (!right) )
      slide = SLIDERIGHT_BEGIN;
    if (middle && (slide == SLIDERIGHT_BEGIN))
      slide = SLIDERIGHT_TO_CENTER;
    if (right && (slide == SLIDERIGHT_TO_CENTER))
      slideNow('R');
  }

  if (slide <= SLIDENONE) {    
    if (right && (!left))
      slide = SLIDELEFT_BEGIN;
    if (middle && slide == SLIDELEFT_BEGIN)
      slide = SLIDELEFT_TO_CENTER;
    if (left && slide == SLIDELEFT_TO_CENTER) {
      slideNow('L');
    }
  }
  delay(50);
}


boolean ping(int echoPin, int pingPin, int ledPin_)
{
  int d = getDistance(pingPin, echoPin);
  boolean pinActivated = false;
  if (d < maxD) {
    digitalWrite(ledPin_, HIGH);
    pinActivated = true;
  } else {
    digitalWrite(ledPin_, LOW);
    pinActivated = false;
  }
}

int getDistance(int pingPin, int echoPin)
{
  long duration, inches, cm;

  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  return (cm);

}
void slideNow(char direction) {
  if ('R' == direction) 
     Serial.println("F");
  if ('L' == direction)
     Serial.println("B");
  digitalWrite(ledPin, HIGH);
  delay(afterSlideDelay); s
  slide = SLIDENONE;
}



long microsecondsToInches (long microseconds) {
  return (microseconds / 2) / 74;
}

long microsecondsToCentimeters(long microseconds) {
  return (microseconds / 2) / 29.1;
}
