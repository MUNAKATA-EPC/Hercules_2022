#include <Arduino.h>
#include <Wire.h>
#include <FaboLCDmini_AQM0802A.h>

FaBoLCDmini_AQM0802A lcd;

int gyro; //ジャイロセンサ値
int USS;  //超音波センサ値(方向指定値)

double Y = 0; //ジャイロ中心値
double K = 10;  //比例ゲイン
double L = 0.8; //積分ゲイン
double M = 19;  //微分ゲイン
double O = 30; //操作分母量
double W, V = 0;
double X, Z = 0;
double A, B, C = 0;

void setup() {
  lcd.begin();  //LCDの準備開始

  Serial.begin(250000); //USBシリアル通信開始
  Serial3.begin(250000);  //USSとのシリアル通信
  Serial4.begin(250000);  //ジャイロセンサとのシリアル通信

  while (!Serial3 || !Serial4) {  //接続待機
    lcd.setCursor(0, 0);
    lcd.print("Hello");
    lcd.setCursor(0, 1);
    lcd.print("World!");
  }

  lcd.clear();  //LCD表示の全削除
}

void PID() {
  X = 0 - Y;  //偏差:現在角度と目標角度のズレ(0は実際にはMPU6050からの値)
  W = W + X;  //偏差の積分値
  Z = X - V;  //偏差の微分値
  V = X;  //微分用前回偏差値の保存
  A = K * X;  //比例ゲイン*偏差
  B = L * W;  //積分ゲイン*偏差の積分値
  C = M * Z;  //微分ゲイン*偏差の微分値
  A = A + B + C;  //最終的な操作量
  A = A / O;  //ゲインを1未満で設定できるように、共通分母で割る(通常ゲインは1以上で設定できない)

  if (A < -30) {
    A = -30;  //下限値
  } else if (A > 30) {
    A = 30; //上限値
  }
  
  A = -A; //操作量の反転(最終的な操作量)
}

void LCD() {
  if (Serial4.available() > 0) {  //ジャイロ入力待ち
    gyro = Serial4.read();
  }

  if (Serial3.available() > 0) {  //USS入力待ち
    USS = Serial3.read();
  }

  Serial.print(gyro); //シリアルモニタ用
  Serial.print("\t");
  Serial.println(USS);
  
  lcd.setCursor(0, 0);  //GyroをLCDに表示
  lcd.print("Gyro:");
  lcd.setCursor(0, 1);  //USSをLCDに表示
  lcd.print("USS:");

  if (gyro < 10) {
    lcd.setCursor(5, 0);
    lcd.print("00");
    lcd.setCursor(7, 0);
    lcd.print(gyro);
  } else if (gyro < 100) {
    lcd.setCursor(5, 0);
    lcd.print("0");
    lcd.setCursor(6, 0);
    lcd.print(gyro);
  } else {
    lcd.setCursor(5, 0);
    lcd.print(gyro);
  }
  
  if (USS < 10) {
    lcd.setCursor(4, 1);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print(USS);
  } else {
    lcd.setCursor(4, 1);
    lcd.print(USS);
  }
}

void loop() {
  PID();
  LCD();
}