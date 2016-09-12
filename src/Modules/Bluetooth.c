/*
 * Bluetooth.c
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */


#include "Bluetooth.h"
#include "micon/SCIc.h"
#include "..\matSystem\System.h"

_UBYTE *bluetoothRecievedData;
_SWORD orderBuffer[8] = { 0 };
_UBYTE i = 0;

ModulePortState commandOut_State = Free;

static void Bluetooth_CommandOut(DUALSHOCK3 data);

void (*Callback)(DUALSHOCK3);


void Bluetooth_Activate(void (*callback)(DUALSHOCK3))
{
	uart0_init();
	Callback = callback;
}

void _Bluetooth_Loop(void)
{
	_UWORD count;
	_UWORD RecievedData_index = 0;
	DUALSHOCK3 data;

	bluetoothRecievedData = uart0_read(&count);

	while(RecievedData_index != count)
	{
		orderBuffer[i] = bluetoothRecievedData[RecievedData_index];


		if(i != 0)
		{
			orderBuffer[i] = bluetoothRecievedData[RecievedData_index];
			i++;
		}

		if(i == 0 && bluetoothRecievedData[RecievedData_index] == 0x80)
		{
			i++;
		}

		if (i == 7)
		{
			i = 0;

			data.Buttons.WORD = (orderBuffer[1] << 8) | orderBuffer[2];

			if((orderBuffer[2] & 0x03) == 0x03)
			{
				data.Buttons.WORD &= 0xFFFC;
				data.Buttons.BIT.Start = True;
			}

			if((orderBuffer[2] & 0x0C) == 0x0C)
			{
				data.Buttons.WORD &= 0xFFF3;
				data.Buttons.BIT.Select = True;
			}

			data.AnalogL.X = orderBuffer[3] - 64;
			data.AnalogL.Y = orderBuffer[4] - 64;
			data.AnalogR.X = orderBuffer[5] - 64;
			data.AnalogR.Y = orderBuffer[6] - 64;

			data.Time = System_CurrentTime;
			Bluetooth_CommandOut(data);
		}

		RecievedData_index ++;
	}
}

static void Bluetooth_CommandOut(DUALSHOCK3 data)
{
	_UBYTE dataBytes[11];

	Callback(data);

	if(commandOut_State == LookByHost)
	{
		Connecter_Send("Mb0;6:", 6);
		dataBytes[0] = data.Time & 0x000000FF;
		dataBytes[1] = (data.Time & 0x0000FF00) >> 8;
		dataBytes[2] = (data.Time & 0x00FF0000) >> 16;
		dataBytes[3] = (data.Time & 0xFF000000) >> 24;
		dataBytes[4] = data.Buttons.WORD & 0x00FF;
		dataBytes[5] = (data.Buttons.WORD & 0xFF00) >> 8;
		dataBytes[6] = data.AnalogL.X;
		dataBytes[7] = data.AnalogL.Y;
		dataBytes[8] = data.AnalogR.X;
		dataBytes[9] = data.AnalogR.Y;
		dataBytes[10] = '\n';
		Connecter_Send(dataBytes, 11);
	}
}

void _Bluetooth_Do(_UBYTE module, _UBYTE command, _UBYTE* value)
{
	switch(command)
	{
		case 5:		// CommandOut_DL_State
			if(value[0] == 1)
				commandOut_State = LookByHost;
			else
				commandOut_State = Free;
			break;

		default:
			break;
	}
}

void Bluetooth_IsLoggingIn(BOOL value)
{

}

void Bluetooth_CommandIn(DUALSHOCK3 value)
{

}

void Bluetooth_Vibrate1(void)
{
	uart0_send("1", 1);
}

void Bluetooth_Vibrate2(void)
{
	uart0_send("2", 1);
}
