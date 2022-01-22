#include <Arduino.h>
#include <Wire.h>
#include <FaBoLCDmini_AQM0802A.h>

FaBoLCDmini_AQM0802A lcd;

//PID制御基盤
double Y = 0; //ジャイロ中心値
double K = 10;  //比例ゲイン
double L = 0.8; //積分ゲイン
double M = 19;  //微分ゲイン
double O = 30; //操作分母量
double W, V = 0;
double X, Z = 0;
double A, B, C = 0;

void setup() {
  // put your setup code here, to run once:
}

void loop() {
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