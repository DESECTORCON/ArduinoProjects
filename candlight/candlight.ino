boolean on  = true;
const int ldrPin = A0;
const int blue = 10;
const int red = 9;
const int green = 5;
const int touch = 6;

void setup()
{
    Serial.begin(9600);
    pinMode(blue, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(touch, INPUT);
    randomSeed(analogRead(A6));
    // color orange
    // analogWrite(red, 255);
    // analogWrite(blue, 100);
    // analogWrite(green, 252);
    
}
void loop()
{
    int brightness = analogRead(ldrPin);
    if (on)
    {

        brightness = constrain(brightness, 400, 900);
        if (brightness > 800){
            analogWrite(red, 250);
            analogWrite(blue, 230);
            analogWrite(green, 200); 
        } else {
             int blueout = map(brightness, 1, 900, 245, 1);
        int redout = map(brightness, 1, 900, 255, 1);
        int greenout = map(brightness, 1, 900, 245, 1);
        analogWrite(red, redout);
        analogWrite(blue, blueout);
        analogWrite(green, greenout);
        }
       


        Serial.println(brightness);
        // if (brightness < 300){
        //     analogWrite(red, 0);
        //     analogWrite(blue, 0);
        //     analogWrite(green, 0);
        // }
        //  if (300 <= brightness <= 400) {
        //     analogWrite(red, 5);
        //     analogWrite(blue, 255);
        //     analogWrite(green, 212);
        // }
        // if (400< brightness <= 500){
        //     analogWrite(red, 5);
        //     analogWrite(blue, 255);
        //     analogWrite(green, 212);
        // }
        //  if (500 < brightness <= 700) {
        //     analogWrite(red, 4);
        //     analogWrite(blue, 200);
        //     analogWrite(green, 170);
        // }
        //  if (700 < brightness) {
        //     analogWrite(red, 3);
        //     analogWrite(blue, 150);
        //     analogWrite(green, 120);
        // }        
    }
    else{
        analogWrite(red, 0);
        analogWrite(blue, 0);
        analogWrite(green, 0);
    }
    if (digitalRead(touch) == HIGH){
        on = !on;
        delay(500);
    }
    delay(100);
        
    
}