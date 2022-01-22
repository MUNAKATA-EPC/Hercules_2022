//created by anbara

#include <DSR1202.h>

DSR1202 dsr1202(1); //Choose SerialPort (1 or 2 or 3)

void setup()
{
  dsr1202.Init(); //Initialization
}

void loop()
{
  //Input 4 motor power value.
  //value is -100 to 100.
  //(ch1, ch2, ch3, ch4)
  dsr1202.move(100, 100, 100, 100);
  delay(500);
}
