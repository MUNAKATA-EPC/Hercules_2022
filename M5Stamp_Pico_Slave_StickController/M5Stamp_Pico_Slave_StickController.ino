#include <Arduino.h>
#include <BluetoothSerial.h>

#define LED 32

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
    Serial.write(SerialBT.read());
    //Serial.println(SerialBT.read() * 2);
  } else {
    digitalWrite(LED, LOW);
  }
}
