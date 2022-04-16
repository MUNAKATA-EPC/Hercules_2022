/*

  SpeedTest.ino
  
  This sketch estimats MGLCD's drawing speed.
  This sketch is an porting of part of GLCDdemo, a sample sketch for GLCD library.
  This file is designed for multi-device.  YOU HAVE TO MODIFY A PART OF THIS FILE to accommodate it to your design.
  
*/

#include <MGLCD.h>
#include <MGLCD_SPI.h>
#include <SPI.h>

// define device number
#define DEV_AQM1248A   1
#define DEV_GH12864_20 2

// select device
#define MGLCD_DEVICE DEV_AQM1248A   // enable this line if AQM1248A is used
//#define MGLCD_DEVICE DEV_GH12864_20 // enable this line if GH12864-20 is used

#define CS_PIN   10
#define DI_PIN    9
#define MAX_FREQ (1000*1000UL)

#if MGLCD_DEVICE==DEV_AQM1248A
  static MGLCD_AQM1248A_SPI MGLCD(MGLCD_SpiPin2(CS_PIN, DI_PIN), MAX_FREQ);
#elif MGLCD_DEVICE==DEV_GH12864_20
  static MGLCD_GH12864_20_SPI MGLCD(MGLCD_SpiPin2(CS_PIN, DI_PIN), MAX_FREQ);
#else
  #error "invalid value:MGLCD_DEVICE"
#endif

#ifndef min // for arduino M0
  #define min(a,b) ((a)<(b) ? (a) : (b))
#endif

#define WIDTH    (MGLCD.GetWidth ())
#define HEIGHT   (MGLCD.GetHeight())
#define CENTER_X (WIDTH /2)
#define CENTER_Y (HEIGHT/2)
#define RIGHT    (WIDTH -1)
#define BOTTOM   (HEIGHT-1)

static unsigned long startMillis;
static unsigned int  loops = 0;
static unsigned int  iter= 0;

void setup()
{
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