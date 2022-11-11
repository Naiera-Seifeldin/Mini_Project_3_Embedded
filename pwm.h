/******************************************************************************
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for PWM driver
 *
 * Author: Naiera Seifeldin
 ******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

/********************************* Includes ***********************************/
#include "std_types.h"

/******************************** Definitions *********************************/
/* Used pins and port for Timer0_PWM */
#define OCO_PORT    PORTB_ID
#define OCO_PIN     PIN3_ID

/**************************** Functions prototypes ****************************/

/*  1-The function responsible for trigger the Timer0 with the PWM Mode.
 *	2-Setup the PWM mode with Non-Inverting.
 *	3-Setup the prescaler with F_CPU/8.
 *	4-Setup the compare value based on the required input duty cycle
 *	5-Setup the direction for OC0 as output pin through the GPIO driver.
 *	6-The generated PWM signal frequency will be 500Hz to control the DC Motor speed */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
