/*
  SerialLcd.ino
  
    This sketch displays characters sent via serial port.
    Software flow control (XON/XOFF) is adopted, so usually both RX and TX signals must be connected.  
  However, if you send characters slowly enough, no flow control is needed, so you can use only RX signal.
    This program sends a 'F' character following XOFF and sends a 'N' character following XON in order to
  visualize software flow control.
    This file is designed for multi-device.  YOU HAVE TO MODIFY A PART OF THIS FILE to accommodate it to your design.

*/

#include <MGLCD.h>

// Define device number
#define DEV_SG12232         1
#define DEV_SG12864         2
#define DEV_S12232ZA        3


// Select device
#define MGLCD_DEVICE DEV_SG12232  // Enable this line if SG12232C is directly connected to your Arduino.
//#define MGLCD_DEVICE DEV_SG12864  // Enable this line if SG12864ASLB-GB is directly connected to your Arduino.
//#define MGLCD_DEVICE DEV_S12232ZA // Enable this line if S12232ZA is directly connected to your Arduino.

// Options
//#define CHARGE_PUMP_OSC_PIN 3

// Error check
#if ((MGLCD_DEVICE==DEV_SERIAL) || (MGLCD_DEVICE==DEV_SOFTWARE_SERIAL)) && defined(CHARGE_PUMP_OSC_PIN)
#error CHARGE_PUMP_OSC_PIN cannot be defined when either MGLCD_DEVICE DEV_SERIAL or MGLCD_DEVICE DEV_SOFTWARE_SERIAL are defined.
#endif

#define XON  0x11 // XON character
#define XOFF 0x13 // XOFF character
#define XON_SIZE  16 // XON is sent when result of Serial.available() function reaches this value
#define XOFF_SIZE 32 // XOFF is sent when result of Serial.avaiiable() function reaches this value

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
#endif

static bool xon;
boolean CrReceived = false;

void setup() {
#ifdef CHARGE_PUMP_OSC_PIN
  // Enable Oscillator for charge pump
  pinMode(CHARGE_PUMP_OSC_PIN,OUTPUT);
  analogWrite(CHARGE_PUMP_OSC_PIN,127);
#endif

  MGLCD.Reset();
  Serial.begin(9600);
  while(!Serial);
  delay(2000);
  Serial.println(F("Serial terminal started."));
  MGLCD.println(F("Serial terminal started."));
  MGLCD.SetScrollMode(MGLCD_SCROLL);
  Serial.write(XON);
  xon=true;
} // setup

void loop() {
  // Software flow control.
  if(xon && Serial.available()>=XOFF_SIZE) {
    Serial.write(XOFF);
    xon=false; 
    Serial.print('F'); // This line is added to visualize flowcontrol.  You can comment out this line if you don't need visualization.
  } // if
  if(!xon && Serial.available()<=XON_SIZE) {
    Serial.write(XON);
    xon=true;
    Serial.print('N'); // This line is added to visualize flowcontrol.  You can comment out this line if you don't need visualization.
  } // if

  if(Serial.available()) {
    int data;

    data=Serial.read();

    // Line feed control.  This process allows you to use any of CR, CR+LF and LF as (an) line feed character(s).
    if(data=='\r') { // CR is received.
      data='\n';
      CrReceived=true;
    } else if(data=='\n') { // LF is received.
      if(CrReceived) data=-1;
      CrReceived=false;
    } else { // A character other than CR and LF is received.
      CrReceived=false;
    } // if

    // Print data on the LCD screen.
    if(data>=0) {
      MGLCD.PutChar(data);
      // Serial.write(data);  // If you need echo back, enable this line.
    } // if
  } // if
} // loop