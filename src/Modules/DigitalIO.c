/*
 * DigitalIO.c
 *
 *  Created on: 2016/09/13
 *      Author: Matsutomo2
 */


#include "DigitalIO.h"
#include "micon\IO.h"

#include "micon\iodefine.h"

BOOL DIO3interrupt = False;
LogicLevel dio3buf[10];
_UBYTE dio3buf_index = 0;
LogicLevel preDIO3state;
LogicLevel curDIO3state;
//_UWORD dio3count = 0;
//_UWORD dio3count2 = 0;
InterruptCallback DIO3callback;

void DIO_Activate(IOMode dio1, IOMode dio2, IOMode dio3, IOMode dio4)
{
	IO_DIO_Init(dio1, dio2, dio3, dio4);
}

void _DIO_Loop(void)
{
//	LogicLevel dio3;
	_UBYTE i;
	_UBYTE sum = 0;

	if(DIO3interrupt == False)
		return;

	dio3buf[dio3buf_index] = DIO_3_In();
	dio3buf_index++;
	if(dio3buf_index >= 10)
	{
		dio3buf_index = 0;
	}

	sum += dio3buf[0];
	sum += dio3buf[1];
	sum += dio3buf[2];
	sum += dio3buf[3];
	sum += dio3buf[4];
	sum += dio3buf[5];
	sum += dio3buf[6];
	sum += dio3buf[7];
	sum += dio3buf[8];
	sum += dio3buf[9];

	if(sum > 8)
		curDIO3state = H;
	else if(sum < 5)
		curDIO3state = L;

	if(preDIO3state == H && curDIO3state == L)
	{
		DIO3callback();
	}

	preDIO3state = curDIO3state;

//	dio3 = PORT5.PIDR.BIT.B0;
//	LED_ERROR(dio3);
//
//	if(dio3count2 != 0)
//	{
//		dio3count2--;
//		return;
//	}
//
//	if(dio3count >= 1 && dio3 == L)
//	{
//		dio3count++;
//	}
//	else
//	{
//		dio3count = 0;
//	}
//
//	if(dio3count == 0 && DIO3state == H && dio3 == L)
//	{
//		dio3count = 1;
//	}
//
//	if(dio3count > 10)
//	{
//		DIO3callback();
//		dio3count = 0;
//		dio3count2 = 100;
//	}
//
//	DIO3state = dio3;
}

void DIO_SetInterrupt(InterruptCallback callback)
{
	DIO3interrupt = True;
	DIO3callback = callback;
}

void DIO1_On(void)
{
	DIO_1_Out(1);
}

void DIO1_Off(void)
{
	DIO_1_Out(0);
}

void DIO2_On(void)
{
	DIO_2_Out(1);
}

void DIO2_Off(void)
{
	DIO_2_Out(0);
}

void DIO3_On(void)
{
	DIO_3_Out(1);
}

void DIO3_Off(void)
{
	DIO_3_Out(0);
}

void DIO4_On(void)
{
	DIO_4_Out(1);
}

void DIO4_Off(void)
{
	DIO_4_Out(0);
}
