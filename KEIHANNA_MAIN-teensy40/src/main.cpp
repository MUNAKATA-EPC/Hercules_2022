//ライブラリ読み込み
#include <Arduino.h>
#include <DSR1202.h>
#include <MGLCD.h>
#include <MGLCD_SPI.h>
#include <SPI.h>

//ライブラリセットアップ
DSR1202 dsr1202(1);

#define CS_PIN 10
#define DI_PIN 34
#define MAX_FREQ (1000*1000L)

MGLCD_AQM1248A_SPI MGLCD(MGLCD_SpiPin2(CS_PIN, DI_PIN), MAX_FREQ);

//定数置き場
#define buzzer 33 //圧電ブザー
#define button_LCD_R 27 //タクトスイッチ(右)
#define button_LCD_L 32 //タクトスイッチ(左)
#define switch_program 31  //トグルスイッチ
#define button_LCD_C 30 //タクトスイッチ(コマンド)
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

Status LCD, LCD_R, LCD_L, LCD_C;
Timer LINE, position, hyouji;

int val_I;
int deviation, old_deviation, val_D;
float operation_A, operation_B, operation_C;

int motor[4]; //モーター出力
int MotorPower[4];  //最終操作量

//ヘッダファイル読み込み
#include "Serial_receive.h"
#include "print_LCD.h"
#include "pid_parameter.h"
#include "pid.h"
#include "motor.h"

void setup() {
  pinMode(button_LCD_R, INPUT);
  pinMode(button_LCD_L, INPUT);
  pinMode(button_LCD_C, INPUT);
  pinMode(switch_program, INPUT);
  pinMode(LINE_1, INPUT);
  pinMode(LINE_2, INPUT);
  pinMode(LINE_3, INPUT);
  pinMode(LINE_4, INPUT);

  MGLCD.Reset();  //液晶初期化

  MGLCD.SetRegulatorVoltage(3); //コントラスト粗調整

  MGLCD.Locate(15, 3);
  MGLCD.print("HELLO!");
  MGLCD.Locate(6, 5);
  MGLCD.print("MUNAKO HERCULES");

  dsr1202.Init(); //MD準備(USBシリアルも同時開始)
  
  Serial2.begin(115200);  //CAMとのシリアル通信
  Serial3.begin(115200);  //USSとのシリアル通信
  Serial4.begin(115200);  //IMUとのシリアル通信
  
  tone(buzzer, 2093, 100);

  MGLCD.ClearScreen();  //液晶表示削除
}

void loop() {
  Serial_receive();
  pid();
  if (LCD.state == 0 && LCD_C.state == 1 && digitalRead(switch_program) == LOW) {
    LINE.timer = millis() - LINE.timer_start;
    if (LINE.timer < 300) {
      Move(0, 0);
    } else if (LINE.timer < 500) {
      Move(CAM_FieldAngle, motor_speed);
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
          if (CAM_distance <= 55) {
            if (CAM_angle < 84) {
              Move((CAM_angle - 90), motor_speed);
            } else if (CAM_angle <= 106) {
              Move(CAM_angle, motor_speed);
            } else if (CAM_angle <= 270) {
              Move((CAM_angle + 90), motor_speed);
            } else {
              Move((CAM_angle - 90), motor_speed);
            }
          } else {
            Move(CAM_angle, motor_speed);
          }
        } else {
          position.timer = millis() - position.timer_start;
          if (position.timer < 1500) {
            Move(0, 0);
          } else {
            if ((CAM_FieldAngle >= 0) || (CAM_FieldAngle >= 180)) {
              Move(CAM_FieldAngle, 0);
            } else {
              Move(CAM_FieldAngle, motor_speed);
            }
          }
        }
      }
    }
  } else if (LCD.state == 5 && LCD_C.state == 1 && digitalRead(switch_program) == LOW) {
    Move(90, 0);
  } else {
    print_LCD();
    dsr1202.move(0, 0, 0, 0);
  }
}