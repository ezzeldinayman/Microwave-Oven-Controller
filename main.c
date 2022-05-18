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
char EnterWeight(char Mode);

int main(void)
{
	LCD_vInit();
	Keypad_vInit();
	Systick_vInitInterrupt();
	Button_vInitPullUp('F',0);
	Button_vInitPullUp('F',4);
	Button_vInitPullUp('A',2);
	LED_vInit('F',1);
	LED_vInit('F',2);
	LED_vInit('F',3);
	
	char Mode;
	char* ModeText;
	char kilos=0;

	while(1)
	{
		switch(State)
		{
			case IDLE:
			{
				reset:
				LCD_ClearScreen();
				LCD_vSend_String("Enter Mode: ");
				Mode = ReadMode();
				LCD_vSend_Char(Mode);
				_delay_ms(500);
				
				ModeProcess:
				
				switch(Mode)
				{
					case 'A':
					{
						MINUTES = 1;
						SECONDS = 0;
						labelA:
						LCD_ClearScreen();
						ModeText = "Popcorn";
						
						DisplayTime();
						LCD_ClearScreen();
						LCD_vSend_String(ModeText);
						
						do
						{
							DisplayTime();
							if(PAUSE_BUTTON==0) goto reset;
						} while (START_BUTTON==1);
						
					}
					break;
					
					case 'B':
					case 'C':
					{
						State = ENTERWEIGHT;
					}
					break;
					
					case 'D':
					{
						State = ENTERTIME;
					}
					break;
					
					default:
					{
						LCD_ClearScreen();
						LCD_vSend_String("Invalid Mode");
						_delay_ms(500);
						
						goto reset;
					}
				}
				
				
				if(CheckDoor()==0 && State == IDLE) State = COOKING;
				else if(CheckDoor()==1 && State == IDLE)
				{
					LCD_MoveCursor(1,1);
					LCD_vSend_String("Close The Door");
					_delay_ms(1000);
					if(Mode == 'A') goto labelA;
				}
			}
			break;

			case COOKING:
			{
				LCD_ClearRow(1);
				LCD_vSend_String(ModeText);
				char doorFlag = 1;
				ConvertToSecond();
				while (totalSeconds >= 0)
				{
					UpdateTime();
					DisplayTime();
					doorFlag = CheckDoor();
					if (doorFlag == 1)
					{
						LCD_ClearRow(1);
						LCD_vSend_String("PAUSED");
						State = PAUSED;
						break;
					}
					if (PAUSE_BUTTON == 0)
					{
						State = PAUSED;
						_delay_ms(250);
						LCD_ClearRow(1);
						LCD_vSend_String("PAUSED");
						break;
					}
				}
				if (State != PAUSED) State = IDLE;
			}
			break;
			
			case ENTERWEIGHT:
			{
				Repeat:
				LCD_ClearScreen();
				kilos = EnterWeight(Mode);
				if(kilos>9 || kilos<1)
				{
					LCD_ClearScreen();
					LCD_vSend_String("Err");
					_delay_ms(2000);
					goto Repeat;
				}
				else if(State == IDLE) break;
				else
				{
					_delay_ms(2000);
					CalculateTime(Mode,kilos);
					if(Mode == 'B') ModeText = "Beef";
					else ModeText = "Chicken";
					UpdateTime();
					DisplayTime();
					LCD_ClearScreen();
					LCD_vSend_String(ModeText);
					
					do
					{
						DisplayTime();
						if(PAUSE_BUTTON==0) goto reset;
					} while (START_BUTTON==1);
					State = COOKING;
				}			
			}
			break;
			
			case PAUSED:
			{
				
				DisplayTime();
				if(START_BUTTON == 0) State = COOKING;
				else if(PAUSE_BUTTON == 0) State = IDLE;
				else State=PAUSED;
				
			}
			break;
		}
	}
	
}



char EnterWeight(char Mode)
{
	char kilos;
	if(Mode == 'B')
	{
		LCD_ClearScreen();
		LCD_vSend_String("Beef Weight?");
		LCD_MoveCursor(2,1);
	}
	else
	{
		LCD_ClearScreen();
		LCD_vSend_String("Chicken Weight?");
		LCD_MoveCursor(2,1);
	}

	do
	{
		kilos = Keypad_u8Read();
		if(PAUSE_BUTTON == 0)
		{
			State = IDLE;
			break;
		}
	} while (kilos == 0xFF);

	LCD_vSend_Char(kilos);
	return (kilos-'0');
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


void CalculateTime(char Mode, char kilos)
{
	if(Mode == 'B')
	{
		totalSeconds = kilos*30;
	}
	else if(Mode == 'C')
	{
		totalSeconds = kilos*12;
	}
}

char CheckDoor()
{
	if(DOOR_BUTTON==1)
	{
		return 1;
	}
	return 0;
}

char ReadMode()
{
	char x;
	do 
	{
		x = Keypad_u8Read();
	} while (x == 0xFF);
	
	return x;
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
