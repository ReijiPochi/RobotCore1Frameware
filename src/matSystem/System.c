/*
 * System.cpp
 *
 *  Created on: 2016/09/12
 *      Author: Matsutomo2
 */


#include "System.h"
#include "Connecter.h"
#include "..\Modules\Buzzer.h"
#include "..\Modules\LED.h"

static void SendLog(void);

_UDWORD System_CurrentTime = 0;
_UBYTE count = 0;

BOOL isCounting = False;

Log log[256];
_UWORD logIndex = 0;

void _System_ClockStart(void)
{
	isCounting = True;
}

void _System_ClockStop(void)
{
	isCounting = False;
}

void _System_SetTime(_UDWORD time)
{
	System_CurrentTime = time;
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

void _System_Do(_UBYTE command, _UBYTE* value)
{
	_SDWORD data;

	switch(command)
	{
		case 1:
			if(value[0] == '1')
			{
				_Connecter_isConnecting = True;
				_LED_R_On();
			}
			else
			{
				_Connecter_isConnecting = False;
				_LED_R_Off();
			}
			break;

		case 2:
			data = BitsToInt(value);
			if(data < 0)
			{
				_System_ClockStop();
			}
			else
			{
				_System_SetTime(data);
				_System_ClockStart();
			}
			break;

		case 3:

			break;

		default:
			break;
	}
}

void System_Log(_UWORD errorLog)
{
	log[logIndex].Time = System_CurrentTime;
	log[logIndex].ErrorNumber = errorLog;


}

void SendLog(Log log)
{
	_UBYTE dataBytes[7];

	dataBytes[0] = log.Time & 0x000000FF;
	dataBytes[1] = (log.Time & 0x0000FF00) >> 8;
	dataBytes[2] = (log.Time & 0x00FF0000) >> 16;
	dataBytes[3] = (log.Time & 0xFF000000) >> 24;
	dataBytes[4] = log.ErrorNumber & 0x00FF;
	dataBytes[5] = (log.ErrorNumber & 0xFF00) >> 8;
	dataBytes[6] = '\n';

	Connecter_Send("S;5:6)", 6);
	Connecter_Send(dataBytes, 8);
}
