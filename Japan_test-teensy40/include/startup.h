void startup() {
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