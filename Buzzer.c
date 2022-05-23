#include "ARM_DIO.h"
#include "Delay.h"

void Buzzer_vInit(unsigned char portname, unsigned char pinnumber)
{
	DIO_vInitPort(portname);
	DIO_vSetPinDir(portname, pinnumber, 1);
}

void Buzzer_On(unsigned char portname, unsigned char pinnumber)
{
	DIO_vWritePin(portname, pinnumber,1);
}

void Buzzer_Off(unsigned char portname, unsigned char pinnumber)
{
	DIO_vWritePin(portname, pinnumber,0);
}