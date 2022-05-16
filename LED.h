#ifndef LED_H_
#define LED_H_

void LED_vInit(unsigned char portname, unsigned char pinnumber);
void LED_ON(unsigned char portname, unsigned char pinnumber);
void LED_OFF(unsigned char portname, unsigned char pinnumber);
void LED_TOG(unsigned char portname, unsigned char pinnumber);

#endif