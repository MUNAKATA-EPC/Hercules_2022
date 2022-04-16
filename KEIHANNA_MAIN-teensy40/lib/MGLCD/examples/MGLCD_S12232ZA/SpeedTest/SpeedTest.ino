/*

  SpeedTest.ino
  
  This sketch estimats MGLCD's drawing speed.
  This sketch is an porting of part of GLCDdemo, a sample sketch for GLCD library.
  This file is designed for multi-device.  YOU HAVE TO MODIFY A PART OF THIS FILE to accommodate it to your design.
  
*/

#include <MGLCD.h>
#include <SoftwareSerial.h>

// Define device number
#define DEV_SG12232         1
#define DEV_SG12864         2
#define DEV_S12232ZA        3
#define DEV_SERIAL          1001
#define DEV_SOFTWARE_SERIAL 1002

// Select device
//#define MGLCD_DEVICE DEV_SG12232
//#define MGLCD_DEVICE DEV_SG12864 // Enable this line if SG12232C is directly connected to your Arduino.
#define MGLCD_DEVICE DEV_S12232ZA // Enable this line if SG12864ASLB-GB is directly connected to your Arduino.
//#define MGLCD_DEVICE DEV_SERIAL // Enable this line if S12232ZA is directly connected to your Arduino.
//#define MGLCD_DEVICE DEV_SOFTWARE_SERIAL // Enable this line if your LCD is connected to your Arduino via software serial port.

// Options
#define CHARGE_PUMP_OSC_PIN 3

// Error check
#if ((MGLCD_DEVICE==DEV_SERIAL) || (MGLCD_DEVICE==DEV_SOFTWARE_SERIAL)) && defined(CHARGE_PUMP_OSC_PIN)
#error CHARGE_PUMP_OSC_PIN cannot be defined when either MGLCD_DEVICE DEV_SERIAL or MGLCD_DEVICE DEV_SOFTWARE_SERIAL are defined.
#endif

#define WIDTH    (MGLCD.GetWidth ())
#define HEIGHT   (MGLCD.GetHeight())
#define CENTER_X (WIDTH /2)
#define CENTER_Y (HEIGHT/2)
#define RIGHT    (WIDTH -1)
#define BOTTOM   (HEIGHT-1)

// The following table illustrates SG12232 LCD-Arduino pin assignemnts.
// If you edit the following table, you can change pin assignemts.  Maximum performance is, however, 
// obtained in default pin assignments.
// LCD's RES pin must be connected to Arduino's RESET pin although RES and RESET pins are not mentioned
// in the table.
// CS1 and CS2 pins require pull up registers to keep their level high while Arduino is initializing
// or programming.
// Avoid to connect CS1 or CS2 to a Arduino's serial pin (1, 2) or a ICSP pin (11, 12, 13) becasuse 
// serial pins and ICSP pins can change thier logic levels while initializing or programming.
// LCD's CL pin must be connected to 2kHz clock oscillator.  Although this 2kHz clock signal can be 
// generated utilizing an Arduino's timer, it is not recommended.  You have to feed the 2kHz clock
// signal while VDD is supplied to LCD.  But Arduino doesn't generate 2kHz clock while initializing 
// or programming.  It can harm the LCD pannel.  An external dedicated clock oscillator is recommemded.
#if MGLCD_DEVICE==DEV_SG12232 || MGLCD_DEVICE==DEV_SG12864
static const TLcdPinAssignTable PinAssignTable={
    A0_DI  : A3, // A0 for SG12232, D/I for SG12864
    CS1_E1 : A0, // CS1
    CS2_E2 : A1, // CS2
    E      : A4,
    RW     : A2,
    DB0    : 8 ,
    DB1    : 9 ,
    DB2    : 10,
    DB3    : 11,
    DB4    : 4 ,
    DB5    : 5 ,
    DB6    : 6 ,
    DB7    : 7
}; // PinAssignTable;
#elif MGLCD_DEVICE==DEV_S12232ZA
static const TLcdPinAssignTable PinAssignTable={
    A0_DI  : A3, // A0
    CS1_E1 : A0, // E1
    CS2_E2 : A1, // E2
    E      : MGLCD_UNUSED_PIN,
    RW     : A2,
    DB0    : 8 ,
    DB1    : 9 ,
    DB2    : 10,
    DB3    : 11,
    DB4    : 4 ,
    DB5    : 5 ,
    DB6    : 6,
    DB7    : 7
}; // PinAssignTable;
#endif

#if MGLCD_DEVICE==DEV_SG12232
static MGLCD_SG12232 MGLCD(PinAssignTable);

#elif MGLCD_DEVICE==DEV_SG12864
static MGLCD_SG12864 MGLCD(PinAssignTable);

#elif MGLCD_DEVICE==DEV_S12232ZA
static MGLCD_S12232ZA MGLCD(PinAssignTable);

#elif MGLCD_DEVICE==DEV_SERIAL
#ifdef USBCON // Leonardo
MGLCD_serial MGLCD(&Serial1,500000); // Assuming that Serial is used at 500,000bps.  You can replace &Serial with &Serial1, &Serial2 and so on.  You can also change the baud rate.
#else // Not Leonardo
MGLCD_serial MGLCD(&Serial,500000); // Assuming that Serial is used at 500,000bps.  You can replace &Serial with &Serial1, &Serial2 and so on.  You can also change the baud rate.
#endif

#elif MGLCD_DEVICE==DEV_SOFTWARE_SERIAL
static SoftwareSerial mySerial(10,11);
static MGLCD_SoftwareSerial MGLCD(&mySerial,38400);

#endif

static unsigned long startMillis;
static unsigned int  loops = 0;
static unsigned int  iter= 0;

void setup()
{
#ifdef CHARGE_PUMP_OSC_PIN
  // Enable Oscillator for charge pump
  pinMode(CHARGE_PUMP_OSC_PIN,OUTPUT);
  analogWrite(CHARGE_PUMP_OSC_PIN,127);
#endif

  while(MGLCD.Reset());
} // setup

void drawSpinner(byte pos, byte x, byte y);

void loop()
{ 
  iter=0;
  startMillis = millis();
  while(iter++ < 10) { // do 10 iterations
    MGLCD.Rect(0, 0, CENTER_X, BOTTOM); // rectangle in left side of screen
    MGLCD.RoundRect(CENTER_X+2, 0, WIDTH-1, HEIGHT-1, 5);  // rounded rectangle around text area  
    for(int i=0; i < BOTTOM; i+=4)
      MGLCD.Line(1,1, CENTER_X-1, i);  // draw lines from upper left down right side of rectangle  
    MGLCD.Circle(CENTER_X/2, CENTER_Y-1, min(CENTER_X/2, CENTER_Y)-2);   // draw circle centered in the left side of screen  
    MGLCD.FillRect(CENTER_X+CENTER_X/2-8,CENTER_Y+CENTER_Y/2-1-8,CENTER_X+CENTER_X/2+8,CENTER_Y+CENTER_Y/2-1+8,0); // clear previous spinner position  
    drawSpinner(loops++, CENTER_X+CENTER_X/2, CENTER_Y+CENTER_Y/2-1);       // draw new spinner position
    MGLCD.Locate(CENTER_X/2/6,(BOTTOM-15)/8);
    MGLCD.print(iter);
  } // while
  // display iterations per second  
  unsigned long duration = millis() - startMillis;  
  int fps = (1000000L / duration) / 100;
  int fps_fract = (1000000L / duration) % 100;
  MGLCD.ClearScreen();               // clear the screen
  MGLCD.Locate(MGLCD.GetColumnNum()/2+1+(WIDTH>122), 1);
  MGLCD.print("FPS=");               // print a text string
  MGLCD.print(fps);                  // print an integer value
  MGLCD.print(".");
  if(fps_fract < 10)
    MGLCD.print((int)0);             // have to manually print the leading 0 when necessary
  MGLCD.print(fps_fract);
} // loop

void drawSpinner(byte pos, byte x, byte y) {   
  // this draws an object that appears to spin
  switch(pos % 8) {
    case 0 : MGLCD.Line( x, y-8, x, y+8);        break;
    case 1 : MGLCD.Line( x+3, y-7, x-3, y+7);    break;
    case 2 : MGLCD.Line( x+6, y-6, x-6, y+6);    break;
    case 3 : MGLCD.Line( x+7, y-3, x-7, y+3);    break;
    case 4 : MGLCD.Line( x+8, y, x-8, y);        break;
    case 5 : MGLCD.Line( x+7, y+3, x-7, y-3);    break;
    case 6 : MGLCD.Line( x+6, y+6, x-6, y-6);    break; 
    case 7 : MGLCD.Line( x+3, y+7, x-3, y-7);    break;
  } 
} // drawSpinner