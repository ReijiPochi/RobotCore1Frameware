/*
 * Connecter.cpp
 *
 *  Created on: 2016/09/05
 *      Author: Matsutomo2
 */


#include "Connecter.h"
#include "..\Modules\UART.h"
#include "..\DataConverter.h"

#include "..\Modules\Motor.h"

_UBYTE *RecievedData;
_UBYTE line[64];
_UBYTE line_index = 0;

_UBYTE TransmitDataBufferA[1024];
_UBYTE BufferA_Count = 0;
_UBYTE TransmitDataBufferB[1024];
_UBYTE BufferB_Count = 0;
_UBYTE BufferAisSelected = 1;


static void Decipher(void);
static void Execute(_UBYTE* trg, _UBYTE command, _UBYTE* value);


void _Connecter_Activate(void)
{
	_UART1_Activate();
}

void _Connecter_Recieve(void)
{
	_UWORD count;
	_UWORD RecievedData_index = 0;

	RecievedData = _UART1_GetRecievedData(&count);

	while(RecievedData_index != count)
	{
		line[line_index] = RecievedData[RecievedData_index];

		line_index ++;
		RecievedData_index ++;

		if(line[line_index - 1] == '\n')
		{
			Decipher();

			line_index = 0;
		}
	}
}

void _Connecter_Transmit(void)
{
	if(BufferAisSelected)
	{
		if(BufferA_Count != 0)
		{
			_UART1_TransmitData(TransmitDataBufferA, BufferA_Count);
			BufferA_Count = 0;
			BufferAisSelected = 0;
		}
	}
	else
	{
		if(BufferB_Count != 0)
		{
			_UART1_TransmitData(TransmitDataBufferB, BufferB_Count);
			BufferB_Count = 0;
			BufferAisSelected = 1;
		}
	}
}


void Decipher()
{
	_UBYTE trg[5];
	_UBYTE trg_index = 0;
	_UBYTE trgRecieved = 0;

	_UBYTE command[5];
	_UBYTE command_index = 0;
	_UBYTE commandRecieved = 0;

	_UBYTE value[15];
	_UBYTE value_index = 0;

	_UBYTE i;

	for(i = 0; i < line_index - 1; i ++)
	{
		if(line[i] == ';')
		{
			trgRecieved = 1;
		}

		if(line[i] == ':')
		{
			commandRecieved = 1;
		}

		if(!trgRecieved)
		{
			trg[trg_index] = line[i];
			trg_index++;
		}
		else if(!commandRecieved && line[i] != ';')
		{
			command[command_index] = line[i];
			command_index++;
		}
		else if(line[i] != ':' && line[i] != ';')
		{
			value[value_index] = line[i];
			value_index++;
		}
	}

	if(trg_index != 0 && command_index != 0)
	{
		Execute(trg , (_UBYTE)StringToWORD(command, command_index), value);
	}
}

void Connecter_Send(_UBYTE* data, _UBYTE count)
{
	_UBYTE i;

	if(BufferAisSelected)
	{
		for(i = 0; i < count; i++)
		{
			TransmitDataBufferA[BufferA_Count] = data[i];
			BufferA_Count++;
		}
	}
	else
	{
		for(i = 0; i < count; i++)
		{
			TransmitDataBufferB[BufferB_Count] = data[i];
			BufferB_Count++;
		}
	}
}

void Connecter_SendFloat(_UBYTE* head, _UBYTE headCount, float value)
{
	_UBYTE *data;

	Connecter_Send(head, headCount);

	data = FloatToBits(value);
	Connecter_Send(data, 4);

	if(BufferAisSelected)
	{
		TransmitDataBufferA[BufferA_Count] = '\n';
		BufferA_Count++;
	}
	else
	{
		TransmitDataBufferB[BufferB_Count] = '\n';
		BufferB_Count++;
	}
}

void Execute(_UBYTE* trg, _UBYTE command, _UBYTE* value)
{
	if(trg[0] == 'M')
	{
		switch(trg[1])
		{
			case 'm':
				_Motor_Do(trg[2], command, value);
				break;

			default:
				break;
		}
	}
}

