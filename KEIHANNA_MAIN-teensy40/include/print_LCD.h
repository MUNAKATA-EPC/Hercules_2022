void print_LCD() {
  //一定間隔でLCD表示にリセットをかけることで表示位置バグが改善するんじゃないかというアレ
  hyouji.timer = millis() - hyouji.timer_start;
  
  if (hyouji.timer > 100) {
    MGLCD.ClearScreen();
    hyouji.timer_start = millis();
  }

  LCD_R.val = digitalRead(button_LCD_R);
  if (LCD_R.val == LOW && LCD_R.old_val == HIGH) {
    LCD.state = LCD.state + 1;
    LCD_C.state = 0;
    if (LCD.state >= 6) {
      LCD.state = 0;
    }
    MGLCD.ClearScreen();
  }
  LCD_R.old_val = LCD_R.val;

  LCD_L.val = digitalRead(button_LCD_L);
  if (LCD_L.val == LOW && LCD_L.old_val == HIGH) {
    LCD.state = LCD.state - 1;
    LCD_C.state = 0;
    if (LCD.state <= -1) {
      LCD.state = 5;
    }
    MGLCD.ClearScreen();
  }
  LCD_L.old_val = LCD_L.val;

  if (LCD.state == 0 || LCD.state == 5) {
    LCD_C.val = digitalRead(button_LCD_C);
    if (LCD_C.val == LOW && LCD_C.old_val == HIGH) {
      LCD_C.state = LCD_C.state + 1;
      if (LCD_C.state >= 2) {
        LCD_C.state = 0;
      }
      MGLCD.ClearScreen();
    }
    LCD_C.old_val = LCD_C.val;
  }

  switch (LCD.state) {
    case 0: //メインプログラム
      MGLCD.Locate(17, 3);
      MGLCD.print("MAIN");
      if (LCD_C.state == 0) {
        MGLCD.Locate(17, 5);
        MGLCD.print("STOP");
      } else if (LCD_C.state == 1) {
        MGLCD.Locate(18, 5);
        MGLCD.print("RUN");
      }
      break;
    case 1: //IMUモニターと超音波
      MGLCD.Locate(14, 1);
      MGLCD.print("IMU:");
      if (IMU < 10) {
        MGLCD.Locate(18, 1);
        MGLCD.print("00");
        MGLCD.Locate(20, 1);
        MGLCD.print(IMU);
      } else if (IMU < 100) {
        MGLCD.Locate(18, 1);
        MGLCD.print("0");
        MGLCD.Locate(19, 1);
        MGLCD.print(IMU);
      } else {
        MGLCD.Locate(18, 1);
        MGLCD.print(IMU);
      }

      MGLCD.Locate(12, 2);
      MGLCD.print("FRONT:");
      if (USS1 < 10) {
        MGLCD.Locate(18, 2);
        MGLCD.print("00");
        MGLCD.Locate(20, 2);
        MGLCD.print(USS1);
      } else if (USS1 < 100) {
        MGLCD.Locate(18, 2);
        MGLCD.print("0");
        MGLCD.Locate(19, 2);
        MGLCD.print(USS1);
      } else {
        MGLCD.Locate(18, 2);
        MGLCD.print(USS1);
      }

      MGLCD.Locate(12, 3);
      MGLCD.print("RIGHT:");
      if (USS4 < 10) {
        MGLCD.Locate(18, 3);
        MGLCD.print("00");
        MGLCD.Locate(20, 3);
        MGLCD.print(USS4);
      } else if (USS4 < 100) {
        MGLCD.Locate(18, 3);
        MGLCD.print("0");
        MGLCD.Locate(19, 3);
        MGLCD.print(USS4);
      } else {
        MGLCD.Locate(18, 3);
        MGLCD.print(USS4);
      }

      MGLCD.Locate(13, 4);
      MGLCD.print("LEFT:");
      if (USS2 < 10) {
        MGLCD.Locate(18, 4);
        MGLCD.print("00");
        MGLCD.Locate(20, 4);
        MGLCD.print(USS2);
      } else if (USS2 < 100) {
        MGLCD.Locate(18, 4);
        MGLCD.print("0");
        MGLCD.Locate(19, 4);
        MGLCD.print(USS2);
      } else {
        MGLCD.Locate(18, 4);
        MGLCD.print(USS2);
      }

      MGLCD.Locate(13, 5);
      MGLCD.print("BACK:");
      if (USS3 < 10) {
        MGLCD.Locate(18, 5);
        MGLCD.print("00");
        MGLCD.Locate(20, 5);
        MGLCD.print(USS3);
      } else if (USS3 < 100) {
        MGLCD.Locate(18, 5);
        MGLCD.print("0");
        MGLCD.Locate(19, 5);
        MGLCD.print(USS3);
      } else {
        MGLCD.Locate(18, 5);
        MGLCD.print(USS3);
      }
      break;
    case 2: //カメラアングルとか
      MGLCD.Locate(13, 1);
      MGLCD.print("BALL:");
      if (CAM_angle < 10) {
        MGLCD.Locate(18, 1);
        MGLCD.print("00");
        MGLCD.Locate(20, 1);
        MGLCD.print(CAM_angle);
      } else if (CAM_angle < 100) {
        MGLCD.Locate(18, 1);
        MGLCD.print("0");
        MGLCD.Locate(19, 1);
        MGLCD.print(CAM_angle);
      } else {
        MGLCD.Locate(18, 1);
        MGLCD.print(CAM_angle);
      }

      MGLCD.Locate(9, 3);
      MGLCD.print("DISTANCE:");
      if (CAM_distance < 10) {
        MGLCD.Locate(18, 3);
        MGLCD.print("00");
        MGLCD.Locate(20, 3);
        MGLCD.print(CAM_distance);
      } else if (CAM_distance < 100) {
        MGLCD.Locate(18, 3);
        MGLCD.print("0");
        MGLCD.Locate(19, 3);
        MGLCD.print(CAM_distance);
      } else {
        MGLCD.Locate(18, 3);
        MGLCD.print(CAM_distance);
      }

      MGLCD.Locate(12, 5);
      MGLCD.print("FIELD:");
      if (CAM_FieldAngle < 10) {
        MGLCD.Locate(18, 5);
        MGLCD.print("00");
        MGLCD.Locate(20, 5);
        MGLCD.print(CAM_FieldAngle);
      } else if (CAM_FieldAngle < 100) {
        MGLCD.Locate(18, 5);
        MGLCD.print("0");
        MGLCD.Locate(19, 5);
        MGLCD.print(CAM_FieldAngle);
      } else {
        MGLCD.Locate(18, 5);
        MGLCD.print(CAM_FieldAngle);
      }
      break;
    case 3: //ToFモニター
      MGLCD.Locate(8, 3);
      MGLCD.print("TOF NOT FOUND");
      break;
    case 4: //マウスセンサチェック
      MGLCD.Locate(6, 3);
      MGLCD.print("MOUSE NOT FOUND");
      break;
    case 5: //テストプログラム(方向修正)
      MGLCD.Locate(17, 3);
      MGLCD.print("TEST");
      if (LCD_C.state == 0) {
        MGLCD.Locate(17, 5);
        MGLCD.print("STOP");
      } else if (LCD_C.state == 1) {
        MGLCD.Locate(18, 5);
        MGLCD.print("RUN");
      }
      break;
  }
}