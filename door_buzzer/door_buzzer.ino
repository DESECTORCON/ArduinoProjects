#include <Adafruit_SSD1306.h>
#include <splash.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int buzzer = 8;
int button2 = 11;
int button = 2;
int led = 7;


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(500);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1.5); //set the font size
  display.setCursor(0, 0); //set the cursor coordinates
  display.print("Welcome to");
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(10, 10);
  display.print("CMJ's room!");
  display.setCursor(1, 20);
  display.print("Please ring the bell");
  display.display();

}

void loop() {
  if (digitalRead(button) == LOW) {
    display.setTextSize(2);
    display.setCursor(80, 1);
    display.setTextColor(BLACK, WHITE);
    display.print("ring");
    display.display();
    digitalWrite(led, HIGH);
    tone(buzzer, 1000, 500);
    delay(500);
    tone(buzzer, 500, 800);
    delay(800);
    digitalWrite(led, LOW);

  } else {
    digitalWrite(led, LOW);
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(2);
    display.setCursor(80, 1);
    display.print("     ");
    display.display();
  }
  Serial.println(digitalRead(button2));
  if (digitalRead(button2) == LOW) {
    
    //  display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1.5); //set the font size
    display.setCursor(0, 0); //set the cursor coordinates
    display.print("Welcome to");
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 10);
    display.print("CMJ's room!");
    display.setCursor(1, 20);
    display.print("                    ");
    display.setCursor(1, 20);
    display.print("   Do not disturb!");
    display.display();
  }else {
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1.5); //set the font size
    display.setCursor(0, 0); //set the cursor coordinates
    display.print("Welcome to");
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 10);
    display.print("CMJ's room!");
    display.setCursor(1, 20);
    display.print("                    ");
    display.setCursor(1, 20);
    display.print("  Come on in!");
    display.display();
  }


}
