
#include "App.h"
#include "..\typedefine.h"
#include "..\DataConverter.h"
#include "..\Modules\LED.h"
#include "..\Modules\Motor.h"
#include "..\Modules\Bluetooth.h"
#include "..\Modules\AnalogIN.h"
#include "..\Modules\AnalogOUT.h"
#include "..\Modules\Buzzer.h"
#include "..\Modules\Servo.h"
#include "..\Modules\DataLogger.h"

#include "..\matSystem\Connecter.h"

static void DecipherAndExecute(_SWORD*);

void Initialize()
{
	_LED_B_On();

	Motor_Activate();
	Bluetooth_Activate();
	AnalogIN_Activate();
	AnalogOUT_Activate();
	Buzzer_Activate();
	Servo_Activate();
	DataLogger_Activate();

	Buzzer_StepUp();
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

	// START
	if(button == 0x0003)
	{
		Motor_UnlockSTBY();
		Buzzer_Siren1();

		_LED_B_Off();
		_LED_G_On();
	}

	// SELECT
	if(button == 0x000C)
	{
		Motor_LockSTBY();
		Buzzer_StepDown();

		_LED_B_On();
		_LED_G_Off();
	}

	if ((button & (1 << 11)) != 0)
	{
//		pump_on();
		//Buzzer_On();
		Buzzer_Siren2();
		_LED_R_On();
	}
	else
	{
		//Buzzer_Off();
		_LED_R_Off();
	}

	// まる
	if ((button & (1 << 6)) != 0)
	{
		_UBYTE test[] = "Mm1;5:0.594\n";
		Connecter_Send(test, 12);
	}

	// しかく
	if ((button & (1 << 8)) != 0)
	{
	}

	if ((button & (1 << 9)) != 0)
	{
		Motor5_DutyIn(-1.0, RobotCore);
	}
	else if ((button & (1 << 10)) != 0)
	{
		Motor5_DutyIn(1.0, RobotCore);
	}
	else
	{
		Motor5_DutyIn(0.0, RobotCore);
	}

	// アナログスティックの解析
	_SDWORD _stick_l_h = order[3] - 64;	// 左水平
	_SDWORD _stick_l_v = -order[4] + 64;	// 左垂直
	_SDWORD _stick_r_h = order[5] - 64;	// 右水平

	_SDWORD stick_l_h_2;
	_SDWORD stick_l_v_2;
	_SDWORD stick_r_h_2;

	if(_stick_l_h > 0) stick_l_h_2 = _stick_l_h * _stick_l_h / 64;
	else stick_l_h_2 = _stick_l_h * _stick_l_h / -64;

	if(_stick_l_v > 0) stick_l_v_2 = _stick_l_v * _stick_l_v / 64;
	else stick_l_v_2 = _stick_l_v * _stick_l_v / -64;

	if(_stick_r_h > 0) stick_r_h_2 = _stick_r_h * _stick_r_h / 64;
	else stick_r_h_2 = _stick_r_h * _stick_r_h / -64;

	Motor1_DutyIn(-(stick_l_v_2 - stick_l_h_2 - stick_r_h_2) / 64.0, RobotCore);
	Motor2_DutyIn((stick_l_v_2 + stick_l_h_2 + stick_r_h_2) / 64.0, RobotCore);
	Motor3_DutyIn((stick_l_v_2 - stick_l_h_2 + stick_r_h_2) / 64.0, RobotCore);
	Motor4_DutyIn(-(stick_l_v_2 + stick_l_h_2 - stick_r_h_2) / 64.0, RobotCore);

	Servo1_RotationIn(stick_l_v_2, RobotCore);
}


