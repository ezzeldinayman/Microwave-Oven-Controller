#include "standard_macros.h"
#include "ARM_DIO.h"
#include "Delay.h"
#include "LCD_CONFIG.h"
#include "LCD.h"

void LCD_vInit(void)
{
	DIO_vInitPort(LCD_PORT);
	DIO_vInitPort(CTRL_PORT);
	DIO_vSetPinDir(LCD_PORT,D4,1);
	DIO_vSetPinDir(LCD_PORT,D5,1);
	DIO_vSetPinDir(LCD_PORT,D6,1);
	DIO_vSetPinDir(LCD_PORT,D7,1);
	DIO_vSetPinDir(CTRL_PORT,E,1);
	DIO_vSetPinDir(CTRL_PORT,RS,1);
	_delay_ms(20);
	LCD_vSend_CMD(0x33);
	LCD_vSend_CMD(0x32);
	LCD_vSend_CMD(FOUR_BITS);
	_delay_ms(1);
	LCD_vSend_CMD(CURSOR_OFF_DISPLAY_ON);
	_delay_ms(1);
	LCD_vSend_CMD(ENTRY_MODE);
	_delay_ms(1);
	LCD_vSend_CMD(CLR_SCREEN);
	_delay_ms(10);

}

static void SendPulse(void)
{
	DIO_vWritePin(CTRL_PORT,E,1);
	_delay_ms(2);
	DIO_vWritePin(CTRL_PORT,E,0);
	_delay_ms(2);
}

void LCD_vSend_CMD(char cmd)
{
	DIO_vWriteHighNibble(LCD_PORT,(cmd>>4));
	DIO_vWritePin(CTRL_PORT,RS,0);
	SendPulse();
	DIO_vWriteHighNibble(LCD_PORT,cmd);
	DIO_vWritePin(CTRL_PORT,RS,0);
	SendPulse();
	_delay_ms(1);
}


void LCD_vSend_Char(char character)
{
	DIO_vWriteHighNibble(LCD_PORT,(character>>4));
	DIO_vWritePin(CTRL_PORT,RS,1);
	SendPulse();
	DIO_vWriteHighNibble(LCD_PORT,character);
	DIO_vWritePin(CTRL_PORT,RS,1);
	SendPulse();
}

void LCD_vSend_String(char data[16])
{
	while((*data)!='\0')
	{
		LCD_vSend_Char(*data);
		data++;
	}
}


void LCD_MoveCursor(char row, char column)
{
	char pos=0;
	if(row==1)
	{
		pos=(0x80)+column-1;
	}
	else if(row==2)
	{
		pos=(0xC0)+column-1;
	}
	else
	{
		pos=0x80;
	}
	LCD_vSend_CMD(pos);
	_delay_ms(1);

}

void LCD_ClearScreen(void)
{
	LCD_vSend_CMD(CLR_SCREEN);
	_delay_ms(10);
}

void LCD_ClearRow(char row)
 {
	 LCD_MoveCursor(row,1);
	 LCD_vSend_String("               ");
	 LCD_MoveCursor(row,1);
 }

