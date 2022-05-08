#include <Arduino.h>
#include <BluetoothSerial.h>

#define LED 32

int head, send_data, send_power;

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
  if (SerialBT.available() > 0) {
    digitalWrite(LED, HIGH);
    head = SerialBT.read();
    if (head == 255) {
      send_data = SerialBT.read();
      send_power = SerialBT.read();
    }
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.write(255);
  Serial.write(send_data);
  Serial.write(send_power);
  //Serial.println(send_data * 2);
}
