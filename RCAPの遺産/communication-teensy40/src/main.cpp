#include <Arduino.h>

int d = 0;

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop() {
  d = Serial3.read();
  Serial.print(d);
}