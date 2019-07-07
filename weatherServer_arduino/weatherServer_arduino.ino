#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
String readString;
int current_month = 0;

float last;
float current;
int last_time = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
IPAddress ip(192, 168, 0, 8); //<<< ENTER YOUR IP ADDRESS HERE!!!

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  bme.begin();
  last = bme.readPressure() / 100.0F;
  current = bme.readPressure() / 100.0F;
}

void loop()
{

  if ((millis() - last_time) > 60000) {
    last = current;
    last_time = millis();
  }

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) {
          readString += c;
          Serial.println(c);
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n') {
          current = bme.readPressure() / 100.0F;
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<meta http-equiv='refresh' content='5'/>");

          //serves a different version of a website depending on whether or not the button
          //connected to pin 2 is pressed.
          client.println("<div bgcolor=#000000><p style='background-color:white; font-size:50px;'>Temperature: ");
          client.println(bme.readTemperature());
          client.println("</p></div>");

          client.println("<div bgcolor=#000000><p style='background-color:white; font-size:50px;'>pressure: ");
          client.println(bme.readPressure() / 100.0F);
          client.println("</p></div>");


          client.println("<div bgcolor=#000000><p style='background-color:white; font-size:50px;'>Humidity: ");
          client.println(bme.readHumidity());
          client.println("</p></div>");

          client.println("<form action='/' method=get >"); //uses IP/port of web page
          //          client.println("<input type=button NAME='LED' VALUE='1'><br><input type=button NAME='LED' VALUE='2'><BR><input type=button NAME='LED' VALUE='3'><BR><input type=button NAME='LED' VALUE='4'><BR><input type=button NAME='LED' VALUE='5'><BR><input type=button NAME='LED' VALUE='6'><BR><input type=button NAME='LED' VALUE='7'><BR><input type=button NAME='LED' VALUE='8'><BR><input type=button NAME='LED' VALUE='9'><BR><input type=button NAME='LED' VALUE='10'><BR><input type=button NAME='LED' VALUE='11'><BR><input type=button NAME='LED' VALUE='12'><BR>");
          client.println("Please put m in front of number;;;1,2,3,4,5,6,7,8,9,10,11,12 :: <INPUT TYPE=TEXT NAME='Month' VALUE='' SIZE='25' MAXLENGTH='50'><BR>");
          client.println("<input type=submit name='submit' value='Submit'>");
          client.println("</form>");
          /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          int Z = calc_zambretti(current, last, current_month);

          if (last > 0 and current > 0) {
            if (current - last >= 1) {
              //RAISING
              //              draw_arrow(670, 450, 1);
              if (Z < 3) {
                //                sunny(500, 350);
                client.println("<p>sunny</p>");
              }
              else if (Z >= 3 and Z <= 9) {
                //                sunny_cloudy(400, 350);
                client.println("<p>sunny_cloudy</p>");
              }
              else if (Z > 9 and Z <= 17)
                //                cloudy(300, 300);
                client.println("<p>cloudy</p>");
              else if (Z > 17) {
                //                rainy(300, 300);
                client.println("<p>rainy</p>");
              }
            }

            else if (last - current >= 1) {
              //FALLING
              //              draw_arrow(670, 450, -1);
              if (Z < 4)
                //                sunny(400, 350);
                client.println("<p>sunny</p>");
              else if (Z >= 4 and Z < 14) {
                //                sunny_cloudy(400, 350);
                client.println("<p>sunny_cloudy</p>");
              }
              else if (Z >= 14 and Z < 19) {
                //                worsening(400, 350);
                client.println("<p></p>");
              }
              else if (Z >= 19 and Z < 21)
                //                cloudy(300, 300);
                client.println("<p>cloudy</p>");
              else if (Z >= 21) {
                //                rainy(300, 300);
                client.println("<p>rainy</p>");
              }
            }
            else {
              //STEADY
              //              draw_arrow(670, 450, 0);
              if (Z < 5)
                //                sunny(400, 350);
                client.println("<p>sunny</p>");
              else if (Z >= 5 and Z <= 11) {
                //                sunny_cloudy(400, 350);
                client.println("<p>sunny_cloudy</p>");
              }
              else if (Z > 11 and Z < 14)
                //                cloudy(300, 300);
                client.println("<p>cloudy</p>");
              else if (Z >= 14 and Z < 19) {
                //                worsening(400, 350);
                client.println("<p>worsening</p>");
              }
              else if (Z > 19) {
                //                rainy(300, 300);
                client.println("<p>rainy</p>");
              }
            }
          }
          client.print("<p style='color:red;'>current pressure::");
          client.print(current);
          client.println("</p>");

          client.print("<p style='color:red;'>last pressure::");
          client.print(last);
          client.println("</p>");

          client.print("<p style='color:red;'>last millis::");
          client.print(last_time);
          client.println("</p>");

          client.print("<p style='color:red;'>current millis::");
          client.print(millis());
          client.println("</p>");

          client.print("<p style='color:red;'>subbmitted month::");
          client.print(current_month);
          client.println("</p>");

          delay(1);
          // close the connection:
          client.stop();
          if (readString.indexOf("m1") > 0)
          {

            current_month = 1;
          }
          if (readString.indexOf("m2") > 0)
          {

            current_month = 2;
          }
          if (readString.indexOf("m3") > 0)
          {

            current_month = 3;
          }
          if (readString.indexOf("m4") > 0)
          {

            current_month = 4;
          }
          if (readString.indexOf("m5") > 0)
          {

            current_month = 5;
          }
          if (readString.indexOf("m6") > 0)
          {

            current_month = 6;
          }
          if (readString.indexOf("m7") > 0)
          {

            current_month = 7;
          }
          if (readString.indexOf("m8") > 0)
          {

            current_month = 8;
          }
          if (readString.indexOf("m9") > 0)
          {

            current_month = 9;
          }
          if (readString.indexOf("m10") > 0)
          {

            current_month = 10;
          }
          if (readString.indexOf("m11") > 0)
          {

            current_month = 11;
          }
          if (readString.indexOf("m12") > 0)
          {

            current_month = 12;
          }
          //clearing string for next read
          readString = "";
          Serial.println("current_month: ");
          Serial.print(current_month);
        }
      }
    }
    // give the web browser time to receive the data

  }
}


int calc_zambretti(int curr_pressure, int prev_pressure, int mon) {
  if ((curr_pressure < prev_pressure) && (mon != 0)) {
    //FALLING
    if (mon >= 4 and mon <= 9)
      //summer
    {
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 18;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 24;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
    else {
      //winter
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 15;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 22;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
  }
  else if (curr_pressure > prev_pressure) {
    //RAISING
    if (mon >= 4 and mon <= 9) {
      //summer
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 3;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 9;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 12;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
    else
      //winter
    {
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 6;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 10;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 13;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
  }
  else {
    if (curr_pressure >= 1030)
      return 1;
    else if (curr_pressure >= 1020 and curr_pressure < 1030)
      return 2;
    else if (curr_pressure >= 1010 and curr_pressure < 1020)
      return 11;
    else if (curr_pressure >= 1000 and curr_pressure < 1010)
      return 14;
    else if (curr_pressure >= 990 and curr_pressure < 1000)
      return 19;
    else if (curr_pressure >= 980 and curr_pressure < 990)
      return 23;
    else if (curr_pressure >= 970 and curr_pressure < 980)
      return 24;
    else if (curr_pressure < 970)
      return 26;

  }

}
