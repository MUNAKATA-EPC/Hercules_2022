#include <Arduino.h>
#include <BluetoothSerial.h>
#include <M5StickC.h>

BluetoothSerial SerialBT;

String name = "Slave";
const char *pin = "1234"; //<- standard pin would be provided by default
bool connected;

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float vbat = 0.0F;

float rads = 0.0F;
float send_data = 0.0F;
float send_power = 0.0F;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(3);
  M5.Lcd.printf("AccelControll");

  //以下、Master(コントローラー)設定
  SerialBT.begin("Master", true); //自分の名前指定(trueでマスター)

  connected = SerialBT.connect(name); //接続先機器名

  if (connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();

  M5.IMU.Init();
}

void loop() {
  vbat = M5.Axp.GetVbatData() * 1.1 / 1000;
  M5.Lcd.setCursor(0, 15);
  if (M5.Axp.GetWarningLeve() == HIGH) {
    M5.Lcd.setTextColor(RED);
    M5.Lcd.printf("Volt:%.2fV\n", vbat);
    M5.Lcd.setTextColor(WHITE);
  } else {
    M5.Lcd.printf("Volt:%.2fV\n", vbat);
  }

  M5.update();
  // データ取得
  M5.IMU.getAccelData(&accX, &accY, &accZ);

  rads = atan2((accY * 100), (accX * 100)) * 180 / PI;
  if (rads < 0) {
    rads += 360;
  }
  /*
     ロボット側の関数の都合に合わせて角度の出方を調整しています
  */

  send_data = abs(rads);  //送るデータの最大値が255を超えないように
  send_data /= 2;

  send_power = sqrt(pow((accX * 100), 2) + pow((accY * 100), 2)), 2;
  send_power /= 3;
  if (send_power > 28) {
    send_power = 28;
  }

  if (abs(accX * 100) > 15 || abs(accY * 100) > 15) {
    send_data = send_data;
    send_power = send_power;
  } else {
    send_data = 254;
    send_power = 0;
  }
  /*
     ノイズが出るため出力角度が荒ぶらないように
  */

  // データ出力
  M5.Lcd.printf("R:%.2f\nSR:%.2f\nP:%.2f", rads, send_data, send_power);

  SerialBT.write(255);
  SerialBT.write(send_data);
  SerialBT.write(send_power);
}