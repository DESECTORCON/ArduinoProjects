// Project 24 - Hypnotizer

int enable1Pin = 11;
int in1Pin = 10;
int in2Pin = 9;

boolean motor_d = false;

String inString = "0";
String message;

//int speeds[] = {80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255};
//int speeds_minus[] = {-80, -100, -160, -240, -250, -255, -250, -240, -160, -100, -80};
int i = 0;
unsigned int drive_speed = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(enable1Pin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop()
{
//    if (Serial.available()) {
//      message = Serial.readString();
//      if (isDigit(message)) {
//        // convert the incoming byte to a char and add it to the string:
//        inString += (char)inChar;
//        drive();
//  
//      }else {
//        Serial.println("Please enter a number (0~255 or 0~-255)");
//      }
//    }
//    if (!Serial.available()) {
//  
//    }

  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;

    } if (!isDigit(inChar)) {
      Serial.println("Please enter a number (0~255 or 0~-255)");
      Serial.println("Help info::");
      Serial.println("--Digit + x or space");
      Serial.println("--m to swich motor directing");
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == ' ' || inChar == '\n' || inChar == 'x') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      drive(inString.toInt());
      // clear the string for new input:
      inString = "";
    }

    if (inChar == 'm'){
      Serial.println("Motor directing changed.");
      Serial.print("Value:(true = forward || false = backward) ");
      Serial.println(motor_d);      
    }
    
    Serial.println(message);
    
  }

  //  //  int speed = speeds[i];
  //  //  i++;
  //  //  if (i == 22)
  //  //  {
  //  //    i = 0;
  //  //  }
  //  //  drive(speed);
  //  //  delay(1500);
  //  if (i > 255) {
  //    while (true) {
  //      i--;
  //      drive(i);
  //      delay(100);
  //      if (i < -255) {
  //        break;
  //      }
  //
  //    }
  //  }
  //  i++;
  //  drive(i);
  //  delay(100);
}

void drive(int speed)
{
  if (speed > 0 || motor_d)
  {
    analogWrite(enable1Pin, speed);
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  }
  else if (speed < 0 || !motord)
  {
    analogWrite(enable1Pin,  -speed);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
  }
}
