#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

//Here are some macros to assist in configuration of LCD.
#define LCD_PORT	 						'D'
#define D4										0
#define D5										1
#define D6										2
#define D7										3
#define CTRL_PORT 						'E'
#define E											1
#define RW										2
#define RS										3
#define CLR_SCREEN 						0x01
#define CURSOR_ON_DISPLAY_ON 	0x0e
#define RETURN_HOME 					0x02
#define ENTRY_MODE 						0x06
#define FOUR_BITS							0x28

#endif