#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define distance A3
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x3F, 20, 4);
Servo locker;

boolean roomopen = false;
boolean lcd_backlight = true;
boolean message = false;

int lockbutton = 5;
int bell = 6;
int motion_sensor = 8;
int red = 2;
int yellow = 3;
int green = 4;

unsigned long last_on = millis();
unsigned long last_message = millis();

byte semark[] = {
  B00100,
  B01000,
  B10110,
  B10110,
  B10110,
  B10000,
  B01000,
  B00100
};

byte lock[] = {
  B01110,
  B10001,
  B10001,
  B11111,
  B10101,
  B10101,
  B10001,
  B11111
};

byte _open[] = {
  B01110,
  B10001,
  B00001,
  B11111,
  B10101,
  B10101,
  B10001,
  B11111
};

void setup()
{

  pinMode(lockbutton, INPUT);
  pinMode(bell, INPUT);
  pinMode(motion_sensor, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  locker.attach(A0);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  lcd.init();

  lcd.createChar(0, semark);
  lcd.createChar(1, lock);
  lcd.createChar(2, _open);
  lcd.backlight(); // backlight를 On 시킵니다.
  lcd.setCursor(0, 0);
  lcd.write(0);
  lcd.print("<CMJ's ROOM>");
  lcd.setCursor(0, 1);
  lcd.write(1);
  lcd.print(">>ROOM LOCKED<<");
  lcd.setCursor(0, 2);
  lcd.print("Card ID: ");

  locker.write(180);
}
void loop()
{
  //  if (((millis() - last_on) > 15000) && (lcd_backlight) || digitalRead(bell) == HIGH || digitalRead(lockbtuuon) == HIGH) {
  //    backlight_off();
  //  }
  led_set(0, 1, 0);

  backlight_checker();
  message_clear_check();
  check_distance();

  if (digitalRead(motion_sensor) == HIGH) {
    backlight_on();
    message_clear();
    lcd.setCursor(0, 3);
    lcd.print(">Motion dected<");
  }

  if (digitalRead(bell) == HIGH) {
    backlight_on();
    tone(A1, 208, 500);
    delay(501);
    noTone(A1);
    tone(A1, 165, 500);
    delay(501);
    noTone(A1);
  }


  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  backlight_on();
  Serial.print("UID tag :");
  String content = "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  message_clear();
  lcd.setCursor(8, 2);
  lcd.print(content.substring(1));
  last_message = millis();
  message = true;

  if (content.substring(1) == "EA 59 61 02") //change here the UID of the card/cards that you want to give access
  {
    led_set(0, 0, 1);
    Serial.println("Authorized access");
    Serial.println();
    play_entry();

    roomopen = true;
    lcd.setCursor(0, 1);
    lcd.write(2);
    lcd.print(">>ROOM UNLOCKED<<");
    locker.write(90);
    lcd.setCursor(8, 2);
    lcd.print("           ");


    while (true) {
      message_clear_check();
      int distance_now = get_distance();
      if (digitalRead(motion_sensor) == HIGH) {
        backlight_on();
        lcd.setCursor(0, 3);
        lcd.print(">Motion dected<");
      }


      if (digitalRead(bell) == HIGH) {
        backlight_on();
        tone(A1, 208, 500);
        delay(501);
        noTone(A1);
        tone(A1, 165, 500);
        delay(501);
        noTone(A1);
      }

      if ((digitalRead(lockbutton) == HIGH) && (distance_now < 10)) {
        roomopen = false;
        backlight_on();

        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print(">>ROOM LOCKED<<");

        locker.write(180);

        tone(A1, 82, 100);
        delay(101); noTone(A1);
        tone(A1, 82, 300);

        break;
      } else if ((digitalRead(lockbutton) == HIGH) && (distance_now > 10)) {
        backlight_on();
        message_clear();
        lcd.setCursor(0, 3);
        lcd.print("Please shut the door");
        last_message = millis();
        message = true;
      }


      backlight_checker();
    }
  }

  else   {
    led_set(1, 0, 0);

    Serial.println(" Access denied");
    //    message = true;
    //    last_message = millis();
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.print(">>Access denied<<")
    ;
    tone(A1, 330, 100);
    delay(101);
    tone(A1, 330, 500);
    delay(501);

    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.print(">>ROOM LOCKED<<");
    lcd.setCursor(8, 2);
    lcd.print("           ");

  }


}

void backlight_on() {
  lcd.backlight();
  last_on = millis();
  lcd_backlight = true;
  //  Serial.println("millis");
  //  Serial.println(millis());
  //  Serial.println("laston");
  //  Serial.println(last_on);
  //  Serial.println("backlight status");
  //  Serial.println(lcd_backlight);
  //  Serial.println("millis laston subtrack");
  //  Serial.println((millis() - last_on));
}

void backlight_off() {
  lcd.noBacklight();
  //  int last_on = millis();
  lcd_backlight = false;
  //  Serial.println("millis laston subtrack");
  //  Serial.println((millis() - last_on));
  //  Serial.println("backlgith status");
  //  Serial.println(lcd_backlight);
  //  Serial.println("laston");
  //  Serial.println(last_on);
  //  Serial.println("backlight status");
  //  Serial.println(lcd_backlight);
}

void play_entry() {
  tone(A1, 262, 300);
  delay(301); noTone(A1);
  tone(A1, 330, 300);
  delay(301); noTone(A1);
  tone(A1, 392, 300);
  delay(301); noTone(A1);
  tone(A1, 523, 400);
  delay(300); noTone(A1);

}

void backlight_checker() {
  if (((millis() - last_on) > 15000) && (lcd_backlight)) {
    backlight_off();
  }
}

void message_clear() {
  message = false;
  last_message = millis();
  lcd.setCursor(0, 3);
  lcd.print("                    ");

}

void message_clear_check() {
  if (message && (millis() - last_message > 3000)) {
    message = false;
    last_message = millis();
    message_clear();
    //        lcd.setCursor(0, 2);
    //    lcd.print("                  ");
  }
}

void led_set(int redled, int yellowled, int greenled) {
  digitalWrite(red, redled);
  digitalWrite(yellow, yellowled);
  digitalWrite(green, greenled);
}

int get_distance() {
  float volts = analogRead(distance) * 0.0048828125; // value from sensor * (5/1024)
  int distance = 13 * pow(volts, -1); // worked out from datasheet graph
  return distance;
}

void check_distance() {
  int distance_now = get_distance();
  if (!roomopen && (distance_now > 10)) {
    led_set(1, 0, 0);
    backlight_on();

    lcd.setCursor(0, 3);
    lcd.print("---INTRUDER!!---");

    while (true) {
      Serial.println("distance INTRUDER");
      tone(A1, 880, 1000);

      if ( ! mfrc522.PICC_IsNewCardPresent())
      {
        return;
      }
      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial())
      {
        return;
      }
      //Show UID on serial monitor
      backlight_on();
      Serial.print("UID tag :");
      String content = "";
      byte letter;

      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }

      Serial.println();
      Serial.print("Message : ");
      content.toUpperCase();

      lcd.setCursor(8, 2);
      lcd.print(content.substring(1));
      last_message = millis();
      message = true;

      if (content.substring(1) == "EA 59 61 02") //change here the UID of the card/cards that you want to give access
      {
        led_set(0, 0, 1);
        Serial.println("Authorized access");
        Serial.println();
        play_entry();

        roomopen = false;
        lcd.setCursor(0, 1);
        lcd.write(2);
        lcd.print(">>Retouch card<<");
        //        locker.write(90);
        lcd.setCursor(8, 2);
        lcd.print("           ");

        message_clear();
        lcd.setCursor(0, 3);
        lcd.print("Alarm disabled");
        last_message = millis();
        message = true;
        break;
      } else   {

        Serial.println(" Access denied");
        //    message = true;
        //    last_message = millis();
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print(">>Access denied<<")
        ;
        tone(A1, 330, 100);
        delay(101);
        tone(A1, 330, 500);
        delay(501);

        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print(">>ROOM LOCKED<<");
        lcd.setCursor(8, 2);
        lcd.print("           ");

      }
    }
  }
}

//void new_card() {
//  if ( ! mfrc522.PICC_IsNewCardPresent())
//  {
//
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial())
//  {
//    return;
//  }
//  //Show UID on serial monitor
//  backlight_on();
//  Serial.print("UID tag :");
//  String content = "";
//  byte letter;
//
//  for (byte i = 0; i < mfrc522.uid.size; i++)
//  {
//    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//    Serial.print(mfrc522.uid.uidByte[i], HEX);
//    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//    content.concat(String(mfrc522.uid.uidByte[i], HEX));
//  }
//
//  Serial.println();
//  Serial.print("Message : ");
//  content.toUpperCase();
//
//  message_clear();
//  lcd.setCursor(8, 2);
//  lcd.print(content.substring(1));
//  last_message = millis();
//  message = true;
//
//  if (content.substring(1) == "EA 59 61 02") //change here the UID of the card/cards that you want to give access
//  {
//    led_set(0, 0, 1);
//    Serial.println("Authorized access");
//    Serial.println();
//    play_entry();
//
//    roomopen = true;
//    lcd.setCursor(0, 1);
//    lcd.write(2);
//    lcd.print(">>ROOM UNLOCKED<<");
//    locker.write(90);
//    lcd.setCursor(8, 2);
//    lcd.print("           ");
//  }
//
