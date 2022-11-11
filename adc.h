/******************************************************************************
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: Header file for ADC driver
 *
 * Author: Naiera Seifeldin
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/********************************* Includes ***********************************/
#include "std_types.h"

/******************************* Definitions **********************************/
#define ADC_MAXIMUM_VALUE    1023 //
#define ADC_REF_VOLT_VALUE   2.56 // internal reference voltage

/***************************** Types declarations *****************************/
typedef enum
{
	AREF,AVCC,RESERVED,INTERNAL
}ADC_ReferenceVolatge; // 0,1,2,3 for REFS1:0 bits ,, Reference selection bits

typedef enum
{
	F_CPU_2 = 1 , F_CPU_4 , F_CPU_8 , F_CPU_16 , F_CPU_32 , F_CPU_64 , F_CPU_128
}ADC_Prescaler; // 1,2,3,4,5,6,7 for ADPS2:0 bits ,, ADC Prescaler selection bits

typedef struct
{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/**************************** Functions prototypes ****************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num); /* uint16 since we have 10 bits for ADC */

#endif /* ADC_H_ */

