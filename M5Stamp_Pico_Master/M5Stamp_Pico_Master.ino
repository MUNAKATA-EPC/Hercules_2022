#include <Arduino.h>
#include <BluetoothSerial.h>

#define FrontSW 19
#define BackSW 18
#define LeftSW 26
#define RightSW 22

int Front, Back, Left, Right, RadsHalf, send_data;

BluetoothSerial SerialBT;

String name = "Slave";
const char *pin = "1234"; //<- standard pin would be provided by default
bool connected;

void setup() {
  Serial.begin(115200);

  //以下、Master(コントローラー)設定
  SerialBT.begin("Master", true); //自分の名前指定(trueでマスター)

  connected = SerialBT.connect(name); //接続先機器名

  if(connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while(!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app."); 
    }
  }
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();

  pinMode(FrontSW, INPUT_PULLUP);
  pinMode(BackSW, INPUT_PULLUP);
  pinMode(LeftSW, INPUT_PULLUP);
  pinMode(RightSW, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(FrontSW)) {
    Front = 1;
  } else {
    Front = 0;
  }
  if (!digitalRead(BackSW)) {
    Back = 4;
  } else {
    Back = 0;
  }
  if (!digitalRead(LeftSW)) {
    Left = 2;
  } else {
    Left = 0;
  }
  if (!digitalRead(RightSW)) {
    Right = 8;
  } else {
    Right = 0;
  }

  send_data = Front + Left + Back + Right;

  SerialBT.write(send_data);
}
