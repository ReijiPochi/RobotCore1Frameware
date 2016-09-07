/*
 * DataLogger.c
 *
 *  Created on: 2016/09/07
 *      Author: Matsutomo2
 */


#include "DataLogger.h"
#include "Buzzer.h"

typedef struct
{
	_UWORD time;
	DataValue data;
} LogData;

static void dataLogger1_Do(_UBYTE command, _UBYTE* value);

BOOL log1_isLoging = False;
LogData log1[2048];
_UWORD log1_time = 1;
_UWORD log1_index = 0;
_UBYTE log1_count = 0;


void DataLogger_Activate(void)
{
	Connecter_RegistHardwarePort(1, DataLogger1_DataIn);
}

void _DataLogger_Loop(void)
{
	if(log1_isLoging)
	{
		log1_time++;
	}
}

void _DataLogger_Do(_UBYTE module, _UBYTE command, _UBYTE* value)
{
	switch(module)
	{
		case '1':
			dataLogger1_Do(command, value);
			break;

		default:
			break;
	}
}

void dataLogger1_Do(_UBYTE command, _UBYTE* value)
{

}

void DataLogger1_DataIn(DataValue data)
{
	if(!log1_isLoging)
		return;

	log1_count++;

	if(log1_count >= 10)
	{
		log1_count = 0;

		if(log1_index >= 2048)
		{
			DataLogger1_LoggingStop();
			Buzzer_Siren2();
			return;
		}

		log1[log1_index].time = log1_time;
		log1[log1_index].data = data;

		log1_index++;
	}
}

void DataLogger1_LoggingStart(void)
{
	log1_isLoging = True;
	log1_index = 0;
}

void DataLogger1_LoggingStop(void)
{
	log1_isLoging = False;
}

void DataLogger_Log(_UBYTE adress, DataValue data)
{

}

