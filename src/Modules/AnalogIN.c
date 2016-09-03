/*
 * AnalogIN.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "AnalogIN.h"
#include "micon\S12ADB.h"

void AnalogIN_Activate(void)
{
	S12AD1_init();
}

void AnalogIN_Sample(void)
{
	S12AD1_Sample();
}

float AnalogIN_GetVoltage(_UBYTE channel)
{
	float volts;
	volts = S12AD1_GetVoltage(channel - 1);
	volts /= 1240.90909090;
	return volts;
}
