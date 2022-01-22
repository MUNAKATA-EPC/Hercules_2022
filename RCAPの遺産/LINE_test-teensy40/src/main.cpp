#include <Arduino.h>

#define LINE_ALL 22 //全体のまとめ
#define LINE_1 2
#define LINE_2 3
#define LINE_3 4
#define LINE_4 5

int O, A, B, C, D = 0;

void setup() {
  Serial.begin(115200);
  //pinMode(LINE_ALL, INPUT);
  pinMode(LINE_1, INPUT);
  pinMode(LINE_2, INPUT);
  pinMode(LINE_3, INPUT);
  pinMode(LINE_4, INPUT);
}

void loop() {
  O = analogRead(LINE_ALL);
  A = digitalRead(LINE_1);
  B = digitalRead(LINE_2);
  C = digitalRead(LINE_3);
  D = digitalRead(LINE_4);

  Serial.print("ALL:");
  Serial.print(O);
  Serial.print("\t");
  Serial.print("LINE_1:");
  Serial.print(A);
  Serial.print("\t");
  Serial.print("LINE_2:");
  Serial.print(B);
  Serial.print("\t");
  Serial.print("LINE_3:");
  Serial.print(C);
  Serial.print("\t");
  Serial.print("LINE_4:");
  Serial.println(D);
}