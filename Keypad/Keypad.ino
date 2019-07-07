#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>  //add '<' and '>' before and after servo.h

int servoPin = A0;

//              0     1   2    3    4    5    6    7    8    9
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//            mid C  C#   D    D#   E    F    F#   G    G#   A
const int speakerPin = 11;
//
//boolean waitandstop = false;
//
//char* numbers = "1234567890*#";

String secretCode = "1234567890";
//int position_ =  0;

boolean lock = true;

String keysPressed;

const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[rows] = {7, 2, 3, 5};
byte colPins[cols] = {6, 8, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int redPin = 13;
int greenPin = 12;
int bluePin = 10;
int buttonPin = 9;

int last_time = 0;

int wrong_times = 0;

int secretcode1, secretcode2, secretcode3, secretcode4;
Servo lockmotor;

LiquidCrystal_I2C lcd(0x3F, 20, 4);

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  //  setLocked(true);
  //  secretCode = "";
  //  int index = EEPROM.read(1);
  //  Serial.println(index);
  //
  //  char code_;
  //
  secretcode1 = EEPROM.read(4);
  //  Serial.println(secretcode1);

  secretcode2 = EEPROM.read(5);
  //  Serial.println(secretcode2);

  secretcode3 = EEPROM.read(6);
  //  Serial.println(secretcode3);

  secretcode4 = EEPROM.read(7);
  //  Serial.println(secretcode4);

  secretCode = String(secretcode4 + secretcode3 * 10 + secretcode2 * 100 + secretcode1 * 1000);
  //  Serial.println(secretCode);

  digitalWrite(redPin, HIGH);
  lockmotor.attach(servoPin);
  lockmotor.write(90);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Box locker™");
  lcd.setCursor(0, 1);
  lcd.print("Currant Status: ");
  lcd.setCursor(0, 2);
  lcd.print("Password: ");


}

void loop() {
  // put your main code here, to run repeatedly:
  int this_time = millis();
  if ((this_time - last_time) > 10000) {
    lcd.setCursor(0, 3);
    lcd.print("                   ");
    last_time = this_time;
  }

  if (Serial.available()) {
    String string = Serial.readString();
    if (string == "rasberrypi connected") {
      lcd.setCursor(0, 3);
      lcd.print("rasberrypi connected");
    }
    //    else if (string == "message off") {
    //      lcd.setCursor(0, 3);
    //      lcd.print("                   ");
    //    }
    else if (string == "lock") {
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      lcd.setCursor(0, 3);
      lcd.print("Locked by MU");
      lockmotor.write(90);
      lcd.setCursor(16, 1);
      lcd.print("LOCK");
      lcd.setCursor(0, 0);
      lcd.print("Box locker™");
      setLocked(true);
      lcd.setCursor(0, 2);
      lcd.print("Password: ");
    }
    else if (string == "unlock") {
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      lcd.setCursor(0, 3);
      lcd.print("Unlocked by MU");
      lcd.setCursor(16, 1);
      lcd.print("OPEN");
      setLocked(false);
      lockmotor.write(180);
      lcd.setCursor(0, 0);
      lcd.print("Box locker™");
      lcd.setCursor(0, 2);
      lcd.print("Password: ");
    }
    else if (string == "powerlock") {

      lockmotor.write(90);
      lcd.setCursor(16, 1);
      lcd.print("LOCK");
      setLocked(true);
      lcd.setCursor(0, 0);
      lcd.print("Box locker™");
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      lcd.setCursor(0, 3);
      lcd.print("Powerlocked by MU");
      lcd.setCursor(0, 2);
      lcd.print("Password: ");
      while (true) {
        if (Serial.available()) {
          String string = Serial.readString();
          if (string == "unlock") {
            lcd.setCursor(0, 3);
            lcd.print("                   ");
            lcd.setCursor(0, 3);
            lcd.print("Unlocked by MU");
            lcd.setCursor(16, 1);
            lcd.print("OPEN");
            setLocked(false);
            lockmotor.write(180);
            lcd.setCursor(0, 2);
            lcd.print("Password: ");
            break;
          }
        }
      }
      lcd.setCursor(0, 0);
      lcd.print("Box locker™");
    }
    else if (string == "backlight off"){
      tone(speakerPin, 261, 300);
      lcd.noBacklight();  
      delay(200);
    }
    else if (string == "backlight on"){
      tone(speakerPin, 392, 300);
      lcd.backlight();
      delay(200);
    }
    
    //else {
    //      lcd.setCursor(0,3);
    //      lcd.print(Serial.readString());
    //    }
  }

  digitalWrite(bluePin, LOW);
  char key = keypad.getKey();
  //  Serial.println(secretCode);
  //  Serial.println(keysPressed);
  if (key == '*' && lock == true) {
    if (secretCode == keysPressed) {
      lcd.setCursor(16, 1);
      lcd.print("OPEN");
      setLocked(false);
      waitUntilKeyundo();
      lockmotor.write(180);
      Serial.println("Lockbox: OPENED");
    } else {
      stressSig();
      wrong_times ++;
    }
    keysPressed = "";
    if (wrong_times == 5) {
      Serial.println("wrong five times");
      wrong_times = 0;
      lcd.setCursor(0, 2);
      lcd.print("                   ");
      lcd.setCursor(0, 2);
      lcd.print("Wrong five times!");
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      lcd.setCursor(0, 3);
      lcd.print("Please wait a minute");
      delay(10000);
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      lcd.setCursor(0, 3);
      lcd.print("Forgot password?");
      delay(5000);
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      lcd.setCursor(0, 3);
      lcd.print("yes: press key *");
      int time_wait = 0;
      while (time_wait < 15000) {

        char key = keypad.getKey();
        if (key == '*') {
          tone(speakerPin, 900, 700);
          Serial.print("psw send: ");
          Serial.println(secretCode);
          lcd.setCursor(0, 3);
          lcd.print("                   ");
          lcd.setCursor(0, 3);
          lcd.print("Sent email with psw");
          delay(1000);
          break;
        }
        Serial.println(key);
        delay(1);
        time_wait ++;
      }
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 2);
      lcd.print("                   ");
      lcd.setCursor(0, 0);
      lcd.print("Box locker™");
      lcd.setCursor(0, 1);
      lcd.print("Currant Status: ");
      lcd.setCursor(0, 2);
      lcd.print("Password: ");
    }
  }
  if (key == '#') {
    lockmotor.write(90);
    lcd.setCursor(16, 1);
    lcd.print("LOCK");
    setLocked(true);
    keysPressed = "";
    waitUntilKeyundo();
    Serial.println("Lockbox: CLOSED");

  }

  if (digitalRead(buttonPin) == LOW && lock == false) {
    Serial.println("Lockbox: PSW CHANGE");
    lcd.setCursor(0, 3);
    lcd.print("SET NEW PASSWORD");
    digitalWrite(bluePin, HIGH);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    tone(speakerPin, tones[7], 200);
    delay(250);
    tone(speakerPin, tones[0], 200);
    delay(250);
    tone(speakerPin, tones[4], 200);
    delay(100);
    keysPressed = "";
    while (true) {
      Serial.println(keysPressed);

      char key = keypad.getKey();
      if (key != NO_KEY) {
        digitalWrite(bluePin, HIGH);
        tone(speakerPin, tones[9], 100);
        if (key == '*' || key == '#') {}
        else {
          keysPressed = keysPressed + key;
        }
        waitUntilKeyundo();

      }

      if (digitalRead(buttonPin) == LOW) {
        break;
      }

      if (keysPressed.length() > 4) {
        tone(speakerPin, tones[1], 500);
        break;
      }
      if (keysPressed.length() == 1) {
        lcd.setCursor(10, 2);
        lcd.print("*");
      } else if (keysPressed.length() == 2) {
        lcd.setCursor(10, 2);
        lcd.print("**");
      }
      else if (keysPressed.length() == 3) {
        lcd.setCursor(10, 2);
        lcd.print("***");
      }
      else if (keysPressed.length() == 4) {
        lcd.setCursor(10, 2);
        lcd.print("****");
      }
      else if (keysPressed.length() == 0) {
        lcd.setCursor(10, 2);
        lcd.print("    ");
      }

      delay(80);
    }
    lcd.setCursor(0, 3);
    lcd.print("                 ");
    lcd.setCursor(0, 3);
    lcd.print("NEW PSW:");
    lcd.print(keysPressed);
    delay(1000);
    lcd.setCursor(0, 3);
    lcd.print("                  ");
    lcd.setCursor(0, 3);
    lcd.print("confirm: press #");
    while (true) {
      Serial.println(keysPressed);

      char key = keypad.getKey();
      if (key != NO_KEY) {
        digitalWrite(bluePin, HIGH);
        tone(speakerPin, tones[9], 100);
        if (key == '#') {
          EEPROM.write(4, String(keysPressed[0]).toInt());
          EEPROM.write(5, String(keysPressed[1]).toInt());
          EEPROM.write(6, String(keysPressed[2]).toInt());
          EEPROM.write(7, String(keysPressed[3]).toInt());
          lcd.setCursor(0, 3);
          lcd.print("                  ");
          lcd.setCursor(0, 3);
          lcd.print("passw saved!");
          tone(speakerPin, tones[4], 500);
          Serial.println("Lockbox");
          break;
        } else {
          lcd.setCursor(0, 3);
          lcd.print("                  ");
          lcd.setCursor(0, 3);
          lcd.print("Cansled!");
          tone(speakerPin, tones[5], 500);
          break;
        }
        waitUntilKeyundo();

      }
    }
    lcd.setCursor(0, 3);
    lcd.print("                  ");

    Serial.print("psw changed:  ");
    Serial.println(keysPressed);


    //    Serial.println(EEPROM.read(4));
    //    Serial.println(EEPROM.read(5));
    //    Serial.println(EEPROM.read(6));
    //    Serial.println(EEPROM.read(7));


    delay(550);
    //    EEPROM.write(1, keysPressed.length());
    //    for (int i = 2; keysPressed.length() <= i - 2; i++) {
    //      EEPROM.write(i, keysPressed[i]);
    //    }
    secretCode = keysPressed;
    keysPressed = "";
  }

  //  if (key == secretCode[position_]) {
  //    position_ ++;
  //  }
  //  if (position_ == secretCode.length()){
  //    setLocked(false);
  //  }
  if (key != NO_KEY) {
    digitalWrite(bluePin, HIGH);
    tone(speakerPin, tones[9], 100);

    if (key == '*' && lock == false) {
      lcd.setCursor(0, 3);
      lcd.print("power off rasberry?");
      delay(1000);
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      lcd.print("yes: key 1");
      while (true) {
        char key = keypad.getKey();
        if (key == '1') {
          tone(speakerPin, 400, 700);
          lcd.setCursor(0, 3);
          lcd.print("                    ");
          lcd.setCursor(0, 3);
          lcd.print("powering off...");
          Serial.println("poweroff");
          delay(800);
          lcd.setCursor(0, 3);
          lcd.print("                    ");
          lcd.setCursor(0, 3);
          lcd.print("powered off");
          break;
        } else if (key != NO_KEY) {
          break;
        }
      }
    }

    if (key == '*' || key == '#') {}
    else {
      keysPressed = keysPressed + key;
    }
    if (keysPressed.length() == 1) {
      lcd.setCursor(10, 2);
      lcd.print("*");
    } else if (keysPressed.length() == 2) {
      lcd.setCursor(10, 2);
      lcd.print("**");
    }
    else if (keysPressed.length() == 3) {
      lcd.setCursor(10, 2);
      lcd.print("***");
    }
    else if (keysPressed.length() == 4) {
      lcd.setCursor(10, 2);
      lcd.print("****");
    }
    else if (keysPressed.length() == 0) {
      lcd.setCursor(10, 2);
      lcd.print("    ");
    }
    waitUntilKeyundo();

  } else {
    //    noTone(speakerPin);
  }
  delay(10);



}


void setLocked(int locked)
{
  if (locked) {
    lock = true;
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    tone(speakerPin, tones[0], 500);
    tone(speakerPin, tones[4], 500);
    tone(speakerPin, tones[7], 500);
    delay(1510);
    lcd.print("                    ");
    lcd.setCursor(0, 3);

  } else {
    lock = false;
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    tone(speakerPin, tones[7], 500);
    tone(speakerPin, tones[4], 500);
    tone(speakerPin, tones[0], 500);
    delay(1510);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
  }
}

void stressSig() {
  lcd.setCursor(10, 2);
  lcd.print("WRONG!");
  tone(speakerPin, tones[3], 600);
  delay(700);
  lcd.setCursor(10, 2);
  lcd.print("      ");
}


void waitUntilKeyundo() {
  while (true) {
    char key = keypad.getKey();
    if (key == NO_KEY) {
      break;
    }
  }
}
