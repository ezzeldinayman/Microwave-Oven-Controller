#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

//Here are some macros to assist in configuration of LCD.
#define LCD_PORT	 						'A'
#define D4										4
#define D5										5
#define D6										6
#define D7										7
#define CTRL_PORT 						'D'
#define E											0
#define RS										1
#define CLR_SCREEN 						0x01
#define CURSOR_ON_DISPLAY_ON 	0x0e
#define CURSOR_OFF_DISPLAY_ON	0x0C
#define RETURN_HOME 					0x02
#define ENTRY_MODE 						0x06
#define FOUR_BITS							0x28

#endif
