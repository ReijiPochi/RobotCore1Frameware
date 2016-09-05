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


static void Decipher(void);
static void Execute(_UBYTE* trg, _UBYTE command, _UBYTE* value);


void Connecter_Activate(void)
{
	UART1_Activate();
}

void Connecter_Recieve(void)
{
	_UWORD count;
	_UWORD RecievedData_index = 0;

	RecievedData = UART1_GetRecievedData(&count);

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

void Connecter_Transmit(void);


void Decipher()
{
	_UBYTE trg[5];
	_UBYTE trg_index = 0;
	bool trgRecieved = false;

	_UBYTE command[5];
	_UBYTE command_index = 0;
	bool commandRecieved = false;

	_UBYTE value[15];
	_UBYTE value_index = 0;

	for(_UBYTE i = 0; i < line_index - 1; i ++)
	{
		if(line[i] == ';')
		{
			trgRecieved = true;
		}

		if(line[i] == ':')
		{
			commandRecieved = true;
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

	if(trg_index != 0 && command_index != 0 && value_index != 0)
	{
		Execute(trg , (_UBYTE)StringToWORD(command, command_index), value);
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

