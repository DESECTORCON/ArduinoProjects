#include <memorysaver.h>
#include <UTFT.h>

#define button1 22
#define button2 24
#define button3 26
#define button4 28

const unsigned short qicon[400] PROGMEM = {
    0x0000, 0x0000, 0xF800, 0xC980, 0x0000, 0x0000, 0xE282, 0xE240, 0xE260, 0xE282, 0xE262, 0xE260, 0xEA60, 0xEA61, 0x0000, 0x0000, // 0x0010 (16) pixels
    0xC980, 0xF800, 0x0000, 0x0000, 0x0000, 0xF800, 0xFC00, 0x0000, 0xEA82, 0xE261, 0xF281, 0xFAE5, 0xF2E5, 0xF2A3, 0xF2A3, 0xF2E5, // 0x0020 (32) pixels
    0xFAE5, 0xF281, 0xEA61, 0xE262, 0x0000, 0xFC00, 0xF800, 0x0000, 0xF800, 0xFC00, 0x0000, 0xE262, 0xEA61, 0xF2A3, 0xEA83, 0xE0E0, // 0x0030 (48) pixels
    0xE020, 0xE180, 0xE180, 0xE000, 0xE100, 0xE283, 0xF2A3, 0xEA81, 0xE262, 0x0000, 0xFC00, 0xF800, 0xCB20, 0x0000, 0xE262, 0xFA81, // 0x0040 (64) pixels
    0xEAA4, 0xE200, 0xE1C0, 0xECF2, 0xF699, 0xFF1B, 0xFF1B, 0xF679, 0xECD1, 0xE180, 0xE220, 0xEA84, 0xFA81, 0xE262, 0x0000, 0xC980, // 0x0050 (80) pixels
    0x0000, 0xEA61, 0xEA81, 0xEA84, 0xE220, 0xEAC6, 0xF6DA, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF6BA, 0xEA83, 0xE240, // 0x0060 (96) pixels
    0xEA83, 0xEA81, 0xE262, 0x0000, 0x0000, 0xE262, 0xF2A2, 0xE262, 0xE1E0, 0xF6FB, 0xFFFF, 0xFFFF, 0xFEFB, 0xF5B5, 0xF5B5, 0xFEFB, // 0x0070 (112) pixels
    0xFFFF, 0xFFFF, 0xF6BA, 0xE1A0, 0xE283, 0xF2A2, 0xE261, 0x0000, 0xE262, 0xF281, 0xE2A4, 0xE120, 0xED12, 0xFFFF, 0xFFFF, 0xF678, // 0x0080 (128) pixels
    0xE120, 0xE000, 0xE000, 0xE140, 0xF699, 0xFFFF, 0xFFFF, 0xECD1, 0xE140, 0xEAA4, 0xF281, 0xEA61, 0xE262, 0xFA81, 0xE2A4, 0xE120, // 0x0090 (144) pixels
    0xF699, 0xFFFF, 0xFF9E, 0xEB08, 0xE1E0, 0xEAE7, 0xEAE7, 0xE1A0, 0xEB8B, 0xFFDE, 0xFFFF, 0xF679, 0xE100, 0xE2A4, 0xFA81, 0xEA62, // 0x00A0 (160) pixels
    0xE261, 0xF281, 0xE262, 0xE220, 0xFF3C, 0xFFFF, 0xFEDB, 0xE1E0, 0xE284, 0xE262, 0xE262, 0xE283, 0xE240, 0xFF1C, 0xFFFF, 0xFF1C, // 0x00B0 (176) pixels
    0xE1E0, 0xEA83, 0xF281, 0xE262, 0xE261, 0xF282, 0xE240, 0xEAA4, 0xFF7D, 0xFFFF, 0xF699, 0xE180, 0xE283, 0xE262, 0xE284, 0xE2A5, // 0x00C0 (192) pixels
    0xE200, 0xF6DA, 0xFFFF, 0xFF3C, 0xE240, 0xE261, 0xF282, 0xE261, 0xEA61, 0xF282, 0xE260, 0xE282, 0xFF5D, 0xFFFF, 0xF6BA, 0xE1A0, // 0x00D0 (208) pixels
    0xE282, 0xE283, 0xE200, 0xE0C0, 0xE160, 0xFEFB, 0xFFFF, 0xFF3C, 0xE200, 0xE262, 0xF281, 0xE261, 0xE262, 0xF281, 0xE284, 0xE1A0, // 0x00E0 (224) pixels
    0xFEFB, 0xFFFF, 0xFF5C, 0xE240, 0xE2A5, 0xE240, 0xEBED, 0xF658, 0xEC0D, 0xFF7D, 0xFFFF, 0xF6BA, 0xE140, 0xEAA4, 0xF281, 0xE262, // 0x00F0 (240) pixels
    0xE262, 0xFA81, 0xE2A5, 0xE0C0, 0xF5F6, 0xFFFF, 0xFFFF, 0xED12, 0xE000, 0xE000, 0xF658, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xF574, // 0x0100 (256) pixels
    0xE0E0, 0xE2A4, 0xFA81, 0xE262, 0xE262, 0xF281, 0xE283, 0xE200, 0xEB6A, 0xFFDE, 0xFFFF, 0xFFBE, 0xED53, 0xEB07, 0xEC6F, 0xFFBE, // 0x0110 (272) pixels
    0xFFFF, 0xFFFF, 0xFF3C, 0xE200, 0xE240, 0xE283, 0xF282, 0xE282, 0x0000, 0xE262, 0xFAA2, 0xE2A4, 0xE140, 0xECF2, 0xFFFF, 0xFFFF, // 0x0120 (288) pixels
    0xFFFF, 0xFFBE, 0xFF9E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFF7D, 0xEC2E, 0xE200, 0xF2A3, 0xE261, 0x0000, 0x0000, 0xE261, 0xEA61, 0xEA62, // 0x0130 (304) pixels
    0xE2A4, 0xE140, 0xEC4F, 0xFEFB, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF699, 0xF6DA, 0xFFFF, 0xF6BA, 0xE140, 0xEAA4, 0xEA60, 0x0000, // 0x0140 (320) pixels
    0xFB20, 0x0000, 0xEA61, 0xF281, 0xEA61, 0xE2A4, 0xE180, 0xE1A0, 0xEB8B, 0xEC4F, 0xEC4F, 0xEB8B, 0xE040, 0xE2A5, 0xF617, 0xEB6A, // 0x0150 (336) pixels
    0xF220, 0xE284, 0x0000, 0xCB20, 0xF800, 0xFAA0, 0x0000, 0xEA61, 0xEA61, 0xFA81, 0xE2A4, 0xE283, 0xE1E0, 0xE160, 0xE160, 0xE1E0, // 0x0160 (352) pixels
    0xE2A5, 0xE260, 0xF0C0, 0xEA20, 0xE284, 0x0000, 0xFC00, 0xF800, 0x0000, 0x0000, 0xFAA0, 0x0000, 0xE261, 0xE262, 0xF281, 0xFAA1, // 0x0170 (368) pixels
    0xF2A3, 0xF2C5, 0xF2C5, 0xF2A3, 0xFA80, 0xF282, 0xE2C6, 0xEAA5, 0x0000, 0xFC00, 0xF800, 0x0000, 0x0000, 0x0000, 0xF800, 0xFB20, // 0x0180 (384) pixels
    0x0000, 0x0000, 0xE262, 0xE262, 0xE261, 0xEA60, 0xE260, 0xE261, 0xE262, 0xE241, 0x0000, 0x0000, 0xCB26, 0xF800, 0x0000, 0x0000, // 0x0190 (400) pixels
};

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
  unsigned int lives = 7;
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
      countdowntime = 3000;
    }
    if (gamecycle > 13)
    {
      // Serial.print("asdfasdfasdf");
      level = 4;
      // countdowntime = 2500;
    }
    if (gamecycle > 16)
    {
      level = 5;
      countdowntime = 7000;
    }
    if (gamecycle > 25)
    {
      level = 6;
      countdowntime = 12000;
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
    case 7:
      captionString = captionString + "lives left:///////";
      break;
    case 6:
      captionString = captionString + "lives left:////// ";
      break;
    case 5:
      captionString = captionString + "lives left://///  ";
      break;
    case 4:
      captionString = captionString + "lives left:////   ";
      break;
    case 3:
      captionString = captionString + "lives left:///    ";
      break;
    case 2:
      captionString = captionString + "lives left://     ";
      break;
    case 1:
      captionString = captionString + "lives left:/      ";
      break;
    case 0:
      captionString = captionString + "lives left:       ";
      gameon = false;

      lcd.setColor(21, 230, 104);
      lcd.drawRoundRect(5, 5, 160, 130);
      lcd.setBackColor(179, 232, 21);
      lcd.setColor(51, 184, 135);
      lcd.setFont(BigFont);
      lcd.print("GAME OVER!!", CENTER, CENTER);
      lcd.setColor(242, 61, 255);
      lcd.setFont(SmallFont);
      lcd.print("Your Score:" + String(score), CENTER, CENTER + 50);
      lcd.print("Reset in 5 seconds...", CENTER - 20, CENTER - 20);

      delay(5000);
      break;
    }

    if (!gameon)
    {
      break;
    }

    setCaption(captionString);
    setCaption_iner("score:" + String(score));
    lcd.print("level:" + String(level), 100, 115);
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
    case 5:
      number1 = random(1, 25);
      number1 = random(1, 25);
    case 6:
      number1 = random(1, 30);
      number1 = random(1, 30);
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

      chansor2 = answerfinder(answer, 1);

      chansor3 = answerfinder(answer, 2);

      chansor4 = answerfinder(answer, 3);
      answernumber = 1;
      break;

    case 1:
      Serial.println("case1");

      chansor1 = answerfinder(answer, 1);

      chansor2 = answer;

      chansor3 = answerfinder(answer, 2);

      chansor4 = answerfinder(answer, 3);

      answernumber = 2;
      break;
    case 2:
      Serial.println("case2");

      chansor1 = answerfinder(answer, 1);

      chansor2 = answerfinder(answer, 2);
      chansor3 = answer;

      chansor4 = answerfinder(answer, 3);

      answernumber = 3;
      break;

    case 3:
      Serial.println("case3");

      chansor1 = answerfinder(answer, 1);

      chansor2 = answerfinder(answer, 2);

      chansor3 = answerfinder(answer, 3);

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
    lcd.drawBitmap(2, 30, 20, 20, qicon);
    lcd.print("Whats, ", CENTER + 10, 30);
    lcd.print(quiz, CENTER, 50);
    lcd.setBackColor(random(1, 140), random(1, 140), random(1, 140));
    lcd.setFont(SmallFont);
    lcd.print(String("1{" + String(chansor1) + " 2{" + String(chansor2)), 1, 70);
    lcd.print(String(" 3{" + String(chansor3) + " 4{" + String(chansor4)), 50, 90);
    //    lcd.print("1{" + String(chansor1), 0, 80);
    //    lcd.print("2{" + String(chansor2), 40, 80);
    //    lcd.print("3{" + String(chansor3), 85, 80);
    //    lcd.print("4{" + String(chansor4), 130, 80);

    unsigned long countdownstart = millis();
    while (true)
    {
      lcd.setColor(255, 255, 255);
      lcd.setFont(SmallFont);
      lcd.print(String("Time left:" + String((countdowntime - (millis() - countdownstart)) / 1000)), 5, 115);
      // Serial.print("string debug:::");
      // Serial.println("Time left: " + String(countdowntime - (millis() - countdownstart)));
      if ((millis() - countdownstart) > countdowntime)
      {
        lives = losescreen(answer, lives, score);
        break;
      }

      if (digitalRead(button1) || digitalRead(button2) || digitalRead(button3) || digitalRead(button4))
      {

        if (digitalRead(button1) && (answernumber == 1))
        {
          score = score + 1;
          Serial.println("win");

          winscreen(score, lives);

          break;
        }
        if (digitalRead(button2) && (answernumber == 2))
        {
          score = score + 1;
          winscreen(score, lives);
          Serial.println("win");
          break;
        }
        if (digitalRead(button3) && (answernumber == 3))
        {
          score = score + 1;
          Serial.println("win");
          winscreen(score, lives);
          break;
        }
        if (digitalRead(button4) && (answernumber == 4))
        {
          score = score + 1;
          Serial.println("win");
          winscreen(score, lives);
          break;
        }
        else
        {
          lives = losescreen(answer, lives, score);
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
  lcd.setColor(255, 255, 255);
  lcd.print(caption, CENTER, 13);
}

void winscreen(int score_, int lives)
{
  // clear_screen();
  lcd.setBackColor(72, 250, 223);
  lcd.setColor(72, 250, 223);
  lcd.fillRoundRect(5, 5, 155, 125);

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
unsigned int losescreen(int answer, int lives, int score)
{
  // clear_screen();
  lcd.setBackColor(252, 81, 81);
  lcd.setColor(252, 81, 81);
  lcd.fillRoundRect(5, 5, 155, 125);

  Serial.print("state::");
  Serial.println(digitalRead(button1) || digitalRead(button2) || digitalRead(button3) || digitalRead(button4));
  score = score - 1;
  Serial.println("loose");
  lives = lives - 1;

  lcd.setColor(255, 255, 255);
  lcd.setBackColor(209, 75, 75);
  lcd.setFont(BigFont);
  lcd.print("<WRONG!>", 10, 10);
  lcd.setFont(SmallFont);
  lcd.print("The answer was::", 20, 30);
  lcd.setColor(255, 0, 0);
  lcd.setBackColor(255, 255, 255);
  lcd.setFont(BigFont);
  lcd.print(String(answer), 60, 45);
  lcd.setFont(SmallFont);

  lcd.setBackColor(242, 199, 80);
  lcd.fillRoundRect(5,50, 150, 120);
  lcd.setBackColor(28, 64, 38);
  lcd.setColor(185, 236, 250);
  lcd.print(String(lives) + " lives left.", 40, 55);

  lcd.setFont(SmallFont);
  lcd.print("continue in 1 seconds...", 0, 80);

  for (int i = 1; i != 0; i--)
  {
    lcd.print("continue in " + String(i) + " seconds...", 0, 80);
    delay(1000);
  }
  return lives;
}

int answerfinder(int answer, int exnumber)
{
  int chansor = 1;
  // chansor = answer - random(15);
  while (true)
  {
    Serial.println(exnumber);
    switch (random(1, 4))
    {
    case 1:
      chansor = answer - random(20);
      break;
    case 2:
      chansor = answer + random(20);
      break;
    case 3:
      chansor = answer * random(1, 10);
      break;
    }
    if (answer == chansor)
    {
      Serial.println(chansor);
      Serial.println(answer == chansor);
      delay(50);
    }
    else
    {
      Serial.println(String(answer) + "--esc");
      break;
    }
  }
  return chansor;
}
