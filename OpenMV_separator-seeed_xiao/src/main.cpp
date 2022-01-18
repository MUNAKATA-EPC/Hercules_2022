#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

#define rads1Pin 3   //コート角度
#define riole1Pin 6 //コート左右
#define rads2Pin 8   //ボール角度
#define riole2Pin 9  //ボール左右
#define LED 13       //LED

int head, rads1, riole1, rads2, riole2;

void setup() {
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  mySerial.begin(115200);
  while (!mySerial) {
    ;
  }
}

void loop() {
  if (mySerial.available() > 0) {
    digitalWrite(LED, HIGH);
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
    } else {
      head = mySerial.read();
    }
  } else {
    digitalWrite(LED, LOW);
  }
  Serial.print(rads1);
  Serial.print("\t");
  Serial.print(riole1);
  Serial.print("\t");
  Serial.print(rads2);
  Serial.print("\t");
  Serial.println(riole2);

  analogWriteResolution(7);

  analogWrite(rads1Pin, rads1);
  analogWrite(riole1Pin, riole1);
  analogWrite(rads2Pin, rads2);
  analogWrite(riole2Pin, riole2);
}