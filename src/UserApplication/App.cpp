
#include "App.h"
#include "..\typedefine.h"
#include "..\Modules\LED.h"
#include "..\Modules\Motor.h"
#include "..\Modules\Bluetooth.h"

#include "..\Modules\micon\SCIc.h"

static void DecipherAndExecute(_SWORD*);

void Initialize()
{
	LED_Activate();

	LED_B_On();

	Motor_Activate();
	Bluetooth_Activate();
}


_SWORD orderBuffer[8] = { 0 };
_UBYTE i = 0;

void MainLoop()
{
	_SWORD orderChar = Bluetooth_GetRecieveData();

	if (orderChar != -1)
	{
		if(i == 0 && orderChar != 0x80)
		{
		}
		else
		{
			orderBuffer[i] = orderChar;
			i++;
		}
	}

	if (i == 7)
	{
		i = 0;

		DecipherAndExecute(orderBuffer);
	}

}



void DecipherAndExecute(_SWORD* order)
{
	_UDWORD button = (order[1] << 8) + order[2];

	if ((button & (1 << 11)) != 0)
	{
//		pump_on();
		LED_R_On();
	}
	else
	{
		LED_R_Off();
	}

	if ((button & (1 << 4)) != 0)
	{
		Motor_UnlockSTBY();

		LED_B_Off();
		LED_G_On();
	}

	if ((button & (1 << 9)) != 0)
	{
		Motor5_SetPWM(-1.0);
	}
	else if ((button & (1 << 10)) != 0)
	{
		Motor5_SetPWM(1.0);
	}
	else
	{
		Motor5_SetPWM(0.0);
	}

	// アナログスティックの解析
	_SDWORD stick_l_h = order[3] - 64;	// 左水平
	_SDWORD stick_l_v = -order[4] + 64;	// 左垂直
	_SDWORD stick_r_h = order[5] - 64;	// 右水平

	Motor1_SetPWM(-(stick_l_v - stick_l_h - stick_r_h) / 64.0);
	Motor2_SetPWM((stick_l_v + stick_l_h + stick_r_h) / 64.0);
	Motor3_SetPWM((stick_l_v - stick_l_h + stick_r_h) / 64.0);
	Motor4_SetPWM(-(stick_l_v + stick_l_h - stick_r_h) / 64.0);
}


