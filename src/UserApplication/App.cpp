
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
#include "..\Modules\DigitalIO.h"

#include "..\matSystem\Connecter.h"
#include "..\matSystem\System.h"

static void BluetoothCallback(DUALSHOCK3 data);

void Initialize()
{
	_LED_B_On();

	Motor_Activate();
	AnalogIN_Activate();
	AnalogOUT_Activate();
	Buzzer_Activate();
	Servo_Activate();
	DataLogger_Activate();
	DIO_Activate(OUT, OUT, IN, IN);

	Bluetooth_Activate(BluetoothCallback);
	//System_ClockStart();

	Buzzer_StepUp();

	Servo1_RotationIn(90.0, RobotCore);
}

void MainLoop()
{
}


static void BluetoothCallback(DUALSHOCK3 data)
{

	if(data.Buttons.BIT.Start)
	{
		Motor_UnlockSTBY();
		System_ClockStart();

		Buzzer_Siren1();

		_LED_B_Off();
		_LED_G_On();
	}

	if(data.Buttons.BIT.Select)
	{
		Motor_LockSTBY();
		Buzzer_StepDown();

		_LED_B_On();
	}

	if(data.Buttons.BIT.Maru)
		Buzzer_OneTime(100);

	if(data.Buttons.BIT.Batsu)
		Buzzer_Siren2();

	if(data.Buttons.BIT.Sankaku)
		Bluetooth_Vibrate1();

	if(data.Buttons.BIT.Shikaku)
		Bluetooth_Vibrate2();

	if(data.Buttons.BIT.L1)
		DIO1_On();

	if(data.Buttons.BIT.L2)
		DIO1_Off();

	if(data.Buttons.BIT.R1)
		DIO2_On();

	if(data.Buttons.BIT.R2)
		DIO2_Off();

	if(data.Buttons.BIT.UpArrow)
	{
		Motor5_DutyIn(1.0, RobotCore);
	}
	else if(data.Buttons.BIT.DownArrow)
	{
		Motor5_DutyIn(-1.0, RobotCore);
	}
	else
	{
		Motor5_DutyIn(0.0, RobotCore);
	}

	_SDWORD _stick_l_h = -data.AnalogL.X * 0.55;
	_SDWORD _stick_l_v = data.AnalogL.Y * 0.55;
	_SDWORD _stick_r_h = -data.AnalogR.X * 0.55;
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

	Servo1_RotationIn(data.AnalogR.Y, RobotCore);
}

