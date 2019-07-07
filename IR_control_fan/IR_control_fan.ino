#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <splash.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>

#define OLED_RESET 4

int RECV_PIN = 10;
int fan = 9;
int fanspeed = 0;

int seq = 0;
int count = 0;
int count_done = 100;

IRrecv irrecv(RECV_PIN);
decode_results results;

Adafruit_SSD1306 display(OLED_RESET);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(1); //set the font size
  display.setCursor(0, 0); //set the cursor coordinates
  display.print("FAN CONTROLER");
  display.display();
}

void loop()
{
  analogWrite(fan, fanspeed);
  if (irrecv.decode(&results))
  {

    Serial.println(results.value, HEX);
    display.clearDisplay();
    if (results.value == 0xFF9867) {
      fanspeed = 0;
      Serial.println("fan:0");
    } else if (results.value == 0xFFA25D) {
      fanspeed = 50;
      Serial.println("fan:1");
    }
    else if (results.value == 0xFF629D) {
      fanspeed = 100;
      Serial.println("fan:2");
    }
    else if (results.value == 0xFFE21D) {
      fanspeed = 150;
      Serial.println("fan:3");
    }
    else if (results.value == 0xFF22DD) {
      fanspeed = 160;
      Serial.println("fan:4");
    }
    else if (results.value == 0xFF02FD) {
      fanspeed = 170;
      Serial.println("fan:5");
    }
    else if (results.value == 0xFFC23D) {
      fanspeed = 180;
      Serial.println("fan:6");
    }
    else if (results.value == 0xFFE01F) {
      fanspeed = 190;
      Serial.println("fan:7");
    }
    else if (results.value == 0xFFA857) {
      fanspeed = 200;
      Serial.println("fan:8");
    }
    else if (results.value == 0xFF906F) {

      fanspeed = 255;
      Serial.println("fan:9");
    }
    else if ( results.value == 0xFF18E7 ) {
      if (fanspeed < 256) {
        fanspeed = fanspeed + 10;
      } else {
        fanspeed = 255;
      }
      Serial.println("fan up");

    }
    else if ( results.value == 0xFF4AB5 ) {
      if (fanspeed > 0) {
        fanspeed = fanspeed - 10;
      } else {
        fanspeed = 0;
      }
      Serial.println("fan down");
    }



    //    display.setTextColor(BLACK, WHITE);
    //    display.setTextSize(1); //set the font size
    //    display.setCursor(0, 0); //set the cursor coordinates
    //    display.print("FAN CONTROLER");
    //    display.setTextColor(WHITE);
    //    display.setTextSize(2); //set the font size
    //    display.setCursor(10, 10); //set the cursor coordinates
    //    display.print(fanspeed);
    //    display.display();
    irrecv.resume(); // Receive the next value
  }

  if (fanspeed > 0 && count > count_done) {

    if (seq == 0) {
      display.fillCircle(100, 13, 5, WHITE);
      display.drawCircle(100, 27, 5, WHITE);
      display.drawCircle(85, 20, 5, WHITE);
      display.drawCircle(115, 20, 5, WHITE);
      //      Serial.println("seq0");
    }
    if (seq == 1) {
      display.fillCircle(100, 13, 5, WHITE);
      display.drawCircle(100, 27, 5, WHITE);
      display.fillCircle(85, 20, 5, WHITE);
      display.drawCircle(115, 20, 5, WHITE);
      //      Serial.println("seq1");
    }
    if (seq == 2) {
      display.fillCircle(100, 13, 5, WHITE);
      display.fillCircle(100, 27, 5, WHITE);
      display.fillCircle(85, 20, 5, WHITE);
      display.drawCircle(115, 20, 5, WHITE);
      //      Serial.println("seq2");
    }
    if (seq == 3) {
      display.fillCircle(100, 13, 5, WHITE);
      display.fillCircle(100, 27, 5, WHITE);
      display.fillCircle(85, 20, 5, WHITE);
      display.fillCircle(115, 20, 5, WHITE);
      //      Serial.println("seq3");
    }
    if (seq == 4) {
      seq = -1;
      display.clearDisplay();
      display.drawCircle(100, 13, 5, WHITE);
      display.drawCircle(100, 27, 5, WHITE);
      display.drawCircle(85, 20, 5, WHITE);
      display.drawCircle(115, 20, 5, WHITE);
      //      Serial.println("seqreset");
    }
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1); //set the font size

    display.setCursor(0, 0); //set the cursor coordinates
    display.print("FAN CONTROLER");
    display.setTextColor(WHITE);
    display.setTextSize(2); //set the font size
    display.setCursor(10, 10); //set the cursor coordinates
    display.print(fanspeed);
    display.display();
    seq ++;
    count = 0;
  } else if (fanspeed == 0) {
    display.drawCircle(100, 13, 5, WHITE);
    display.drawCircle(100, 27, 5, WHITE);
    display.drawCircle(85, 20, 5, WHITE);
    display.drawCircle(115, 20, 5, WHITE);

    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0); //set the cursor coordinates
    display.print("FAN CONTROLER");
    display.setTextColor(WHITE);
    display.setTextSize(2); //set the font size
    display.setCursor(10, 10); //set the cursor coordinates
    display.print(fanspeed);
    display.display();

  }
  count ++;
  //  Serial.println(count_done);

  if (fanspeed == 50 || fanspeed < 50) {
    count_done = 100;
    Serial.println("one");
  } else if (fanspeed == 100 || 149 > fanspeed > 50) {
    count_done = 90;
    Serial.println("two");
  } else if (fanspeed == 150 || fanspeed == 160 || fanspeed == 170 || fanspeed == 190 || fanspeed == 180 || 200 > fanspeed > 150) {
    count_done = 70;
    Serial.println("three");
  } else if (fanspeed == 200 || 254 > fanspeed > 201) {
    count_done = 50;
    Serial.println("four");
  } else if (fanspeed == 255 || fanspeed >= 255) {
    count_done = 20;
    Serial.println("five");
  }

}
