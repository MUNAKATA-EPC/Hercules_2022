/*
  demo.ino
  
  This is a demo sketch for MGLCD library.
  This file is designed for multi-device.  YOU HAVE TO MODIFY A PART OF THIS FILE to accommodate it to your design.
  
*/

#include <MGLCD.h>
#include "kyoto.h"
#include <MGLCD_SPI.h>
#include <SPI.h>

// define device number
#define DEV_AQM1248A   1
#define DEV_GH12864_20 2

// select device
//#define MGLCD_DEVICE DEV_AQM1248A   // enable this line if AQM1248A is used
#define MGLCD_DEVICE DEV_GH12864_20 // enable this line if GH12864-20 is used

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

#define s ((((((((((((((((0
#define M <<1)+1)
#define _ <<1))
  
PROGMEM const uint8_t UserChars[][5] =
{
  { // 80
    s  _ M _ _ _ _ _ _  ,
    s  _ _ M M M M _ _  ,
    s  _ _ M _ _ _ _ _  ,
    s  _ _ M _ _ _ _ _  ,
    s  _ M M M M M _ _  
  },
  { // 81
    s  _ M _ M M _ _ _  ,
    s  _ M M _ _ M _ _  ,
    s  _ _ _ _ _ M _ _  ,
    s  _ M M _ _ M _ _  ,
    s  _ M _ M M _ _ _  
  },
  { // 82
    s  _ M M M M M M M  ,
    s  _ _ _ _ M _ _ M  ,
    s  _ _ _ _ M M M M  ,
    s  _ _ _ _ M _ _ M  ,
    s  _ M M M M M M M  
  }
};

#undef s
#undef M
#undef _

// This function displays a maze.  If you set d's value grater than 0, maze is drawn slowly according to d's value.
void maze(int d)
{
  int MazeWidth;
  int MazeHeight;
  int x,y,xx,yy,old_xx,old_yy;
  unsigned char FreeDirectionNum;
  unsigned char FreeDirection[4];
  unsigned char direction;

  // Get maze size
  MazeWidth =(MGLCD.GetWidth ()-1)/2;
  MazeHeight=(MGLCD.GetHeight()-1)/2;
  
  // Initialize screen
  MGLCD.SetInvertMode(MGLCD_NON_INVERT);
  MGLCD.ClearScreen();  
  MGLCD.FillRect(0,0,MazeWidth*2,MazeHeight*2);
  MGLCD.SetPixel(0,1,0);
  MGLCD.SetPixel(MazeWidth*2,MazeHeight*2-1,0);
  MGLCD.SetPixel(1,1,0);
  
  // Draw maze
  for(x=0; x<MazeWidth; x++) {
    for(y=0; y<MazeHeight; y++) {
      xx=x; yy=y;
      do{
        FreeDirectionNum=0;
        if(yy>0            && MGLCD.GetPixel((xx  )*2+1,(yy-1)*2+1)) FreeDirection[FreeDirectionNum++]=0;
        if(xx<MazeWidth-1  && MGLCD.GetPixel((xx+1)*2+1,(yy  )*2+1)) FreeDirection[FreeDirectionNum++]=1;
        if(yy<MazeHeight-1 && MGLCD.GetPixel((xx  )*2+1,(yy+1)*2+1)) FreeDirection[FreeDirectionNum++]=2;
        if(xx>0            && MGLCD.GetPixel((xx-1)*2+1,(yy  )*2+1)) FreeDirection[FreeDirectionNum++]=3;
        
        if(FreeDirectionNum) {
          direction=FreeDirection[random(FreeDirectionNum)];
          old_xx=xx; old_yy=yy;
          switch(direction) {
          case 0:
            yy--;
            break;
          case 1:
            xx++;
            break;
          case 2:
            yy++;
            break;
          case 3:
            xx--;
            break;
          } // switch
          MGLCD.Line(old_xx+xx+1,old_yy+yy+1,xx*2+1,yy*2+1,0);
          if(d) delay(d);
        } // if
      } while(FreeDirectionNum); 
    } // for y
  } // for x
} // maze

void setup() {
  // reset MGLCD
  while(MGLCD.Reset());

  // install user characters
  MGLCD.UserChars(UserChars,sizeof(UserChars)/5);
  
  // randomize
  randomSeed(analogRead(0));
} // setup

void loop() {
  MGLCD.ClearScreen();
  MGLCD.println("DEMO START");
  MGLCD.print("library:");
  MGLCD.println(MGLCD_VERSION/100.0,2);
  delay(4000);
  
  MGLCD.SetInvertMode(MGLCD_NON_INVERT);  
  MGLCD.SetScrollMode(MGLCD_NON_SCROLL);
  MGLCD.ClearScreen();
  MGLCD.println("Non invert mode");
  MGLCD.println("Non scroll mode"); 
  delay(2000); 
  for(int i=0x20; i<=0xdf; i++) {
    MGLCD.PutChar(i);
    delay(50);    
  } // for i

  delay(2000);
  MGLCD.SetInvertMode(MGLCD_NON_INVERT);  
  MGLCD.SetScrollMode(MGLCD_NON_SCROLL);
  MGLCD.ClearScreen();
  MGLCD.println("Non invert mode");
  MGLCD.println("Non scroll mode"); 
  for(int i=0x20; i<=0xdf; i++) {
    MGLCD.PutChar(i);
  } // for i
   
  delay(2000);
  MGLCD.SetInvertMode(MGLCD_INVERT);  
  MGLCD.SetScrollMode(MGLCD_SCROLL);
  MGLCD.ClearScreen();
  MGLCD.println("Invert mode");
  MGLCD.println("Scroll mode");  
  delay(2000); 
  for(int i=0x20; i<=0xdf; i++) {
    MGLCD.PutChar(i);
    delay(50);     
  } // for i
  
  delay(2000);
  MGLCD.SetInvertMode(MGLCD_INVERT);  
  MGLCD.SetScrollMode(MGLCD_SCROLL);
  MGLCD.ClearScreen();
  MGLCD.println("Invert mode");
  MGLCD.println("Scroll mode");  
  for(int i=0x20; i<=0xdf; i++) {
    MGLCD.PutChar(i);
  } // for i
  
  delay(2000);
  MGLCD.SetInvertMode(MGLCD_NON_INVERT);  
  MGLCD.SetScrollMode(MGLCD_SCROLL);
  MGLCD.ClearScreen();
  MGLCD.println("User-defined");
  MGLCD.println("characters");
  MGLCD.println("47\x80""F  33\x81  1,234\x82");
    
  delay(4000);
  MGLCD.SetCodeMode(MGLCD_CODE_UTF8);
  MGLCD.ClearScreen();
  MGLCD.println("Kana in UTF-8 code");
  MGLCD.println("MGLCD.print(\"ｶﾀｶﾅ\");");
  MGLCD.print("result:");
  MGLCD.print("ｶﾀｶﾅ");
  MGLCD.SetCodeMode(MGLCD_CODE_STRAIGHT);
  
  delay(10000);
  MGLCD.SetTextWindow(10,(MGLCD.GetLineNum()-4)/2,19,(MGLCD.GetLineNum()-4)/2+3);
  MGLCD.SetInvertMode(MGLCD_NON_INVERT); 
  MGLCD.ClearScreen();
  for(int i=0; i<MGLCD.GetWidth(); i++) {
    for(int j=0; j<MGLCD.GetHeight(); j++) {
      if((i+j)&1) MGLCD.SetPixel(i,j);
    } // for j
  } // for i
  MGLCD.println(MGLCD.GetPixel(0,0));
  MGLCD.println(MGLCD.GetPixel(0,1));  

  delay(1000);
  MGLCD.SetTextWindow(9,(MGLCD.GetLineNum()-4)/2,17,(MGLCD.GetLineNum()-4)/2+3);
  MGLCD.SetInvertMode(MGLCD_INVERT); 
  MGLCD.ClearScreen();
  for(int i=0; i<MGLCD.GetWidth(); i++) {
    for(int j=0; j<MGLCD.GetHeight(); j++) {
      if((i+j)&1) MGLCD.SetPixel(i,j);
    } // for j
  } // for i
  MGLCD.println(MGLCD.GetPixel(0,0));
  MGLCD.println(MGLCD.GetPixel(0,1));  

  delay(1000);
  MGLCD.ClearScreen();
  MGLCD.SetScrollMode(MGLCD_SCROLL);
  MGLCD.println(F("DEC"));
  for(int i=0; i<32; i++) {
    delay(300);
    MGLCD.println(i);
  } // for i;

  delay(1000);
  MGLCD.SetScrollMode(MGLCD_NON_SCROLL);
  MGLCD.println(F("HEX"));  
  for(int i=0; i<32; i++) {
    delay(300);
    MGLCD.println(i,HEX);
  } // for i;
  
  delay(1000);
  MGLCD.SetTextWindow(0,0,MGLCD.GetColumnNum()-1,MGLCD.GetLineNum()-1);
  MGLCD.ClearScreen();
  for(int i=0; i<MGLCD.GetLineNum(); i++) {
    unsigned char x,y;
    
    MGLCD.print(i);
    x=MGLCD.GetX();
    y=MGLCD.GetY();
    MGLCD.Locate(x+1,y+1);
  } // for i
  
  delay(1000);
  {
    int height;
    int width;
    int cnt;
    
    height=MGLCD.GetHeight()/5*5;
    width=height+3;
    cnt=MGLCD.GetWidth()/width;
 
    MGLCD.SetInvertMode(MGLCD_NON_INVERT); 
    MGLCD.ClearScreen();
    for(int i=0; i<height; i+=5) {  
      for(int j=0; j<cnt; j++) {
        MGLCD.Line(i       +j*width,0       ,height  +j*width,i       );
        MGLCD.Line(height  +j*width,i       ,height-i+j*width,height  );
        MGLCD.Line(height-i+j*width,height  ,0       +j*width,height-i);
        MGLCD.Line(0       +j*width,height-i,i       +j*width,0       );
      } // for j    
    } // for i
  }
  
  delay(1000);
  {
    int offset;
    int height;
    int bottom;
    
    offset=(MGLCD.GetWidth()-MGLCD.GetHeight())/2;
    height=MGLCD.GetHeight();
    bottom=height-1;
    
    MGLCD.SetInvertMode(MGLCD_NON_INVERT); 
    MGLCD.ClearScreen();
    for(int i=0; i<height/2; i++) {
      MGLCD.FillRect(offset+i,i,offset+bottom-i,bottom-i,(i+1)&1);
    } // for i
  }
  delay(1000);
  {
    int x0, y0;
    
    x0=MGLCD.GetWidth()/2;
    y0=MGLCD.GetHeight()/2;
        
    MGLCD.SetInvertMode(MGLCD_NON_INVERT);  
    MGLCD.SetScrollMode(MGLCD_NON_SCROLL);
    MGLCD.ClearScreen();
    for(int i=0; i<MGLCD.GetHeight()/2; i+=2) {
      MGLCD.Circle(x0,y0,i,1);
    } // for i  
  }  
  
  delay(1000);
  {
    int x0, y0;
    
    x0=MGLCD.GetWidth()/2;
    y0=MGLCD.GetHeight()/2;
    MGLCD.SetInvertMode(MGLCD_NON_INVERT);  
    MGLCD.SetScrollMode(MGLCD_NON_SCROLL);
    MGLCD.ClearScreen();
    for(int i=MGLCD.GetHeight()/2-1; i>=0; i-=2) {
      MGLCD.FillCircle(x0,y0,i,(i>>1)&1);
    } // for i  
  }
  delay(1000);
  MGLCD.SetInvertMode(MGLCD_NON_INVERT);  
  MGLCD.SetScrollMode(MGLCD_NON_SCROLL);
  MGLCD.ClearScreen();
  for(int i=0; i<=8; i+=2) {
    MGLCD.RoundRect(i,i,MGLCD.GetWidth()-1-i,MGLCD.GetHeight()-1-i,5);
  } // for i  

  delay(1000);
  maze(10);
  
  delay(2000);
  maze(0);
  
  delay(5000);
  MGLCD.SetInvertMode(MGLCD_NON_INVERT); 
  MGLCD.ClearScreen();
  for(int i=0; i<1000; i++) {
    int x1,y1,x2,y2;
    
    x1=random(MGLCD.GetWidth()); y1=random(MGLCD.GetHeight());
    x2=random(MGLCD.GetWidth()); y2=random(MGLCD.GetHeight());
    
    MGLCD.FillRect(x1,y1,x2,y2,i&1    );
    MGLCD.Rect    (x1,y1,x2,y2,1-(i&1));
  } // for i  
 
  delay(1000); 
  MGLCD.SetInvertMode(MGLCD_NON_INVERT); 
  MGLCD.ClearScreen();
  for(int i=0; i<1000; i++) {
    int r, x, y;
    
    r=random(MGLCD.GetHeight()/2);
    x=random(MGLCD.GetWidth() -2*r)+r;
    y=random(MGLCD.GetHeight()-2*r)+r;
    
    MGLCD.FillCircle(x,y,r,i&1    );
    MGLCD.Circle    (x,y,r,1-(i&1));
  } // for i  
  
  delay(1000);  
  {
    int rx,ry;
    const unsigned char BmpMem=MGLCD_ROM;
    
    rx=1+MGLCD.GetWidth ()-(BmpMem==MGLCD_ROM ? pgm_read_byte_near(BMP_kyoto+0) : BMP_kyoto[0]);
    ry=1+MGLCD.GetHeight()-(BmpMem==MGLCD_ROM ? pgm_read_byte_near(BMP_kyoto+1) : BMP_kyoto[1]);
    MGLCD.SetInvertMode(MGLCD_NON_INVERT);
    MGLCD.ClearScreen(); 
    for(int i=0; i<500; i++) {
      MGLCD.DrawBitmap(BMP_kyoto,random(rx),random(ry),BmpMem);
    } // for i
  }
  
  delay(1000);  
} // loop
