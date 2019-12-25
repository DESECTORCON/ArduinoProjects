#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial BT(10, 11); 
Servo leftservo;
Servo rightservo;

int light1 = 5;
int light2 = 6;
int light3 = 7;

int left = 2;
int right = 3;
int leftspeed = 90;
int rightspeed = 90;

void setup()  
{

  pinMode(13, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);

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
        leftspeed = 140;
        rightspeed = 0;
        BT.println("AR:ac");
      }
      if (a == 'b'){
        leftspeed = 50;
        rightspeed = 180;BT.println("AR:ac");
          
      }
      if (a == 'c'){
        leftspeed = 130;
        rightspeed = 180;BT.println("AR:ac");
      }
      if (a == 'd'){
        leftspeed = 50;
        rightspeed = 0;BT.println("AR:ac");
      }
      if (a == 'e'){
        leftspeed = 90;
        rightspeed = 90;BT.println("AR:ac");
      }

      if (a == 'x'){
        digitalWrite(7,HIGH);digitalWrite(6,HIGH);digitalWrite(5,HIGH);
      }
      if (a == 'z'){
        digitalWrite(7,LOW);digitalWrite(6,LOW);digitalWrite(5,LOW);
      }

  }
  
    leftservo.write(leftspeed);
    rightservo.write(rightspeed);

}