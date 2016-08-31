/*
 * LED.h
 *
 *  Created on: 2016/08/31
 *      Author: Matsutomo2
 */

#ifndef MODULES_LED_H_
#define MODULES_LED_H_


#ifdef __cplusplus
extern "C" {
#endif

void LED_Activate(void);

void LED_R_On(void);
void LED_G_On(void);
void LED_B_On(void);
void LED_Info_On(void);
void LED_Error_On(void);

void LED_R_Off(void);
void LED_G_Off(void);
void LED_B_Off(void);
void LED_Info_Off(void);
void LED_Error_Off(void);


#ifdef __cplusplus
}
#endif


#endif /* MODULES_LED_H_ */
