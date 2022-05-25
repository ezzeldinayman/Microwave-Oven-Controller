#include "tm4c123gh6pm.h" 
#include "standard_macros.h"


void Systick_vInitInterrupt(void)
{
	NVIC_ST_CTRL_R = 0; //disable systick during setup
	NVIC_ST_RELOAD_R = 159999;
	NVIC_ST_CURRENT_R = 0;	//clears any current value
	SET_BIT(NVIC_ST_CTRL_R,0);
	SET_BIT(NVIC_ST_CTRL_R,2);
	SET_BIT(NVIC_ST_CTRL_R,1); //interrupt enable
}
//TickTime 1/80Mhz = 12.5ns
