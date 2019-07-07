


// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 4
#include <DS1302.h>

DS1302 rtc(2, 3, 4);

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  

Serial.begin(9600);
  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(SUNDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(15, 2, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(24, 3, 2019);   // Set the date to August 6th, 2010
}

void loop()
{

  Serial.println(rtc.getTimeStr());
  
 
  delay (1000);
}
