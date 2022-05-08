#include <Arduino.h>
#include <M5StickC.h>

float vbat = 0.0F;

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setRotation(3);
  M5.Lcd.printf("Voltage");
}

void loop() {
  vbat = M5.Axp.GetVbatData() * 1.1 / 1000;
  M5.Lcd.setCursor(0, 15);
  if (M5.Axp.GetWarningLeve() == HIGH) {
    M5.Lcd.setTextColor(RED);
    M5.Lcd.printf("Volt:%.2fV\n", vbat);
    M5.Lcd.setTextColor(WHITE);
  } else {
    M5.Lcd.printf("Volt:%.2fV\n", vbat);
  }
}