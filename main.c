#include "ARM_DIO.h"
#include "Delay.h"
#include "Systick.h"
#include "LCD.h"
#include "Keypad.h"
#include "Button.h"
#include "LED.h"

#define MINUTES (*(time+1))
#define SECONDS (*time)
#define START_BUTTON 	Button_u8Read('F',0)
#define PAUSE_BUTTON	Button_u8Read('F',4)
#define DOOR_BUTTON 	Button_u8Read('A',2)

enum {IDLE,COOKING,PAUSED,ENTERWEIGHT, ENTERTIME} State;

volatile unsigned int totalSeconds=0;
volatile unsigned int counter = 0;
volatile unsigned char time[2];

void ConvertToSecond();
void DisplayTime();
void UpdateTime();

int main(void)
{
	
}

void DisplayTime()
{
	LCD_MoveCursor(2,1);
	LCD_vSend_Char(MINUTES/10 + '0');
	LCD_vSend_Char(MINUTES%10 + '0');
	LCD_vSend_Char(':');
	LCD_vSend_Char(SECONDS/10 + '0');
	LCD_vSend_Char(SECONDS%10 + '0');
}

void ConvertToSecond()
{
	totalSeconds = MINUTES*60 + SECONDS;
}

void UpdateTime()
{
	MINUTES = totalSeconds/60;
	SECONDS = totalSeconds - (MINUTES*60);
}

void SysTick_Handler(void)
{
	counter++;
	if(counter == 100)
	{
		counter = 0;
		if (State == COOKING)
		{
			totalSeconds--;
		}
	}
}