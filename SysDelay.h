#ifndef _SYSDELAY_H_
#define _SYSDELAY_H_

#include "tm4c123gh6pm.h"

	
void Systick_Wait10ms(unsigned long delay);
void Systick_Wait(unsigned long delay);
void Systick_vInit(void);
void Systick_vInitInterrupt(void);

#endif