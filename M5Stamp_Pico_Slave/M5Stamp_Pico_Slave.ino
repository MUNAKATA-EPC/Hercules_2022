#include <Arduino.h>
#include <BluetoothSerial.h>

#define LED 32

int receive_data, send_data;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Slave");  //自分の名前指定
  pinMode(LED, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    digitalWrite(LED, HIGH);
    receive_data = SerialBT.read();
    if (receive_data == 0) {  //停止
      //Serial.println("Stop");
      send_data = 255;
    } else if (receive_data == 1) { //前
      //Serial.println("Front");
      send_data = 0;
    } else if (receive_data == 2) { //左
      //Serial.println("Left");
      send_data = 90 / 2;
    } else if (receive_data == 3) { //左前
      //Serial.println("LeftFront");
      send_data = 45 / 2;
    } else if (receive_data == 4) { //後
      //Serial.println("Back");
      send_data = 180 / 2;
    } else if (receive_data == 6) { //左後
      //Serial.println("LeftBack");
      send_data = 135 / 2;
    } else if (receive_data == 8) { //右
      //Serial.println("Right");
      send_data = 270 / 2;
    } else if (receive_data == 9) { //右前
      //Serial.println("RightFront");
      send_data = 315 / 2;
    } else if (receive_data == 12) {  //右後
      //Serial.println("RightBack");
      send_data = 225 / 2;
    } else {
      //Serial.println("DataError");
      send_data = 255;
    }
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.write(send_data);
  //Serial.println(send_data * 2);
}
