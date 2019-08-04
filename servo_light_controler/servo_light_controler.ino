#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#define delay_time 480
#define RECVP_PIN 10

LiquidCrystal_I2C lcd(0x27, 20, 4);
IRrecv irrecv(RECVP_PIN);
decode_results results;
Servo Mlight1;
Servo Mlight2;

boolean light1 = false;
boolean light2 = false;

unsigned long timer = millis();
boolean timeron  = false;

void setup() {
  Mlight1.attach(12);
  Mlight2.attach(8);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  irrecv.enableIRIn();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("<<Arduino Light");
  lcd.setCursor(0, 1);
  lcd.print("      Controler V1>>");
}

void loop() {
  //  int coupler = analogRead(A5);
  //  Serial.print("Analog Input: ");
  //  Serial.println(coupler);
  if (irrecv.decode(&results)) {
    timer = millis();
    lcd.display();
    lcd.backlight();
    lcd.setCursor(0, 2);
    lcd.print("Signal:");
    lcd.print(String(results.value));
    if (results.value == 0xFF9867) {
      //      Serial.println("ALL OFF");
      //      Mlight1.write(180);
      //      delay(delay_time);
      //      Mlight1.write(90);
      lightset('1', false);
      lightset('2', false);
      set_LCD( light1,  light2);

      timeron  = true;
    } else if (results.value == 0xFFA25D) {
      lightset('1', true);
      lightset('2', false);

      timeron  = true;
      set_LCD( light1,  light2);
    }    else if (results.value == 0xFF629D) {
      lightset('1', false);
      lightset('2', true);

      timeron  = true;
      set_LCD( light1,  light2);
    }    else if (results.value == 0xFF906F) {
      lightset('1', true);
      lightset('2', true);

      timeron  = true;
      set_LCD( light1,  light2);
    }
    irrecv.resume();
  }
  if (timeron && (timer + 10000 < millis())) {
    lcd.noDisplay();
    lcd.noBacklight();
  }
}

void lightset (char MID, boolean stat) {
  if (MID == '1') {
    if (stat && !light1) {
      Serial.println("1 ON");
      Mlight1.write(180);
      delay(delay_time);
      Mlight1.write(90);
      light1 = true;

    } else if (!stat && light1) {
      Serial.println("1 OFF");
      Mlight1.write(0);
      delay(delay_time);
      Mlight1.write(90);
      light1 = false;
    }
  } else if (MID == '2') {
    if (stat && !light2) {
      Serial.println("2 ON");
      Mlight2.write(0);
      delay(delay_time);
      Mlight2.write(90);

      light2 = true;
    } else if (!stat && light2) {
      Serial.println("2 OFF");
      Mlight2.write(180);
      delay(delay_time);
      Mlight2.write(90);
      light2 = false;
    }
  }
}

void set_LCD(boolean light1, boolean light2) {
  lcd.setCursor(0, 3);
  lcd.print("Light1:");

  if (light1) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }

  lcd.print("Light1:");

  if (light2) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }
}

//  Serial.println(analogRead(A5));
//  delay(10);
//    if (coupler > 800) {
//      //        delay(500);
//      for (int i = 0; i < 3; i++) {
//        if (analogRead(A5) < 60) {
//          break;
//        }
//        Serial.print("LOOPSTATUS:::");
//        Serial.println(i);
//        digitalWrite(13, HIGH);
//        delay(100);
//        digitalWrite(13, LOW);
//        delay(100);
//      }
//      if (analogRead(A5) > 800) {
//        Serial.println("ON");
//        Mlight1.write(180);
//        delay(delay_time);
//        Mlight1.write(90);
//
//        while (true) {
//          int coupler = analogRead(A5);
//          if (coupler < 40) {
//            //          delay(5000); ---25
//            for (int i = 0; i < 5; i++) {
//              if (analogRead(A5) > 800) {
//                break;
//              }
//              Serial.print("LOOPSTATUS:::");
//              Serial.println(i);
//              digitalWrite(13, HIGH);
//              delay(100);
//              digitalWrite(13, LOW);
//              delay(100);
//            }
//            if (analogRead(A5) < 60) {
//              Serial.println("OFF");
//              Mlight1.write(0);
//              delay(delay_time);
//              Mlight1.write(90);
//              break;
//            }
//          }
//        }
