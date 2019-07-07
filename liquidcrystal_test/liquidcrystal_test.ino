#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() {
  
  lcd.init(); // lcd를 사용을 시작합니다.
  lcd.backlight(); // backlight를 On 시킵니다.
  lcd.print("Hello, world!");
}

void loop() {
  delay(100);

}
