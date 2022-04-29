#include "ARM_DIO.h"


void Keypad_vInit(unsigned char KPORT)
{
		DIO_vSetPortDir(KPORT,0x0F); //P4 to P7 are input & P0 to P3 are output
		DIO_vEnablePullUp(KPORT,7);
		DIO_vEnablePullUp(KPORT,6);
		DIO_vEnablePullUp(KPORT,5);
		DIO_vEnablePullUp(KPORT,4);
}


unsigned char Keypad_u8Read(unsigned char KPORT)
{
		unsigned char ascii[4][4] = {
																{'7','8','9','/'},
																{'4','5','6','x'},
																{'1','2','3','-'},
																{'A','0','=','+'}
																};
		char row,col,x;
		char return_value = 0xFF;
		for(row=0;row<=3;row++)
		{
			DIO_vWriteLowNibble(KPORT,0xFF);
			DIO_vWritePin(KPORT,row,0);
			for(col=0;col<=3;col++)
			{
					x = DIO_u8ReadPin(KPORT,col+4);
					if(x==0)
					{
							return_value=ascii[row][col];
							break;
					}
					if(x==0) break;
			}
			return return_value;	
		}
		
}
