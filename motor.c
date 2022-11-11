/******************************************************************************
 * Module: DC Motor
 *
 * File Name: motor.c
 *
 * Description: source file for DC Motor driver
 *
 * Author: Naiera Seifeldin
 ******************************************************************************/

/********************************* Includes ***********************************/
#include "motor.h"
#include "pwm.h"
#include "gpio.h"

/*************************** Functions definitions ****************************/

void DcMotor_Init(void)
{
	/* Make 2 pins of PORTB output to be used as input for H-bridge */
	GPIO_setupPinDirection(PORT_OF_MOTOR,MOTOR_PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_OF_MOTOR,MOTOR_PIN2_ID,PIN_OUTPUT);

	/* Initialize motor as stopped at beginning */
	GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN1_ID,LOGIC_LOW);
	GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN2_ID,LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state == CW)
	{
		/* if direction sent was CW, we write 01 to input pins */
		GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN2_ID,LOGIC_HIGH);
		/* to start PWM in timer0 with required duty cycle */
		PWM_Timer0_Start(speed);
	}
	else if(state == A_CW)
	{
		/* if direction sent was A_CW, we write 10 to input pins */
		GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN1_ID,LOGIC_HIGH);
		GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN2_ID,LOGIC_LOW);
		/* to start PWM in timer0 with required duty cycle */
		PWM_Timer0_Start(speed);
	}
	else if(state == STOP)
	{
		/* if direction sent was STOP, we write 00 to input pins */
		GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN1_ID,LOGIC_LOW);
		GPIO_writePin(PORT_OF_MOTOR,MOTOR_PIN2_ID,LOGIC_LOW);
		/* to start PWM in timer0 with required duty cycle */
		PWM_Timer0_Start(speed);
	}
}

