#ifndef BUTTON_H_
#define BUTTON_H_

void Button_vInit(unsigned char portname, unsigned char pinnumber);
void Button_vInitPullUp(unsigned char portname, unsigned char pinnumber);
unsigned char Button_u8Read(unsigned char portname, unsigned char pinnumber);
void Button_vInitPullDown(unsigned char portname, unsigned char pinnumber);

#endif
