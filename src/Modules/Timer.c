/*
 * Timer.c
 *
 *  Created on: 2016/09/02
 *      Author: Matsutomo2
 */


#include "Timer.h"
#include "micon/CMT.h"

#define PCLK_CLOCK	(100000000)

void _Timer_Activate(void)
{
	CMT_init();
}

void _Timer1_Set(TimerClock clock, _UDWORD interval, void (*callback)(void))
{
	float microSec = (PCLK_CLOCK / (float)clock) / 1000000.0;
	_UDWORD CMCOR_value = (_UDWORD)(interval * microSec);

	if(CMCOR_value > 65535)
	{
		CMCOR_value = 65535;
	}

	switch(clock)
	{
		case TimerClock_8:
			CMT0_Set(0x00, CMCOR_value, callback);
			break;

		case TimerClock_32:
			CMT0_Set(0x01, CMCOR_value, callback);
			break;

		case TimerClock_128:
			CMT0_Set(0x02, CMCOR_value, callback);
			break;

		case TimerClock_512:
			CMT0_Set(0x03, CMCOR_value, callback);
			break;
		default:
			break;
	}
}

void _Timer1_Start(void)
{
	CMT0_Start();
}

void _Timer1_Stop(void)
{
	CMT0_Stop();
}

void Timer2_Set(TimerClock clock, _UDWORD interval, void (*callback)(void))
{
	float microSec = (PCLK_CLOCK / (float)clock) / 1000000.0;
	_UDWORD CMCOR_value = (_UDWORD)(interval * microSec);

	if(CMCOR_value > 65535)
	{
		CMCOR_value = 65535;
	}

	switch(clock)
	{
		case TimerClock_8:
			CMT1_Set(0x00, CMCOR_value, callback);
			break;

		case TimerClock_32:
			CMT1_Set(0x01, CMCOR_value, callback);
			break;

		case TimerClock_128:
			CMT1_Set(0x02, CMCOR_value, callback);
			break;

		case TimerClock_512:
			CMT1_Set(0x03, CMCOR_value, callback);
			break;
		default:
			break;
	}
}

void Timer2_Start(void)
{
	CMT1_Start();
}

void Timer2_Stop(void)
{
	CMT1_Stop();
}

void _Timer3_Set(TimerClock clock, _UDWORD interval, void (*callback)(void))
{
	float microSec = (PCLK_CLOCK / (float)clock) / 1000000.0;
	_UDWORD CMCOR_value = (_UDWORD)(interval * microSec);

	if(CMCOR_value > 65535)
	{
		CMCOR_value = 65535;
	}

	switch(clock)
	{
		case TimerClock_8:
			CMT2_Set(0x00, CMCOR_value, callback);
			break;

		case TimerClock_32:
			CMT2_Set(0x01, CMCOR_value, callback);
			break;

		case TimerClock_128:
			CMT2_Set(0x02, CMCOR_value, callback);
			break;

		case TimerClock_512:
			CMT2_Set(0x03, CMCOR_value, callback);
			break;
		default:
			break;
	}
}

void _Timer3_Start(void)
{
	CMT2_Start();
}

void _Timer3_Stop(void)
{
	CMT2_Stop();
}
