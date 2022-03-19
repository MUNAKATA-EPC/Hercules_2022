#include <Arduino.h>
#include <Wire.h>
#include <FaboLCDmini_AQM0802A.h>
#include <DSR1202.h>

FaBoLCDmini_AQM0802A lcd;
DSR1202 dsr1202(1);

#include "define.h"
#include "variable.h"
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
  Serial3.begin(115200); //USSとのシリアル通信
  Serial4.begin(115200); //IMUとのシリアル通信

  while (!Serial1 || !Serial2 || !Serial3 || !Serial4) { //接続待機
    ;
  }

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

  lcd.clear(); //LCD表示の全削除
}

void loop() {
  Serial_receive();
  control_LED();
  pid();
  if (LCD.state == 4 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    LINE.timer = millis() - LINE.timer_start;
    if (LINE.timer < 300) {
      Motor(1);  //方向修正
    } else if (LINE.timer < 500) {
      Motor(USS);
    } else {
      if (digitalRead(LINE_1) == LOW || digitalRead(LINE_2) == LOW || digitalRead(LINE_3) == LOW || digitalRead(LINE_4) == LOW) {
        Serial1.println("1R0002R0003R0004R000");
        LINE.timer_start = millis();
      } else {
        if (CAM_distance > 0) {
          position.timer = millis();
          position.timer_start = position.timer;
          if (CAM_distance < 70) {
            if (CAM_angle <= 6) {
              Move(CAM_angle, motor_speed);
            } else if (CAM_angle <= 180) {
              Move(CAM_angle + 100, motor_speed);
            } else if (CAM_angle < 354) {
              Move(CAM_angle - 100, motor_speed);
            } else {
              Move(CAM_angle, motor_speed);
            }
          } else if (CAM_distance < 80) {
            if (CAM_angle <= 6) {
              Move(CAM_angle, motor_speed);
            } else if (CAM_angle <= 180) {
              Move(CAM_angle + 90, motor_speed);
            } else if (CAM_angle < 354) {
              Move(CAM_angle - 90, motor_speed);
            } else {
              Move(CAM_angle, motor_speed);
            }
          } else if (CAM_distance <= 100) {
            if (CAM_angle <= 6){
              Move(CAM_angle, motor_speed);
            } else if (CAM_angle <= 180) {
              Move(CAM_angle + 80, motor_speed);
            } else if (CAM_angle < 354) {
              Move(CAM_angle - 80, motor_speed);
            } else {
              Move(CAM_angle, motor_speed);
            }
          } else {
            Move(CAM_angle, motor_speed);
          }
        } else {
          position.timer = millis() - position.timer_start;
          if (position.timer < 1500) {
            Motor(1);  //方向修正
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
  } else if (LCD.state == 5 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    Motor(1);
  } else {
    print_LCD();
    dsr1202.move(0, 0, 0, 0);
  }
}