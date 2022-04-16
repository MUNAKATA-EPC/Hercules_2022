/*
  SerialMglcd.ino

  This sketch is the firmware for serial MGLCD shileds.
    
  This file is part of Monochrome Graphic LCD library (MGLCD) for Arduino.
  
  MGLCD was developed by Synapse(Hiroshi Tanigawa) from 2012 to 2016.  This
  Library is originally distributed at Team Schaft's Homepage. 
  <http://www3.big.or.jp/~schaft/hardware>

  MGLCD is now under beta testing, so specification may be changed 
  in the future.

  MGLCD is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 2.1 of the License, or
  (at your option) any later version.

  MGLCD is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with MGLCD.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <MGLCD.h>
#include <EEPROM.h>

// Define device number
#define DEV_SG12232         1
#define DEV_SG12864         2
#define DEV_S12232ZA        3

// Select device
//#define MGLCD_DEVICE DEV_SG12232
//#define MGLCD_DEVICE DEV_SG12864
#define MGLCD_DEVICE DEV_S12232ZA

// Options
#define CHARGE_PUMP_OSC_PIN 3
//#define CONTRAST_CTRL
//#define BACKLIGHT_CTRL

unsigned char ButtonPinNo[]={
  2,12,13,A4
}; // pins assigned for buttons

unsigned char LedPinNo[] = {
  A5
}; // pins assigned for LEDs

#define XON  0x11 // XON character
#define XOFF 0x13 // XOFF character
#define STX  0x02 // STX character
#define ETX  0x03 // ETX character
#define ACK  0x06 // ACK character
#define NAK  0x15 // NAK character
#define ERR  0x07 // character which means errors occured in command
#define XON_SIZE  16 // XON is sent when result of Serial.available() function reaches this value
#define XOFF_SIZE 48 // XOFF is sent when result of Serial.avaiiable() function reaches this value
#define MAX_PACKET_SIZE (MGLCD_serial::MaxCommandSize*2)
#define CONTRAST_ADDRESS 0

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

static boolean        xon;
static boolean        CrReceived = false;
static boolean        ReceivingPacket = false;
static unsigned char  packet[MAX_PACKET_SIZE];
static unsigned char  PacketSize;
static unsigned char  PacketIndex;
static unsigned char  command[MGLCD_serial::MaxCommandSize];
static unsigned char  CommandSize;
static unsigned char  CommandResult[MGLCD_serial::MaxCommandResultSize];
static unsigned char  UserChars[32][5]={};
static unsigned char  BacklightState;
static unsigned char  contrast;
static unsigned char  BitmapWidth;
static unsigned char  BitmapHeight;
static unsigned char  BitmapPageNum;
static unsigned char  BitmapX;
static unsigned char  BitmapY;
static unsigned       BitmapIndex;
static unsigned       BitBuffer;
static unsigned char  ValidBitNum;
static const int      ButtonNum = sizeof(ButtonPinNo)/sizeof(*ButtonPinNo);
static const int      LedNum    = sizeof(LedPinNo   )/sizeof(*LedPinNo   );
static unsigned char  LedState[LedNum];
static unsigned long  LastBlinkTime;
static const unsigned BlinkInterval = 500;


#if MGLCD_VERSION != 41
#error Version of firmware is different from that of library.
#endif

static signed char SetBacklightState(unsigned char val)
{
  if(val==MGLCD_BACKLIGHT_ON || val==MGLCD_BACKLIGHT_OFF) {
    BacklightState=val;
    pinMode(A5,OUTPUT);
    digitalWrite(A5,val==MGLCD_BACKLIGHT_ON ? HIGH : LOW);
  } else if(val!=MGLCD_GET_BACKLIGHT_STATE) {
    return -1;
  } // if

  return BacklightState;  
} // SetBacklightState

static signed char SetContrast(unsigned char val)
{
  if(val>MGLCD_MAX_CONTRAST) return -1;
  digitalWrite( 2,(val>>0)&1 ? LOW : HIGH);
  digitalWrite( 3,(val>>1)&1 ? LOW : HIGH);
  digitalWrite(12,(val>>2)&1 ? LOW : HIGH);
  digitalWrite(13,(val>>3)&1 ? LOW : HIGH);
  contrast=val;
  return 0;
} // SetContrast

static unsigned char GetDefaultContrast()
{
  unsigned char data;
  
  data=EEPROM.read(CONTRAST_ADDRESS);
  if((data&0xf)!=(((~data)>>4)&0xf)) {
    return 6;
  } else {
    return data&0xf;
  } // if
} // GetDefaultContrast

static signed char SetDefaultContrast(unsigned char val)
{
  if(val>MGLCD_MAX_CONTRAST) return -1;
  EEPROM.write(CONTRAST_ADDRESS,val|((~val)<<4));
  return 0;
} // SetDefaultContrast

static signed char SetBitmapSizeAndCoordiante(unsigned char bw, unsigned char bh, unsigned char x, unsigned char y)
{
  if(x+bw>MGLCD.GetWidth() || y+bh>MGLCD.GetHeight()) return -1;
  BitmapWidth  =bw;
  BitmapHeight =bh;
  BitmapPageNum=(bh+7)/8;
  BitmapX      =x;
  BitmapY      =y;
  BitmapIndex  =0;
  return 0;
} // SetBitmapSizeAndCoordiante

static void DrawBitmapFragment(unsigned char bmp[])
{
  unsigned char HalfWidth,InvertMode,x,page,BitmapPage,YOffset,ValidBits,mask,cs;
  unsigned char ColumnCommand;
  unsigned char LcdData,BmpData;

  HalfWidth=MGLCD.GetWidth()/2;
  InvertMode=MGLCD.GetInvertMode();
  BitmapPage=BitmapY>>3;
  YOffset=BitmapY&0x7;
  for(unsigned char i=0; i<MGLCD_serial::MaxCommandSize-1; i++) {
    if(BitmapIndex>=unsigned(BitmapWidth*BitmapPageNum)) break;
    page=BitmapIndex/BitmapWidth;
    x   =BitmapIndex-page*BitmapWidth+BitmapX;
    page+=BitmapPage;
    if(x<HalfWidth) {
      cs=MGLCD_CS1;
      ColumnCommand=MGLCD.ColumnAddressCommand+x;
    } else {
      cs=MGLCD_CS2;
      ColumnCommand=MGLCD.ColumnAddressCommand+x-HalfWidth;
    } // if
    BmpData=bmp[i];
    if(InvertMode==MGLCD_INVERT) BmpData=~BmpData;
    ValidBits=((page-BitmapPage)==(BitmapPageNum-1) ? ((1<<((BitmapHeight-1)&7)+1)-1) : 0xff);
    mask=(ValidBits<<YOffset);
    MGLCD.WriteData(cs|MGLCD_COMMAND,MGLCD.PageAddressCommand+page);
    MGLCD.WriteData(cs|MGLCD_COMMAND,ColumnCommand);
    MGLCD.ReadData(cs|MGLCD_DATA);
    LcdData=(MGLCD.ReadData(cs|MGLCD_DATA)&(~mask)) | ((BmpData<<YOffset)&  mask );
    MGLCD.WriteData(cs|MGLCD_COMMAND,ColumnCommand);
    MGLCD.WriteData(cs|MGLCD_DATA,LcdData);
    if(YOffset>0 && (mask=ValidBits>>(8-YOffset))!=0) {
      MGLCD.WriteData(cs|MGLCD_COMMAND,MGLCD.PageAddressCommand+page+1);
      MGLCD.WriteData(cs|MGLCD_COMMAND,ColumnCommand);
      MGLCD.ReadData(cs|MGLCD_DATA);
      LcdData=(MGLCD.ReadData(cs|MGLCD_DATA)&(~mask)) | ((BmpData>>(8-YOffset))&  mask );
      MGLCD.WriteData(cs|MGLCD_COMMAND,ColumnCommand);
      MGLCD.WriteData(cs|MGLCD_DATA,LcdData);
    } // if
    BitmapIndex++;
  } // for i
} // DrawBitmapFragment

static signed char SetLedState(unsigned char LedNo, unsigned char state)
{
  if(LedNo==MGLCD_GET_LED_NUM) return LedNum;
  if(LedNo>=LedNum) return -1;
  
  switch(state) {
    case MGLCD_LED_ON:
    case MGLCD_LED_OFF:
    case MGLCD_LED_BLINK:
      LedState[LedNo]=state;
      break;
    case MGLCD_LED_TOGGLE:  
      switch(LedState[LedNo]) {
        case MGLCD_LED_OFF:
          LedState[LedNo]=MGLCD_LED_ON;
          break;
        case MGLCD_LED_ON:
          LedState[LedNo]=MGLCD_LED_OFF;
          break;
        default:
          return -2;
      } // switch
      break;
    case MGLCD_GET_LED_STATE:
      break;
    default:
      return -3;
  } // switch
  if(LedState[LedNo]==MGLCD_LED_OFF) {
    digitalWrite(LedPinNo[LedNo],LOW);
  } else if(LedState[LedNo]==MGLCD_LED_ON) {
    digitalWrite(LedPinNo[LedNo],HIGH);
  } // if 
  return LedState[LedNo];
} // SetLedState

static void SendBits(unsigned char data, unsigned char BitNum)
{
  BitBuffer=(BitBuffer<<BitNum)|data;
  ValidBitNum+=BitNum;
  while(ValidBitNum>=7) {
    Serial.write(0x80|((BitBuffer>>(ValidBitNum-=7))&0x7f));
  } // while
} // SendBits

static int ReceiveBits(unsigned char BitNum)
{
  unsigned char data;
  
  while(ValidBitNum<BitNum) {
    if(PacketIndex>=PacketSize || ((data=packet[PacketIndex++])&0x80)==0) return -1;    
    BitBuffer=(BitBuffer<<7)|(data&0x7f);
    ValidBitNum+=7;
  } // while
  ValidBitNum-=BitNum;
  return (BitBuffer>>ValidBitNum)&((1<<BitNum)-1);
} // ReceiveBits

static int DecodePacket(void)
{
  unsigned char parity;
  int received;
  unsigned char ParamNum;
  
  if(PacketSize>MAX_PACKET_SIZE) return -1;
  
  ValidBitNum=0;
  PacketIndex=0;
  
  if((received=ReceiveBits(6))<0) return -2;
  command[0]=received;
  if(command[0]>=MGLCD_serial::SCMax) return -3; // Undefined command
  ParamNum=pgm_read_byte_near(&MGLCD_serial::ParamNum[command[0]][0]); // Get parameter number
  parity=(command[0]>>4)^(command[0]&0xf);
  CommandSize=1;

  for(unsigned char i=0; i<ParamNum; i++) {
    if((received=ReceiveBits(8))<0) return -4;
    command[CommandSize++]=received;
    parity^=(received>>4)^(received&0xf);
  } // for i
  
  if((received=ReceiveBits(4))<0 || received!=parity) return -5;
  
  return 0;
} // DecodePacket

static void SendCommandResult(unsigned char CommandResultSize)
{
  unsigned char parity;
  int i;
  unsigned char data;
  
  Serial.write(STX);
  
  ValidBitNum=0;
  parity=0;
  for(i=0; i<CommandResultSize; i++) {
    data=CommandResult[i];
    SendBits(data,8);
    parity^=(data>>4)^(data&0xf);
  } // for i

  SendBits(parity,4);
  SendBits(0,6); // Flush BitBuffer
  Serial.write(ETX);  
} // SendCommandResult

static char *VersionStr(unsigned v)
{
  static char str[6];
  char *p;
  
  p=str;
  if(v>=1000) { // Version equals to or grater than 10.00
    *(p++)='0'+v/1000;
    v%=1000;
  } // if
  
  *(p++)='0'+v/100;
  v%=100;
  
  *(p++)='.';
  
  *(p++)='0'+v/10;
  v%=10;
  
  *(p++)='0'+v;
  
  return str;
} // PrintVersion

static void ProcessCommand(void)
{
  signed char result;
  unsigned long NewBaudRate;
  unsigned LibVer;
  
  NewBaudRate=0;
  result=0;
  switch(command[0]) {
  case MGLCD_serial::SCPing:
    break;  
  case MGLCD_serial::SCChangeBaudRate:
    NewBaudRate=command[1]+((unsigned long)(command[2])<<8)+((unsigned long)(command[3])<<16)+((unsigned long)(command[4])<<24);
    break;
  case MGLCD_serial::SCReset:
    LibVer=unsigned(command[3])+(unsigned(command[4])<<8);
    if(LibVer==MGLCD_VERSION) { // Versions of MGLCD library and firmware are the same
      result=MGLCD.Reset(command[1],command[2]);
      CommandResult[0]=MGLCD.GetWidth();
      CommandResult[1]=MGLCD.GetHeight();
#ifdef BACKLIGHT_CTRL
      SetBacklightState(MGLCD_BACKLIGHT_OFF);
#endif
#ifdef CONTRAST_CTRL
      SetContrast(GetDefaultContrast());
#endif
      if(LedNum>0) SetLedState(0,MGLCD_LED_ON);
    } else { // Version difference detected
      MGLCD.Reset();
      MGLCD.println(F("Versions differ!"));
      MGLCD.print(F("firmware:"));
      MGLCD.println(VersionStr(MGLCD_VERSION));
      MGLCD.print(F("library :"));
      MGLCD.println(VersionStr(LibVer));
      delay(10000);
      result=-1;
    } // if
    break;
  case MGLCD_serial::SCClearScreen:
    result=MGLCD.ClearScreen();
    break;
  case MGLCD_serial::SCSetTextWindow:
    result=MGLCD.SetTextWindow(command[1],command[2],command[3],command[4]);
    break;    
  case MGLCD_serial::SCSetInvertMode:
    result=MGLCD.SetInvertMode(command[1]);
    break;
  case MGLCD_serial::SCSetScrollMode:
    result=MGLCD.SetScrollMode(command[1]);
    break;
  case MGLCD_serial::SCSetCodeMode:
    {
      PDecodeFunc CodeMode;
      
      CodeMode=IndexToCodeMode(command[1]);
      if(CodeMode==NULL) {
        result=-1;
      } else {
        result=MGLCD.SetCodeMode(CodeMode);
      } // if
    }
    break;
  case MGLCD_serial::SCGetCodeMode:
    CommandResult[0]=CodeModeToIndex(MGLCD.GetCodeMode());
    break;
  case MGLCD_serial::SCLocate:
    result=MGLCD.Locate(command[1],command[2]);
    break;  
  case MGLCD_serial::SCGetX:
    CommandResult[0]=MGLCD.GetX();
    break;
  case MGLCD_serial::SCGetY:
    CommandResult[0]=MGLCD.GetY();
    break;
  case MGLCD_serial::SCClearRestOfLine:
    result=MGLCD.ClearRestOfLine();
    break;   
  case MGLCD_serial::SCUserChar:
    UserChars[command[1]][0]=command[2];
    UserChars[command[1]][1]=command[3];
    UserChars[command[1]][2]=command[4];
    UserChars[command[1]][3]=command[5];
    UserChars[command[1]][4]=command[6];    
    break;       
  case MGLCD_serial::SCSetPixel:
    result=MGLCD.SetPixel(command[1],command[2],command[3]);
    break;      
  case MGLCD_serial::SCGetPixel:
    result=MGLCD.GetPixel(command[1],command[2]);
    if(result>=0) {
      CommandResult[0]=(unsigned char)result;
      result=0;
    } // if
    break;      
  case MGLCD_serial::SCLine:
    result=MGLCD.Line(command[1],command[2],command[3],command[4],command[5]);
    break;
  case MGLCD_serial::SCRect:
    result=MGLCD.Rect(command[1],command[2],command[3],command[4],command[5]);
    break;
  case MGLCD_serial::SCFillRect:
    result=MGLCD.FillRect(command[1],command[2],command[3],command[4],command[5]);
    break;
  case MGLCD_serial::SCRoundRect:
    result=MGLCD.RoundRect(command[1],command[2],command[3],command[4],command[5],command[6]);
    break;
  case MGLCD_serial::SCCircle:
    result=MGLCD.Circle(command[1],command[2],command[3],command[4]);
    break;
  case MGLCD_serial::SCFillCircle:
    result=MGLCD.FillCircle(command[1],command[2],command[3],command[4]);
    break;
  case MGLCD_serial::SCBacklight:
#ifdef BACKLIGHT_CTRL  
    result=SetBacklightState(command[1]);
    if(result>=0) {
      CommandResult[0]=result;
      result=0;
    } // if
#else
    result=-1;
#endif
    break;
  case MGLCD_serial::SCContrast:
#ifdef CONTRAST_CTRL  
    if(command[1]==MGLCD_GET_CURRENT_CONTRAST) {
      CommandResult[0]=contrast;
    } else if(command[1]==MGLCD_GET_DEFAULT_CONTRAST) {
      CommandResult[0]=GetDefaultContrast();
    } else {
      if(command[2]!=MGLCD_NOT_SET_DEFAULT && command[2]!=MGLCD_SET_DEFAULT) {
        CommandResult[0]=-1;
      } else{
        CommandResult[0]=(SetContrast(command[1])==0 ? 0 : -2);
        if(CommandResult[0]==0 && command[2]==MGLCD_SET_DEFAULT) {
          SetDefaultContrast(command[1]);
        } // if
      } // if
    } // if
#else
    CommandResult[0]=-10;
#endif
    break;
  case MGLCD_serial::SCStartDrawBitmap:
    result=SetBitmapSizeAndCoordiante(command[1],command[2],command[3],command[4]);
    break; 
  case MGLCD_serial::SCSendBitmap:
    result=BitmapIndex<unsigned(BitmapWidth*BitmapPageNum) ? 0 : -1;
    break;
  case MGLCD_serial::SCReadButton:
    if(command[1]==MGLCD_GET_BUTTON_NUM) {
      CommandResult[0]=ButtonNum;
    } else if(command[1]>=ButtonNum) {
      result=-1;
    } else {
      CommandResult[0]=digitalRead(ButtonPinNo[command[1]])==HIGH ? MGLCD_BUTTON_OFF : MGLCD_BUTTON_ON;
    } // if
    break;
  case MGLCD_serial::SCLed:
    result=SetLedState(command[1],command[2]);
    if(result>=0) {
      CommandResult[0]=result;
      result=0;
    } // if
    break;
  } // switch

  if(result==0) {
      unsigned char CommandResultSize=(unsigned char)pgm_read_byte_near(&MGLCD_serial::ParamNum[command[0]][1]);
    if(CommandResultSize==0) {
      Serial.write(ACK);
      switch(command[0]) {
      case MGLCD_serial::SCSendBitmap:
        DrawBitmapFragment(&command[1]);
        break;
      } // switch
    } else {
      SendCommandResult(CommandResultSize);
    } // if
  } else {
    Serial.write(ERR);
  } // if

  if(NewBaudRate) {
    Serial.flush(); 
    delay(35);
    Serial.begin(NewBaudRate);
  } // if
} // ProcessCommand

void setup() {
#ifdef CHARGE_PUMP_OSC_PIN
  // Enable Oscillator for charge pump
  pinMode(CHARGE_PUMP_OSC_PIN,OUTPUT);
  analogWrite(CHARGE_PUMP_OSC_PIN,127);
#endif

#ifdef CONTRAST_CTRL
  // initialize pins for contrast
  pinMode( 2,OUTPUT);
  pinMode( 3,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
#endif

  // initialize pins for buttons
  for(int i=0; i<ButtonNum; i++) {
    pinMode(ButtonPinNo[i],INPUT_PULLUP);
  } // for i
  
  // initialize pins for Leds
  for(int i=0; i<LedNum; i++) {
    pinMode(LedPinNo[i],OUTPUT);
    SetLedState(i,i==0 ? MGLCD_LED_ON : MGLCD_LED_OFF);
  } // for i
  LastBlinkTime=millis();
  
#ifdef BACKLIGHT_CTRL
  // initialize pin for backlight control
  SetBacklightState(MGLCD_BACKLIGHT_OFF);
#endif

  // initialize serial port  
  Serial.begin(MGLCD_serial::DefaultBaudRate);
  pinMode(0,INPUT_PULLUP);
  
  // initialize LCD
  MGLCD.Reset();
  MGLCD.UserChars(UserChars,32,MGLCD_RAM);
  
#ifdef CONTRAST_CTRL
  // Contrast test
  MGLCD.print(F("Contrast Test"));
  for(int i=0; i<MGLCD_MAX_CONTRAST; i++) {
    MGLCD.Locate(0,1);
    MGLCD.print("contrast = ");
    MGLCD.print(i);
    MGLCD.ClearRestOfLine();
    SetContrast(i);
    delay(150);
  } // for i
  for(int i=MGLCD_MAX_CONTRAST; i>=0; i--) {
    MGLCD.Locate(0,1);
    MGLCD.print("contrast = ");
    MGLCD.print(i);
    MGLCD.ClearRestOfLine();
    SetContrast(i);
    delay(150);
  } // for i  
  SetContrast(GetDefaultContrast());
#endif
  
  // Display opening message.
  MGLCD.ClearScreen();
  MGLCD.print(F("Serial MGLCD "));
  MGLCD.println(VersionStr(MGLCD_VERSION));

  // Send opening message.
  Serial.print(F("Serial MGLCD "));
  Serial.println(VersionStr(MGLCD_VERSION));
  
  // initalize software flow control  
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

    if(ReceivingPacket) { // Receiving a packet
      if(data==ETX) { // ETX was received.
        if(DecodePacket()==0) { // Command received
          ProcessCommand();
        } else { // Not command
          Serial.write(NAK);
        } // if        
        ReceivingPacket=false;
      } else { // A character other than ETX was Received.
        if(PacketSize>=MAX_PACKET_SIZE) {
          Serial.write(NAK);
          PacketSize=0;
          ReceivingPacket=false;
        } else { // PacketSize<MAX_PACKET_SIZE
          packet[PacketSize++]=data;
        } // if
      } // if
    } else { // Receiving a character
      // Line feed control.  This process allows you to use any of CR, CR+LF and LF as (an) line feed character(s).
      if(data=='\r') { // CR was received.
        data='\n';
        CrReceived=true;
      } else if(data=='\n') { // LF was received.
        if(CrReceived) data=-1;
        CrReceived=false;
      } else if(data==STX) { // STX was received.
        ReceivingPacket=true;
        PacketSize=0;
      } else { // A character other than CR, LF and STX was received.
        CrReceived=false;
      } // if
    
      // Print data on the LCD screen.
      if(!ReceivingPacket && data>=0) {
        MGLCD.PutChar(data);
      } // if
    } // if
  } // if
 
  // Blink Leds
  if(LedNum>0 && millis()-LastBlinkTime>BlinkInterval) {
    static unsigned char BlinkingLedState = LOW;

    LastBlinkTime+=BlinkInterval;
    BlinkingLedState=BlinkingLedState==LOW ? HIGH : LOW;
    for(int i=0; i<LedNum; i++) {
      if(LedState[i]==MGLCD_LED_BLINK) digitalWrite(LedPinNo[i],BlinkingLedState);
    } // for i
  } //if
} // loop