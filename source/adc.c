/*
 * adc.c
 *
 *  Created on: Aug 27, 2021
 *      Author: vishakha
 */

#include <include/adc.h>

void ADC_Init(adc_config_args_t *adc_config_params, pin_num_e pin_num)
{
    //using default ref vol 0 - 3.3, sample and hold time as 16 times adc10 clock, and lastly enable the adc
    ADC10CTL0 = SREF_0|adc_config_params->sample_hold_time|ADC10ON;

    //chose ch 3 at P1.3, no div t the clk, default module's clk, and signle ch single conv
    ADC10CTL1 = adc_config_params->adc_ch|adc_config_params->sample_hold_src|ADC10DIV_0|adc_config_params->clk_src|adc_config_params->conv_seq_mode;

    ADC10AE0 = 1 << pin_num;  //P1.3 also above, INCH_3
    ADC10CTL0 |= ENC; // Enabled conv
}

uint16_t ADC_Read(void)
{
    uint16_t memval;

    ADC10CTL0 |= ADC10SC;  //Start conv

    while(ADC10CTL1 & ADC10BUSY);

    memval = ADC10MEM;

    return memval;
}
