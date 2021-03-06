/*

  u8x8_d_st75256.c

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2017, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

  0x030	ext 00
  0x031	ext 01
  0x038	ext 10
  0x039	ext 11
  
  cad 011
  
*/


#include "u8x8.h"


/* not a real power down for the st75256... just a display off */
static const uint8_t u8x8_d_st75256_256x128_powersave0_seq[] = {
  U8X8_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8X8_C( 0x030 ),				/* select 00 commands */  
  U8X8_C( 0x94 ),				/* sleep out */
  U8X8_DLY(10),
  U8X8_C( 0xaf ),				/* display on */
  U8X8_END_TRANSFER(),             	/* disable chip */
  U8X8_END()             			/* end of sequence */
};

static const uint8_t u8x8_d_st75256_256x128_powersave1_seq[] = {
  U8X8_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0xae ),				/* display off */
  U8X8_C( 0x95 ),				/* sleep in */
  U8X8_END_TRANSFER(),             	/* disable chip */
  U8X8_END()             			/* end of sequence */
};




static uint8_t u8x8_d_st75256_256x128_generic(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t x, c;
  uint8_t *ptr;
  switch(msg)
  {
    /* handled by the calling function
    case U8X8_MSG_DISPLAY_SETUP_MEMORY:
      u8x8_d_helper_display_setup_memory(u8x8, &u8x8_st75256_256x128_display_info);
      break;
    */
    /* handled by the calling function
    case U8X8_MSG_DISPLAY_INIT:
      u8x8_d_helper_display_init(u8x8);
      u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_256x128_init_seq);    
      break;
    */
    case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
      if ( arg_int == 0 )
	u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_256x128_powersave0_seq);
      else
	u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_256x128_powersave1_seq);

      break;
#ifdef U8X8_WITH_SET_CONTRAST
    case U8X8_MSG_DISPLAY_SET_CONTRAST:

      u8x8_cad_StartTransfer(u8x8);
      
      u8x8_cad_SendCmd(u8x8, 0x030 );
      u8x8_cad_SendCmd(u8x8, 0x081 );  /* there are 9 bit for the volume control */
      u8x8_cad_SendArg(u8x8, (arg_int & 0x1f)<<1 );	/* lower 6 bit */
      u8x8_cad_SendArg(u8x8, (arg_int>>5));		/* upper 3 bit */
      
      u8x8_cad_EndTransfer(u8x8);
      break;
#endif
    case U8X8_MSG_DISPLAY_DRAW_TILE:
      
      u8x8_cad_StartTransfer(u8x8);
      x = ((u8x8_tile_t *)arg_ptr)->x_pos;    
      x *= 8;
      
      x += u8x8->x_offset;
	
      u8x8_cad_SendCmd(u8x8, 0x030 );	/* select command set */
      u8x8_cad_SendCmd(u8x8, 0x075 );	/* row */
      u8x8_cad_SendArg(u8x8, (((u8x8_tile_t *)arg_ptr)->y_pos));
      u8x8_cad_SendArg(u8x8, (((u8x8_tile_t *)arg_ptr)->y_pos));
      u8x8_cad_SendCmd(u8x8, 0x015 );	/* col */
      u8x8_cad_SendArg(u8x8, x);
      u8x8_cad_SendArg(u8x8, 255);
      u8x8_cad_SendCmd(u8x8, 0x05c );	
    
      
      do
      {
	c = ((u8x8_tile_t *)arg_ptr)->cnt;
	ptr = ((u8x8_tile_t *)arg_ptr)->tile_ptr;
	/* SendData can not handle more than 255 bytes, treat c > 31 correctly  */
	if ( c > 31 )
	{
	  u8x8_cad_SendData(u8x8, 248, ptr); 	
	  ptr+=248;
	  c -= 31;
	}
	u8x8_cad_SendData(u8x8, c*8, ptr); 	
	arg_int--;
      } while( arg_int > 0 );
      
      u8x8_cad_EndTransfer(u8x8);
      break;
    default:
      return 0;
  }
  return 1;
}

/*=============================================*/

static const u8x8_display_info_t u8x8_st75256_256x128_display_info =
{
  /* chip_enable_level = */ 0,
  /* chip_disable_level = */ 1,
  
  /* post_chip_enable_wait_ns = */ 20,
  /* pre_chip_disable_wait_ns = */ 20,
  /* reset_pulse_width_ms = */ 5, 	
  /* post_reset_wait_ms = */ 5, 		/**/
  /* sda_setup_time_ns = */ 20,		/* */
  /* sck_pulse_width_ns = */ 40,	/*  */
  /* sck_clock_hz = */ 4000000UL,	/* since Arduino 1.6.0, the SPI bus speed in Hz. Should be  1000000000/sck_pulse_width_ns */
  /* spi_mode = */ 0,		/* active high, rising edge */
  /* i2c_bus_clock_100kHz = */ 4,	/* 400KHz */
  /* data_setup_time_ns = */ 15,
  /* write_pulse_width_ns = */ 70,	
  /* tile_width = */ 32,
  /* tile_hight = */ 16,
  /* default_x_offset = */ 0,	/* must be 0, because this is checked also for normal mode */
  /* flipmode_x_offset = */ 0,		
  /* pixel_width = */ 256,
  /* pixel_height = */ 128
};


static const uint8_t u8x8_d_st75256_256x128_init_seq[] = {
  U8X8_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  
  U8X8_DLY(120),

  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0x06e ),				/* enable master */

  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_CA( 0x0d7, 0x09f ),		/* disable auto read */  
  U8X8_DLY(20),
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_CA( 0x0e0, 0x000 ),		/* enable OTP read */
  U8X8_DLY(20),
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_C( 0x0e3 ),				/* OTP Upload */
  U8X8_DLY(20),
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_C( 0x0e1 ),				/* OTP controll out */
  U8X8_DLY(20),
  
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0x094 ),				/* sleep out */
  U8X8_DLY(10),

  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0xae ),				/* display off */
  U8X8_DLY(10),
  
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_CA( 0x020, 0x00b ),		/* Power control: Regulator, follower & booster on */
  U8X8_DLY(10),
 
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_CAA( 0x81, 0x36, 0x05 ),	/* Volume control */
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_C( 0x020 ),				/* gray levels */
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x17 ),
  U8X8_A( 0x17),
  U8X8_A( 0x17 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x1d ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x1d ),
  U8X8_A( 0x1d ),
  U8X8_A( 0x1d ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_C( 0x032 ),				/* analog circuit set */
  U8X8_A( 0x000 ),				/* code example: OSC Frequency adjustment */
  U8X8_A( 0x001 ),				/* Frequency on booster capacitors 1 = 6KHz? */
  U8X8_A( 0x000 ),				/* Bias: 1: 1/13, 2: 1/12, 3: 1/11, 4:1/10, 5:1/9 */
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_CA( 0x051, 0x0fb ),		/* booster level x10 */

  U8X8_C( 0x030 ),				/* select 00 commands */ 
  U8X8_CA( 0x0f0, 0x011 ),		/* monochrome mode  = 0x010*/

  U8X8_C( 0x030 ),				/* select 00 commands */ 
  U8X8_C( 0xca ),				/* display control, 3 args follow  */
  U8X8_A( 0x00 ),				/* no clock division */
  U8X8_A( 0x7f ),				/* 1/128 duty value from the DS overview page*/
  //U8X8_A( 0x9f ),				/* 1/160 duty value from the DS example code */
  U8X8_A( 0x00 ),				/* nline off */ 

  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_CA( 0xbc, 0x00 ),			/* data scan dir */

  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_C( 0x040 ),				/* internal power */

  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0xa6 ),				/* normal display  */
  U8X8_C( 0x22 ),				/* all pixel off mode  */
  U8X8_C( 0xaf ),				/* display on  */

  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_CAA(0x75, 0, 16),		/* row range */
  U8X8_CAA(0x15, 0, 255),		/* col range */
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0x5c ),				/* write data to RAM  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */

  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
 
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */
  U8X8_A( 0xaa ),				/*  */

  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */
  U8X8_A( 0x55 ),				/*  */

  U8X8_END_TRANSFER(),             	/* disable chip */
  U8X8_END()             			/* end of sequence */
};    

static const uint8_t u8x8_d_st75256_240x160_init_seq_c[] = {
		U8X8_END_TRANSFER(),	/* disable chip */
//		U8G_ESC_RST(1),			/* hardware reset. Min 1 ms */
		U8X8_DLY(1),			/* Delay max 1 ms */
		U8X8_START_TRANSFER(),	/* enable chip, delay is part of the transfer start */

		U8X8_C(0x030),	// EXT=0

		U8X8_C(0x094),	// Sleep Out

		U8X8_C(0x031),	// EXT=1

//		U8X8_CA(0x0D7,0x09F), // Autoread disable

		U8X8_C(0x032),	// Analog set
		U8X8_A(0x000),	/* OSC Frequency adjustment */
		U8X8_A(0x001),	/* Booster Efficiency =Level 1 */
		U8X8_A(0x003),	/* Bias = 1/11 */

		U8X8_CA(0x051,0x0FB), /* Booster Level x10 */
		
//		U8X8_C(0x020),	// Gray levels tune for 4-gray mode
//		U8X8_A(0x001),	//
//		U8X8_A(0x002),	//
//		U8X8_A(0x005),	//
//		U8X8_A(0x007),	//
//		U8X8_A(0x009),	//
//		U8X8_A(0x00b),	//
//		U8X8_A(0x00d),	//
//		U8X8_A(0x010),	//
//		U8X8_A(0x011),	//
//		U8X8_A(0x013),	//
//		U8X8_A(0x015),	//
//		U8X8_A(0x017),	//
//		U8X8_A(0x019),	//
//		U8X8_A(0x01B),	//
//		U8X8_A(0x01D),	//
//		U8X8_A(0x01F),	//

		U8X8_C(0x030),	// EXT1 = 0, EXT0 = 0 "?????????????????????? ????????????????????"
		U8X8_C(0x075),	// ???????????????????? ?????????? ????????????????
		U8X8_A(0x001),	// Start page
		U8X8_A(0x015),	// End page

		U8X8_C(0x015),	// ???????????????????? ?????????? ??????????????
		U8X8_A(0x000),	// ?????????????????? ?????????? ??????????????: XS = 0
		U8X8_A(0x0EF),	// ?????????? ???????????????????? ??????????????: XE = 240 (0xF0)

		U8X8_C(0x0BC),	// ?????????????????????? ????????????????????????
		U8X8_A(0x001),	// MX.MY=Normal
		U8X8_A(0x0A6),	//

		U8X8_C(0x008),	// ?????????? ?????????????? ????????????, 0x0C ?????????????? - ?????????????? D0-D7, 0x08 ?????????????? - ?????????????? D7-D0

		U8X8_C(0x0CA),	// ?????????????????? ??????????????????????
		U8X8_A(0x000),	// ???????????????????? ?????????????? ?????????????? CL: CLD = 0
		U8X8_A(0x09F),	// ?????????????? ????????: Duty=160
		U8X8_A(0x020),	// N ?????????? ???? ???????????? ????????????????????????: Nline=off

		U8X8_C(0x0F0),	// ?????????? ??????????????????????
		U8X8_A(0x010),	// 0x11: 4-lever.  0x10: 2-level

		U8X8_C(0x081),	// ???????????????????? ????????????????, "0x81" ????????????????, ?? ?????????? ???????? ???????????? ?????????? ???????? ??????????????, ???? "?????????? ?????????????? ?????????????????? ????????????" ???????? ?????????????? ????????????????????
		U8X8_A(0x03F),	// ???????????? ????????????????, ???????????????????????? ???????????????? 0x00 ~ 0x3f ?? ?????????? ?????????????????? 64
		U8X8_A(0x003),	// ???????????? ????????????????, ???????????????????????? ???????????????? 0x00 0x07 ~, ?? ?????????? ?????????????????? ????????????

		U8X8_C(0x020),	// ???????????????????? ????????????????
		U8X8_A(0x00B),	// D0=regulator ; D1=follower ; D3=booste, on:1 off:0

		U8X8_DLY(1),	// Delay 0,1 ms

		U8X8_C(0x0AF),	// ?????????????? ????????????????

		U8X8_END_TRANSFER(),	/* disable chip */
		U8X8_END()	/* end of sequence */
};


static const uint8_t u8x8_d_st75256_256x128_init_seq_x[] = {
    
  U8X8_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */

  U8X8_C( 0x030 ),				/* select 00 commands */

  U8X8_C( 0x094 ),				/* sleep out */
  U8X8_DLY(10),
  //U8X8_C( 0xae ),				/* display off */

  
  U8X8_C( 0x031 ),				/* select 01 commands */
  
  U8X8_C( 0x0d7 ),				/* OTP Auto Read */
  U8X8_A( 0x09f ),				/* ... disable */
  U8X8_C( 0x032 ),				/* analog circuit set */
  U8X8_A( 0x000 ),				/* code example: OSC Frequency adjustment */
  U8X8_A( 0x001 ),				/* Frequency on booster capacitors 1 = 6KHz? */
  U8X8_A( 0x000 ),				/* Bias: 1: 1/13, 2: 1/12, 3: 1/11, 4:1/10, 5:1/9 */
  U8X8_CA( 0x051, 0x0fb ),		/* booster level x10 */

  U8X8_C( 0x020 ),				/* gray levels */
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x1f ),
  U8X8_A( 0x00 ),
  U8X8_A( 0x00 ),
/*
  U8X8_A( 0x01 ),
  U8X8_A( 0x03 ),
  U8X8_A( 0x05 ),
  U8X8_A( 0x07 ),
  U8X8_A( 0x09 ),
  U8X8_A( 0x0b ),
  U8X8_A( 0x0d ),
  U8X8_A( 0x10 ),
  U8X8_A( 0x11 ),
  U8X8_A( 0x13 ),
  U8X8_A( 0x15 ),
  U8X8_A( 0x17 ),
  U8X8_A( 0x19 ),
  U8X8_A( 0x1b ),
  U8X8_A( 0x1d ),
  U8X8_A( 0x1f ),
*/
  U8X8_C( 0x030 ),				/* select 00 commands */
 
  U8X8_C( 0xca ),				/* display control, 3 args follow  */
  U8X8_A( 0x00 ),				/* no clock division */
  U8X8_A( 0x7f ),				/* 1/128 duty value from the DS overview page*/
  //U8X8_A( 0x9f ),				/* 1/160 duty value from the DS example code */
  U8X8_A( 0x00 ),				/* nline off */  
  U8X8_CA( 0x0f0, 0x011 ),		/* monochrome mode */
  //U8X8_C( 0x76 ),				/* ICON  */

  //U8X8_C( 0xd1 ),				/* OSC on  */

  U8X8_CAA( 0x81, 0x36, 0x05 ),	/* Volume control */
  U8X8_CA( 0x020, 0x00b ),		/* Power control: Regulator, follower & booster on */
  U8X8_DLY(10),
  U8X8_CA( 0xbc, 0x00 ),			/* data scan dir */
  
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0xa6 ),				/* normal display  */
  U8X8_C( 0x22 ),				/* all pixel off mode  */
  
  U8X8_C( 0x031 ),				/* select 01 commands */
  U8X8_C( 0x040 ),				/* internal power */
  
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0xaf ),				/* display on  */
  
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0x077 ),				/* enable ICON */
  U8X8_CAA( 0x015,0,255 ),		/* col */
  U8X8_C( 0x5c ),				/* write data to RAM  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_C( 0x076 ),				/* disable ICON */
  


  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_CAA(0x75, 1, 2),		/* row range */
  U8X8_CAA(0x15, 0, 50),		/* col range */
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_C( 0x5c ),				/* write data to RAM  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xfc ),				/*  */
  U8X8_A( 0xf0 ),				/*  */
  U8X8_A( 0xc0 ),				/*  */
  U8X8_A( 0xf0 ),				/*  */
  U8X8_A( 0xfc ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xfc ),				/*  */
  U8X8_A( 0xf0 ),				/*  */
  U8X8_A( 0xc0 ),				/*  */
  U8X8_A( 0xf0 ),				/*  */
  U8X8_A( 0xfc ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  U8X8_A( 0xff ),				/*  */
  
    
  U8X8_END_TRANSFER(),             	/* disable chip */
  U8X8_END()             			/* end of sequence */
};


static const uint8_t u8x8_d_st75256_jlx12864_flip0_seq[] = {
  U8X8_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_END_TRANSFER(),             	/* disable chip */
  U8X8_END()             			/* end of sequence */
};

static const uint8_t u8x8_d_st75256_jlx12864_flip1_seq[] = {
  U8X8_START_TRANSFER(),             	/* enable chip, delay is part of the transfer start */
  U8X8_C( 0x030 ),				/* select 00 commands */
  U8X8_END_TRANSFER(),             	/* disable chip */
  U8X8_END()             			/* end of sequence */
};


uint8_t u8x8_d_st75256_jlx256128(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  if ( u8x8_d_st75256_256x128_generic(u8x8, msg, arg_int, arg_ptr) != 0 )
    return 1;
  if ( msg == U8X8_MSG_DISPLAY_SETUP_MEMORY )
  {
    u8x8_SetI2CAddress(u8x8, 0x078);		/* lowest I2C adr of the ST75256 */
    u8x8_d_helper_display_setup_memory(u8x8, &u8x8_st75256_256x128_display_info);
    return 1;
  }
  else if ( msg == U8X8_MSG_DISPLAY_INIT )
  {
    u8x8_d_helper_display_init(u8x8);
    u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_256x128_init_seq);    
    //u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_240x160_init_seq_c);    
    
    for(;;)
      ;
    return 1;
  }
  else if  ( msg == U8X8_MSG_DISPLAY_SET_FLIP_MODE )
  {
    if ( arg_int == 0 )
    {
      u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_jlx12864_flip0_seq);
      u8x8->x_offset = u8x8->display_info->default_x_offset;
    }
    else
    {
      u8x8_cad_SendSequence(u8x8, u8x8_d_st75256_jlx12864_flip1_seq);
      u8x8->x_offset = u8x8->display_info->flipmode_x_offset;
    }
    return 1;
  }
  return 0;
}


