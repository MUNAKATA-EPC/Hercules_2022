//ライブラリ読み込み
#include <Arduino.h>
#include <DSR1202.h>
#include <U8g2lib.h>

//ライブラリセットアップ
DSR1202 dsr1202(1);

//AQM1248Aは128 * 48
U8G2_ST7565_AK_AQM1248_F_4W_HW_SPI u8g2(U8G2_R0, 10, 34, 35); //CS, DC(RS), Reset(適当)

//定数置き場
#define buzzer 33 //圧電ブザー
#define button_LCD_R 27 //タクトスイッチ(右)
#define button_LCD_L 32 //タクトスイッチ(左)
#define switch_program 31  //トグルスイッチ
#define button_LCD_C 30 //タクトスイッチ(コマンド)
#define LINE_1 2  //前
#define LINE_2 3  //右
#define LINE_3 4  //後
#define LINE_4 5  //左
#define LED 9

//グローバル変数置き場(本当は減らしたいけど初心者なので当分このまま)
int head_CAM, CAM_angle, CAM_distance, CAM_YellowAngle, CAM_BlueAngle;  //OpenMVから受け取るデータ用
int head_USS, USS, USS1, USS2, USS3, USS4;  //USSから受け取るデータ用
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
Timer LINE, position, Ball;

int val_I;
int deviation, old_deviation, val_D;
float operation_A, operation_B, operation_C;

int motor[4]; //モーター出力(前向いてるときの各モーターの出力値設定)
int MotorPower[4];  //最終操作量(方向修正による操作量を含めた最終モーター出力値)

//ヘッダファイル読み込み
#include "Serial_receive.h"
#include "print_LCD.h"
#include "pid_parameter.h"
#include "pid.h"
#include "motor.h"

void setup() {
  u8g2.begin(); //LCD初期化

  u8g2.setFlipMode(1);  //反転は1(通常表示は0)

  u8g2.clearBuffer(); //内部メモリクリア(毎回表示内容更新前に置く)
  u8g2.setFont(u8g2_font_ncenB14_tr);	//フォント選択(これは横に14ピクセル、縦に14ピクセル)
  u8g2.drawStr(0,31,"Hello World!");	//書き込み内容書くところ(画面左端から横に何ピクセル、縦に何ピクセルか指定。ちなみに、文字の左下が指示座標になる。)
  u8g2.sendBuffer();  //ディスプレイに送る(毎回書く)

  //tone(buzzer, 1568, 100);  //通電確認音

  //各ピン設定開始
  pinMode(button_LCD_R, INPUT);
  pinMode(button_LCD_L, INPUT);
  pinMode(button_LCD_C, INPUT);
  pinMode(switch_program, INPUT);
  pinMode(LINE_1, INPUT);
  pinMode(LINE_2, INPUT);
  pinMode(LINE_3, INPUT);
  pinMode(LINE_4, INPUT);

  dsr1202.Init(); //MD準備(USBシリアルも同時開始)
  
  Serial2.begin(115200);  //OpenMVとのシリアル通信
  Serial3.begin(115200);  //USSとのシリアル通信
  Serial4.begin(115200);  //IMUとのシリアル通信
  
  //tone(buzzer, 2093, 100);  //起動確認音

  //Adventurer 3 Lite
  tone(buzzer, 1046.502, 1000); //ド6
  delay(1000);
  noTone(buzzer);
  delay(250);
  tone(buzzer, 1318.510, 150); //ミ6
  delay(150);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 1396.913, 250); //ファ6
  delay(250);
  noTone(buzzer);
  delay(150);
  tone(buzzer, 1567.982, 150); //ソ6
  delay(150);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 1760.000, 300); //ラ6
  delay(300);
  noTone(buzzer);
  delay(100);
  tone(buzzer, 1567.982, 250); //ソ6
  delay(250);
  noTone(buzzer);
  delay(200);
  tone(buzzer, 1567.982, 250); //ソ6
  delay(250);
  noTone(buzzer);
  delay(200);
  tone(buzzer, 2093.005, 250); //ド7
  delay(250);
  noTone(buzzer);
}

void loop() {
  Serial_receive();
  pid();
  if ((LCD.state == 0) && (LCD_C.state == 1) && (digitalRead(switch_program) == LOW)) {
    LINE.timer = millis() - LINE.timer_start;
    if (LINE.timer < 150) {
      if (IMU == 10) {
        LINE.timer = 300;
        goto Ball;  //Ballラベルまで飛ぶ
      }
      Move(0, 0);
    } else if (LINE.timer < 300) {
      if (IMU == 10) {
        LINE.timer = 300;
        goto Ball;  //上に同じ
      }
      Motor(USS);
    } else {
      if ((digitalRead(LINE_1) == LOW) || (digitalRead(LINE_2) == LOW) || (digitalRead(LINE_4) == LOW)) {
        if (USS == 10) {
          goto Ball;  //上に同じ
        }
        for (size_t i = 0; i < 10; i++) {
          Serial1.println("1R0002R0003R0004R000");
        }
        LINE.timer_start = millis();
      } else {
        Ball: //超音波のパターン次第でライン見ずにここまで飛ぶ
        if (CAM_distance > 0) {
          position.timer = millis();
          position.timer_start = position.timer;
          Ball.timer = millis() - Ball.timer_start;
          if (Ball.timer <= 500) { //標準速度
            if (CAM_distance <= 52) {
              if (CAM_angle <= 20) {
                Move(CAM_angle, motor_speed);
              } else if (CAM_angle <= 180) {
                Move((CAM_angle + 90), motor_speed);
                Ball.timer_start = millis();
              } else if (CAM_angle < 340) {
                Move((CAM_angle - 90), motor_speed);
                Ball.timer_start = millis();
              } else {
                Move(CAM_angle, motor_speed);
              }
            } else {
              Move(CAM_angle, motor_speed);
              Ball.timer_start = millis();
            }
          } else {  //マキシマムモード(一定時間経過後パワーを2%上げる)
            if (CAM_distance <= 52) {
              if (CAM_angle <= 20) {
                Move(CAM_angle, (motor_speed + 3));
              } else if (CAM_angle <= 180) {
                Move((CAM_angle + 90), motor_speed);
                Ball.timer_start = millis();
              } else if (CAM_angle < 340) {
                Move((CAM_angle - 90), motor_speed);
                Ball.timer_start = millis();
              } else {
                Move(CAM_angle, (motor_speed + 3));
              }
            } else {
              Move(CAM_angle, motor_speed);
              Ball.timer_start = millis();
            }
          }
        } else {
          position.timer = millis() - position.timer_start;
          if (position.timer < 2000) {
            Move(0, 0);
          } else {
            if (USS3 > 50) {
              if (USS2 < 70) {
                if (USS4 < 70) {
                  Motor(3);  //後
                } else {
                  Motor(9);  //右後
                }
              } else if (USS4 < 70) {
                Motor(8);  //左後
              } else {
                Motor(3);  //後
              }
            } else if (USS2 < 70) {
              if (USS4 < 70) {
                Motor(1);  //方向修正
              } else {
                Motor(5);  //右
              }
            } else if (USS4 < 70) {
              Motor(4);  //左
            } else {
              Motor(1);  //方向修正
            }
          }
        }
      }
    }
  } else if ((LCD.state == 7) && (LCD_C.state == 1) && (digitalRead(switch_program) == LOW)) {
    Move(0, 0);
  } else {
    print_LCD();
    dsr1202.move(0, 0, 0, 0);
  }
}