#include "tm4c123gh6pm.h" 



void Systick_init_1ms(){  //in io.h the NVIC_ST_CTRL_R, NVIC_ST_Reload_R,NVIC_ST_CURRENT_R are added
NVIC_ST_CTRL_R=0x00;
NVIC_ST_RELOAD_R=16000-1; // 16Mhz ->62.5ns  
NVIC_ST_CURRENT_R=0;
NVIC_ST_CTRL_R=0x05;
while((NVIC_ST_CTRL_R&0x00010000)==0){};  //wait for flag
}
void wait_Xms(unsigned long delay){
int i=0;
	for(i=0;i<delay;i++){
		Systick_init_1ms();
	}
}