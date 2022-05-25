#include "ARM_DIO.h"
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

void ConvertToSecond(void);
unsigned char ReadMode(void);
void DisplayTime(void);
void UpdateTime(void);
char CheckDoor(void);
void EnterTime(void);
void CalculateTime(char Mode, char kilos);
char EnterWeight(char Mode);

int main(void)
{
	unsigned char Mode;
	char* ModeText;
	unsigned char kilos=0;
	LCD_vInit();
	Keypad_vInit();



	Systick_vInitInterrupt();
	Button_vInitPullUp('F',0);
	Button_vInitPullUp('F',4);
	Button_vInitPullUp('A',2);
	LED_vInit('F',1);
	LED_vInit('F',2);
	LED_vInit('F',3);
	Buzzer_vInit('A',3);


	while(1)
	{
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

			case COOKING:
			{
				char doorFlag = 0;
				LCD_ClearRow(1);
				LCD_vSend_String(ModeText);
				LED_ON('F',1);
				LED_ON('F',2);
				LED_ON('F',3);
				
				ConvertToSecond();
				while(totalSeconds>0) ///////////////////////////////////////////////
				{
					UpdateTime();
					DisplayTime();
					doorFlag = CheckDoor();
					if(totalSeconds==0)
					{
							State = FINISHED;
							break;
					}
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
				
				if(State!=PAUSED && State != FINISHED) State = IDLE;
			}
			break;

			case ENTERWEIGHT:
			{
				Repeat:
				LCD_ClearScreen();
				kilos = EnterWeight(Mode);
				if(State == IDLE) break;
				else if(kilos>9 || kilos<1)
				{
					LCD_ClearScreen();
					LCD_vSend_String("Err");
					_delay_ms(2000);
					goto Repeat;
				}
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
				break;
			}

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
				char z;
				LCD_ClearScreen();
				LCD_vSend_String("Done :) ");
				for(z=0;z<3;z++)
				{
					Buzzer_Off('A',3);
					LED_OFF('F',1);
					LED_OFF('F',2);
					LED_OFF('F',3);
					_delay_ms(1000);

					Buzzer_On('A',3);
					LED_ON('F',1);
					LED_ON('F',2);
					LED_ON('F',3);
					_delay_ms(1000);
				}
				Buzzer_Off('A',3);
				LCD_ClearScreen();
				State = IDLE;
			}
			break;
		}
	}

}



char EnterWeight(char Mode)
{
	unsigned char kilos;
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

void EnterTime(void)
{
	char i;
	char x;
	char inputTime[4] = {0,0,0,0};
	char Start;
	EnterTimeAgain:
	LCD_ClearScreen();
	LCD_vSend_String("Cooking Time? ");
	LCD_MoveCursor(2,1);
	inputTime[0] = 0;
	inputTime[1] = 0;
	inputTime[2] = 0;
	inputTime[3] = 0;

	Start = 0;
	SECONDS = 0;
	MINUTES = 0;
	DisplayTime();

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

char CheckDoor(void)
{
	if(DOOR_BUTTON==1)
	{
		return 1;
	}
	return 0;
}

unsigned char ReadMode(void)
{
	unsigned char x = 0xFF;
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
