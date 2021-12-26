#include <Arduino.h>
#include <Wire.h>
#include <FaboLCDmini_AQM0802A.h>
#include <DSR1202.h>

FaBoLCDmini_AQM0802A lcd;

DSR1202 dsr1202(1);

#include <define.h>
#include <variable.h>
#include <startup.h>
#include <Serial_receive.h>
#include <print_LCD.h>
#include <control_LED.h>

void setup() {

  startup();

}

void loop() {

  Serial_receive();
  print_LCD();
  control_LED();

  if ((state_LCD == 4) && (state_white == 1) && (switch_program == HIGH)) {

    //オフェンスプログラム

  } else if ((state_LCD == 5) && (state_white == 1) && (switch_program == HIGH)) {

    //ディフェンスプログラム

  } else if ((state_LCD == 6) && (state_white == 1) && (switch_program == HIGH)) {

    dsr1202.move(10, 10, 10, 10);

  }
  
}