/*
 * adc.h
 *
 *  Created on: Aug 27, 2021
 *      Author: vishakha
 */

#ifndef ADC_H_
#define ADC_H_

#include <msp430.h>

void ADC_Init(void);

int ADC_Read(void);

#endif /* ADC_H_ */
