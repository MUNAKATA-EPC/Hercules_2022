//ライブラリ読み込み
#include <Arduino.h>
#include <Wire.h>
#include <FaboLCDmini_AQM0802A.h>
#include <DSR1202.h>

//ライブラリセットアップ
FaBoLCDmini_AQM0802A lcd;
DSR1202 dsr1202(1);

//定数置き場
#define buzzer 23 //圧電ブザー
#define button_LCD 11 //タクトスイッチ
#define switch_program 9  //トグルスイッチ
#define button_white 10 //白いボタン
#define LED 13
#define LINE_1 2
#define LINE_2 3
#define LINE_3 4
#define LINE_4 5

//グローバル変数置き場(本当は減らしたいけど初心者なので当分このまま)
int head_CAM, CAM_angle, CAM_distance, CAM_FieldAngle;  //OpenMV 
int head_USS, USS, USS1, USS2, USS3, USS4;  //USS
int IMU; //IMU値

class Status {
public:
  int val, old_val;
  int state;
};

class Timer {
public:
  unsigned long timer, timer_start;
};

Status LCD, white;
Timer LINE, position;

int val_I;
int deviation, old_deviation, val_D;
float operation_A, operation_B, operation_C;

int motor[4]; //モーター出力
int MotorPower[4];  //最終操作量

//ヘッダファイル読み込み
#include "Serial_receive.h"
#include "print_LCD.h"
#include "control_LED.h"
#include "pid_parameter.h"
#include "pid.h"
#include "motor.h"

void setup() {
  pinMode(button_LCD, INPUT);
  pinMode(switch_program, INPUT);
  pinMode(button_white, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(LINE_1, INPUT);
  pinMode(LINE_2, INPUT);
  pinMode(LINE_3, INPUT);
  pinMode(LINE_4, INPUT);

  lcd.begin(); //LCDの準備開始

  lcd.setCursor(0, 0);
  lcd.print("System");
  lcd.setCursor(0, 1);
  lcd.print("booting");

  dsr1202.Init(); //MD準備(USBシリアルも同時開始)
  
  Serial2.begin(115200);  //CAMとのシリアル通信
  Serial3.begin(115200);  //USSとのシリアル通信
  Serial4.begin(115200);  //IMUとのシリアル通信

  while ((!Serial2) || (!Serial3) || (!Serial4)) { //接続待機
    noTone(buzzer);
  }
  
  tone(buzzer, 2093, 100);

  lcd.clear(); //LCD表示の全削除
}

void loop() {
  Serial_receive();
  control_LED();
  pid();
  if (LCD.state == 4 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    LINE.timer = millis() - LINE.timer_start;
    if (LINE.timer < 300) {
      Move(0, 0);
    } else if (LINE.timer < 500) {
      Move(CAM_FieldAngle, (motor_speed * 0.75));
    } else {
      if ((digitalRead(LINE_1) == LOW) || (digitalRead(LINE_2) == LOW) || (digitalRead(LINE_3) == LOW) || (digitalRead(LINE_4) == LOW)) {
        for (size_t i = 0; i < 50; i++) {
          Serial1.println("1R0002R0003R0004R000");
        }
        LINE.timer_start = millis();
      } else {
        if (CAM_distance > 0) {
          position.timer = millis();
          position.timer_start = position.timer;
          if (CAM_distance <= 57) {
            if (CAM_angle <= 16) {
              Move(CAM_angle, motor_speed);
            } else if (CAM_angle <= 180) {
              Move((CAM_angle + 90), motor_speed);
            } else if (CAM_angle < 344) {
              Move((CAM_angle - 90), motor_speed);
            } else {
              Move(CAM_angle, motor_speed);
            }
          } else {
            Move(CAM_angle, motor_speed);
          }
        } else {
          position.timer = millis() - position.timer_start;
          if (position.timer < 1500) {
            Move(0, 0);
          } else {
            if ((CAM_FieldAngle <= 90) || (CAM_FieldAngle >= 270)) {
              Move(CAM_FieldAngle, 0);
            } else {
              Move(CAM_FieldAngle, (motor_speed * 0.75));
            }
          }
        }
      }
    }
  } else if (LCD.state == 5 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    Move(0, 0);
  } else {
    print_LCD();
    dsr1202.move(0, 0, 0, 0);
  }
}