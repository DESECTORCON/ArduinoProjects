#include <memorysaver.h>
#include <UTFT.h>

#define button1 22
#define button2 24
#define button3 26
#define button4 28

int score = 10;
unsigned int lives = 8;
boolean gameon = true;

//String quiz = "";
//int answer;
//int answernumber;
//int number1;
//int number2;
//String operator_ = "+";

int chansor1;
int chansor2;
int chansor3;
int chansor4;

int level = 1;

extern uint8_t SmallFont[];
extern uint8_t  BigFont[];
UTFT lcd(ITDB18SP, 7, 6, 5, 3, 4);
void setup() {
  Serial.begin(9600);
  lcd.InitLCD();
  lcd.setFont(SmallFont);
  randomSeed(analogRead(0));
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

}

void loop() {
  lcd.clrScr();

  int score = 10;
  unsigned int lives = 8;
  boolean gameon = true;

  setCaption("Quiz machine");
  lcd.setBackColor(179, 232, 21);
  lcd.setColor(51, 184, 135);
  lcd.setFont(BigFont);
  lcd.print("Welcome!!", CENTER, CENTER);
  lcd.setColor(151, 43, 194); lcd.setFont(SmallFont);
  lcd.print("<To start,", CENTER, 60);
  lcd.print("please push 2,3>", CENTER, 70);
  while (true) {
    lcd.setColor(random(255), random(255), random(255)); lcd.setFont(SmallFont);
    lcd.print("<To start,", CENTER, 60);
    lcd.print("please push 2,3>", CENTER, 70);
    lcd.setBackColor(random(255), random(255), random(255));
    lcd.setColor(random(255), random(255), random(255));
    lcd.setFont(BigFont);
    lcd.print("Welcome!!", CENTER, CENTER);
    delay(200);
    if (digitalRead(button2) && digitalRead(button3)) {
      break;
    }
  }

  while (gameon) {
    lcd.clrScr();
    String captionString = "";
    String operator_ = "";
    String quiz = "";
    int answer;
    int answernumber;
    int number1;
    int number2;
    switch (lives)
    {
      case 8:
        captionString = captionString + "////////";
        break;
      case 7:
        captionString = captionString + "/////// ";
        break;
      case 6:
        captionString = captionString + "//////  ";
        break;
      case 5:
        captionString = captionString + "/////   ";
        break;
      case 4:
        captionString = captionString + "////    ";
        break;
      case 3:
        captionString = captionString + "///     ";
        break;
      case 2:
        captionString = captionString + "//      ";
        break;
      case 1:
        captionString = captionString + "/       ";
        break;
      case 0:
        captionString = captionString + "        ";
        gameon = false;
        lcd.setBackColor(179, 232, 21);
        lcd.setColor(51, 184, 135);
        lcd.setFont(BigFont);
        lcd.print("GAME OVER!!", CENTER, CENTER);
        delay(5000);
        break;
    }
    setCaption(captionString + score);

    switch (level) {
      case 1:
        number1 = random(10);
        number2 = random(10);
        break;
      case 2:
        number1 = random(13);
        number2 = random(13);
        break;
      case 3:
        number1 = random(17);
        number2 = random(17);
        break;
    }

    switch (random(2)) {
      case 0:
        operator_ = "+";
        answer = number2 + number1;
        break;
      case 1:
        operator_ = "-";
        answer = number2 - number1;
        break;
      //      case 2:
      //        operator_ = "/";
      //        answer = number2 / number1;
      //        break;
      case 2:
        operator_ = "*";
        answer = number2 * number1;
        break;
    }
    //    quiz = number2 + "  " + operator_ + "  " + number1;
    quiz = quiz + String(number2);
    //    quiz = quiz + " ";
    quiz = quiz + operator_;
    //    quiz = quiz + " ";
    quiz = quiz + String(number1);

    switch (random(3)) {
      case 0:
        chansor1 = answer;
        chansor2 = answer - random(15);
        chansor3 = answer * random(3);
        chansor4 = answer * random(7);
        answernumber = 1;

        if (chansor1 == chansor2){
          
        }

        
        break;
      case 1:
        chansor1 = answer - random(15);
        chansor2 = answer;
        chansor3 = answer * random(3);
        chansor4 = answer * random(7);
        answernumber = 2;
        break;
      case 2:
        chansor1 = answer * random(3);
        chansor2 = answer - random(15);
        chansor3 = answer ;
        chansor4 = answer * random(7);
        answernumber = 3;
        break;
      case 3:
        chansor1 = answer * random(7);
        chansor2 = answer - random(15);
        chansor3 = answer * random(3);
        chansor4 = answer ;
        answernumber = 4;
        break;
    }
    Serial.print("chansor1::");
    Serial.println(chansor1);
    Serial.print("chansor2::");
    Serial.println(chansor2);
    Serial.print("chansor3::");
    Serial.println(chansor3);
    Serial.print("chansor4::");
    Serial.println(chansor4);

    Serial.print("number1::");
    Serial.println(number1);
    Serial.print("number2::");
    Serial.println(number2);

    Serial.print("answernumber::");
    Serial.println(answernumber);

    Serial.print("quiz::");
    Serial.println(quiz);
    Serial.print("Answer::");
    Serial.println(answer);
    Serial.print("operator::");
    Serial.println(operator_);

    lcd.setColor(random(255), random(255), random(255)); lcd.setFont(BigFont);
    //    lcd.setBackColor(
    //      103, 107, 89
    //    );
    lcd.print("Whats, ", CENTER, 30);
    lcd.print(quiz, CENTER, 50);
    lcd.setColor(random(255), random(255), random(255)); lcd.setFont(SmallFont);
    lcd.print("1{" + String(chansor1), 0, 80);
    lcd.print("2{" + String(chansor2), 40, 80);
    lcd.print("3{" + String(chansor3), 80, 80);
    lcd.print("4{" + String(chansor4), 130, 80);


    while (true) {
      if (digitalRead(button1) && ( answernumber == 1)) {
        score = score + 1;
        Serial.println("win"); break;
      } else if (digitalRead(button2) && ( answernumber == 2)) {
        score = score + 1;
        Serial.println("win"); break;
      } else if (digitalRead(button3) && ( answernumber == 3)) {
        score = score + 1; Serial.println("win"); break;
      } else if (digitalRead(button4) && ( answernumber == 4)) {
        score = score + 1; Serial.println("win"); break;
      } else if (digitalRead(button1) || digitalRead(button2) || digitalRead(button3) || digitalRead(button4)) {
        score = score - 1; Serial.println("loose");
        lives = lives - 1;
        break;
      }
    }
  }

}
void setCaption(String caption) {
  lcd.setColor(255, 0, 0);
  lcd.fillRect(0, 0, 159, 13);
  lcd.setColor(64, 64, 64);
  lcd.fillRect(0, 114, 159, 127);
  lcd.setColor(255, 255, 255);
  lcd.setBackColor(255, 0, 0);
  lcd.print(caption, CENTER, 1);
}
