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

class ClassA {
private:
  
public:
  double Duration = 0;
  double Distance = 0;

  int send_Distance = 0;

};

ClassA front, left, back, right;

int timeout = 20000; //タイムアウト設定値(マイクロ秒)

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

  front.Duration = pulseIn(echoPin1, HIGH, timeout); //パスル確認処理

  if (front.Duration > 0) {  //前超音波
    front.Duration = front.Duration / 2;
    front.Distance = front.Duration * 340 * 100 / 1000000;

  }

  if (front.Distance >= 254) {
    front.Distance = 254;

  }
  
  Serial.print(front.Distance);  //シリアルモニタ用
  Serial.print("\t");

  digitalWrite(LED, LOW);  //動作確認用LED処理

  digitalWrite(trigPin2, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH); //パスル出力処理
  delayMicroseconds(10);  //モジュールごとに要確認

  digitalWrite(trigPin2, LOW);  //パスル出力終了処理

  left.Duration = pulseIn(echoPin2, HIGH, timeout); //パスル確認処理

  if (left.Duration > 0) {  //左超音波
    left.Duration = left.Duration / 2;
    left.Distance = left.Duration * 340 * 100 / 1000000;

  }

  if (left.Distance >= 254) {
    left.Distance = 254;

  }

  Serial.print(left.Distance);  //シリアルモニタ用
  Serial.print("\t");

  digitalWrite(LED, HIGH); //動作確認用LED処理

  digitalWrite(trigPin3, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin3, HIGH); //パスル出力処理
  delayMicroseconds(10);  //モジュールごとに要確認

  digitalWrite(trigPin3, LOW);  //パスル出力終了処理

  back.Duration = pulseIn(echoPin3, HIGH, timeout); //パスル確認処理

  if (back.Duration > 0) {  //後超音波
    back.Duration = back.Duration / 2;
    back.Distance = back.Duration * 340 * 100 / 1000000;

  }

  if (back.Distance >= 254) {
    back.Distance = 254;

  }

  Serial.print(back.Distance);  //シリアルモニタ用
  Serial.print("\t");

  digitalWrite(LED, LOW);  //動作確認用LED処理

  digitalWrite(trigPin4, LOW);  //パスル出力準備
  delayMicroseconds(2);

  digitalWrite(trigPin4, HIGH); //パスル出力処理
  delayMicroseconds(10);  //モジュールごとに要確認

  digitalWrite(trigPin4, LOW);  //パスル出力終了処理

  right.Duration = pulseIn(echoPin4, HIGH, timeout); //パスル確認処理

  if (right.Duration > 0) {  //右超音波
    right.Duration = right.Duration / 2;
    right.Distance = right.Duration * 340 * 100 / 1000000;

  }

  if (right.Distance >= 254) {
    right.Distance = 254;

  }

  Serial.println(right.Distance);  //シリアルモニタ用

  front.send_Distance = front.Distance;
  left.send_Distance = left.Distance;
  back.send_Distance = back.Distance;
  right.send_Distance = right.Distance;

  Serial1.write(255);
  
  if (front.Distance < 40.00) {
    if (left.Distance < 40.00) {
      if (back.Distance < 40.00) {
        if (right.Distance < 40.00) {
          Serial1.write(1); //停止

        } else {
          Serial1.write(5); //右

        }
      } else if (right.Distance < 40.00) {
        Serial1.write(3); //後

      } else {
        Serial1.write(9); //右後

      }
    } else if (back.Distance < 40.00) {
      if (right.Distance < 40.00) {
        Serial1.write(4); //左

      } else {
        Serial1.write(1); //停止

      }
    } else if (right.Distance < 40.00) {
      Serial1.write(8); //左後

    } else {
      Serial1.write(3); //後

    }
  } else if (left.Distance < 40.00) {
    if (back.Distance < 40.00) {
      if (right.Distance < 40.00) {
        Serial1.write(2); //前

      } else {
        Serial1.write(7); //右前

      }
    } else if (right.Distance < 40.00) {
      Serial1.write(1); //停止

    } else {
      Serial1.write(5); //右

    }
  } else if (back.Distance < 40.00) {
    if (right.Distance < 40.00) {
      Serial1.write(6); //左前

    } else {
      Serial1.write(2); //前

    }
  } else if (right.Distance < 40.00) {
    Serial1.write(2); //左

  } else {
    Serial1.write(1); //停止

  }

  Serial1.write(front.send_Distance);
  Serial1.write(left.send_Distance);
  Serial1.write(back.send_Distance);
  Serial1.write(right.send_Distance);

  Serial1.flush();

}