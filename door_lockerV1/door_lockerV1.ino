#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x3F, 16, 2);
Servo locker;

boolean roomopen = false;
boolean lcd_backlight = true;

int lockbutton = 5;
int bell = 6;
int red = 2;
int yellow = 3;
int green = 4;

unsigned long last_on = millis();

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
  backlight_checker();

  if (digitalRead(bell) == HIGH) {
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

  if (content.substring(1) == "EA 59 61 02") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    play_entry();
    Serial.println();
    roomopen = true;
    lcd.setCursor(0, 1);
    lcd.write(2);
    lcd.print(">>ROOM UNLOCKED<<");
    locker.write(90);


    while (true) {
      if (digitalRead(lockbutton) == HIGH) {
        roomopen = false;
        backlight_on();
        lcd.setCursor(0, 1);
        lcd.write(1);
        lcd.print(">>ROOM LOCKED<<");
        locker.write(180);
        tone(A1, 82, 100);
        delay(101);
        tone(A1, 82, 300);

        break;
      }
      //      if (((millis() - last_on) > 15000) && (lcd_backlight)) {
      //        backlight_off();
      //      }
      backlight_checker();
    }
  }

  else   {
    Serial.println(" Access denied");
    lcd.setCursor(0, 3);
    lcd.write(1);
    lcd.print(">>Access denied<<");
    tone(A1, 330, 100);
    delay(101);
    tone(A1, 330, 500);
    delay(501);
    lcd.setCursor(0, 3);
    lcd.write(1);
    lcd.print(">>ROOM LOCKED<<");
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
  delay(301);
  tone(A1, 330, 300);
  delay(301);
  tone(A1, 392, 300);
  delay(301);
  tone(A1, 523, 400);
  delay(300);

}

void backlight_checker() {
  if (((millis() - last_on) > 15000) && (lcd_backlight) || digitalRead(bell) == HIGH || digitalRead(lockbutton) == HIGH) {
    backlight_off();
  }
}
