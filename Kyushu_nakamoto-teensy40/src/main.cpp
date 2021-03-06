#include <Arduino.h>
#include <Wire.h>
#include <FaboLCDmini_AQM0802A.h>
#include <DSR1202.h>

FaBoLCDmini_AQM0802A lcd;
DSR1202 dsr1202(1);

#include "define.h"
#include "variable.h"
#include "startup.h"
#include "Serial_receive.h"
#include "print_LCD.h"
#include "control_LED.h"
#include "pid_parameter.h"
#include "pid.h"
#include "motor.h"

void setup() {
  startup();
}

void loop() {
  Serial_receive();
  print_LCD();
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
          if (CAM_distance < 90) {
            if (CAM_area == 2) {  //前
              Motor(2);
            } else if (CAM_area == 3) { //後
              Motor(8);
            } else if (CAM_area == 4) { //左
              Motor(3);
            } else if (CAM_area == 5) { //右
              Motor(3);
            } else if (CAM_area == 6) { //左前
              Motor(8);
            } else if (CAM_area == 7) { //右前
              Motor(9);
            } else if (CAM_area == 8) { //左後
              Motor(9);
            } else if (CAM_area == 9) { //右後
              Motor(8);
            }
          } else {
            Motor(CAM_area);
          }
        } else {
          position.timer = millis() - position.timer_start;
          if (position.timer < 2000) {  //ボールが見えなくなって2秒以内
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
    dsr1202.move(0, 0, 0, 0);
  }
}