/*
 * adc.c
 *
 *  Created on: Aug 27, 2021
 *      Author: vishakha
 */

#include <include/adc.h>

void ADC_Init(void)
{
    //using default ref vol 0 - 3.3, sample and hold time as 16 times adc10 clock, and lastly enable the adc
    ADC10CTL0 = SREF_0|ADC10SHT_2|ADC10ON;

    //chose ch 3 at P1.3, no div t the clk, default module's clk, and signle ch single conv
    ADC10CTL1 = INCH_3|SHS_0|ADC10DIV_0|ADC10SSEL_0|CONSEQ_0;

    ADC10AE0 = BIT3;  //P1.3 also above, INCH_3
    ADC10CTL0 |= ENC; // Enabled conv
}

int ADC_Read(void)
{
    int memval;

    ADC10CTL0 |= ADC10SC;  //Start conv

    while(ADC10CTL1 & ADC10BUSY);

    memval = ADC10MEM;

    return memval;
}
