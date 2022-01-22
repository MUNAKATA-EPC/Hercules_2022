void print_LCD() {
  val_LCD = digitalRead(button_LCD);

  if ((val_LCD == LOW) && (old_val_LCD == HIGH)) {
    state_LCD = state_LCD + 1;
    
    if (state_LCD >= 7) {
      state_LCD = 0;
    }

    lcd.clear();
  }
  
  old_val_LCD = val_LCD;

  if ((state_LCD == 4) || (state_LCD == 5) || (state_LCD == 6)) {
    val_white = digitalRead(button_white);
    
    if ((val_white == LOW) && (old_val_white == HIGH)) {
      state_white = state_white + 1;

      if (state_white >= 2) {
        state_white = 0;
      }

      lcd.clear();
    }
  
    old_val_white = val_white;
  }
  
  if (state_LCD == 0) { //システム全停止
    if (state_white == 1) {
      state_white = 0;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("System");
    lcd.setCursor(0, 1);
    lcd.print("Stop");
  } else if (state_LCD == 1) {  //USSとIMU
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
  } else if (state_LCD == 2) {  //USS個別の値
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
  } else if (state_LCD == 3) {  //カメラアングルとか
    lcd.setCursor(0, 0);
    lcd.print("rads:");
    lcd.setCursor(5, 0);
    lcd.print("num");

    lcd.setCursor(0, 1);
    lcd.print("dis:");
    lcd.setCursor(4, 1);
    lcd.print("num");
  } else if (state_LCD == 4) {  //オフェンスモード
    lcd.setCursor(0, 0);
    lcd.print("Offense");

    if (state_white == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Stop");
    } else if (state_white == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Run");
    }    
  } else if (state_LCD == 5) {  //ディフェンスモード
    lcd.setCursor(0, 0);
    lcd.print("Defence");

    if (state_white == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Stop");
    } else if (state_white == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Run");
    }
  } else if (state_LCD == 6) {  //モーターチェック
    lcd.setCursor(0, 0);
    lcd.print("Motor");

    if (state_white == 0) {
      lcd.setCursor(0, 1);
      lcd.print("Stop");
    } else if (state_white == 1) {
      lcd.setCursor(0, 1);
      lcd.print("Run");
    }
  }
}