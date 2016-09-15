/*
 * IO.c
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */


#include "IO.h"
#include "iodefine.h"

void IO_LED_init()
{
	PORT7.PDR.BYTE = 0x7C;
}

void LED_STATUS_R(_UBYTE value)
{
	PORT7.PODR.BIT.B2 = value;
}

void LED_STATUS_G(_UBYTE value)
{
	PORT7.PODR.BIT.B3 = value;
}

void LED_STATUS_B(_UBYTE value)
{
	PORT7.PODR.BIT.B4 = value;
}

void LED_INFO(_UBYTE value)
{
	PORT7.PODR.BIT.B5 = value;
}

void LED_ERROR(_UBYTE value)
{

	PORT7.PODR.BIT.B6 = value;
}



void IO_Motor_Init()
{
	PORT3.PDR.BIT.B5 = 1;
	PORTA.PDR.BYTE = 0x7F;
	PORTB.PDR.BYTE = 0x0F;
	PORTE.PDR.BIT.B0 = 0;
	PORTF.PDR.BIT.B4 = 1;
}

_UBYTE ALERT(void)
{
	return PORTE.PIDR.BIT.B0;
}

void STBY(_UBYTE value)
{
	PORTF.PODR.BIT.B4 = value;
}

void Motor1_MODE(_UBYTE m1, _UBYTE m2)
{
	PORTB.PODR.BIT.B2 = m1;
	PORTB.PODR.BIT.B3 = m2;
}

void Motor2_MODE(_UBYTE m1, _UBYTE m2)
{
	PORTB.PODR.BIT.B0 = m1;
	PORTB.PODR.BIT.B1 = m2;
}

void Motor3_MODE(_UBYTE m1, _UBYTE m2)
{
	PORTA.PODR.BIT.B5 = m1;
	PORTA.PODR.BIT.B6 = m2;
}

void Motor4_MODE(_UBYTE m1, _UBYTE m2)
{
	PORTA.PODR.BIT.B3 = m1;
	PORTA.PODR.BIT.B4 = m2;
}

void Motor5_MODE(_UBYTE m1, _UBYTE m2)
{
	PORTA.PODR.BIT.B1 = m1;
	PORTA.PODR.BIT.B2 = m2;
}

void Motor6_MODE(_UBYTE m1, _UBYTE m2)
{
	PORT3.PODR.BIT.B5 = m1;
	PORTA.PODR.BIT.B0 = m2;
}



void IO_DIO_Init(IOMode dio1, IOMode dio2, IOMode dio3, IOMode dio4)
{
	PORT3.PDR.BIT.B2 = (_UBYTE)dio1;
	PORT3.PDR.BIT.B3 = (_UBYTE)dio2;
	PORT7.PDR.BIT.B0 = (_UBYTE)dio3;
	PORT7.PDR.BIT.B1 = (_UBYTE)dio4;
}

void DIO_1_Out(_UBYTE value)
{
	PORT3.PODR.BIT.B2 = value;
}

void DIO_2_Out(_UBYTE value)
{
	PORT3.PODR.BIT.B3 = value;
}

void DIO_3_Out(_UBYTE value)
{
	PORT7.PODR.BIT.B0 = value;
}

void DIO_4_Out(_UBYTE value)
{
	PORT7.PODR.BIT.B1 = value;
}
