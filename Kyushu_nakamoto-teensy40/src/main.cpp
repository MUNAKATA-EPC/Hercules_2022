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
#include "motor.h"

void setup() {
  startup();
}

void loop() {
  if (LCD.state == 4 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    Serial_receive();
    control_LED();
    timer = millis() - timer_start;

    if (timer < 300) {
      Motor_1();  //方向修正
    } else if (timer < 500) {
      if (latest_USS == 1) {
        Motor_1();  //方向修正
      } else if (latest_USS == 2) {
        Motor_2();  //前
      } else if (latest_USS == 3) {
        Motor_3();  //後
      } else if (latest_USS == 4) {
        Motor_4();  //左
      } else if (latest_USS == 5) {
        Motor_5();  //右
      } else if (latest_USS == 6) {
        Motor_6();  //左前
      } else if (latest_USS == 7) {
        Motor_7();  //右前
      } else if (latest_USS == 8) {
        Motor_8();  //左後
      } else if (latest_USS == 9) {
        Motor_9();  //右後
      }
    } else {
      if (digitalRead(LINE_1) == LOW || digitalRead(LINE_2) == LOW || digitalRead(LINE_3) == LOW || digitalRead(LINE_4) == LOW) {
        //for (size_t i = 0; i <= 300; i++) {
          //Serial1.println("1R0002R0003R0004R000");
        //}
        Serial1.println("1R0002R0003R0004R000");
        if (USS == 1) {
          latest_USS = 1;
        } else if (USS == 2) {
          latest_USS = 2;
        } else if (USS == 3) {
         latest_USS = 3;
        } else if (USS == 4) {
          latest_USS = 4;
        } else if (USS == 5) {
          latest_USS = 5;
        } else if (USS == 6) {
          latest_USS = 6;
        } else if (USS == 7) {
          latest_USS = 7;
        } else if (USS == 8) {
          latest_USS = 8;
        } else if (USS == 9) {
          latest_USS = 9;
        }

        timer_start = millis();
      } else {
        if (CAM_distance > 0) {
          position_timer = millis();
          old_position_timer = millis();
          if (CAM_distance < 90) {
            if (CAM_area == 2) {  //前
              Motor_2();
            } else if (CAM_area == 3) { //後
              Motor_8();
            } else if (CAM_area == 4) { //左
              Motor_3();
            } else if (CAM_area == 5) { //右
              Motor_3();
            } else if (CAM_area == 6) { //左前
              Motor_8();
            } else if (CAM_area == 7) { //右前
              Motor_9();
            } else if (CAM_area == 8) { //左後
              Motor_9();
            } else if (CAM_area == 9) { //右後
              Motor_8();
            }
          } else {
            if (CAM_area == 2) {  //前
              Motor_2();
            } else if (CAM_area == 3) { //後
              Motor_3();
            } else if (CAM_area == 4) { //左
              Motor_4();
            } else if (CAM_area == 5) { //右
              Motor_5();
            } else if (CAM_area == 6) { //左前
              Motor_6();
            } else if (CAM_area == 7) { //右前
              Motor_7();
            } else if (CAM_area == 8) { //左後
              Motor_8();
            } else if (CAM_area == 9) { //右後
              Motor_9();
            }
          }
        } else {
          position_timer = millis() - old_position_timer;
          if (position_timer > 2000) {//ボールが見えなくなって二秒以上経過したら
            if (USS3 > 50) {
              if (USS2 < 70) {
                if (USS4 < 70) {
                  Motor_3();  //後
                } else {
                  Motor_9();  //右後
                }
              } else if (USS4 < 70) {
                Motor_8();  //左後
              } else {
                Motor_3();  //後
              }
            } else if (USS2 < 70) {
              if (USS4 < 70) {
                Motor_1();  //方向修正
              } else {
                Motor_5();  //右
              }
            } else if (USS4 < 70) {
              Motor_4();  //左
            } else {
              Motor_1();  //方向修正
            }
          } else {
            Motor_1();//方向修正
          }
        }
      }
    }
  } else if (LCD.state == 5 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    Serial_receive();
    control_LED();
    Motor_1();
  } else {
    Serial_receive();
    print_LCD();
    control_LED();
    dsr1202.move(0, 0, 0, 0);
  }
}