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
#include "..\Modules\Bluetooth.h"
#include "..\Modules\LED.h"
#include "..\Modules\Buzzer.h"

BOOL Connecter_isConnecting = False;


_UBYTE trg[5];
_UBYTE trg_index = 0;
BOOL trgRecieved = False;

_UBYTE command[5];
_UBYTE command_index = 0;
BOOL commandRecieved = False;

_UBYTE valueLength[5];
_UBYTE valueLength_index = 0;
_UBYTE lengthOfValue = 0;
BOOL valueLengthRecieved = False;

_UBYTE value[15];
_UBYTE value_index = 0;
BOOL valueRecieved = False;

BOOL lineRecieved = False;


_UBYTE TransmitDataBufferA[1024];
_UBYTE BufferA_Count = 0;
_UBYTE TransmitDataBufferB[1024];
_UBYTE BufferB_Count = 0;
_UBYTE BufferAisSelected = 1;

void (*Inputs[32])(DataValue data);


static void Execute(_UBYTE* trg, _UBYTE command, _UBYTE* value);


void _Connecter_Activate(void)
{
	_UART1_Activate();
}

BOOL connecter_Recieve_running = False;
void _Connecter_Recieve(void)
{
	_UWORD count;
	_UWORD RecievedData_index = 0;

	_UBYTE* uart1RecievedData = _UART1_GetRecievedData(&count);

	if(connecter_Recieve_running)
	{
		Buzzer_OneTime(1000);
		return;
	}

	connecter_Recieve_running = True;

	while(RecievedData_index != count)
	{
		if(uart1RecievedData[RecievedData_index] == ';')
		{
			trgRecieved = True;
			RecievedData_index ++;
			continue;
		}
		else if(uart1RecievedData[RecievedData_index] == ':')
		{
			commandRecieved = True;
			RecievedData_index ++;
			continue;
		}
		else if(uart1RecievedData[RecievedData_index] == ')')
		{
			valueLengthRecieved = True;
			lengthOfValue = (_UBYTE)StringToWORD(valueLength, valueLength_index);
			RecievedData_index ++;
			continue;
		}

		if(!trgRecieved)
		{
			trg[trg_index] = uart1RecievedData[RecievedData_index];
			trg_index++;
		}
		else if(!commandRecieved)
		{
			command[command_index] = uart1RecievedData[RecievedData_index];
			command_index++;
		}
		else if(!valueLengthRecieved)
		{
			valueLength[valueLength_index] = uart1RecievedData[RecievedData_index];
			valueLength_index++;
		}
		else if(!valueRecieved)
		{
			value[value_index] = uart1RecievedData[RecievedData_index];
			value_index++;


			if(value_index >= lengthOfValue)
			{
				valueRecieved = True;
			}
		}
		else if(uart1RecievedData[RecievedData_index] == '\n')
		{
			lineRecieved = True;
		}
		else
		{
			trgRecieved = False;
			commandRecieved = False;
			valueLengthRecieved = False;
			valueRecieved = False;
			lineRecieved = False;

			Buzzer_OneTime(300);

			trg_index = 0;
			command_index = 0;
			valueLength_index = 0;
			value_index = 0;
		}

		if(trgRecieved && commandRecieved && valueLengthRecieved && valueRecieved && lineRecieved)
		{
			trgRecieved = False;
			commandRecieved = False;
			valueLengthRecieved = False;
			valueRecieved = False;
			lineRecieved = False;

			Execute(trg , (_UBYTE)StringToWORD(command, command_index), value);

			trg_index = 0;
			command_index = 0;
			valueLength_index = 0;
			value_index = 0;
		}

		RecievedData_index ++;
	}

	connecter_Recieve_running = False;
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

BOOL connecter_send_running = False;
void Connecter_Send(_UBYTE* data, _UBYTE count)
{
	_UBYTE i;

	if(connecter_send_running)
	{
		Buzzer_OneTime(300);
	}
	connecter_send_running = True;

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

	connecter_send_running = False;
}

void Connecter_SendFloat(_UBYTE* head, _UBYTE headCount, float value)
{
	Connecter_Send(head, headCount);
	Connecter_Send("4)", 2);
	Connecter_Send(FloatToBits(value), 4);
	Connecter_Send("\n", 1);
}

void Connecter_SendInt(_UBYTE* head, _UBYTE headCount, _SDWORD value)
{
	Connecter_Send(head, headCount);
	Connecter_Send("4)", 2);
	Connecter_Send(IntToBits(value), 4);
	Connecter_Send("\n", 1);
}

void Execute(_UBYTE* trg, _UBYTE command, _UBYTE* value)
{
	_SDWORD data;

	if(trg[0] == 'S')
	{
		switch(command)
		{
			case 1:
				if(value[0] == '1')
				{
					Connecter_isConnecting = True;
					_LED_R_On();
				}
				else
				{
					Connecter_isConnecting = False;
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

			default:
				break;
		}
	}


	if(!Connecter_isConnecting) return;


	if(trg[0] == 'M')
	{
		switch(trg[1])
		{
			case 'm':
				_Motor_Do(trg[2], command, value);
				break;

			case 'b':
				_Bluetooth_Do(trg[2], command, value);
				break;

			default:
				break;
		}
	}
}


void Connecter_InputToHardwarePort(_UBYTE Adress, DataValue data)
{
	Inputs[Adress](data);
}

void Connecter_RegistHardwarePort(_UBYTE Adress, void (*Input)(DataValue data))
{
	Inputs[Adress] = Input;
}

