#ifndef SYSTICK_H_
#define SYSTICK_H_

void Systick_init_1ms();
void wait_Xms(unsigned long delay);
void Systick_vInitInterrupt(void);

#endif
