#include "tm4c123gh6pm.h"
#include "standard_macros.h"

void Systick_vInit(void)
{
	NVIC_ST_CTRL_R = 0; //disable systick during setup
	NVIC_ST_RELOAD_R = 0x00FFFFFF; //(24-bit) maximum reload value
	NVIC_ST_CURRENT_R = 0;	//clears any current value
	SET_BIT(NVIC_ST_CTRL_R,0);
	SET_BIT(NVIC_ST_CTRL_R,2);
}

void Systick_vInitInterrupt(void)
{
	NVIC_ST_CTRL_R = 0; //disable systick during setup
	NVIC_ST_RELOAD_R = 799999; //(24-bit) maximum reload value
	NVIC_ST_CURRENT_R = 0;	//clears any current value
	SET_BIT(NVIC_ST_CTRL_R,0);
	SET_BIT(NVIC_ST_CTRL_R,2);
	SET_BIT(NVIC_ST_CTRL_R,1); //interrupt enable
}

void Systick_Wait(unsigned long delay)
{
	NVIC_ST_RELOAD_R = delay-1; //number of counts
	NVIC_ST_CURRENT_R = 0; //clear any written value (3ed melawal)
	while(READ_BIT(NVIC_ST_CTRL_R,16)==0); //wait for flag
}
//hena el delay bymasel kam mara 1/80Mhz = 12.5 ns

void Systick_Wait10ms(unsigned long delay)
{
	unsigned long i;
	for(i=0;i<delay;i++)
	{
		Systick_Wait(800000); //80000*12.5ns = 10ms
	}
}