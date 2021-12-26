#include <Arduino.h>

#define echoPin1 2  //  前超音波のechoピン
#define trigPin1 3  //  前超音波のトリガー
#define echoPin2 4  //  左超音波のechoピン
#define trigPin2 5  //  左超音波のトリガー
#define echoPin3 0  //  後超音波のechoピン
#define trigPin3 1  //  後超音波のトリガー
#define echoPin4 8  //  右超音波のechoピン
#define trigPin4 9  //  右超音波のトリガー
#define LED 13  //LEDピン

double Duration1 = 0;  //  前からの出力値
double Distance1 = 0;  //  前の距離
double Duration2 = 0;  //  左からの出力値
double Distance2 = 0;  //  左の距離
double Duration3 = 0;  //  後からの出力値
double Distance3 = 0;  //  後の距離
double Duration4 = 0;  //  右からの出力値
double Distance4 = 0;  //  右の距離

int timeout = 20000; //タイムアウト設定値(マイクロ秒)
int buffer = 0; //Teensyからの定位置送信要求処理用

int send_Distance1;
int send_Distance2;
int send_Distance3;
int send_Distance4;

void setup() {
  pinMode(echoPin1, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(115200); //USBシリアル通信開始
  Serial1.begin(115200);  //Teensyとの接続開始

  while (!Serial1) {
    ; //Teensyとの接続待機
  }
}

void loop() {
  digitalWrite(LED, HIGH); //動作確認用LED処理

  digitalWrite(trigPin1, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH); //パルス出力処理
  delayMicroseconds(10);  //モジュールごとに送信時間要確認

  digitalWrite(trigPin1, LOW);  //パスル出力終了処理

  Duration1 = pulseIn(echoPin1, HIGH, timeout); //パスル確認処理

  if (Duration1 > 0) {  //前超音波
    Duration1 = Duration1 / 2;
    Distance1 = Duration1 * 340 * 100 / 1000000;
  }

  if (Distance1 >= 254) {
    Distance1 = 254;
  }
  
  Serial.print(Distance1);  //シリアルモニタ用
  Serial.print("\t");

  digitalWrite(LED, LOW);  //動作確認用LED処理

  digitalWrite(trigPin2, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH); //パスル出力処理
  delayMicroseconds(10);  //モジュールごとに要確認

  digitalWrite(trigPin2, LOW);  //パスル出力終了処理

  Duration2 = pulseIn(echoPin2, HIGH, timeout); //パスル確認処理

  if (Duration2 > 0) {  //左超音波
    Duration2 = Duration2 / 2;
    Distance2 = Duration2 * 340 * 100 / 1000000;
  }

  if (Distance2 >= 254) {
    Distance2 = 254;
  }

  Serial.print(Distance2);  //シリアルモニタ用
  Serial.print("\t");

  digitalWrite(LED, HIGH); //動作確認用LED処理

  digitalWrite(trigPin3, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH); //パスル出力処理
  delayMicroseconds(10);  //モジュールごとに要確認

  digitalWrite(trigPin3, LOW);  //パスル出力終了処理

  Duration3 = pulseIn(echoPin3, HIGH, timeout); //パスル確認処理

  if (Duration3 > 0) {  //後超音波
    Duration3 = Duration3 / 2;
    Distance3 = Duration3 * 340 * 100 / 1000000;
  }

  if (Distance3 >= 254) {
    Distance3 = 254;
  }

  Serial.print(Distance3);  //シリアルモニタ用
  Serial.print("\t");

  digitalWrite(LED, LOW);  //動作確認用LED処理

  digitalWrite(trigPin4, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin4, HIGH); //パスル出力処理
  delayMicroseconds(10);  //モジュールごとに要確認

  digitalWrite(trigPin4, LOW);  //パスル出力終了処理

  Duration4 = pulseIn(echoPin4, HIGH, timeout); //パスル確認処理

  if (Duration4 > 0) {  //右超音波
    Duration4 = Duration4 / 2;
    Distance4 = Duration4 * 340 * 100 / 1000000;
  }

  if (Distance4 >= 254) {
    Distance4 = 254;
  }

  Serial.println(Distance4);  //シリアルモニタ用

  send_Distance1 = Distance1;
  send_Distance2 = Distance2;
  send_Distance3 = Distance3;
  send_Distance4 = Distance4;

  buffer = Serial1.read();  //Teensyからの要求確認

  Serial1.write(255);
  
  if (buffer == 1) {
    if (Distance3 < 45.00) {
      if (Distance2 > 50.00) {
        if (Distance4 > 50.00) {
          Serial1.write(10);  //停止
        } else {
          Serial1.write(13);  //左
        }
      } else if (Distance4 > 50.00) {
        Serial1.write(14);  //右
      } else {
        Serial1.write(10);  //停止
      }
    } else if (Distance2 > 50.00) {
      if (Distance4 > 50.00) {
        Serial1.write(12);  //後
      } else {
        Serial1.write(17);  //左後
      }
    } else if (Distance4 > 50.00) {
      Serial1.write(18);  //右後
    } else {
      Serial1.write(12);  //後
    }
  } else {
    if (Distance1 < 30.00) {
      if (Distance2 < 30.00) {
        if (Distance3 < 30.00) {
          if (Distance4 < 30.00) {
            Serial1.write(1); //停止
          } else {
            Serial1.write(5); //右
          }
        } else if (Distance4 < 30.00) {
          Serial1.write(3); //後
        } else {
          Serial1.write(9); //右後
        }
      } else if (Distance3 < 30.00) {
        if (Distance4 < 30.00) {
          Serial1.write(4); //左
        } else {
          Serial1.write(1); //停止
        }
      } else if (Distance4 < 30.00) {
        Serial1.write(8); //左後
      } else {
        Serial1.write(3); //後
      }
    } else if (Distance2 < 30.00) {
      if (Distance3 < 30.00) {
        if (Distance4 < 30.00) {
          Serial1.write(2); //前
        } else {
          Serial1.write(7); //右前
        }
      } else if (Distance4 < 30.00) {
        Serial1.write(1); //停止
      } else {
        Serial1.write(5); //右
      }
    } else if (Distance3 < 30.00) {
      if (Distance4 < 30.00) {
        Serial1.write(6); //左前
      } else {
        Serial1.write(2); //前
      }
    } else if (Distance4 < 30.00) {
      Serial1.write(2); //左
    } else {
      Serial1.write(1); //停止
    }
  }

  Serial1.write(send_Distance1);
  Serial1.write(send_Distance2);
  Serial1.write(send_Distance3);
  Serial1.write(send_Distance4);
}