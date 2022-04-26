#ifndef ARM_DIO_H_
#define ARM_DIO_H_

void DIO_vInitPort(unsigned char portname);
void DIO_vSetPinDir(unsigned char portname, unsigned char pinnumber, unsigned char direction);
void DIO_vWritePin(unsigned char portname, unsigned char pinnumber, unsigned char value);
unsigned long DIO_u32ReadPin(unsigned char portname, unsigned char pinnumber);
void DIO_vTogglePin(unsigned char portname, unsigned char pinnumber);
void DIO_vSetPortDir(unsigned char portname, unsigned long direction);
void DIO_vWritePort(unsigned char portname, unsigned long value);
unsigned long DIO_u32ReadPort(unsigned char portname);
void DIO_vEnablePullUp(unsigned char portname, unsigned char pinnumber);
void DIO_vWriteHighNibble(unsigned char portname, unsigned long value);
void DIO_vWriteLowNibble(unsigned char portname, unsigned long value);


#endif /*__ARM_DIO_H__*/
