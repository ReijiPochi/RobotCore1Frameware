
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

#define FORKLIFT
#define BIGFORK
//#define LITTLEFORK
//#define DOLLY
//#define BRIDGE

static void BluetoothCallback(DUALSHOCK3 data);
static void Timer2Callback(void);
static void StartAimMode(void);
static void EndAimMode(void);
static void Sleep(void);

bool dualshockConnecting = false;
_SBYTE actCount = 50;
float buffer[100];
float buffer2[10];
float buffer3[10];
_SBYTE sumpleCount = 0;
bool isStandby = true;
bool ArmDown = false;
bool ArmUpForce = false;
bool waitingForStop = false;
bool motorMoving = false;
bool pumpOnL = false;
bool pumpOnR = false;
bool pumpHold = false;
_SBYTE autoUpCount = 0;
bool isAimMode = false;
bool dollyL_turned = false;
bool dollyL_clicked = false;

float floors[] = {0.75, 1.15};
_SBYTE currentFloor = -1;
_SBYTE targetFloor = -1;

float deltaL[] = {0.0, 0.0}, deltaR[] = {0.0, 0.0};
float integralL = 0.0, integralR = 0.0;


void Initialize()
{
	_LED_B_On();

	Motor_Activate();
	AnalogIN_Activate();
	AnalogOUT_Activate();
	Buzzer_Activate();
	Servo_Activate();
	Servo1_RotationIn(0.0, RobotCore);
	Servo2_RotationIn(0.0, RobotCore);
	DataLogger_Activate();
	DIO_Activate(OUT, OUT, OUT, IN);

	Timer2_Set(TimerClock_32, 5000, Timer2Callback);
	Timer2_Start();

	Bluetooth_Activate(BluetoothCallback);

	EndAimMode();
	Motor5_AccelerationIn(0.03, RobotCore);

	Buzzer_StepUp();
}

void MainLoop()
{
}

void _SystemClockCallBack()
{
	if(dualshockConnecting)
	{
		actCount--;

		if(actCount <= 0)
		{
			dualshockConnecting = false;
			actCount = 50;
			Sleep();
			_LED_R_On();
			Buzzer_Siren2();
		}
	}

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

	buffer2[0] = AnalogIN_GetVoltage(2);
	buffer3[0] = AnalogIN_GetVoltage(3);

	for(_SBYTE i =9; i > 0; i--)
	{
		buffer2[i] = buffer2[i - 1];
		buffer3[i] = buffer3[i - 1];
	}



	if(motorMoving || !ArmDown || (!pumpOnL && !pumpOnR) || pumpHold)
	{
		sumpleCount = 0;
		return;
	}

	for(_SBYTE i =99; i > 0; i--)
	{
		buffer[i] = buffer[i - 1];
	}


	buffer[0] = AnalogIN_GetVoltage(1);

	if(sumpleCount < 100)
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

	if(pumpCurrent > abeCurrent + 0.015)	// max 0.2
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
	if(actCount < 50)
		actCount = 50;

	if(data.Buttons.BIT.Start)
	{
		Motor_UnlockSTBY();

		Buzzer_Siren1();
		_LED_B_Off();
		_LED_G_On();

		isStandby = false;
		dualshockConnecting = true;
	}

	if(data.Buttons.BIT.Select)
	{
		Sleep();

		Buzzer_StepDown();
		_LED_B_On();

		isStandby = true;
	}

	if(isStandby)
	{
		return;
	}

#ifdef FORKLIFT

	if(data.Buttons.BIT.Maru)
	{

	}

	if(data.Buttons.BIT.Batsu)
	{
		Motor5_DutyIn(0.0, RobotCore);
		ArmDown = false;
		ArmUpForce = false;
		autoUpCount = 0;

		if(pumpOnL || pumpOnR)
			pumpHold = true;

#ifdef BIGFORK
		if(isAimMode) EndAimMode();
#endif

#ifdef LITTLEFORK
		if(!pumpOnR && !pumpOnL)
			DIO3_Off();
#endif
	}

	if(data.Buttons.BIT.Sankaku)
	{
#ifdef BIGFORK
		StartAimMode();
#endif

#ifdef LITTLEFORK
		DIO3_On();
#endif
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
		Motor5_AccelerationIn(0.03, RobotCore);
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

	if(stick_l_h != 0 || stick_l_v != 0 || stick_r_h != 0 || stick_r_v != 0)
	{
		motorMoving = true;
	}
	else
	{
		motorMoving = false;
	}

#ifdef BIGFORK

	stick_l_h *= 0.8;
	stick_l_v *= 0.8;
	stick_r_h *= 0.8;

#endif

#ifdef LITTLEFORK

	stick_l_h *= 0.9;
	stick_l_v *= 0.9;
	stick_r_h *= 0.9;

#endif

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
		if(stick_l_h * stick_l_h < 100)
			stick_l_h = 0;

		if(stick_l_v * stick_l_v < 900)
			stick_l_v = 0;

		if(stick_r_h * stick_r_h < 900)
			stick_r_h = 0;

#ifdef BIGFORK

		float distL, distR;
		float moveL = 0.0, moveR = 0.0;
#define TRG_DIST (1.9)
#define KP (0.2)
#define KI (0.01)
#define KD (0.00)

		if(stick_l_v < -30 || stick_l_h != 0)
		{
			float vL = 0.0, vR = 0.0;

			for(_SBYTE i = 0; i < 9; i++)
			{
				vL += buffer2[i];
			}

			for(_SBYTE i = 0; i < 9; i++)
			{
				vR += buffer3[i];
			}

			vL /= 10.0;
			vR /= 10.0;


			float pL, iL ,dL, pR, iR, dR;

			deltaL[1] = deltaL[0];
			deltaR[1] = deltaR[0];

			deltaL[0] = TRG_DIST - vL;
			deltaR[0] = TRG_DIST - vR;

			integralL = (deltaL[0] + deltaL[1]) / 2.0;
			integralR = (deltaR[0] + deltaR[1]) / 2.0;

			pL = KP * deltaL[0];
			iL = KI * integralL;
			dL = KD * (deltaL[0] - deltaL[1]);
			moveL = pL + iL + dL;

			pR = KP * deltaR[0];
			iR = KI * integralR;
			dR = KD * (deltaR[0] - deltaR[1]);
			moveR = pR + iR + dR;

			if(moveL > 0.4)
				moveL = 0.4;
			else if(moveL < -0.4)
				moveL = -0.4;

			if(moveR > 0.4)
				moveR = 0.4;
			else if(moveR < -0.4)
				moveR = -0.4;
//
//			distL = TRG_DIST - vL;
//			distR = TRG_DIST - vR;
//
//			distL *= 0.3;
//			distR *= 0.3;
//
//			moveL = distL > 0.2 ? 0.2 : distL;
//			moveR = distR > 0.2 ? 0.2 : distR;
		}

		if(stick_l_v > 30)
		{
			moveL = -stick_l_v / 300.0;
			moveR = -stick_l_v / 300.0;
		}

		float moveH = stick_l_h / 300.0;

		Motor1_DutyIn(moveH + moveR, RobotCore);
		Motor2_DutyIn(moveH - moveL, RobotCore);
		Motor3_DutyIn(-moveH - moveL, RobotCore);
		Motor4_DutyIn(-moveH + moveR, RobotCore);

#endif

#ifdef LITTLEFORK

		Motor1_DutyIn(-(stick_l_v - stick_l_h - stick_r_h) / 64.0, RobotCore);
		Motor2_DutyIn((stick_l_v + stick_l_h + stick_r_h) / 64.0, RobotCore);
		Motor3_DutyIn((stick_l_v - stick_l_h + stick_r_h) / 64.0, RobotCore);
		Motor4_DutyIn(-(stick_l_v + stick_l_h - stick_r_h) / 64.0, RobotCore);

#endif

	}

#endif

#ifdef DOLLY

	if(dollyL_clicked && !data.Buttons.BIT.Maru)
	{
		dollyL_turned = true;
		dollyL_clicked = false;
	}

	if(data.Buttons.BIT.Maru)
	{
		if(dollyL_turned)
		{
			Servo2_RotationIn(80.0, RobotCore);
		}
		else
		{
			Servo1_RotationIn(80.0, RobotCore);
			dollyL_clicked = true;
		}
	}
	else if(data.Buttons.BIT.Shikaku)
	{
		Servo1_RotationIn(0.0, RobotCore);
		Servo2_RotationIn(0.0, RobotCore);
		dollyL_turned = false;
		dollyL_clicked = false;
	}

	if(data.Buttons.BIT.Sankaku)
	{
		StartAimMode();
	}

	if(data.Buttons.BIT.Batsu)
	{
		if(isAimMode) EndAimMode();
	}

	if(data.Buttons.BIT.L1 || data.Buttons.BIT.R1)
	{
		DIO1_On();
	}
	else if(data.Buttons.BIT.L2 || data.Buttons.BIT.R2)
	{
		DIO1_Off();
		if(isAimMode) EndAimMode();
	}

	if(isAimMode)
	{
		Motor1_AccelerationIn(0.05, RobotCore);
		Motor1_DutyIn(-data.AnalogL.Y / 256.0, RobotCore);
	}
	else
	{
		Motor1_AccelerationIn(0.3, RobotCore);
		Motor1_DutyIn(-data.AnalogL.Y / 64.0, RobotCore);
	}

#endif

#ifdef BRIDGE

	Motor3_DutyIn(data.AnalogR.Y / 64.0, RobotCore);

	if(data.Buttons.BIT.UpArrow)
	{
		Motor1_DutyIn(-1.0, RobotCore);
		Motor2_DutyIn(1.0, RobotCore);
	}
	else if(data.Buttons.BIT.DownArrow)
	{
		Motor1_DutyIn(1.0, RobotCore);
		Motor2_DutyIn(-1.0, RobotCore);
	}
	else
	{
		Motor1_DutyIn(0.0, RobotCore);
		Motor2_DutyIn(0.0, RobotCore);
	}

#endif
}

void StartAimMode(void)
{
	Motor1_AccelerationIn(0.1, RobotCore);
	Motor2_AccelerationIn(0.1, RobotCore);
	Motor3_AccelerationIn(0.1, RobotCore);
	Motor4_AccelerationIn(0.1, RobotCore);

	Bluetooth_Vibrate1Long();
	Buzzer_OneTime(1000);
	isAimMode = true;
}

void EndAimMode(void)
{
#ifdef BIGFORK

	Motor1_AccelerationIn(0.05, RobotCore);
	Motor2_AccelerationIn(0.05, RobotCore);
	Motor3_AccelerationIn(0.05, RobotCore);
	Motor4_AccelerationIn(0.05, RobotCore);

#endif

#ifdef LITTLEFORK

	Motor1_AccelerationIn(0.03, RobotCore);
	Motor2_AccelerationIn(0.03, RobotCore);
	Motor3_AccelerationIn(0.03, RobotCore);
	Motor4_AccelerationIn(0.03, RobotCore);

#endif

#ifdef DOLLY

	Motor1_AccelerationIn(0.3, RobotCore);

#endif

	isAimMode = false;
	Bluetooth_Vibrate1();
	Buzzer_StepUp();
}

void Sleep(void)
{
	Motor1_DutyIn(0.0, RobotCore);
	Motor2_DutyIn(0.0, RobotCore);
	Motor3_DutyIn(0.0, RobotCore);
	Motor4_DutyIn(0.0, RobotCore);
	Motor5_DutyIn(0.0, RobotCore);

	Motor_LockSTBY();
}

