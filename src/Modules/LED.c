/*
 * LED.c
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */


#include "LED.h"
#include "micon\IO.h"

void LED_Activate(void)
{
	IO_LED_init();
}

void LED_R_On(void)
{
	LED_STATUS_R(1);
}

void LED_G_On(void)
{
	LED_STATUS_G(1);
}

void LED_B_On(void)
{
	LED_STATUS_B(1);
}

void LED_Info_On(void)
{
	LED_INFO(1);
}

void LED_Error_On(void)
{
	LED_ERROR(1);
}

void LED_R_Off(void)
{
	LED_STATUS_R(0);
}

void LED_G_Off(void)
{
	LED_STATUS_G(0);
}

void LED_B_Off(void)
{
	LED_STATUS_B(0);
}

void LED_Info_Off(void)
{
	LED_INFO(0);
}

void LED_Error_Off(void)
{
	LED_ERROR(0);
}
