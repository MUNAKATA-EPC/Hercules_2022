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
  Serial_receive();
  print_LCD();
  control_LED();

  if (LCD.state == 4 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    if (timer_start != 0) {   
      timer = millis() - timer_start;
    }
    
    if (timer < 200) {
      Motor_1();  //方向修正
    } else if (timer < 700) {
      if (USS == 1) {
        Motor_1();  //方向修正
      } else if (USS == 2) {
        Motor_2();  //前
      } else if (USS == 3) {
        Motor_3();  //後
      } else if (USS == 4) {
        Motor_4();  //左
      } else if (USS == 5) {
        Motor_5();  //右
      } else if (USS == 6) {
        Motor_6();  //左前
      } else if (USS == 7) {
        Motor_7();  //右前
      } else if (USS == 8) {
        Motor_8();  //左後
      } else if (USS == 9) {
        Motor_9();  //右後
      }
    } else {
      if (analogRead(LINE_ALL) < 300) {
        Serial1.println("1R0002R0003R0004R000");
        timer_start = millis();
      } else {
        if (CAM_distance < 70) {
          if (CAM_angle < 6) {
            Motor_2();  //前進
          } else if (CAM_angle < 35) {
            Motor_7();  //右前
          } else if (CAM_angle < 56) {
            Motor_3();  //右
          } else if (CAM_angle < 76) {
            Motor_8();  //右後
          } else if (CAM_angle < 96) {
            Motor_4();  //後
          } else if (CAM_angle < 116) {
            Motor_9();  //左後
          } else if (CAM_angle < 136) {
            Motor_3();  //左
          } else if (CAM_angle < 176) {
            Motor_6();  //左前
          }
        } else {
          if (CAM_angle < 6) {
            Motor_2();  //前進
          } else if (CAM_angle < 35) {
            Motor_7();  //右前
          } else if (CAM_angle < 56) {
            Motor_5();  //右
          } else if (CAM_angle < 76) {
            Motor_9();  //右後
          } else if (CAM_angle < 96) {
            Motor_3();  //後
          } else if (CAM_angle < 116) {
            Motor_8();  //左後
          } else if (CAM_angle < 136) {
            Motor_4();  //左
          } else if (CAM_angle < 176) {
            Motor_6();  //左前
          } else {
            if (USS3 < 45) {
              if (USS2 > 50) {
                if (USS4 > 50) {
                  Motor_1();  //方向修正
                } else {
                  Motor_4();  //左
                }
              } else if (USS4 > 50) {
                Motor_5();  //右
              } else {
                Motor_1();  //方向修正
              }
            } else if (USS2 > 50) {
              if (USS4 > 50) {
                Motor_3();  //後
              } else {
                Motor_8();  //左後
              }
            } else if (USS4 > 50) {
              Motor_9();  //右後
            } else {
              Motor_3();  //後
            }
          }
        }
      }
    }
  } else if (LCD.state == 5 && white.state == 1 && digitalRead(switch_program) == HIGH) {
    //dsr1202.move(10, 10, 10, 10);  //右前, 右後, 左前, 左後(全部正回転で反時計回り)
    Motor_1();
  } else {
    dsr1202.move(0, 0, 0, 0);
  }
}