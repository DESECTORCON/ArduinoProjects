#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
unsigned long delayTime;

Adafruit_BME280 bme;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };
IPAddress ip(192,168,0,8); //<<< ENTER YOUR IP ADDRESS HERE!!!

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
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
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

          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}
