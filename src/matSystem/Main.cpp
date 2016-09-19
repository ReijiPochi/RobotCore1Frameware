/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  RobotCore1Framework                    */
/*      FILE         :  RobotCore1Framework.cpp                */
/*      DESCRIPTION  :  Main Program                           */
/*      CPU SERIES   :  RX600                                  */
/*      CPU TYPE     :  RX63T                                  */
/*                                                             */
/*      This file is generated by e2 studio.                   */
/*                                                             */
/***************************************************************/                              

//#include "typedefine.h"
#include "../UserApplication/App.h"

#include "BatteryCheck.h"
#include "Connecter.h"
#include "System.h"

#include "..\Modules\Timer.h"
#include "..\Modules\Motor.h"
#include "..\Modules\Battery.h"
#include "..\Modules\LED.h"
#include "..\Modules\Buzzer.h"
#include "..\Modules\DataLogger.h"
#include "..\Modules\Bluetooth.h"
#include "..\Modules\AnalogIN.h"


void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
static void Timer1_Callback(void);
}
#endif

/**
 *  メイン関数
 */
void main(void)
{
	_LED_Activate();

	Initialize();

	_Battery_Activate();

	_Timer_Activate();
	_Timer1_Set(TimerClock_32, 10000, Timer1_Callback);
	_Timer1_Start();

	_Connecter_Activate();

	while(true)
	{
		MainLoop();
	}
}

bool timer1_callbackRunning = false;

void Timer1_Callback()
{
	if(timer1_callbackRunning)
	{
		_LED_Error_On();
		Buzzer_Siren2();
	}

	timer1_callbackRunning = true;

	_System_Loop();

	BatteryCheck();
	_Bluetooth_Loop();
	_Motor_Loop();
	_Battery_Sample();
	_Buzzer_Loop();
	_DataLogger_Loop();

	_Connecter_Recieve();
	_Connecter_Transmit();

	_SystemClockCallBack();

	timer1_callbackRunning = false;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
