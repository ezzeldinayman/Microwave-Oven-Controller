#include "ARM_DIO.h"

void LED_vInit(unsigned char portname, unsigned char pinnumber)
{
	DIO_vInitPort(portname);
	DIO_vSetPinDir(portname, pinnumber,1);
}

void LED_ON(unsigned char portname, unsigned char pinnumber)
{
	DIO_vWritePin(portname,pinnumber,1);
}

void LED_OFF(unsigned char portname, unsigned char pinnumber)
{
	DIO_vWritePin(portname,pinnumber,0);
}

void LED_TOG(unsigned char portname, unsigned char pinnumber)
{
	DIO_vTogglePin(portname, pinnumber);
}