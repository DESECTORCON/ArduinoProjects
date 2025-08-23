#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define SLEEP		53
#define	VI 			51

void setup(void) {
	Serial.begin(9600);

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
	tft.setRotation(3);	
	tft.fillScreen(WHITE);
	tft.setCursor(25,10);
	tft.setTextColor(BLACK);
	tft.setTextSize(4);
	tft.print("Current CO2");
	tft.setTextColor(GREEN);									// This should be changed as the read value from sensor
	tft.setTextSize(6);
	tft.setCursor(25,45);
	tft.print(" ");
	tft.print("500");
	tft.setTextSize(3);
	tft.println("ppm");
	
	tft.sendrawdata8(0x53, 0b00101100);
	tft.sendrawdata8(0x51, 0x01);
}

void loop(void) {
}
