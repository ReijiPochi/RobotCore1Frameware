
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
#include "..\Modules\Timer.h"

#include "..\matSystem\Connecter.h"
#include "..\matSystem\System.h"

//#define BIGFORK
//#define LITTLEFORK
#define DOLLY

static void BluetoothCallback(DUALSHOCK3 data);
static void Timer2Callback(void);
static void StartAimMode(void);
static void EndAimMode(void);

float buffer[100];
_SBYTE sumpleCount = 0;
bool ArmDown = false;
bool ArmUpForce = false;
bool waitingForStop = false;
bool pumpOnL = false;
bool pumpOnR = false;
bool pumpHold = false;
_SBYTE autoUpCount = 0;
bool isAimMode = false;

void Initialize()
{
	_LED_B_On();

	Motor_Activate();
	Motor5_AccelerationIn(0.03, RobotCore);
	AnalogIN_Activate();
	AnalogOUT_Activate();
	Buzzer_Activate();
	Servo_Activate();
	DataLogger_Activate();
	DIO_Activate(OUT, OUT, IN, IN);

	Timer2_Set(TimerClock_32, 5000, Timer2Callback);
	Timer2_Start();

	Bluetooth_Activate(BluetoothCallback);
	//System_ClockStart();

	Buzzer_StepUp();
}

void MainLoop()
{
}

void _SystemClockCallBack()
{
	if(autoUpCount != 0)
	{
		Motor5_AccelerationIn(0.4, RobotCore);
		Motor5_DutyIn(0.5, RobotCore);

		autoUpCount--;

		if(autoUpCount == 0)
		{
			Motor5_AccelerationIn(0.03, RobotCore);
			Motor5_DutyIn(0.0, RobotCore);
		}
	}

}

void Timer2Callback(void)
{
	AnalogIN_Sample();

	for(_SBYTE i =99; i > 0; i--)
	{
		buffer[i] = buffer[i - 1];
	}

	buffer[0] = AnalogIN_GetVoltage(1);

	if(!pumpOnL && !pumpOnR)
		sumpleCount = 0;

	if((pumpOnL || pumpOnR) && sumpleCount < 100)
	{
		sumpleCount++;
		return;
	}

	float pumpCurrent = 0.0;
	for(_SBYTE i = 0; i < 10; i++)
	{
		pumpCurrent += buffer[i];
	}
	pumpCurrent /= 10.0;

	float abeCurrent = 0.0;
	for(_SBYTE i = 10; i < 100; i++)
	{
		abeCurrent += buffer[i];
	}
	abeCurrent /= 90.0;

	if(pumpCurrent > abeCurrent + 0.01 && ArmDown && (pumpOnL || pumpOnR) && !pumpHold)
	{
		Motor5_DutyIn(1.0, RobotCore);
		Bluetooth_Vibrate2();
		ArmDown = false;
		ArmUpForce = true;
		pumpHold = true;
	}
}

static void BluetoothCallback(DUALSHOCK3 data)
{

	if(data.Buttons.BIT.Start)
	{
		Motor_UnlockSTBY();

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

#ifdef BIGFORK

	if(data.Buttons.BIT.Maru)
	{

	}

	if(data.Buttons.BIT.Batsu)
	{
		Motor5_DutyIn(0.0, RobotCore);
		ArmDown = false;
		ArmUpForce = false;
		autoUpCount = 0;

		if(isAimMode) EndAimMode();
	}

	if(data.Buttons.BIT.Sankaku)
	{
		StartAimMode();
	}

	if(data.Buttons.BIT.Shikaku)
	{

	}

	if(data.Buttons.BIT.L1)
	{
		DIO1_On();
		pumpOnL = true;
	}

	if(data.Buttons.BIT.L2)
	{
		DIO1_Off();
		pumpOnL = false;
		if(pumpHold)
		{
			autoUpCount = 30;
			if(isAimMode) EndAimMode();
		}
		pumpHold = false;
	}

	if(data.Buttons.BIT.R1)
	{
		DIO2_On();
		pumpOnR = true;
	}

	if(data.Buttons.BIT.R2)
	{
		DIO2_Off();
		pumpOnR = false;
		if(pumpHold)
		{
			autoUpCount = 30;
			if(isAimMode) EndAimMode();
		}
		pumpHold = false;
	}

	if(data.Buttons.BIT.UpArrow)
	{
		Motor5_DutyIn(1.0, RobotCore);
		ArmDown = false;
		ArmUpForce = false;
	}
	else if(data.Buttons.BIT.DownArrow)
	{
		if(!ArmUpForce || waitingForStop)
		{
			if(!pumpHold && (pumpOnL || pumpOnR))
			{
				Motor5_AccelerationIn(0.4, RobotCore);
				Motor5_DutyIn(-0.3, RobotCore);
			}
			else
			{
				Motor5_AccelerationIn(0.03, RobotCore);
				Motor5_DutyIn(-1.0, RobotCore);
			}

			ArmDown = true;
			ArmUpForce = false;
			waitingForStop = false;
		}
	}
	else
	{
		if(!ArmUpForce)
		{
			Motor5_DutyIn(0.0, RobotCore);
			ArmDown = false;
			ArmUpForce = false;
		}
		else if(!waitingForStop)
		{
			waitingForStop = true;
		}
	}

	_SDWORD stick_l_h = -data.AnalogL.X;
	_SDWORD stick_l_v = data.AnalogL.Y;
	_SDWORD stick_r_h = -data.AnalogR.X;
	_SDWORD stick_r_v = data.AnalogR.Y;

	if(!isAimMode)
	{
		_SDWORD stick_l_h_2;
		_SDWORD stick_l_v_2;
		_SDWORD stick_r_h_2;

		if(stick_l_h > 0) stick_l_h_2 = stick_l_h * stick_l_h / 64;
		else stick_l_h_2 = stick_l_h * stick_l_h / -64;

		if(stick_l_v > 0) stick_l_v_2 = stick_l_v * stick_l_v / 64;
		else stick_l_v_2 = stick_l_v * stick_l_v / -64;

		if(stick_r_h > 0) stick_r_h_2 = stick_r_h * stick_r_h / 64;
		else stick_r_h_2 = stick_r_h * stick_r_h / -64;

		Motor1_DutyIn(-(stick_l_v_2 - stick_l_h_2 - stick_r_h_2) / 64.0, RobotCore);
		Motor2_DutyIn((stick_l_v_2 + stick_l_h_2 + stick_r_h_2) / 64.0, RobotCore);
		Motor3_DutyIn((stick_l_v_2 - stick_l_h_2 + stick_r_h_2) / 64.0, RobotCore);
		Motor4_DutyIn(-(stick_l_v_2 + stick_l_h_2 - stick_r_h_2) / 64.0, RobotCore);
	}
	else
	{
		if(stick_l_h * stick_l_h < 1600)
			stick_l_h = 0;

		if(stick_l_v * stick_l_v < 1600)
			stick_l_v = 0;

		if(stick_r_h * stick_r_h < 1600)
			stick_r_h = 0;

		Motor1_DutyIn(-(stick_l_v - stick_l_h - stick_r_h) / 500.0, RobotCore);
		Motor2_DutyIn((stick_l_v + stick_l_h + stick_r_h) / 500.0, RobotCore);
		Motor3_DutyIn((stick_l_v - stick_l_h + stick_r_h) / 500.0, RobotCore);
		Motor4_DutyIn(-(stick_l_v + stick_l_h - stick_r_h) / 500.0, RobotCore);

		Motor5_AccelerationIn(0.1, RobotCore);
		Motor5_DutyIn(-stick_r_v / 100.0, RobotCore);
	}

#endif

#ifdef DOLLY

	Motor1_DutyIn(data.AnalogL.Y / 64.0, RobotCore);

	if(data.Buttons.BIT.Maru)
	{
		Servo1_RotationIn(90.0, RobotCore);
		Servo2_RotationIn(90.0, RobotCore);
	}
	else if(data.Buttons.BIT.Shikaku)
	{
		Servo1_RotationIn(0.0, RobotCore);
		Servo2_RotationIn(0.0, RobotCore);
	}

#endif
}

void StartAimMode(void)
{
	Bluetooth_Vibrate1Long();
	Buzzer_OneTime(1000);
	isAimMode = true;
}

void EndAimMode(void)
{
	isAimMode = false;
	Bluetooth_Vibrate1();
	Buzzer_StepUp();
}

