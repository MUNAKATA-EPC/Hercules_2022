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

  }
  
}