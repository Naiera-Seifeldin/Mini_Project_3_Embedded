/******************************************************************************
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for PWM driver
 *
 * Author: Naiera Seifeldin
 ******************************************************************************/

/********************************* Includes ***********************************/
#include "pwm.h"
#include "gpio.h"
#include <avr/io.h> /* For timer0 registers access */

/*************************** Functions definitions ****************************/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0; /* Set Timer Initial Value to 0 */

	/* IMP NOTE: the passed duty cycle is the percentage, so to get the duty cycle
	 * value (number) used in compare for PWM ,, we need to this calculation
	 * 0           ---> 0 %
	 * 255         ---> 100 %
	 * OCR0 value  ---> duty cycle percentage
	 * OCR0 value  = ((duty cycle percentage * 255) / 100) */

	OCR0  = (((uint32)(duty_cycle*255))/100); /* (uint32) to avoid overflow of multiplication */

	/*
	 * Configure Timer0 control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

	/* Set OC0 as output pin */
	GPIO_setupPinDirection(OCO_PORT,OCO_PIN,PIN_OUTPUT);
}
