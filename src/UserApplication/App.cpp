
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
#include "..\Modules\Multi.h"

#include "..\matSystem\Connecter.h"
#include "..\matSystem\System.h"

#define FORKLIFT
#define BIGFORK
//#define LITTLEFORK
//#define TW_LITTLEFORK
//#define DOLLY
//#define BRIDGE

static void BluetoothCallback(DUALSHOCK3 data);
static void Timer2Callback(void);
static void DIO3Callback(void);
static void MotorErrorCallack(void);
static void StartAimMode(void);
static void EndAimMode(void);
static void Sleep(void);


bool SystemStandby = true;
bool motorMoving = false;
bool dualshockConnecting = false;
_SBYTE actCount = 50;

float AIN1buffer[100];
float startCurrent = 0.0;
float AIN2buffer2[10];
float AIN3buffer3[10];
_SWORD AIN1sumpleCount = 0;

bool ArmDown = false;
bool ArmUpForce = false;
bool waitingForStop = false;

bool pumpOnL = false;
bool pumpOnR = false;
bool pumpHold = false;
_SBYTE autoUpCount = 0;

bool isAimMode = false;

bool dollyL_turned = false;
bool dollyL_clicked = false;

//_UBYTE floars[] = {0, 27, 47, 67, 87, 107};
//_SBYTE rotationCount = -1;
//_SBYTE currentFloor = 0;
//_SBYTE targetFloor = 0;
//float fdelta[] = {0.0, 0.0};
//bool allowUp = false;
//bool UpPressed = false;
//bool DownPressed = false;

float deltaL[] = {0.0, 0.0}, deltaR[] = {0.0, 0.0};
float integralL = 0.0, integralR = 0.0;

bool bridgeMode = false;


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
	Multi1_Activate(AllIO);

#ifdef BIGFORK
	DIO_Activate(OUT, OUT, IN, IN);
//	DIO_SetInterrupt(DIO3Callback);
#endif
#ifdef LITTLEFORK
	DIO_Activate(OUT, OUT, OUT, IN);
	//Motor_SetErrorCallback(MotorErrorCallack);
#endif
#ifdef DOLLY
	DIO_Activate(OUT, IN, IN, IN);
	//Motor_SetErrorCallback(MotorErrorCallack);
#endif
#ifdef BRIDGE
	DIO_Activate(IN, IN, IN, IN);
#endif

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
//#ifdef BIGFORK
//	if(allowUp)
//	{
//		float p, move;
//
//		fdelta[1] = fdelta[0];
//		fdelta[0] = floars[targetFloor] - rotationCount;
//
//		p = 0.1 * fdelta[0];
//		move = p;
//
//		if(move > 1.0)
//			move = 1.0;
//		else if(move < -0.8)
//			move = -0.8;
//		else if(move < 0.1 && move > -0.1)
//			move = 0;
//
//		Motor5_AccelerationIn(0.03, RobotCore);
//		Motor5_DutyIn(move, RobotCore);
//	}
//#endif

	AnalogIN_Sample();

	AIN2buffer2[0] = AnalogIN_GetVoltage(2);
	AIN3buffer3[0] = AnalogIN_GetVoltage(3);

	for(_SBYTE i =9; i > 0; i--)
	{
		AIN2buffer2[i] = AIN2buffer2[i - 1];
		AIN3buffer3[i] = AIN3buffer3[i - 1];
	}


#ifdef FORKLIFT
#ifdef BIGFORK
	if(motorMoving || !ArmDown || (!pumpOnL && !pumpOnR) || pumpHold)
	{
		AIN1sumpleCount = 0;
		return;
	}
#else
	if(motorMoving || (!pumpOnL && !pumpOnR) || pumpHold)
	{
		AIN1sumpleCount = 0;
		return;
	}
#endif
#endif
#ifdef DOLLY
	if((!pumpOnL && !pumpOnR) || pumpHold)
	{
		AIN1sumpleCount = 0;
		return;
	}
#endif

	for(_SBYTE i =99; i > 0; i--)
	{
		AIN1buffer[i] = AIN1buffer[i - 1];
	}


	AIN1buffer[0] = AnalogIN_GetVoltage(1);

	if(AIN1sumpleCount < 200)
	{
		AIN1sumpleCount++;
		return;
	}

	float pumpCurrent = 0.0;
	for(_SBYTE i = 0; i < 10; i++)
	{
		pumpCurrent += AIN1buffer[i];
	}
	pumpCurrent /= 10.0;

	if(AIN1sumpleCount == 200)
	{
		AIN1sumpleCount++;
		startCurrent = 0.0;
		for(_SBYTE i = 0; i < 100; i++)
		{
			startCurrent += AIN1buffer[i];
		}
		startCurrent /= 100.0;
	}

	float th = 0.015;

#ifdef LITTLEFORK
	th = 0.012;
#endif
#ifdef BIGFORK
	th = 0.015;
#endif

	if(pumpCurrent > startCurrent + th)	// max 0.2
	{
		ArmDown = false;
		ArmUpForce = true;
		pumpHold = true;
		Bluetooth_Vibrate2();

#ifdef FORKLIFT
//#ifdef LITTLEFORK
		Motor5_DutyIn(1.0, RobotCore);
//#endif

#ifdef BIGFORK
		Motor5_AccelerationIn(0.025, RobotCore);
//		rotationCount = 0;
//		targetFloor = 1;
//		if(!isAimMode)
//		{
//			allowUp = true;
//		}
//		else
//		{
//			Motor5_DutyIn(0.7, RobotCore);
//		}
#endif
#ifdef LITTLEFORK
		Motor5_AccelerationIn(0.1, RobotCore);
#endif
#endif

#ifdef DOLLY
		Multi1_DOUT3(H);
#endif
	}
}

void DIO3Callback(void)
{
//	if(Motor5_GetDuty() == 0)
//		return;
//
//	if(Motor5_GetDirection())
//	{
//		rotationCount++;
//	}
//	else
//	{
//		rotationCount--;
//	}
}

void MotorErrorCallack(void)
{
	SystemStandby = true;
	Bluetooth_Vibrate1();
	Motor_LockSTBY();
	for(_UWORD c = 0; c < 50000; c++)
	{
		actCount = 50;
		;;;;
	}
	Motor_UnlockSTBY();
	SystemStandby = false;
}

static void BluetoothCallback(DUALSHOCK3 data)
{
	actCount = 50;

	if(data.Buttons.BIT.Start)
	{
		Motor_UnlockSTBY();

		Buzzer_Siren1();
		_LED_B_Off();
		_LED_G_On();

		SystemStandby = false;
		dualshockConnecting = true;

//		rotationCount = 0;
	}

	if(data.Buttons.BIT.Select)
	{
		Sleep();

		Buzzer_StepDown();
		_LED_B_On();

		SystemStandby = true;
	}

	if(SystemStandby)
	{
		return;
	}

#ifdef FORKLIFT

	if(data.Buttons.BIT.Maru)
	{
//#ifdef BIGFORK
//		allowUp = true;
//#endif
#ifdef BIGFORK
		bridgeMode = true;
#endif
	}
	else
	{
#ifdef BIGFORK
		if(bridgeMode && data.AnalogL.X == 0 && data.AnalogL.Y == 0 && data.AnalogR.X == 0)
		{
			bridgeMode = false;
		}
#endif
	}

	if(data.Buttons.BIT.Batsu)
	{
//		allowUp = false;

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
//		allowUp = false;
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
#ifdef BIGFORK
		pumpOnL = true;
#endif
#ifdef LITTLEFORK
		pumpHoldL = true;
#endif
		AIN1sumpleCount = 0;
	}

	if(data.Buttons.BIT.L2)
	{
//		allowUp = false;
		DIO1_Off();
		pumpOnL = false;
		if(pumpHold)
		{
			autoUpCount = 60;
		}
		pumpHold = false;
		if(!pumpOnR && isAimMode) EndAimMode();
	}

	if(data.Buttons.BIT.R1)
	{
		DIO2_On();
#ifdef BIGFORK
		pumpOnL = true;
#endif
#ifdef LITTLEFORK
		pumpHoldL = true;
#endif
		AIN1sumpleCount = 0;
	}

	if(data.Buttons.BIT.R2)
	{
//		allowUp = false;
		DIO2_Off();
		pumpOnR = false;
		if(pumpHold)
		{
			autoUpCount = 60;
		}
		pumpHold = false;
		if(!pumpOnL && isAimMode) EndAimMode();
	}

	if(data.Buttons.BIT.RightArrow)
	{

	}

	if(data.Buttons.BIT.LeftArrow)
	{

	}

	if(data.Buttons.BIT.UpArrow)
	{
//		if(allowUp)
//		{
//			UpPressed = true;
//		}
//		else
//		{
			Motor5_AccelerationIn(0.03, RobotCore);
			Motor5_DutyIn(1.0, RobotCore);
			ArmDown = false;
			ArmUpForce = false;
//		}
	}
	else if(data.Buttons.BIT.DownArrow)
	{
//		if(allowUp && !ArmUpForce)
//		{
//			DownPressed = true;
//		}
//		else
		if(!ArmUpForce || waitingForStop)
		{
			if(!pumpHold && (pumpOnL || pumpOnR))
			{
				Motor5_AccelerationIn(0.4, RobotCore);
#ifdef BIGFORK
				Motor5_DutyIn(-0.3, RobotCore);
#else
				Motor5_DutyIn(-0.3, RobotCore);
#endif
			}
			else
			{
				Motor5_AccelerationIn(0.03, RobotCore);

				if(pumpHold) Motor5_DutyIn(-0.6, RobotCore);
				else Motor5_DutyIn(-1.0, RobotCore);
			}

			ArmDown = true;
			ArmUpForce = false;
			waitingForStop = false;
		}
	}
	else
	{
//		if(allowUp && !ArmUpForce)
//		{
//			if(UpPressed)
//			{
//				UpPressed = false;
//
//				if(targetFloor < 6)
//					targetFloor++;
//			}
//			else if(DownPressed)
//			{
//				DownPressed = false;
//
//				if(targetFloor > 1)
//					targetFloor--;
//			}
//		}
//		else
			if(!ArmUpForce)
		{
			Motor5_DutyIn(0.0, RobotCore);
			ArmDown = false;
			ArmUpForce = false;
		}
		else if(!waitingForStop)
		{
//#ifdef BIGFORK
//			ArmUpForce = false;
//#endif
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

	if(bridgeMode)
	{
		stick_l_h *= 0.0;
		stick_l_v *= 0.7;
		stick_r_h *= 0.0;
	}
	else
	{
		stick_l_h *= 0.8;
		stick_l_v *= 0.8;
		stick_r_h *= 0.7;
	}

#endif

#ifdef LITTLEFORK

	stick_l_h *= 0.85;
	stick_l_v *= 1.0;
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

		float move1 = 0.0, move2 = 0.0, move3 = 0.0, move4 = 0.0;

#ifdef TW_LITTLEFORK
#define COS30 (0.6)
		move1 = (-stick_l_v_2 +    stick_l_h_2*COS30   + stick_r_h_2) / 64.0;
		move2 = ( stick_l_v_2 +    stick_l_h_2*COS30    + stick_r_h_2) / 64.0;
		move3 = (      0      - stick_l_h_2 + stick_r_h_2) / 64.0;
#else
		move1 = -(stick_l_v_2 - stick_l_h_2 - stick_r_h_2) / 64.0;
		move2 = (stick_l_v_2 + stick_l_h_2 + stick_r_h_2) / 64.0;
		move3 = (stick_l_v_2 - stick_l_h_2 + stick_r_h_2) / 64.0;
		move4 = -(stick_l_v_2 + stick_l_h_2 - stick_r_h_2) / 64.0;
#endif

#ifdef LITTLEFORK
#define MAX (0.75)
#endif

#ifdef BIGFORK
#define MAX (1.0)
#endif

		if(move1 > MAX) move1 = MAX;
		if(move1 < -MAX) move1 = -MAX;

		if(move2 > MAX) move2 = MAX;
		if(move2 < -MAX) move2 = -MAX;

		if(move3 > MAX) move3 = MAX;
		if(move3 < -MAX) move3 = -MAX;

		if(move4 > MAX) move4 = MAX;
		if(move4 < -MAX) move4 = -MAX;

		Motor1_DutyIn(move1, RobotCore);
		Motor2_DutyIn(move2, RobotCore);
		Motor3_DutyIn(move3, RobotCore);
		Motor4_DutyIn(move4, RobotCore);
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

		float moveL = 0.0, moveR = 0.0;
#define TRG_DIST (1.9)
#define KP (0.2)
#define KI (0.00)
#define KD (0.00)

		if(stick_l_v < -30 || stick_l_h != 0)
		{
			float vL = 0.0, vR = 0.0;

			for(_SBYTE i = 0; i < 9; i++)
			{
				vL += AIN2buffer2[i];
			}

			for(_SBYTE i = 0; i < 9; i++)
			{
				vR += AIN3buffer3[i];
			}

			vL /= 10.0;
			vR /= 10.0;


			float pL, iL ,dL, pR, iR, dR;

			deltaL[1] = deltaL[0];
			deltaR[1] = deltaR[0];

			deltaL[0] = TRG_DIST - vL;
			deltaR[0] = TRG_DIST - vR;

			integralL += (deltaL[0] + deltaL[1]) / 2.0;
			integralR += (deltaR[0] + deltaR[1]) / 2.0;

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
		}

		if(stick_l_v > 30)
		{
			moveL = -stick_l_v / 300.0;
			moveR = -stick_l_v / 300.0;
		}

		float moveH = stick_l_h / 300.0;
		float moveA = stick_r_h / 500.0;

		Motor1_DutyIn(moveH + moveR + moveA, RobotCore);
		Motor2_DutyIn(moveH - moveL + moveA, RobotCore);
		Motor3_DutyIn(-moveH - moveL + moveA, RobotCore);
		Motor4_DutyIn(-moveH + moveR + moveA, RobotCore);

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
		pumpOnL = true;
		pumpOnR = true;
		DIO1_On();
		Multi1_DOUT1(H);
		Multi1_DOUT2(L);
	}
	else if(data.Buttons.BIT.L2 || data.Buttons.BIT.R2)
	{
		pumpOnL = false;
		pumpOnR = false;
		pumpHold = false;
		DIO1_Off();
		Multi1_DOUT1(L);
		Multi1_DOUT2(H);
		Multi1_DOUT3(L);
		if(isAimMode) EndAimMode();
	}

	if(isAimMode)
	{
		Motor1_AccelerationIn(0.05, RobotCore);
		Motor1_DutyIn(data.AnalogL.Y / 300.0, RobotCore);
	}
	else
	{
		Motor1_AccelerationIn(0.02, RobotCore);
		Motor1_DutyIn(data.AnalogL.Y / 64.0, RobotCore);
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

//	allowUp = false;

#endif

#ifdef LITTLEFORK
#ifdef TW_LITTLEFORK
	Motor1_AccelerationIn(0.03, RobotCore);
	Motor2_AccelerationIn(0.03, RobotCore);
	Motor3_AccelerationIn(0.03, RobotCore);
#else
	Motor1_AccelerationIn(0.025, RobotCore);
	Motor2_AccelerationIn(0.025, RobotCore);
	Motor3_AccelerationIn(0.025, RobotCore);
	Motor4_AccelerationIn(0.025, RobotCore);
#endif
#endif

#ifdef DOLLY

	Motor1_AccelerationIn(0.02, RobotCore);

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

