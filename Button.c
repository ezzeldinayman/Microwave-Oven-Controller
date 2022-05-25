#include "ARM_DIO.h"

void Button_vInit(unsigned char portname, unsigned char pinnumber)
{
		DIO_vInitPort(portname);
		DIO_vSetPinDir(portname, pinnumber,0);
}

void Button_vInitPullUp(unsigned char portname, unsigned char pinnumber)
{
		DIO_vInitPort(portname);
		DIO_vSetPinDir(portname, pinnumber,0);
		DIO_vEnablePullUp(portname,pinnumber);
}

unsigned char Button_u8Read(unsigned char portname, unsigned char pinnumber)
{
		return DIO_u8ReadPin(portname, pinnumber);
}

void Button_vInitPullDown(unsigned char portname, unsigned char pinnumber)
{
	DIO_vInitPort(portname);
	DIO_vSetPinDir(portname, pinnumber, 0);
	DIO_vEnablePullDown(portname, pinnumber);
}