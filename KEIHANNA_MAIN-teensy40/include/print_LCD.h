void print_LCD() {
  u8g2.clearBuffer();					//内部メモリクリア(毎回表示内容更新前に置く)
  u8g2.setFont(u8g2_font_ncenB14_tr);	//フォント選択(これは横に14ピクセル、縦に14ピクセル)

  LCD_R.val = digitalRead(button_LCD_R);
  if ((LCD_R.val == LOW) && (LCD_R.old_val == HIGH)) {
    LCD.state = LCD.state + 1;
    LCD_C.state = 0;
    if (LCD.state >= 8) {
      LCD.state = 0;
    }
  }
  LCD_R.old_val = LCD_R.val;

  LCD_L.val = digitalRead(button_LCD_L);
  if ((LCD_L.val == LOW) && (LCD_L.old_val == HIGH)) {
    LCD.state = LCD.state - 1;
    LCD_C.state = 0;
    if (LCD.state <= -1) {
      LCD.state = 7;
    }
  }
  LCD_L.old_val = LCD_L.val;

  if ((LCD.state == 0) || (LCD.state == 7)) {
    LCD_C.val = digitalRead(button_LCD_C);
    if ((LCD_C.val == LOW) && (LCD_C.old_val == HIGH)) {
      LCD_C.state = LCD_C.state + 1;
      if (LCD_C.state >= 2) {
        LCD_C.state = 0;
      }
    }
    LCD_C.old_val = LCD_C.val;
  }

  if (LCD.state == 0) { //メインプログラム

    if (LCD_C.state == 0) {
      u8g2.drawStr(0, 28, "Stop.Main");
    } else if (LCD_C.state == 1) {
      u8g2.drawStr(0, 28, "Run.Main");
    }

  } else if (LCD.state == 1) {  //IMU

    u8g2.drawStr(0, 28, "IMU:");
    char DisplayIMU [4] = {"000"};
    DisplayIMU [0] = '0' + (IMU / 100) % 10;
    DisplayIMU [1] = '0' + (IMU / 10) % 10;
    DisplayIMU [2] = '0' + IMU % 10;
    u8g2.drawStr(56, 28, DisplayIMU);

  } else if (LCD.state == 2) {  //超音波値
    
    //前
    char DisplayUSS1 [4] = {"000"};
    DisplayUSS1 [0] = '0' + (USS1 / 100) % 10;
    DisplayUSS1 [1] = '0' + (USS1 / 10) % 10;
    DisplayUSS1 [2] = '0' + USS1 % 10;
    u8g2.drawStr(42, 14, DisplayUSS1);

    //左
    char DisplayUSS2 [4] = {"000"};
    DisplayUSS2 [0] = '0' + (USS2 / 100) % 10;
    DisplayUSS2 [1] = '0' + (USS2 / 10) % 10;
    DisplayUSS2 [2] = '0' + USS2 % 10;
    u8g2.drawStr(0, 28, DisplayUSS2);

    //後
    char DisplayUSS3 [4] = {"000"};
    DisplayUSS3 [0] = '0' + (USS3 / 100) % 10;
    DisplayUSS3 [1] = '0' + (USS3 / 10) % 10;
    DisplayUSS3 [2] = '0' + USS3 % 10;
    u8g2.drawStr(42, 42, DisplayUSS3);

    //右
    char DisplayUSS4 [4] = {"000"};
    DisplayUSS4 [0] = '0' + (USS4 / 100) % 10;
    DisplayUSS4 [1] = '0' + (USS4 / 10) % 10;
    DisplayUSS4 [2] = '0' + USS4 % 10;
    u8g2.drawStr(86, 28, DisplayUSS4);

    //全体
    char DisplayUSS [3] = {"00"};
    DisplayUSS [0] = '0' + (USS / 10) % 10;
    DisplayUSS [1] = '0' + USS % 10;
    u8g2.drawStr(48, 28, DisplayUSS);

  } else if (LCD.state == 3) {  //カメラアングル

    u8g2.drawStr(0, 14, "Ball:");
    char DisplayCAM_angle [4] = {"000"};
    DisplayCAM_angle [0] = '0' + (CAM_angle / 100) % 10;
    DisplayCAM_angle [1] = '0' + (CAM_angle / 10) % 10;
    DisplayCAM_angle [2] = '0' + CAM_angle % 10;
    u8g2.drawStr(56, 14, DisplayCAM_angle);

    u8g2.drawStr(0, 28, "Dst:");
    char DisplayCAM_distance [4] = {"000"};
    DisplayCAM_distance [0] = '0' + (CAM_distance / 100) % 10;
    DisplayCAM_distance [1] = '0' + (CAM_distance / 10) % 10;
    DisplayCAM_distance [2] = '0' + CAM_distance % 10;
    u8g2.drawStr(56, 28, DisplayCAM_distance);

  } else if (LCD.state == 4) {  //ラインセンサ

    if (digitalRead(LINE_1) == LOW) { //前のライン反応
      u8g2.drawStr(32, 14, "LOW");
    } else if (digitalRead(LINE_1) == HIGH) {
      u8g2.drawStr(32, 14, "HIGH");
    }

    if (digitalRead(LINE_4) == LOW) { //左のライン反応
      u8g2.drawStr(0, 42, "LOW");
    } else if (digitalRead(LINE_4) == HIGH) {
      u8g2.drawStr(0, 42, "HIGH");
    }

    if (digitalRead(LINE_2) == LOW) { //右のライン反応
      u8g2.drawStr(65, 42, "LOW");
    } else if (digitalRead(LINE_2) == HIGH) {
      u8g2.drawStr(65, 42, "HIGH");
    }

  } else if (LCD.state == 5) {  //ゴール角度

    u8g2.drawStr(0, 14, "Yellow:");
    char DisplayCAM_YellowAngle [4] = {"000"};
    DisplayCAM_YellowAngle [0] = '0' + (CAM_YellowAngle / 100) % 10;
    DisplayCAM_YellowAngle [1] = '0' + (CAM_YellowAngle / 10) % 10;
    DisplayCAM_YellowAngle [2] = '0' + CAM_YellowAngle % 10;
    u8g2.drawStr(98, 14, DisplayCAM_YellowAngle);

    u8g2.drawStr(0, 28, "Blue:");
    char DisplayCAM_BlueAngle [4] = {"000"};
    DisplayCAM_BlueAngle [0] = '0' + (CAM_BlueAngle / 100) % 10;
    DisplayCAM_BlueAngle [1] = '0' + (CAM_BlueAngle / 10) % 10;
    DisplayCAM_BlueAngle [2] = '0' + CAM_BlueAngle % 10;
    u8g2.drawStr(56, 28, DisplayCAM_BlueAngle);

  } else if (LCD.state == 6) {  //マウス

    u8g2.drawStr(0, 28, "Mouse");

  } else if (LCD.state == 7) {  //テストラン

    if (LCD_C.state == 0) {
      u8g2.drawStr(0, 28, "Stop.Test");
    } else if (LCD_C.state == 1) {
      u8g2.drawStr(0, 28, "Run.Test");
    }

  }

  u8g2.sendBuffer();					//ディスプレイに送る(毎回書く)
}