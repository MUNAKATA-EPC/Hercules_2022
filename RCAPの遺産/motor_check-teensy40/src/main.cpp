#include <Arduino.h>
#include <DSR1202.h>

DSR1202 dsr1202(1);

void setup() {
  dsr1202.Init();
}

void loop() {
  for (size_t i = 0; i < 100; i++)
  {
    dsr1202.move(i,i,i,i);
    delay(100);
  }
}