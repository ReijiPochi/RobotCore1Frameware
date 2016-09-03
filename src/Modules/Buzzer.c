/*
 * Buzzer.c
 *
 *  Created on: 2016/09/03
 *      Author: Matsutomo2
 */


#include "Buzzer.h"
#include "micon/GPT46.h"

_UWORD oneTime = 0;
_UWORD stepUp = 0;
_UWORD stepDown = 0;
_UWORD siren1 = 0, siren1Fq = 500;

void Buzzer_Activate(void)
{
	GPT46_init();
}

void _Buzzer_Loop(void)
{
	if(oneTime != 0)
	{
		if(oneTime == 1)
			BUZZER_Off();

		oneTime--;
	}

	if(stepUp != 0)
	{
		switch(stepUp)
		{
			case 20:
				BUZZER_set(700, 0.5);
				break;

			case 10:
				BUZZER_set(1046, 0.5);
				break;

			case 1:
				BUZZER_Off();
				break;

			default:
				break;
		}

		stepUp--;
	}

	if(stepDown != 0)
	{
		switch(stepDown)
		{
			case 20:
				BUZZER_set(700, 0.5);
				break;

			case 10:
				BUZZER_set(523, 0.5);
				break;

			case 1:
				BUZZER_Off();
				break;

			default:
				break;
		}

		stepDown--;
	}

	if(siren1 != 0)
	{
		if(siren1 == 20)
			siren1Fq = 300;

		BUZZER_set(siren1Fq, 0.5);
		BUZZER_On();

		siren1Fq += 70;

		if(siren1 == 1)
		{
			BUZZER_Off();
			siren1Fq = 300;
		}

		siren1--;
	}
}

void Buzzer_On(void)
{
	BUZZER_set(700, 0.5);
	BUZZER_On();
}

void Buzzer_Off(void)
{
	if(oneTime != 0 || stepUp != 0 || stepDown != 0 || siren1 != 0)
		return;

	BUZZER_Off();
}

void Buzzer_OneTime(_UWORD ms)
{
	if(oneTime != 0)
		return;

	BUZZER_set(850, 0.5);
	BUZZER_On();
	oneTime = ms / 10 - 1;
}

void Buzzer_StepUp(void)
{
	if(stepUp != 0)
		return;

	BUZZER_set(523, 0.5);
	BUZZER_On();
	stepUp = 30;
}

void Buzzer_StepDown(void)
{
	if(stepDown != 0)
		return;

	BUZZER_set(1046, 0.5);
	BUZZER_On();
	stepDown = 30;
}

void Buzzer_Siren1(void)
{
	if(siren1 != 0)
		return;

	BUZZER_set(500, 0.5);
	BUZZER_On();
	siren1 = 40;
}
