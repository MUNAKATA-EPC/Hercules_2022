#include <Arduino.h>

int d = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  while (!Serial)
  {
    ; //接続待機
  }
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
  
}

void loop() {
  if (Serial.available() > 0)
  {
    d = Serial.read();
    Serial1.print(d);
  }
}
