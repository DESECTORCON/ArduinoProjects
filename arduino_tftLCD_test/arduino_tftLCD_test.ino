// UTFT_Demo_128x128_Serial (C)2012 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made to work on the 128x128 modules.
// Any other size displays may cause strange behaviour.
//
// This program requires the UTFT library.
//

#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Declare an instance of the class
UTFT L(ITDB18SP,7,6,5,3,4);   // Remember to change the model parameter to suit your display module!

void setup()
{
  randomSeed(analogRead(0));
   L.setBrightness(16);
 
// Setup the LCD
  L.InitLCD(PORTRAIT);
  L.setFont(SmallFont);
}

void loop()
{
  byte buf[126];
  int x, x2;
  int y, y2;
  int r;
  
// Clear the screen and draw the frame
  L.clrScr();
  L.setContrast(64);

  L.setColor(255, 0, 0);
  L.drawRect(0,0,L.getDisplayXSize()-1,L.getDisplayYSize()-1);
  L.setColor(VGA_SILVER);
  L.print("Hello", 5,50, 270);
  while (true) {}
}
