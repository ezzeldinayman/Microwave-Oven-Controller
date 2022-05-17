#include "Delay.h"
#include "Systick.h"
#include "LCD.h"
#include "Keypad.h"
#include "Button.h"
#include "LED.h"
#include "Buzzer.h"


#define MINUTES (*(time+1))
#define SECONDS (*time)
#define START_BUTTON 	Button_u8Read('F',0)
#define PAUSE_BUTTON	Button_u8Read('F',4)
#define DOOR_BUTTON 	Button_u8Read('A',2)

enum {IDLE,COOKING,PAUSED,ENTERWEIGHT, ENTERTIME, FINISHED} State;

volatile unsigned int totalSeconds=0;
volatile unsigned int counter = 0;
volatile unsigned char time[2];

void ConvertToSecond();
char ReadMode();
void DisplayTime();
void UpdateTime();
char CheckDoor();
void EnterTime();
void CalculateTime(char Mode, char kilos);
char EnterWeight(char Mode);

int main(void)
{
	LCD_vInit();
	Keypad_vInit();
	Systick_vInitInterrupt();
	Button_vInitPullUp('F',0);
	Button_vInitPullUp('F',4);
	Button_vInitPullDown('A',2);
	LED_vInit('F',1);
	LED_vInit('F',2);
	LED_vInit('F',3);
	Buzzer_vInit('E',3);

	char Mode;
	char* ModeText;
	char kilos=0;

	while(1)
	{
		//TODO

		switch(State)
		{

			case IDLE:
			{
				reset:
				LCD_ClearScreen();
				LCD_vSend_String("Enter Mode: ");
				LED_OFF('F',2);
				LED_OFF('F',3);
				LED_ON('F',1);
				
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

			case ENTERTIME:
			{
				resetEnterTime:
				EnterTime();
				ModeText = "Cooking :)";
				do
				{
					DisplayTime();
					if(PAUSE_BUTTON==0) goto reset;
				} while (START_BUTTON==1);
				State = COOKING;
			}
			break;

			case COOKING:
			{
				LCD_ClearRow(1);
				LCD_vSend_String(ModeText);
				LED_ON('F',1);
				LED_ON('F',2);
				LED_ON('F',3);
				char doorFlag = 0;
				ConvertToSecond();
				while(totalSeconds>=0)
				{
					UpdateTime();
					DisplayTime();
					doorFlag = CheckDoor();
					if(doorFlag == 1)
					{
						LCD_ClearRow(1);
						LCD_vSend_String("PAUSED");
						State = PAUSED;
						break;
					}
					if(PAUSE_BUTTON==0)
					{
						State = PAUSED;
						_delay_ms(250);
						LCD_ClearRow(1);
						LCD_vSend_String("PAUSED");
						break;
					}
				}
				if(State!=PAUSED) State = IDLE;
			}
			break;

			case PAUSED:
			{

				DisplayTime();
				LED_TOG('F',1);
				LED_TOG('F',2);
				LED_TOG('F',3);
				_delay_ms(200);
				if(START_BUTTON == 0) State = COOKING;
				else if(PAUSE_BUTTON == 0) State = IDLE;
				else State=PAUSED;

			}
			break;
			
			case FINISHED:
			{
				LED_OFF('F',3);
				LED_ON('F',2);
				LCD_ClearScreen();
				LCD_vSend_String("Done :) ");
				Buzzer_On('E',2);
				_delay_ms(2000);
				Buzzer_Off('E',2);
				LCD_ClearScreen();
				State = IDLE;
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


void EnterTime()
{
	EnterTimeAgain:
	LCD_ClearScreen();
	LCD_vSend_String("Cooking Time? ");
	LCD_MoveCursor(2,1);
	char inputTime[4] = {0,0,0,0};
	char Start = 0;
	SECONDS = 0;
	MINUTES = 0;
	DisplayTime();
	char i;
	char x;
	for(i=0;i<4;i++)
	{
		do
		{
			x = Keypad_u8Read();
			Start = START_BUTTON;
			if((x<'0' || x>'9') && x!= 0xFF)
			{
				LCD_ClearScreen();
				LCD_vSend_String("Invalid");
				_delay_ms(1000);
				LCD_ClearScreen();
				LCD_vSend_String("Cooking Time? ");
				LCD_MoveCursor(2,1);
				continue;
			}
			else if(PAUSE_BUTTON == 0) break;
			else if(x != 0xFF)
			{
				(*(inputTime+i)) = x-'0';
				switch(i)
				{
					case 0:
					{
						SECONDS = (*inputTime);
						break;
					}
					case 1:
					{
						SECONDS = (*inputTime)*10 + (*(inputTime+1));
						break;
					}

					case 2:
					{
						MINUTES = (*inputTime);
						SECONDS = (*(inputTime+1))*10 + (*(inputTime+2));
						break;

					}

					case 3:
					{
						MINUTES = (*(inputTime+1)) + (*inputTime)*10;
						SECONDS = (*(inputTime+2))*10 + (*(inputTime+3));
						break;
					}
				}
			}
			if(Start == 0) break;
		} while (x==0xFF);
		if (Start == 0) break;
		if(PAUSE_BUTTON==0)break;
		DisplayTime();
		_delay_ms(300);
	}

	if(SECONDS>60 || MINUTES>30 || (SECONDS>0 && MINUTES==30))
	{
		LCD_ClearScreen();
		LCD_vSend_String("Invalid");
		_delay_ms(1000);
		goto EnterTimeAgain;
	}
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
	if(DOOR_BUTTON==0)
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
//Interrupt Service Routine -----> Function
