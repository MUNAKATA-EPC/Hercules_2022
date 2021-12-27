#include <Arduino.h>
#include <Wire.h>
#include <FaboLCDmini_AQM0802A.h>
#include <DSR1202.h>

FaBoLCDmini_AQM0802A lcd;

DSR1202 dsr1202(1);

#include <define.h>
#include <variable.h>
#include <startup.h>
#include <Serial_receive.h>
#include <print_LCD.h>
#include <control_LED.h>

void setup() {

  startup();

}

void loop() {

  Serial_receive();
  print_LCD();
  control_LED();

  if ((state_LCD == 4) && (state_white == 1) && (switch_program == HIGH)) {

    if (timer_start != 0.00) {
      
      timer = (millis() / 100) - timer_start;

    }

    if (timer < 2.00) {

      /* モーター_1(方向修正) */

    } else if (timer < 7.00) {
      
      if (USS == 1) {

        /* モーター_1(方向修正) */

      } else if (USS == 2) {

        /* モーター_2(前) */

      } else if (USS == 3) {

        /* モーター_3(後) */

      } else if (USS == 4) {

        /* モーター_4(左) */

      } else if (USS == 5) {

        /* モーター_5(右) */

      } else if (USS == 6) {

        /* モーター_6(左前) */

      } else if (USS == 7) {

        /* モーター_7(右前) */

      } else if (USS == 8) {

        /* モーター_8(左後) */

      } else if (USS == 9) {

        /* モーター_9(右後) */

      }
      
    } else {

      if (analogRead(LINE_ALL) < 100) {

        Serial1.print("100R200R300R400R");
        timer_start = millis() / 100;

      } else {

        if (CAM_angle < 120) {

          /* code */

        } else if (CAM_angle < 240) {

          /* code */

        } else {

          if (USS3 < 45) {

            if (USS2 > 50) {

              if (USS4 > 50) {

                /* モーター_1(方向修正) */

              } else {

                /* モーター_4(左) */

              }

            } else if (USS4 > 50) {

              /* モーター_5(右) */

            } else {

              /* モーター_1(方向修正) */

            }

          } else if (USS2 > 50) {

            if (USS4 > 50) {

              /* モーター_3(後) */

            } else {

              /* モーター_8(左後) */

            }

          } else if (USS4 > 50) {

            /* モーター_9(右後) */

          } else {

            /* モーター_3(後) */

          }

        }
      
      }

    }

  } else if ((state_LCD == 5) && (state_white == 1) && (switch_program == HIGH)) {

    dsr1202.move(10, 10, 10, 10);

  }
  
}//編集してみました