/*

  SetContrast.ino

  This sketch sets default contrast of LCD controlled via MGLCD_serial libaray.
  This file is designed for multi-device.  YOU HAVE TO MODIFY A PART OF THIS FILE to accommodate it to your design.

*/

#include <MGLCD.h>
#include <SoftwareSerial.h>

// Define device number
#define DEV_SERIAL          1001
#define DEV_SOFWARE_SERIAL  1002

// Select device
//#define MGLCD_DEVICE DEV_SERIAL // Enable this line if your LCD is connected to your Arduino via hardware serial port.
#define MGLCD_DEVICE DEV_SOFTWARE_SERIAL // Enable this line if your LCD is connected to your Arduino via software serial port. 

// Default contrast
#define DEFAULT_CONTRAST 6 // Set number between 0 and 15.

#if MGLCD_DEVICE==DEV_SERIAL
#ifdef USBCON // Leonardo
MGLCD_serial MGLCD(&Serial1,500000); // Assuming that Serial is used at 500,000bps.  You can replace &Serial with &Serial1, &Serial2 and so on.  You can also change the baud rate.
#else // Not Leonardo
MGLCD_serial MGLCD(&Serial,500000); // Assuming that Serial is used at 500,000bps.  You can replace &Serial with &Serial1, &Serial2 and so on.  You can also change the baud rate.
#endif

#elif MGLCD_DEVICE==DEV_SOFTWARE_SERIAL
SoftwareSerial mySerial(10,11); // Assuming that RX is on pin 10 and that TX is on pin 11.  You can change the key assignments.
MGLCD_SoftwareSerial MGLCD(&mySerial,38400);

#endif

void setup()
{
  signed char result;
  while(MGLCD.Reset()); // Wait until LCD is reset.
  
  result=MGLCD.Contrast(DEFAULT_CONTRAST);
  if(result==0) {
    MGLCD.print("Default contrast was successfully changed to ");
    MGLCD.print(DEFAULT_CONTRAST);
    MGLCD.println(".");
  } else {
    MGLCD.println("Failed to change default contrast.");
    MGLCD.print("Error code:");
    MGLCD.println(result);
  } // if
} // setup

void loop()
{
} // loop