/*
 * Multi.c
 *
 *  Created on: 2016/10/20
 *      Author: Reiji
 */


#include "Multi.h"
#include "micon\IO.h"

void Multi1_Activate(MultiMode mode)
{
	IO_Multi1_Init(OUT, OUT, OUT);
}

void Multi1_DOUT1(LogicLevel value)
{
	Multi1_1_Out(value);
}

void Multi1_DOUT2(LogicLevel value)
{
	Multi1_2_Out(value);
}

void Multi1_DOUT3(LogicLevel value)
{
	Multi1_3_Out(value);
}
