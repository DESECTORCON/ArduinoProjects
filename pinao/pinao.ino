#include "pitches.h"

int c = 2;
int d = 4;
int e = 4;
int f = 5;
int g = 6;
int a = 7;
int b = 8;
int C = 9;

int peazo1 = 11;
int peazo2 = 12;

void setup() {
  pinMode(c, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  pinMode(e, INPUT_PULLUP);
  pinMode(f, INPUT_PULLUP);
  pinMode(g, INPUT_PULLUP);
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(C, INPUT_PULLUP);
  pinMode(peazo1, OUTPUT);
  pinMode(peazo2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //  Serial.println(digitalRead(c));

  if (digitalRead(c) == LOW) {
    while (digitalRead(c) == LOW) {
      tone(peazo1, NOTE_C4); Serial.println("c");
    }
  }


  else if (digitalRead(d) == LOW) {
    while (digitalRead(d) == LOW) {
      tone(peazo1, NOTE_D4); Serial.println("d");
    }
  }


  else if (digitalRead(e) == LOW) {
    while (digitalRead(e) == LOW) {
      tone(peazo1, NOTE_E4); Serial.println("e");
    }
  }


  else if (digitalRead(f) == LOW) {
    while (digitalRead(f) == LOW) {
      tone(peazo1, NOTE_F4); Serial.println("f");
    }
  }


  else if (digitalRead(g) == LOW) {
    while (digitalRead(g) == LOW) {
      tone(peazo1, NOTE_G4); Serial.println("g");
    }
  }


  else if (digitalRead(a) == LOW) {
    while (digitalRead(a) == LOW) {
      tone(peazo1, NOTE_A4); Serial.println("a");
    }
  }


  else if (digitalRead(b) == LOW) {
    while (digitalRead(b) == LOW) {
      tone(peazo1, NOTE_B4); Serial.println("b");
    }
  }


  else if (digitalRead(C) == LOW) {
    while (digitalRead(C) == LOW) {
      tone(peazo1, NOTE_C5); Serial.println("C");
    }
  } else {
    noTone(peazo1);
  }

}
