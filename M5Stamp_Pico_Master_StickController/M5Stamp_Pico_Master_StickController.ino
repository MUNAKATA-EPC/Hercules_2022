#include <Arduino.h>
#include <BluetoothSerial.h>

#define SW 18   //押し込んだらカチッ！ってなるやつ
#define XSW 36  //X方向データ取得
#define YSW 26  //Y方向データ取得

#define MAX_X 52    //X中心
#define MAX_Y 53.5  //Y中心

int SWState, XState, YState, rads, send_data, send_power; //変数たち

BluetoothSerial SerialBT; //ライブラリのセットアップ

String MACadd = "4C:75:25:C4:14:F0";  //デバイスMACアドレス
uint8_t address[6]  = {0x4C, 0x75, 0x25, 0xC4, 0x14, 0xF0}; //MACアドレスを配列にして保存
//uint8_t address[6]  = {0x00, 0x1D, 0xA5, 0x02, 0xC3, 0x22};
String name = "Slave";
const char *pin = "1234"; //<- standard pin would be provided by default
bool connected;

void setup() {
  Serial.begin(115200);

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

  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  SWState = digitalRead(SW);  //スイッチの状態確認

  analogReadResolution(7);  //アナログ入力分解能を7bitに設定

  XState = analogRead(XSW); //X方向の状態確認
  YState = analogRead(YSW); //Y方向確認

  rads = atan2((YState - MAX_Y), (XState - MAX_X)) * 180 / PI;  //X,Y座標から逆正接関数を用いて角度を求める

  if (rads > 0) {
    rads -= 360;
  }
  /*
     ロボット側の関数の都合に合わせて角度の出方を調整しています
  */

  send_data = abs(rads);  //送るデータの最大値が255を超えないように
  send_data /= 2;

  send_power = sqrt(pow((XState - MAX_X), 2) + pow((YState - MAX_Y), 2)), 2;
  send_power /= 2.3;
  if (send_power > 28) {
    send_power = 28;
  }

  if (abs(XState - MAX_X) > 15 || abs(YState - MAX_Y) > 15) {
    send_data = send_data;
    send_power = send_power;
  } else {
    send_data = 254;
    send_power = 0;
  }
  /*
     アナログ入力にはノイズが出るため出力角度が荒ぶらないように
  */

  //Serial.print("SW:");
  //Serial.print(SWState);
  //Serial.print("\t");
  //Serial.print("X:");
  //Serial.print(XState);
  //Serial.print("\t");
  //Serial.print("Y:");
  //Serial.print(YState);
  //Serial.print("\t");
  //Serial.print("Rads:");
  //Serial.print(rads);
  //Serial.print("\t");
  //Serial.print("send:");
  //Serial.print(send_data);
  //Serial.print("power:");
  //Serial.println(send_power);

  SerialBT.write(255);
  SerialBT.write(send_data);
  SerialBT.write(send_power);
}
