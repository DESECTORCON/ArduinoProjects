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

long pwm_width = 0;
long co2			 = 0;
float temp		 = 0;
float humidity = 0;
float heatindex= 0;
long  gas			 = 0;

long history[290];

void setup(void) {
	Serial.begin(9600);
	randomSeed(analogRead(A11));							// TODO debug

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
	tft.setRotation(3);	

	for (int i=0;i<290;i++)
	{
		history[i] = 0;
	}
		
}

void loop(void) {
	tft.fillScreen(WHITE);
	tft.setCursor(10,10);
	tft.setTextColor(BLACK);
	tft.setTextSize(3);
	tft.print("Current CO2");
																							// TODO sensor pwm width to co2 value convertion logic
	co2 = random(400, 5000);										// TODO debug
	humidity = random(0,100);
	temp    = random(10,40);										// If over these temps, dont run fill rect part
	for (long i=0;i < 290;i++){
		history[i] = history[i+1];	
	}
	history[289] = co2;
	
	if (co2 > 2700){
		tft.setTextColor(RED);
	} else if (co2 > 1000) {
		tft.setTextColor(tft.color565(201,209,48));
	} else if (co2 > 650)	{
		tft.setTextColor(GREEN);
	} else {
		tft.setTextColor(BLUE);
	}
	tft.setTextSize(5);
	tft.setCursor(10,40);
	tft.print(co2);
	tft.setTextSize(3);
	tft.println("ppm");

	tft.drawLine(20, 230, 310, 230, BLACK);
	tft.drawLine(20, 230, 20, 100, BLACK);
	tft.setTextColor(RED);
	tft.setTextSize(1);
	tft.setCursor(0,100);
	tft.print("5000");
	tft.drawLine(20, 100, 310, 100, tft.color565(255,186,186));
	tft.setCursor(0,165);
	tft.print("2700");
	tft.drawLine(20, 165, 310, 165, tft.color565(255,218,186));
	tft.setCursor(0,202);
	tft.setTextColor(tft.color565(201,209,48));
	tft.print("1400");
	tft.drawLine(20, 202, 310, 202, tft.color565(250,255,201));
	tft.setCursor(0,216);
	tft.print("900");
	tft.drawLine(20, 216, 310, 216, tft.color565(224,255,201));
	tft.setCursor(0,223);
	tft.setTextColor(tft.color565(39,207,50));
	tft.print("650");
	tft.drawLine(20, 223, 310, 223, tft.color565(201,255,207));
	tft.setCursor(0,230);
	tft.setTextColor(BLUE);
	tft.print("400");
	tft.drawLine(20, 230, 310, 230, tft.color565(201,243,255));
	
	for (long i=0;i<290;i++){
		if (history[i] > 2700){
			tft.drawPixel(map(i, 0, 289, 310,20), map(history[i], 0, 5000, 240, 100), tft.color565(87,0,0));
		}
		else if (history[i] > 1400){
			tft.drawPixel(map(i, 0, 289, 310,20), map(history[i], 0, 5000, 240, 100), RED);
		}
		else if (history[i] > 1000){
			tft.drawPixel(map(i, 0, 289, 310,20), map(history[i], 0, 5000, 240, 100), tft.color565(201,209,48));
		}
		else if (history[i] > 650){
			tft.drawPixel(map(i, 0, 289, 310,20), map(history[i], 0, 5000, 240, 100), GREEN);
	}
		else {
			tft.drawPixel(map(i, 0, 289, 310,20), map(history[i], 0, 5000, 240, 100), BLUE);
		}
		
	}
	
	tft.fillRoundRect(200, 40, 300, 60, 1, tft.color565(128,128,128));

	tft.drawRect(210, 45, 80,10, WHITE);
	tft.fillRect(210, 45, (int)map((int)temp, 10, 40, 0,80),10, 
							tft.color565((int)map((int)temp, 10, 40, 0, 255), 0, (int)map((int)temp, 10, 40, 255, 0)));
	tft.setCursor(205, 48);
	tft.setTextColor(WHITE);
	tft.setTextSize(1);
	tft.print("T:");
	tft.print("   ");
	tft.print(temp);
	tft.print(" C");
	
	tft.drawRect(210, 56, 80,10, WHITE);
	tft.fillRect(210, 56, (int)map((int)humidity, 0, 100, 0, 80),10, 
							tft.color565((int)cos(map((int)humidity, 0, 100, 0, 2*PI)+1)*255, 0, 
							(int)(-cos(map((int)humidity, 0, 100, 0, 2*PI))+1)*255));	
	tft.setCursor(205, 58);
	tft.setTextColor(WHITE);
	tft.setTextSize(1);
	tft.print("H:");
	tft.print("   ");
	tft.print(humidity);
	tft.print(" %");
	
	tft.setCursor(205, 78);
	tft.setTextColor(WHITE);
	tft.setTextSize(1);
	tft.print("G:");
	tft.print(" ");
	tft.print(gas);
	//delay(60000);															// TODO debug - should be one minute at deploy	
	delay(1000);
}
