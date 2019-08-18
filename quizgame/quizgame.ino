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

int countdowntime = 4000;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
UTFT lcd(ITDB18SP, 7, 6, 5, 3, 4);
void setup()
{
  Serial.begin(115200);
  lcd.InitLCD();
  lcd.setFont(SmallFont);
  randomSeed(analogRead(15));
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
}

void loop()
{
  lcd.clrScr();

  int score = 10;
  unsigned int lives = 8;
  boolean gameon = true;

  setCaption("Quiz machine");
  lcd.setBackColor(179, 232, 21);
  lcd.setColor(51, 184, 135);
  lcd.setFont(BigFont);
  lcd.print("Welcome!", CENTER, CENTER);
  lcd.setColor(151, 43, 194);
  lcd.setFont(SmallFont);
  lcd.print("<To start,", CENTER, 60);
  lcd.print("please push 2,3>", CENTER, 70);
  while (true)
  {

    lcd.setColor(random(255), random(255), random(255));
    lcd.setFont(SmallFont);
    lcd.print("<To start,", CENTER, 60);
    lcd.print("please push 2,3>", CENTER, 70);
    lcd.setBackColor(random(255), random(255), random(255));
    lcd.setColor(random(255), random(255), random(255));
    lcd.setFont(BigFont);
    lcd.print("Welcome!", CENTER, CENTER);
    delay(200);
    if (digitalRead(button2) && digitalRead(button3))
    {
      break;
    }
  }
  int gamecycle = 0;
  while (gameon)
  {

    lcd.clrScr();
    gamecycle++;
    if (gamecycle > 4)
    {
      // Serial.print("asdf");
      level = 2;
    }
    if (gamecycle > 8)
    {
      // Serial.print("asdfasdf");
      level = 3;
    }
    if (gamecycle > 13)
    {
      // Serial.print("asdfasdfasdf");
      level = 4;
    }
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
      captionString = captionString + "lives left:////////";
      break;
    case 7:
      captionString = captionString + "lives left://///// ";
      break;
    case 6:
      captionString = captionString + "lives left://////  ";
      break;
    case 5:
      captionString = captionString + "lives left://///   ";
      break;
    case 4:
      captionString = captionString + "lives left:////    ";
      break;
    case 3:
      captionString = captionString + "lives left:///     ";
      break;
    case 2:
      captionString = captionString + "lives left://      ";
      break;
    case 1:
      captionString = captionString + "lives left:/       ";
      break;
    case 0:
      captionString = captionString + "lives left:        ";
      gameon = false;
      lcd.setBackColor(179, 232, 21);
      lcd.setColor(51, 184, 135);
      lcd.setFont(BigFont);
      lcd.print("GAME OVER!!", CENTER, CENTER);
      delay(5000);
      break;
    }
    setCaption(captionString);
    setCaption_iner(String(score));
    Serial.println("setting level...");
    Serial.print("currentlevel::");
    Serial.println(String(level));
    switch (level)
    {
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
    case 4:
      number1 = random(20);
      number2 = random(20);
      break;
    }
    Serial.println("setting operator...");
    switch (random(3))
    {
    case 0:
      operator_ = "+";
      answer = number2 + number1;
      break;
    case 1:
      operator_ = "-";
      answer = number2 - number1;
      break;
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

    Serial.println("setting choose number...");
    Serial.print("answer::");
    Serial.println(answer);

    switch (random(3))
    {
    case 0:

      Serial.println("case0");
      chansor1 = answer;
      chansor2 = answer - random(15);

      while (true)
      {
        if (answer == chansor2)
        {
          Serial.println("1");
          chansor2 = answer - random(15);
          Serial.println(chansor2);
          Serial.println(answer == chansor2);
          delay(50);
        }
        else
        {
          Serial.println("1--esc");
          break;
        }
      }
      chansor3 = answer * random(1, 5);

      while (true)
      {
        if (answer == chansor3)
        {
          Serial.println("2");
          chansor3 = answer * random(1, 4);
          delay(50);

          if (chansor3 == 0)
          {
            chansor3 = answer + random(1, 5);
          }

          Serial.println(chansor3);
          Serial.println(answer == chansor3);
        }
        else
        {
          Serial.println("2--esc");
          break;
        }
      }
      chansor4 = answer * random(1, 7);

      while (true)
      {
        if (answer == chansor4)
        {
          Serial.println("3");
          chansor4 = answer * random(1, 7);
          delay(50);

          if (chansor4 == 0)
          {
            chansor4 = answer - random(1, 5);
          }

          Serial.println(chansor4);
          Serial.println(answer == chansor4);
        }
        else
        {
          break;
        }
      }
      answernumber = 1;
      break;

    case 1:
      Serial.println("case1");
      chansor1 = answer - random(15);
      while (true)
      {
        if (answer == chansor1)
        {
          Serial.println("1");
          chansor1 = answer - random(15);
          delay(50);
          Serial.println(chansor1);
          Serial.println(answer == chansor1);
        }
        else
        {
          break;
        }
      }
      chansor2 = answer;
      chansor3 = answer * random(1, 4);

      while (true)
      {
        if (answer == chansor3)
        {
          Serial.println("2");
          chansor3 = answer * random(1, 5);
          delay(50);

          if (chansor3 == 0)
          {
            chansor3 = answer - random(1, 5);
          }

          Serial.println(chansor3);
          Serial.println(answer == chansor3);
        }
        else
        {
          break;
        }
      }
      chansor4 = answer * random(1, 7);

      while (true)
      {
        if (answer == chansor4)
        {
          Serial.println("3");
          chansor4 = answer * random(1, 15);
          delay(50);

          if (chansor4 == 0)
          {
            chansor4 = answer + random(1, 5);
          }
          Serial.println(chansor4);
          Serial.println(answer == chansor4);
        }
        else
        {
          break;
        }
      }
      answernumber = 2;
      break;
    case 2:
      Serial.println("case2");
      chansor1 = answer * random(1, 3);

      while (true)
      {
        if (answer == chansor1)
        {
          Serial.println("1");
          chansor1 = answer * random(1, 4);
          delay(50);

          if (chansor1 == 0)
          {
            chansor1 = answer + random(1, 5);
          }

          Serial.println(chansor1);
          Serial.println(answer == chansor1);
        }
        else
        {
          break;
        }
      }
      chansor2 = answer - random(15);

      while (true)
      {
        if (answer == chansor2)
        {
          Serial.println("2");
          chansor2 = answer - random(15);
          delay(50);
          Serial.println(chansor2);
          Serial.println(answer == chansor2);
        }
        else
        {
          break;
        }
      }
      chansor3 = answer;
      chansor4 = answer * random(1, 8);

      while (true)
      {
        if (answer == chansor4)
        {
          Serial.println("3");
          chansor4 = answer * random(1, 9);
          delay(50);
          if (chansor4 == 0)
          {
            chansor4 = answer - random(1, 5);
          }

          Serial.println(chansor4);
          Serial.println(answer == chansor4);
        }
        else
        {
          break;
        }
      }
      answernumber = 3;
      break;

    case 3:
      Serial.println("case3");
      chansor1 = answer * random(1, 8);

      while (true)
      {
        if (answer == chansor1)
        {
          Serial.println("1");
          chansor1 = answer * random(1, 7);
          delay(50);

          if (chansor1 == 0)
          {
            chansor1 = answer + random(1, 20);
          }
          Serial.println(chansor1);
          Serial.println(answer == chansor1);
        }
        else
        {
          break;
        }
      }
      chansor2 = answer - random(15);

      while (true)
      {
        if (answer == chansor2)
        {
          Serial.println("2");
          chansor2 = answer - random(15);
          delay(50);
          Serial.println(chansor2);
          Serial.println(answer == chansor2);
        }
        else
        {
          break;
        }
      }
      chansor3 = answer * random(1, 3);

      while (true)
      {
        if (answer == chansor3)
        {
          Serial.println("3");
          chansor3 = answer * random(1, 5);
          if (chansor3 == 0)
          {
            chansor3 = answer + random(1, 20);
          }
          delay(50);
          Serial.println(chansor3);
          Serial.println(answer == chansor3);
        }
        else
        {
          break;
        }
      }
      chansor4 = answer;
      answernumber = 4;
      break;
    }
    Serial.println("---------DEBUG-------------");
    Serial.print("chansor1::");
    Serial.println(chansor1);
    Serial.print("chansor2::");
    Serial.println(chansor2);
    Serial.print("chansor3::");
    Serial.println(chansor3);
    Serial.print("chansor4::");
    Serial.println(chansor4);

    Serial.println("----------------------");

    Serial.print("number1::");
    Serial.println(number1);
    Serial.print("number2::");
    Serial.println(number2);

    Serial.println("----------------------");

    Serial.print("answernumber::");
    Serial.println(answernumber);

    Serial.println("----------------------");

    Serial.print("quiz::");
    Serial.println(quiz);
    Serial.print("Answer::");
    Serial.println(answer);
    Serial.print("operator::");
    Serial.println(operator_);

    Serial.print("gamelevel::");
    Serial.println(level);
    Serial.print("gamecycle::");
    Serial.println(gamecycle);
    Serial.println("---------DEBUGEND-------------");

    lcd.setBackColor(random(1, 140), random(1, 140), random(1, 140));
    lcd.setFont(BigFont);
    lcd.setColor(255, 255, 255);
    //    lcd.setBackColor(
    //      103, 107, 89
    //    );
    lcd.print("Whats, ", CENTER, 30);
    lcd.print(quiz, CENTER, 50);
    lcd.setBackColor(random(1, 140), random(1, 140), random(1, 140));
    lcd.setFont(SmallFont);
    lcd.print(String("1{" + String(chansor1) + " 2{" + String(chansor2) + " 3{" + String(chansor3) + " 4{" + String(chansor4)), 0, 80);
    //    lcd.print("1{" + String(chansor1), 0, 80);
    //    lcd.print("2{" + String(chansor2), 40, 80);
    //    lcd.print("3{" + String(chansor3), 85, 80);
    //    lcd.print("4{" + String(chansor4), 130, 80);

    unsigned long countdownstart = millis();
    while (true)
    {
      lcd.setColor(255, 255, 255);
      lcd.setFont(SmallFont);
      lcd.print(String("Time left: " + String((countdowntime - (millis() - countdownstart))/1000)), 20, 115);
      // Serial.print("string debug:::");
      // Serial.println("Time left: " + String(countdowntime - (millis() - countdownstart)));
      if ((millis() - countdownstart) > countdowntime)
      {
        lives = losescreen(answer, lives);
        break;
      }

      if (digitalRead(button1) || digitalRead(button2) || digitalRead(button3) || digitalRead(button4))
      {

        if (digitalRead(button1) && (answernumber == 1))
        {
          score = score + 1;
          Serial.println("win");

          winscreen(score);

          break;
        }
        if (digitalRead(button2) && (answernumber == 2))
        {
          score = score + 1;
          winscreen(score);
          Serial.println("win");
          break;
        }
        if (digitalRead(button3) && (answernumber == 3))
        {
          score = score + 1;
          Serial.println("win");
          winscreen(score);
          break;
        }
        if (digitalRead(button4) && (answernumber == 4))
        {
          score = score + 1;
          Serial.println("win");
          winscreen(score);
          break;
        }
        else
        {
          lives = losescreen(answer, lives);
          break;
        }
      }
    }
    delay(50);
  }
}
void setCaption(String caption)
{
  lcd.setFont(SmallFont);
  lcd.setColor(255, 0, 0);
  lcd.fillRect(0, 0, 159, 25);
  lcd.setColor(64, 64, 64);
  lcd.fillRect(0, 114, 159, 127);
  lcd.setColor(255, 255, 255);
  lcd.setBackColor(255, 0, 0);
  lcd.print(caption, CENTER, 1);
}

void setCaption_iner(String caption)
{
  lcd.setFont(SmallFont);
  lcd.setColor(255,255,255);
  lcd.print(caption, CENTER, 15);
}

void winscreen(int score_)
{
  lcd.setColor(255, 255, 255);
  lcd.setBackColor(209, 75, 75);
  lcd.setFont(BigFont);
  lcd.print("<Correct!>", 0, 30);

  lcd.setFont(SmallFont);
  lcd.print("Score: " + String(score_), 30, 50);

  lcd.setFont(SmallFont);
  lcd.print("continue in 1 seconds...", 0, 80);

  for (int i = 1; i != 0; i--)
  {
    lcd.print("continue in " + String(i) + " seconds...", 0, 80);
    delay(1000);
  }
}
unsigned int losescreen(int answer, int lives)
{
  Serial.print("state::");
  Serial.println(digitalRead(button1) || digitalRead(button2) || digitalRead(button3) || digitalRead(button4));
  score = score - 1;
  Serial.println("loose");
  lives = lives - 1;

  lcd.setColor(255, 255, 255);
  lcd.setBackColor(209, 75, 75);
  lcd.setFont(BigFont);
  lcd.print("<WRONG!>", 10, 30);
  lcd.setFont(SmallFont);
  lcd.print("The answer was::", 20, 50);
  lcd.setColor(255, 0, 0);
  lcd.setBackColor(255, 255, 255);
  lcd.setFont(BigFont);
  lcd.print(String(answer), 60, 60);
  lcd.setFont(SmallFont);

  lcd.setBackColor(28, 64, 38);
  lcd.setColor(185, 236, 250);
  lcd.print(String(lives) + " lives left.", 40, 100);

  lcd.setFont(SmallFont);
  lcd.print("continue in 1 seconds...", 0, 80);

  for (int i = 1; i != 0; i--)
  {
    lcd.print("continue in " + String(i) + " seconds...", 0, 80);
    delay(1000);
  }
  return lives;
}
