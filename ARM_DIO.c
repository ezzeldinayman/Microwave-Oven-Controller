#include "standard_macros.h"
#include "tm4c123gh6pm.h"
#include "ARM_DIO.h"

void DIO_vInitPort(unsigned char portname)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,0);
				while(READ_BIT(SYSCTL_RCGCGPIO_R,0)==0);
				GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTA_CR_R = 0xFF;
				GPIO_PORTA_AFSEL_R = 0x00;
				GPIO_PORTA_AMSEL_R = 0x00;
				GPIO_PORTA_PCTL_R = 0x00;
				GPIO_PORTA_DEN_R = 0xFF;
				
			}
			break;
			
			case 'B':
			case 'b':
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,1);
				while(READ_BIT(SYSCTL_RCGCGPIO_R,1)==0);
				GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTB_CR_R = 0xFF;
				GPIO_PORTB_AFSEL_R = 0x00;
				GPIO_PORTB_AMSEL_R = 0x00;
				GPIO_PORTB_PCTL_R = 0x00;
				GPIO_PORTB_DEN_R = 0xFF;
			}
			break;
			
			case 'C':
			case 'c':
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,2);
				while(READ_BIT(SYSCTL_RCGCGPIO_R,2)==0);
				GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTC_CR_R = 0xFF;
				GPIO_PORTC_AFSEL_R = 0x00;
				GPIO_PORTC_AMSEL_R = 0x00;
				GPIO_PORTC_PCTL_R = 0x00;
				GPIO_PORTC_DEN_R = 0xFF;
				
			}
			break;
			
			case 'D':
			case 'd':
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,3);
				while(READ_BIT(SYSCTL_RCGCGPIO_R,3)==0);
				GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTD_CR_R = 0xFF;
				GPIO_PORTD_AFSEL_R = 0x00;
				GPIO_PORTD_AMSEL_R = 0x00;
				GPIO_PORTD_PCTL_R = 0x00;
				GPIO_PORTD_DEN_R = 0xFF;
				
			}
			break;
			
			case 'E':
			case 'e':
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,4);
				while(READ_BIT(SYSCTL_RCGCGPIO_R,4)==0);
				GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTE_CR_R = 0x1F;
				GPIO_PORTE_AFSEL_R = 0x00;
				GPIO_PORTE_AMSEL_R = 0x00;
				GPIO_PORTE_PCTL_R = 0x00;
				GPIO_PORTE_DEN_R = 0x1F;
			}
			break;
			
			case 'F':
			case 'f':
			{
				SET_BIT(SYSCTL_RCGCGPIO_R,5);
				while(READ_BIT(SYSCTL_RCGCGPIO_R,5)==0);
				GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
				GPIO_PORTF_CR_R = 0x1F;
				GPIO_PORTF_AFSEL_R = 0x00;
				GPIO_PORTF_AMSEL_R = 0x00;
				GPIO_PORTF_PCTL_R = 0x00;
				GPIO_PORTF_DEN_R = 0x1F;
				
			}
			break;
			
		}
}

/*-----------------------------------------------------------------------*/

void DIO_vSetPinDir(unsigned char portname, unsigned char pinnumber, unsigned char direction)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				if(direction==1) SET_BIT(GPIO_PORTA_DIR_R,pinnumber);
				else CLR_BIT(GPIO_PORTA_DIR_R,pinnumber);
			}
			break;
			
			
			case 'B':
			case 'b':
			{
				if(direction==1) SET_BIT(GPIO_PORTB_DIR_R,pinnumber);
				else CLR_BIT(GPIO_PORTB_DIR_R,pinnumber);
			}
			break;
			
			
			case 'C':
			case 'c':
			{
				if(direction==1) SET_BIT(GPIO_PORTC_DIR_R,pinnumber);
				else CLR_BIT(GPIO_PORTC_DIR_R,pinnumber);
			}
			break;
			
			
			case 'D':
			case 'd':
			{
				if(direction==1) SET_BIT(GPIO_PORTD_DIR_R,pinnumber);
				else CLR_BIT(GPIO_PORTD_DIR_R,pinnumber);	
			}
			break;
			
			
			case 'E':
			case 'e':
			{
				if(direction==1) SET_BIT(GPIO_PORTE_DIR_R,pinnumber);
				else CLR_BIT(GPIO_PORTE_DIR_R,pinnumber);
			}
			break;
			
			
			case 'F':
			case 'f':
			{
				if(direction==1) SET_BIT(GPIO_PORTF_DIR_R,pinnumber);
				else CLR_BIT(GPIO_PORTF_DIR_R,pinnumber);	
			}
			break;				
		}
}

/*------------------------------------------------------------------------------*/


void DIO_vWritePin(unsigned char portname, unsigned char pinnumber, unsigned char value)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			if(value==1) SET_BIT(GPIO_PORTA_DATA_R,pinnumber);
			else CLR_BIT(GPIO_PORTA_DATA_R,pinnumber);
		}
		break;
		
		case 'B':
		case 'b':
		{
			if(value==1) SET_BIT(GPIO_PORTB_DATA_R,pinnumber);
			else CLR_BIT(GPIO_PORTB_DATA_R,pinnumber);
		}
		break;
		
		case 'C':
		case 'c':
		{
			if(value==1) SET_BIT(GPIO_PORTC_DATA_R,pinnumber);
			else CLR_BIT(GPIO_PORTC_DATA_R,pinnumber);
		}
		break;
		
		case 'D':
		case 'd':
		{
			if(value==1) SET_BIT(GPIO_PORTD_DATA_R,pinnumber);
			else CLR_BIT(GPIO_PORTD_DATA_R,pinnumber);
		}
		break;
		
		case 'E':
		case 'e':
		{
			if(value==1) SET_BIT(GPIO_PORTE_DATA_R,pinnumber);
			else CLR_BIT(GPIO_PORTE_DATA_R,pinnumber);
		}
		break;
		
		case 'F':
		case 'f':
		{
			if(value==1) SET_BIT(GPIO_PORTF_DATA_R,pinnumber);
			else CLR_BIT(GPIO_PORTF_DATA_R,pinnumber);
		}
		break;
	}
}

/*----------------------------------------------------------------------------------*/

unsigned char DIO_u8ReadPin(unsigned char portname, unsigned char pinnumber)
{
		unsigned char returnValue;
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				returnValue = READ_BIT(GPIO_PORTA_DATA_R,pinnumber);
				return returnValue;
			}
			
			
			case 'B':
			case 'b':
			{
				returnValue = READ_BIT(GPIO_PORTB_DATA_R,pinnumber);
				return returnValue;
			}
			
			
			case 'C':
			case 'c':
			{
				returnValue = READ_BIT(GPIO_PORTC_DATA_R,pinnumber);
				return returnValue;
			}
			
			
			case 'D':
			case 'd':
			{
				returnValue = READ_BIT(GPIO_PORTD_DATA_R,pinnumber);
				return returnValue;
			}
			
			case 'E':
			case 'e':
			{
				returnValue = READ_BIT(GPIO_PORTE_DATA_R,pinnumber);
				return returnValue;
			}
			
			case 'F':
			case 'f':
			{
				returnValue = READ_BIT(GPIO_PORTF_DATA_R,pinnumber);
				return returnValue;
			}
		}
}

/*---------------------------------------------------------------------------------*/

void DIO_vTogglePin(unsigned char portname, unsigned char pinnumber)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				TOG_BIT(GPIO_PORTA_DATA_R,pinnumber);
			}
			break;
			
			case 'B':
			case 'b':
			{
				TOG_BIT(GPIO_PORTB_DATA_R,pinnumber);
			}
			break;
			
			case 'C':
			case 'c':
			{
				TOG_BIT(GPIO_PORTC_DATA_R,pinnumber);
			}
			break;
			
			case 'D':
			case 'd':
			{
				TOG_BIT(GPIO_PORTD_DATA_R,pinnumber);
			}
			break;
			
			case 'E':
			case 'e':
			{
				TOG_BIT(GPIO_PORTE_DATA_R,pinnumber);
			}
			break;
			
			case 'F':
			case 'f':
			{
				TOG_BIT(GPIO_PORTF_DATA_R,pinnumber);
			}
			break;
		}
}

/*-------------------------------------------------------------------------------*/

void DIO_vSetPortDir(unsigned char portname, unsigned long direction)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				GPIO_PORTA_DIR_R = direction;
			}
			break;
			
			case 'B':
			case 'b':
			{
				GPIO_PORTB_DIR_R = direction;
			}
			break;
			
			case 'C':
			case 'c':
			{
				GPIO_PORTC_DIR_R = direction;
			}
			break;
			
			case 'D':
			case 'd':
			{
				GPIO_PORTD_DIR_R = direction;
			}
			break;
			
			case 'E':
			case 'e':
			{
				GPIO_PORTE_DIR_R = direction;
			}
			break;
			
			case 'F':
			case 'f':
			{
				GPIO_PORTF_DIR_R = direction;
			}
			break;
			
		}
}

/*--------------------------------------------------------------------------------------------------------*/

void DIO_vWritePort(unsigned char portname, unsigned long value)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			GPIO_PORTA_DATA_R = value;
		}
		break;
		
		case 'B':
		case 'b':
		{
			GPIO_PORTB_DATA_R = value;
		}
		break;
		
		case 'C':
		case 'c':
		{
			GPIO_PORTC_DATA_R = value;
		}
		break;
		
		case 'D':
		case 'd':
		{
			GPIO_PORTD_DATA_R = value;
		}
		break;
		
		case 'E':
		case 'e':
		{
			GPIO_PORTE_DATA_R = value;
		}
		break;
		
		case 'F':
		case 'f':
		{
			GPIO_PORTF_DATA_R = value;
		}
		break;
	}
}

/*----------------------------------------------------------------------------------------*/

unsigned long DIO_u32ReadPort(unsigned char portname)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				return GPIO_PORTA_DATA_R;
			}
			
			case 'B':
			case 'b':
			{
				return GPIO_PORTB_DATA_R;
			}
			
			case 'C':
			case 'c':
			{
				return GPIO_PORTC_DATA_R;
			}
			
			case 'D':
			case 'd':
			{
				return GPIO_PORTD_DATA_R;
			}
			
			case 'E':
			case 'e':
			{
				return GPIO_PORTE_DATA_R;
			}
			
			case 'F':
			case 'f':
			{
				return GPIO_PORTF_DATA_R;
			}
		}
			
}

void DIO_vEnablePullUp(unsigned char portname, unsigned char pinnumber)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				SET_BIT(GPIO_PORTA_PUR_R,pinnumber);
			}
			break;
			
			case 'B':
			case 'b':
			{
				SET_BIT(GPIO_PORTB_PUR_R,pinnumber);
			}
			break;
			
			case 'C':
			case 'c':
			{
				SET_BIT(GPIO_PORTC_PUR_R,pinnumber);
			}
			break;
			
			case 'D':
			case 'd':
			{
				SET_BIT(GPIO_PORTD_PUR_R,pinnumber);
			}
			break;
			
			case 'E':
			case 'e':
			{
				SET_BIT(GPIO_PORTE_PUR_R,pinnumber);
			}
			break;
			
			case 'F':
			case 'f':
			{
				SET_BIT(GPIO_PORTF_PUR_R,pinnumber);
			}
			break;
		}
}

void DIO_vWriteHighNibble(unsigned char portname, unsigned long value)
{
		value<<=4;
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				GPIO_PORTA_DATA_R &= 0x0F; 
				GPIO_PORTA_DATA_R |= value;
			}
			break;
			
			case 'B':
			case 'b':
			{
				GPIO_PORTB_DATA_R &= 0x0F; 
				GPIO_PORTB_DATA_R |= value;
			}
			break;
			
			case 'C':
			case 'c':
			{
				GPIO_PORTC_DATA_R &= 0x0F; 
				GPIO_PORTC_DATA_R |= value;
			}
			break;
			
			case 'D':
			case 'd':
			{
				GPIO_PORTD_DATA_R &= 0x0F; 
				GPIO_PORTD_DATA_R |= value;
			}
			break;
		}
			
}

void DIO_vWriteLowNibble(unsigned char portname, unsigned long value)
{
		switch(portname)
		{
			case 'A':
			case 'a':
			{
				GPIO_PORTA_DATA_R &= 0xF0; 
				GPIO_PORTA_DATA_R |= value;
			}
			break;
			
			case 'B':
			case 'b':
			{
				GPIO_PORTB_DATA_R &= 0xF0; 
				GPIO_PORTB_DATA_R |= value;
			}
			break;
			
			case 'C':
			case 'c':
			{
				GPIO_PORTC_DATA_R &= 0xF0; 
				GPIO_PORTC_DATA_R |= value;
			}
			break;
			
			case 'D':
			case 'd':
			{
				GPIO_PORTD_DATA_R &= 0xF0; 
				GPIO_PORTD_DATA_R |= value;
			}
			break;
		}
			
}

void DIO_vEnablePullDown(unsigned char portname, unsigned char pinnumber)
{
	switch (portname)
	{
	case 'A':
	case 'a':
	{
		CLR_BIT(GPIO_PORTA_PUR_R, pinnumber);
		SET_BIT(GPIO_PORTA_PDR_R, pinnumber);
	}
	break;

	case 'B':
	case 'b':
	{
		CLR_BIT(GPIO_PORTA_PUR_R, pinnumber);
		SET_BIT(GPIO_PORTB_PDR_R, pinnumber);
	}
	break;

	case 'C':
	case 'c':
	{
		CLR_BIT(GPIO_PORTA_PUR_R, pinnumber);
		SET_BIT(GPIO_PORTC_PDR_R, pinnumber);
	}
	break;

	case 'D':
	case 'd':
	{
		CLR_BIT(GPIO_PORTA_PUR_R, pinnumber);
		SET_BIT(GPIO_PORTD_PDR_R, pinnumber);
	}
	break;

	case 'E':
	case 'e':
	{
		CLR_BIT(GPIO_PORTA_PUR_R, pinnumber);
		SET_BIT(GPIO_PORTE_PDR_R, pinnumber);
	}
	break;

	case 'F':
	case 'f':
	{
		CLR_BIT(GPIO_PORTA_PUR_R, pinnumber);
		SET_BIT(GPIO_PORTF_PDR_R, pinnumber);
	}
	break;
	}
}





