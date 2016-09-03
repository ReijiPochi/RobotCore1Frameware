/*
 * DAC.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "AnalogOUT.h"
#include "micon/DAa.h"

void AnalogOUT_Activate(void)
{
	DAa_init();
}

void AnalogOUT1_SetVoltage(float volts)
{
	_UWORD value;

	value = (_UWORD)(volts * 310.30303030);
	DA0_SetValue(value);
}

void AnalogOUT2_SetVoltage(float volts)
{
	_UWORD value;

	value = (_UWORD)(volts * 310.30303030);
	DA1_SetValue(value);
}
