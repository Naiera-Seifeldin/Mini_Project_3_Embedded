/*
 ============================================================================
 Name        : Fan Controller.c
 Author      : Naiera Seifeldin
 Description : System to control a fan speed depend on room temperature
 Date        : October 6, 2022
 ============================================================================
 */

#include "lcd.h"   		   /* to access function of LCD to display on it */
#include "motor.h"		  /* to control motor */
#include "adc.h"		 /* to initialize ADC */
#include "lm35_sensor.h"/* to get temperature */
#include "avr/io.h"    /* to access I-bit register */

int main()
{
	uint8 temp;        /* to store temperature value */
	ADC_ConfigType ADC_Config = {INTERNAL,F_CPU_8}; /* to initialize structure of ADC */
	SREG  |= (1<<7);  /* Enable interrupts by I-bit */

	/********************** Initializations of functions **********************/
	LCD_init();                     /* Initialize LCD driver */
	ADC_init(&ADC_Config); /* Initialize ADC driver */
	DcMotor_Init();               /* Initialize Motor driver */

	/* we want to display these 2 messages only once ,, thats why we write them
	 * before while(1) since the text is the same for whole program ,, and we use
	 * displayStringRowColumn to make them written at middle of screen */
	LCD_displayStringRowColumn(0,4,"Fan is ");       // First row
	LCD_displayStringRowColumn(1,4,"Temp =    C");	// Second row


	while(1)
	{
		/*** first we get temperature coming from the lm35 sensor and display it ***/
		temp = LM35_getTemperature();
		/* moving cursor for temperature display ,, we display it every time at same position */
		LCD_moveCursor(1,9);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in
			 *  the next digit place */
			LCD_displayCharacter(' ');
		}

		/***** Controlling motor and displaying the state of fan *****/
		if(temp>=120)
		{
			/* Rotate motor with required speed and direction */
			DcMotor_Rotate(CW,100);
			/* Display state of fan */
			LCD_displayStringRowColumn(0,11,"ON ");
		}
		else if(temp>=90)
		{
			/* Rotate motor with required speed and direction */
			DcMotor_Rotate(CW,75);
			/* Display state of fan */
			LCD_displayStringRowColumn(0,11,"ON ");
		}
		else if(temp>=60)
		{
			/* Rotate motor with required speed and direction */
			DcMotor_Rotate(CW,50);
			/* Display state of fan */
			LCD_displayStringRowColumn(0,11,"ON ");
		}
		else if(temp>=30)
		{
			/* Rotate motor with required speed and direction */
			DcMotor_Rotate(CW,25);
			/* Display state of fan */
			LCD_displayStringRowColumn(0,11,"ON ");
		}
		else
		{
			/* Turn off motor */
			DcMotor_Rotate(STOP,0);
			/* Display state of fan */
			LCD_displayStringRowColumn(0,11,"OFF");
		}

	}
}
