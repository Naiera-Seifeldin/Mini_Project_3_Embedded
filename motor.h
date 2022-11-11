/******************************************************************************
 * Module: DC Motor
 *
 * File Name: motor.h
 *
 * Description: header file for DC Motor driver
 *
 * Author: Naiera Seifeldin
 ******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

/********************************* Includes ***********************************/
#include "std_types.h"

/******************************** Definitions *********************************/
/* Used pins and port for DC Motor */
#define 	PORT_OF_MOTOR			PORTB_ID
#define 	MOTOR_PIN1_ID       	PIN0_ID
#define 	MOTOR_PIN2_ID	        PIN1_ID

/***************************** Types declarations *****************************/
typedef enum
{
	STOP , CW , A_CW
}DcMotor_State;

/**************************** Functions prototypes ****************************/

/* This function used to setup the direction for the two motor pins through
 * the GPIO driver, and Stop the DC-Motor at the beginning through the GPIO driver */
void DcMotor_Init(void);

/* This function used to rotate the DC Motor CW/ or A-CW or stop the motor
 * based on the state input state value, and Send the required duty cycle to
 *  the PWM driver based on the required speed value */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* MOTOR_H_ */
