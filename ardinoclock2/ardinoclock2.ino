#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int hour, minute, second = 0;


void setup()
{
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, world!");
  lcd.clear();
  lcd.print("    --S.E clock--");
  lcd.setCursor(0, 1);
  lcd.print("---starting up...---");
  lcd.setCursor(5, 2);
   delay(1000);
   lcd.clear();
   lcd.setCursor(6, 3);
   lcd.print(":");
   lcd.setCursor(9, 3);
   lcd.print(":");
   lcd.setCursor(0,0);
   lcd.print("Have a nice day-!");
}

void loop()
{
  delay(1000);
  second += 1;
  if (second >= 60){
    second = 0;
    minute += 1;
  }
  if (minute >= 60){
    minute = 0;
    hour += 1;
  }
  if (hour >= 24){
    hour = 0;
  }
  lcd.setCursor(10, 3);
  lcd.print("  ");
  lcd.setCursor(10, 3);
  lcd.print(String(second));
  lcd.setCursor(7, 3);
  lcd.print("  ");
  lcd.setCursor(7, 3);
  lcd.print(String(minute));
  lcd.setCursor(4, 3);
  lcd.print("  ");
  lcd.setCursor(4, 3);
  lcd.print(String(hour));
  
  
}
