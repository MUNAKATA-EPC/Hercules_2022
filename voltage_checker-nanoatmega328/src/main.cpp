#include <Arduino.h>

#define buzzer 3  //ブザー接続ピン

double V1 = 0;  //セル1の電圧
double V2 = 0;  //セル2の電圧
double V3 = 0;  //セル3の電圧
double V = 0;  //全体での電圧
double a = 0; // = V1
double b = 0; // = ( V1 + V2 ) / 2
double c = 0; // = ( V1 + V2 + V3 ) / 3

void setup() {
  Serial.begin(250000);  //シリアル通信開始
}

void loop() {
  a = analogRead(3);
  b = analogRead(2);
  c = analogRead(1);
  a = a * 5.0 / 1024.0;  //電圧に変換
  b = b * 5.0 / 1024.0;
  c = c * 5.0 / 1024.0;
  V1 = a;
  V2 = b * 2 - a;
  V3 =  c * 3 - b * 2;
  V = V1 + V2 + V3;
  V1 = 0.9393 * V1 - 0.00005;
  V2 = 0.9403 * V2 + 0.0004;
  V3 = 0.9504 * V3 - 0.0008;
  V = 0.942 * V - 0.0001;
  Serial.print("V1: ");
  Serial.print(V1);
  Serial.print("\t");
  Serial.print("V2: ");
  Serial.print(V2);
  Serial.print("\t");
  Serial.print("V3: ");
  Serial.print(V3);
  Serial.print("\t");
  Serial.print("V: ");
  Serial.println(V);
  delay(500);

  if ( V > 0 ) {
    if ( V1 < 3.90 || V2 < 3.90 || V3 < 3.90 ) {
      tone(buzzer, 587, 200);  //レ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 300);  //ソ5
      delay(300);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 300);  //ソ5
      delay(300);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 400);  //ラ5
      delay(400);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 1047, 200); //ド6
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 1175, 200); //レ6
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 200);  //ソ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 587, 200);  //レ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 300);  //ソ5
      delay(300);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 300);  //ソ5
      delay(300);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 400);  //ラ5
      delay(400);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 932, 200);  //ラ#5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 200);  //ソ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 587, 200);  //レ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 300);  //ソ5
      delay(300);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 300);  //ソ5
      delay(300);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 400);  //ラ5
      delay(400);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 1047, 200); //ド6
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 1175, 200); //レ6
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 200);  //ソ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(250);

      tone(buzzer, 587, 200); //レ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 932, 400);  //ラ#5
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 400);  //ラ5
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 784, 400);  //ソ5
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 400);  //ファ5
      delay(400);
      noTone(buzzer);
      delay(50);

      tone(buzzer, 784, 200);  //ソ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 698, 200);  //ファ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 880, 200);  //ラ5
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 1047, 200) ; //ド6
      delay(200) ;
      noTone(buzzer) ;
      delay(50) ;
      tone(buzzer, 1175, 1000) ; //レ6
      delay(1000) ;
      noTone(buzzer) ;
      delay(1000) ;
    }
  }
}