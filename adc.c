/******************************************************************************
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for ADC driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

/********************************* Includes ***********************************/
#include <avr/io.h>
#include "adc.h"
#include "common_macros.h"

// NOTE: We didn't include here gpio.h or lcd.h since we didn't use in this file

/*************************** Functions definitions ****************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register:  ADLAR = 0 right adjusted (default)
	 * MUX4:0  = 00000 to choose channel 0 as initialization (default)
	 * REFS1:0 = 00 for initialization to choose later internal */
	ADMUX = 0; // All register bits = 0

	/* After initialization set the reference voltage ,, REFS1:0 bits */
	ADMUX |= (Config_Ptr->ref_volt << 6);
	// will text replace Internal by 11 = 3 in ref_volt

	/* ADCSRA Register:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable the AUTO trigger
	 * ADPS2:0 = 000 Clear these three bits before setup the required prescaler value */
	ADCSRA = (1<<ADEN);

	/* After initialization set the prescaler value ,, ADPS2:0 bits */
	ADCSRA |= Config_Ptr->prescaler;
	// will text replace F_CPU_8 by 11 = 3 in prescaler
}


uint16 ADC_readChannel(uint8 channel_num)
{
	// channel_num = channel_num & 0000 0111 ,, if channel = 0 ,, 00000000 & 00000111 = 00000000
	// if channel = 2 ,, 00000010 & 00000111 = 00000010 and so on stored in hexadecimal

	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	/* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits)
	 * before set the required channel ,, 0xE0=0b11100000 */
	ADMUX &= 0xE0;
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX = ADMUX | channel_num;
	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);
	/* Wait for conversion to complete, ADIF becomes '1' */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); // if ADIF = 0 ,, stay in loop = do nothing
	/* Clear ADIF by write '1' to it ,, flags are cleared by 1 :) */
	SET_BIT(ADCSRA,ADIF);
	return ADC; /* Read the digital value from the data register */
}
