#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial BT(10, 11); 
Servo leftservo;
Servo rightservo;

int left = 2;
int right = 3;
int leftspeed = 90;
int rightspeed = 90;

void setup()  
{

  pinMode(13, OUTPUT);
  BT.begin(9600);
  BT.println("AR:connected");
  leftservo.attach(left);
  rightservo.attach(right);
}
char a;
void loop() 
{
  if (BT.available())
  { 
      a=(BT.read());

      if (a == 'a'){
        leftspeed = 130;
        rightspeed = 180;
        BT.println("AR:ac");
      }
      if (a == 'b'){
        leftspeed = 40;
        rightspeed = 90;BT.println("AR:ac");
          
      }
      if (a == 'c'){
        leftspeed = 130;
        rightspeed = 90;BT.println("AR:ac");
      }
      if (a == 'd'){
        leftspeed = 90;
        rightspeed = 180;BT.println("AR:ac");
      }
      if (a == 'e'){
        leftspeed = 90;
        rightspeed = 90;BT.println("AR:ac");
      }

  }
  
    leftservo.write(leftspeed);
    rightservo.write(rightspeed);

}