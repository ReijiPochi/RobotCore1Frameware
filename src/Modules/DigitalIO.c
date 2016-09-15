/*
 * DigitalIO.c
 *
 *  Created on: 2016/09/13
 *      Author: Matsutomo2
 */


#include "DigitalIO.h"
#include "micon\IO.h"

void DIO_Activate(IOMode dio1, IOMode dio2, IOMode dio3, IOMode dio4)
{
	IO_DIO_Init(dio1, dio2, dio3, dio4);
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
