#include <Arduino.h>
#include <SoftwareSerial.h>

#define rads1Pin 7  //コート角度
#define riole1Pin 8 //コート左右
#define rads2Pin 9  //ボール角度
#define riole2Pin 10  //ボール左右

SoftwareSerial mySerial(4, 5); // RX, TX

int head, rads1, riole1, rads2, riole2;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  while (!mySerial) {
    ;
  }
  
}

void loop() {
  if (mySerial.available() > 0) {
    head = mySerial.read();

    if (head == 'w') {
      rads1 = mySerial.read();
      head = mySerial.read();

      if (head == 'x') {
        riole1 = mySerial.read();
      }

      head = mySerial.read();

      if (head == 'y') {
        rads2 = mySerial.read();
      }

      head = mySerial.read();

      if (head == 'z') {
        riole2 = mySerial.read();
      }
    }
  }

  Serial.print("rads1 : ");
  Serial.println(rads1);
  Serial.print("\t");
  Serial.print("riole1 : ");
  Serial.print(riole1);
  Serial.print("\t");
  Serial.print("rads2 : ");
  Serial.print(rads2);
  Serial.print("\t");
  Serial.print("riole2 : ");
  Serial.println(riole2);

  analogWrite(rads1Pin, rads1);
  analogWrite(riole1Pin, riole1);
  analogWrite(rads2Pin, rads2);
  analogWrite(riole2Pin, riole2);
}