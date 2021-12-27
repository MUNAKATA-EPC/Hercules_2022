void print_LCD() {
  LCD.val = digitalRead(button_LCD);

  if (LCD.val == LOW && LCD.old_val == HIGH) {
    LCD.state = LCD.state + 1;

    if (LCD.state >= 6) {
      LCD.state = 0;
    }

    lcd.clear();
  }
  
  LCD.old_val = LCD.val;

  if (LCD.state == 4 || LCD.state == 5) {
    white.val = digitalRead(button_white);
    
    if (white.val == LOW && white.old_val == HIGH) {
      white.state = white.state + 1;

      if (white.state >= 2) {
        white.state = 0;
      }

      lcd.clear();
    }
  
    white.old_val = white.val;
  }
  
  if (LCD.state == 0) { //システム全停止
    if (white.state == 1) {
      white.state = 0;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("System");
    lcd.setCursor(0, 1);
    lcd.print("Stop");

  } else if (LCD.state == 1) {  //USSとIMU
    lcd.setCursor(0, 0); //USSをLCDに表示
    lcd.print("USS:");
    lcd.setCursor(0, 1); //IMUをLCDに表示
    lcd.print("IMU:");

    if (USS < 10) {
      lcd.setCursor(6, 0);
      lcd.print("0");
      lcd.setCursor(7, 0);
      lcd.print(USS);

    } else {
      lcd.setCursor(6, 0);
      lcd.print(USS);
    }

    if (IMU < 10) {
      lcd.setCursor(5, 1);
      lcd.print("00");
      lcd.setCursor(7, 1);
      lcd.print(IMU);

    } else if (IMU < 100) {
      lcd.setCursor(5, 1);
      lcd.print("0");
      lcd.setCursor(6, 1);
      lcd.print(IMU);

    } else {
      lcd.setCursor(5, 1);
      lcd.print(IMU);
    }

  } else if (LCD.state == 2) {  //USS個別の値
    lcd.setCursor(0, 0);
    lcd.print("F");

    if (USS1 < 10) {
      lcd.setCursor(1, 0);
      lcd.print("00");
      lcd.setCursor(3, 0);
      lcd.print(USS1);

    } else if (USS1 < 100) {
      lcd.setCursor(1, 0);
      lcd.print("0");
      lcd.setCursor(2, 0);
      lcd.print(USS1);

    } else {
      lcd.setCursor(1, 0);
      lcd.print(USS1);
    }

    lcd.setCursor(4, 0);
    lcd.print("L");

    if (USS2 < 10) {
      lcd.setCursor(5, 0);
      lcd.print("00");
      lcd.setCursor(7, 0);
      lcd.print(USS2);

    } else if (USS2 < 100) {
      lcd.setCursor(5, 0);
      lcd.print("0");
      lcd.setCursor(6, 0);
      lcd.print(USS2);

    } else {
      lcd.setCursor(5, 0);
      lcd.print(USS2);
    }

    lcd.setCursor(0, 1);
    lcd.print("B");

    if (USS3 < 10) {
      lcd.setCursor(1, 1);
      lcd.print("00");
      lcd.setCursor(3, 1);
      lcd.print(USS3);

    } else if (USS3 < 100) {
      lcd.setCursor(1, 1);
      lcd.print("0");
      lcd.setCursor(2, 1);
      lcd.print(USS3);

    } else {
      lcd.setCursor(1, 1);
      lcd.print(USS3);
    }

    lcd.setCursor(4, 1);
    lcd.print("R");

    if (USS4 < 10) {
      lcd.setCursor(5, 1);
      lcd.print("00");
      lcd.setCursor(7, 1);
      lcd.print(USS4);

    } else if (USS4 < 100) {
      lcd.setCursor(5, 1);
      lcd.print("0");
      lcd.setCursor(6, 1);
      lcd.print(USS4);

    } else {
      lcd.setCursor(5, 1);
      lcd.print(USS4);
    }

  } else if (LCD.state == 3) {  //カメラアングルとか
    lcd.setCursor(0, 0);
    lcd.print("rads:");

    if (CAM_angle < 10) {
      lcd.setCursor(5, 0);
      lcd.print("00");
      lcd.setCursor(7, 0);
      lcd.print(CAM_angle);

    } else if (CAM_angle < 100) {
      lcd.setCursor(5, 0);
      lcd.print("0");
      lcd.setCursor(6, 0);
      lcd.print(CAM_angle);

    } else {
      lcd.setCursor(5, 1);
      lcd.print(CAM_angle);
    }

    lcd.setCursor(0, 1);
    lcd.print("dis:");

    if (CAM_distance < 10) {
      lcd.setCursor(5, 1);
      lcd.print("00");
      lcd.setCursor(7, 1);
      lcd.print(CAM_distance);

    } else if (CAM_distance < 100) {
      lcd.setCursor(5, 1);
      lcd.print("0");
      lcd.setCursor(6, 1);
      lcd.print(CAM_distance);

    } else {
      lcd.setCursor(5, 1);
      lcd.print(CAM_distance);
    }

  } else if (LCD.state == 4) {  //ゲームモード
    lcd.setCursor(0, 0);
    lcd.print("GameMode");

    if (white.state == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Stop");

    } else if (white.state == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Run");
    }

  } else if (LCD.state == 5) {  //モーターチェック
    lcd.setCursor(0, 0);
    lcd.print("Motor");

    if (white.state == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Stop");

    } else if (white.state == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Run");
    }
  }
}