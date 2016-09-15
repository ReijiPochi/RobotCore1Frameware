/*
 * System.cpp
 *
 *  Created on: 2016/09/12
 *      Author: Matsutomo2
 */


#include "System.h"
#include "..\Modules\Buzzer.h"
#include "..\Modules\LED.h"

_UDWORD System_CurrentTime = 0;

BOOL isCounting = False;

void System_ClockStart(void)
{
	isCounting = True;
}

void _System_Loop(void)
{
	if(isCounting)
	{
		System_CurrentTime++;

		if(System_CurrentTime >= 4294967296)
		{
			_LED_Error_On();
			Buzzer_Siren2();
		}
	}
}