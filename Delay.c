#include "standard_macros.h"
#include "tm4c123gh6pm.h"
#include "Delay.h"

void _delay_init(void)
{
	SYSCTL_RCGCTIMER_R |= 1;
}
void _delay_OneMs(void)
{ 
		CLR_BIT(TIMER0_CTL_R,0);
		TIMER0_CFG_R = 0x00;						
		SET_BIT(TIMER0_TAMR_R,1); 	
		CLR_BIT(TIMER0_TAMR_R,4);
		TIMER0_TAILR_R = 16000-1;	
		SET_BIT(TIMER0_CTL_R,0);	
		while(1)
		{
			if(READ_BIT(TIMER0_RIS_R,0) == 1)
			{
				SET_BIT(TIMER0_ICR_R,0);
				TOG_BIT(TIMER0_MIS_R,2);
				break;
			}
		}
}
void _delay_ms(int delay)
{
	_delay_init();
	int i;
	for(i=0;i<delay;i++)
	{
		_delay_OneMs();
	}
}

