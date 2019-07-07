int ledPins[7] = { 2,3,4,5,7,8,6 };
int dicePatterns[7][7] = {
  {0,0,0,0,0,0,1},
  {0,0,1,1,0,0,0},
  {0,0,1,1,0,0,1},
  {1,0,1,1,0,1,0},
  {1,0,1,1,0,1,1},
  {1,1,1,1,1,1,0},
  {0,0,0,0,0,0,0}
};

int switchPin = 9;
int blank = 6;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i=0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
  pinMode(switchPin, INPUT_PULLUP);
  randomSeed(analogRead(0));

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(switchPin) == LOW){
    Serial.println("ROLL!!!");
    Serial.println(digitalRead(switchPin));
    rollTheDice();
  }
  delay(100);
  
}


void rollTheDice() {
  int result = 0;
  int lengthOfRoll = random(30, 50);

  for (int i=0; i < lengthOfRoll; i++)
  {

    result = random(0,6);
    show(result);
    if ( lengthOfRoll - i <  10) { delay(10 + i * 20); }
    else { delay(10 + i * 5); }
    
  }

  for (int j = 0; j< 5; j++)
  {

    show(blank);
    delay(500);
    show(result);
    delay(500);
    
  }
  
}


void show(int result) 
{

  for (int i=0; i<7; i++)
  {

    digitalWrite(ledPins[i], dicePatterns[result][i]);
    
  }
  
}
