#include <Arduino.h>
#include <DSR1202.h>
#include <Wire.h>
#include <FaBoLCDmini_AQM0802A.h>

FaBoLCDmini_AQM0802A lcd;

DSR1202 dsr1202(1); //Serial1をMDと定義する

volatile boolean line_state = false; //ラインの状態について
volatile int stay_time = 0;

#define buzzer 23 //圧電ブザー

int CAM_angle = 0;
int IMU = 0;
int USS = 0;
int CAM_distance = 0;

//void online(); //割り込み関数の定義

void setup() {
  //attachInterrupt(2, online, RISING); //ラインセンサーの割り込み処理
  pinMode(A8, INPUT);
  pinMode(13, OUTPUT);

  lcd.begin();  //LCDセットアップ

  dsr1202.Init();

  Serial.begin(115200);
  Serial1.begin(115200);  //MDのセットアップ(IMU)
  Serial2.begin(115200); //OpenMV(角度)
  Serial3.begin(115200); //Seeeduino（超音波センサ)
  Serial4.begin(115200); //IMU

  while (!Serial1 || !Serial2 || !Serial3 || !Serial4) {
    ;
  }

  lcd.setCursor(0, 0);
  lcd.print("Hello");
  lcd.setCursor(0, 1);    
  lcd.print("World!");

  tone(buzzer, 784, 1000);
  delay(1000);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 1047, 100);
  delay(100);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 1047, 100);
  delay(100);
  noTone(buzzer);

  lcd.clear();  //LCD表示の全削除
}

void receive() {
  if (Serial2.available() > 0) {
    CAM_angle = Serial2.read();
    CAM_angle = CAM_angle * 2;
  }

  if (Serial3.available() > 0) {
    USS = Serial3.read();
  }
  
  if (Serial4.available() > 0) {
    IMU = Serial4.read();
    IMU = IMU * 2;
  }
}

void LCD() {
  lcd.setCursor(0, 0);  //USSをLCDに表示
  lcd.print("USS:");
  lcd.setCursor(0, 1);  //IMUをLCDに表示
  lcd.print("IMU:");

  if (USS < 10) {
    lcd.setCursor(4, 0);
    lcd.print("0");
    lcd.setCursor(5, 0);
    lcd.print(USS);
  } else {
    lcd.setCursor(4, 0);
    lcd.print(USS);
  }

  if (IMU < 10) {
    lcd.setCursor(4, 1);
    lcd.print("00");
    lcd.setCursor(6, 1);
    lcd.print(IMU);
  } else if (IMU < 100) {
    lcd.setCursor(4, 1);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print(IMU);
  } else {
    lcd.setCursor(4, 1);
    lcd.print(IMU);
  }
}

void loop() {
  receive();

  if (CAM_angle < 27) {
      dsr1202.move(0, 0, 20, IMU);
    }
    else if (CAM_angle < 72) { //前
      dsr1202.move(45, 0, 20, IMU);
    }
    else if (CAM_angle < 117) { //usiro
      dsr1202.move(90, 0, 20, IMU);
    }
    else if (CAM_angle < 162) { //hidari
      dsr1202.move(135, 0, 20, IMU);
    }
    else if (CAM_angle < 207) { //migi
      dsr1202.move(180, 0, 20, IMU);
    }
    else if (CAM_angle < 253) { //hidarimae
      dsr1202.move(225, 0, 20, IMU);
    }
    else if (CAM_angle < 297)
    { //migimae
      dsr1202.move(270, 0, 20, IMU);
    }
    else if (CAM_angle < 342)
    { //hidariusiro
      dsr1202.move(315, 0, 20, IMU);
    }
    Serial.println(CAM_angle);

} 
        