/*
 * Battery.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "Battery.h"
#include "micon/S12ADB.h"

void _Battery_Activate(void)
{
	S12AD_init();
}

void _Battery_Sample(void)
{
	S12AD_Sample();
}

float _Battery_GetVoltage1(void)
{
	float volts = S12ADB_GetVoltage(0);
	volts /= 203.4277198;
	return volts;
}

float _Battery_GetVoltage2(void)
{
	float volts = S12ADB_GetVoltage(1);
	volts /= 203.4277198;
	return volts;
}

float _Battery_GetVoltage3(void)
{
	float volts = S12ADB_GetVoltage(2);
	volts /= 203.4277198;
	return volts;
}
