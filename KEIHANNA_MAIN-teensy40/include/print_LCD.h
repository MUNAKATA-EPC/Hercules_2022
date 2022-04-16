void print_LCD() {
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
      MGLCD.Locate(0, 0);
      MGLCD.print("Main");
      if (LCD_C.state == 0) {
        MGLCD.Locate(0, 2);
        MGLCD.print("Stop");
      } else if (LCD_C.state == 1) {
        MGLCD.Locate(0, 2);
        MGLCD.print("Run");
      }
      break;
    case 1: //IMUモニターと超音波
      MGLCD.Locate(0, 0);
      MGLCD.print("IMU:");
      if (IMU < 10) {
        MGLCD.Locate(4, 0);
        MGLCD.print("00");
        MGLCD.Locate(6, 0);
        MGLCD.print(IMU);
      } else if (IMU < 100) {
        MGLCD.Locate(4, 0);
        MGLCD.print("0");
        MGLCD.Locate(5, 0);
        MGLCD.print(IMU);
      } else {
        MGLCD.Locate(4, 0);
        MGLCD.print(IMU);
      }

      MGLCD.Locate(0, 2);
      MGLCD.print("Front:");
      if (USS1 < 10) {
        MGLCD.Locate(6, 2);
        MGLCD.print("00");
        MGLCD.Locate(8, 2);
        MGLCD.print(USS1);
      } else if (USS1 < 100) {
        MGLCD.Locate(6, 2);
        MGLCD.print("0");
        MGLCD.Locate(7, 2);
        MGLCD.print(USS1);
      } else {
        MGLCD.Locate(6, 2);
        MGLCD.print(USS1);
      }

      MGLCD.Locate(12, 2);
      MGLCD.print("Right:");
      if (USS4 < 10) {
        MGLCD.Locate(18, 2);
        MGLCD.print("00");
        MGLCD.Locate(20, 2);
        MGLCD.print(USS4);
      } else if (USS4 < 100) {
        MGLCD.Locate(18, 2);
        MGLCD.print("0");
        MGLCD.Locate(19, 2);
        MGLCD.print(USS4);
      } else {
        MGLCD.Locate(18, 2);
        MGLCD.print(USS4);
      }

      MGLCD.Locate(1, 4);
      MGLCD.print("Left:");
      if (USS2 < 10) {
        MGLCD.Locate(6, 4);
        MGLCD.print("00");
        MGLCD.Locate(8, 4);
        MGLCD.print(USS2);
      } else if (USS2 < 100) {
        MGLCD.Locate(6, 4);
        MGLCD.print("0");
        MGLCD.Locate(7, 4);
        MGLCD.print(USS2);
      } else {
        MGLCD.Locate(6, 4);
        MGLCD.print(USS2);
      }

      MGLCD.Locate(13, 4);
      MGLCD.print("Back:");
      if (USS3 < 10) {
        MGLCD.Locate(18, 4);
        MGLCD.print("00");
        MGLCD.Locate(20, 4);
        MGLCD.print(USS3);
      } else if (USS3 < 100) {
        MGLCD.Locate(18, 4);
        MGLCD.print("0");
        MGLCD.Locate(19, 4);
        MGLCD.print(USS3);
      } else {
        MGLCD.Locate(18, 4);
        MGLCD.print(USS3);
      }
      break;
    case 2: //カメラアングルとか
      MGLCD.Locate(0, 0);
      MGLCD.print("Ball:");
      if (CAM_angle < 10) {
        MGLCD.Locate(5, 0);
        MGLCD.print("00");
        MGLCD.Locate(7, 0);
        MGLCD.print(CAM_angle);
      } else if (CAM_angle < 100) {
        MGLCD.Locate(5, 0);
        MGLCD.print("0");
        MGLCD.Locate(6, 0);
        MGLCD.print(CAM_angle);
      } else {
        MGLCD.Locate(5, 0);
        MGLCD.print(CAM_angle);
      }

      MGLCD.Locate(0, 2);
      MGLCD.print("Distance:");
      if (CAM_distance < 10) {
        MGLCD.Locate(9, 2);
        MGLCD.print("00");
        MGLCD.Locate(11, 2);
        MGLCD.print(CAM_distance);
      } else if (CAM_distance < 100) {
        MGLCD.Locate(9, 2);
        MGLCD.print("0");
        MGLCD.Locate(10, 2);
        MGLCD.print(CAM_distance);
      } else {
        MGLCD.Locate(9, 2);
        MGLCD.print(CAM_distance);
      }

      MGLCD.Locate(0, 4);
      MGLCD.print("Field:");
      if (CAM_FieldAngle < 10) {
        MGLCD.Locate(6, 4);
        MGLCD.print("00");
        MGLCD.Locate(8, 4);
        MGLCD.print(CAM_FieldAngle);
      } else if (CAM_FieldAngle < 100) {
        MGLCD.Locate(6, 4);
        MGLCD.print("0");
        MGLCD.Locate(7, 4);
        MGLCD.print(CAM_FieldAngle);
      } else {
        MGLCD.Locate(6, 4);
        MGLCD.print(CAM_FieldAngle);
      }
      break;
    case 3: //ToFモニター
      MGLCD.Locate(0, 0);
      MGLCD.print("404 Not Found");
      break;
    case 4: //マウスセンサチェック
      MGLCD.Locate(0, 0);
      MGLCD.print("404 Not Found");
      break;
    case 5: //テストプログラム(方向修正)
      MGLCD.Locate(0, 0);
      MGLCD.print("Test");
      if (LCD_C.state == 0) {
        MGLCD.Locate(0, 2);
        MGLCD.print("Stop");
      } else if (LCD_C.state == 1) {
        MGLCD.Locate(0, 2);
        MGLCD.print("Run");
      }
      break;
  }
}