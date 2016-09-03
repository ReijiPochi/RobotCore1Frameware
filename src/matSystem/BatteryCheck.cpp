/*
 * BatteryCheck.cpp
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */

#include "BatteryCheck.h"
#include "..\Modules\Battery.h"
#include "..\Modules\LED.h"

#define THRESHOLD	(0.1)

void BatteryCheck(void)
{
	float cell1 = _Battery_GetVoltage1();
	float cell2 = _Battery_GetVoltage2();
	float cell3 = _Battery_GetVoltage3();

	if(cell1 < 1.0) return;

	if(cell1 - _Battery_GetVoltage2() > THRESHOLD || cell1 - _Battery_GetVoltage3() > THRESHOLD)
	{
		_LED_Error_On();
	}

	if(cell1 < 3.0)
	{
		_LED_Error_On();
	}
}
