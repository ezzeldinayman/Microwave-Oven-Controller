#include "ARM_DIO.h"
#define KPORT1 'B'
#define KPORT2 'E'
#include "Keypad.h"

void Keypad_vInit()
{
        DIO_vInitPort(KPORT1);
        DIO_vInitPort(KPORT2);
        DIO_vSetPortDir(KPORT1,0x0F);  //PB0 --> PB3 : ROWS (OUTPUT)
        DIO_vSetPinDir(KPORT2,1,0);
		DIO_vSetPinDir(KPORT2,2,0);
		DIO_vSetPinDir(KPORT2,3,0);
		DIO_vSetPinDir(KPORT2,4,0);
        DIO_vEnablePullUp(KPORT2,1);
        DIO_vEnablePullUp(KPORT2,2);
        DIO_vEnablePullUp(KPORT2,3);
        DIO_vEnablePullUp(KPORT2,4);
        DIO_vWritePort(KPORT1,0x0F);
}


unsigned char Keypad_u8Read()
{
        unsigned char ascii[4][4] = {
                                                                {'1','2','3','A'},
                                                                {'4','5','6','B'},
                                                                {'7','8','9','C'},
                                                                {'*','0','#','D'}
                                                                };
        unsigned char row,col,x;
        char return_value = 0xFF;
        for(row=0;row<4;row++)
        {
            DIO_vWriteLowNibble(KPORT1,0xFF);
            DIO_vWritePin(KPORT1,row,0);
            for(col=0;col<4;col++)
            {
                    x = DIO_u8ReadPin(KPORT2,col+1);
                    if(x==0)
                    {
                            return_value=ascii[row][col];
                            break;
                    }
            }

        }
        return return_value;
}

