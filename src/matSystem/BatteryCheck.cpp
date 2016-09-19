/*
 * BatteryCheck.cpp
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */

#include "BatteryCheck.h"
#include "..\Modules\Battery.h"
#include "..\Modules\LED.h"
#include "..\Modules\Buzzer.h"

#define THRESHOLD	(0.1)

void BatteryCheck(void)
{
	float v1 = _Battery_GetVoltage1();
	float v2 = _Battery_GetVoltage2();
	float v3 = _Battery_GetVoltage3();

	if(v1 < 1.0) return;

	float cell1 = v1;
	float cell2 = v2 - v1;
	float cell3 = v3 - v2;

	float d1 = (cell1 - cell2) * (cell1 - cell2);
	float d2 = (cell1 - cell3) * (cell1 - cell3);
	float d3 = (cell3 - cell2) * (cell3 - cell2);

	if(d1 > THRESHOLD || d2 > THRESHOLD || d3 > THRESHOLD)
	{
		_LED_Error_On();
		Buzzer_Siren2();
	}

	if(cell1 < 3.3)
	{
		_LED_Error_On();
		Buzzer_LowBattery();
	}
}
