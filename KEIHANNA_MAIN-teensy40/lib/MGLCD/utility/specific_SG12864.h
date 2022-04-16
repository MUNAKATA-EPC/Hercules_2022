/* 
  specific_SG12864.h
  
  This file is part of Monochrome Graphic LCD library (MGLCD) for Arduino.
  
  MGLCD was developed by Synapse(Hiroshi Tanigawa) from 2012 to 2016.  This Library is
  originally distributed at Team Schaft's Homepage. 
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

#ifndef SPECIFIC_SG12864_H
#define SPECIFIC_SG12864_H

#include <arduino.h>
#include <MGLCD.h>

#ifdef ARDUINO_ARCH_AVR

#if MGLCD_VERSION != 41
#error versions of this file and header file are different.
#endif

class specific_SG12864
{
public : 
  static const uint8_t Width = 128; // Screen Width
  static const uint8_t Height = 64; // Screen Height
  static const uint8_t HalfWidth = Width/2; // Half of screen width
  static const uint8_t PageNum = Height/8; // Number of character lines
  static const uint8_t ColumnNum = Width/MGLCD_FONT_WIDTH; // Number of character columns
  static const uint8_t DisplayOnCommand     = 0x3f;
  static const uint8_t DisplayOffCommand    = 0x3e;
  static const uint8_t DisplayLineCommand   = 0xc0;
  static const uint8_t PageAddressCommand   = 0xb8;
  static const uint8_t ColumnAddressCommand = 0x40;
  static const boolean EPinUsed = true;
  
  static uint8_t (*const GeneralReadData )(uint8_t ctrl, const TPinSet &PinSet);
  static uint8_t (*const StandardReadData)(uint8_t ctrl, const TPinSet &PinSet);
  static void (*const GeneralWriteData )(uint8_t ctrl, uint8_t data, const TPinSet &PinSet);
  static void (*const StandardWriteData)(uint8_t ctrl, uint8_t data, const TPinSet &PinSet);

  TPinSet PinSet;
  uint8_t (*ReadData)(uint8_t ctrl, const TPinSet &PinSet);
  void (*WriteData)(uint8_t ctrl, uint8_t data, const TPinSet &PinSet);

  void Reset(void);
}; // specific_SG12864

typedef MGLCD_direct<specific_SG12864> MGLCD_SG12864;
typedef MGLCD_SG12864 mglcd_SG12864;

#endif // #ifdef ARDUINO_ARCH_AVR
#endif // #ifndef SPECIFIC_SG12864_H
