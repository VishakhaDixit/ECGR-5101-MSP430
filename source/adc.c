/**************************
 *
 * @file    adc.c
 *
 * @brief   This file contains definition of functions for initializing and reading the digital value of ADC.
 *
 * @date    Aug 27, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include <include/adc.h>


/**************************
 * @brief       This function initializes the provided ADC channel.
 *
 * @param [in]  *adc_config_params, pin_num
 *
 * @return      NULL
 **************************/
void ADC_Init(adc_config_args_t *adc_config_params, pin_num_e pin_num)
{
    //using default ref vol as Vcc, enable the adc
    ADC10CTL0 = SREF_0|adc_config_params->sample_hold_time|ADC10ON;

    ADC10CTL1 = adc_config_params->adc_ch|adc_config_params->sample_hold_src|ADC10DIV_0|adc_config_params->clk_src|adc_config_params->conv_seq_mode;

    ADC10AE0 = 1 << pin_num;  //Configuring the pin for analog input
    ADC10CTL0 |= ENC; // Enabled conv
}


/**************************
 * @brief       This function reads the digital value of ADC.
 *
 * @param [in]  NULL
 *
 * @return      uint16_t Digital value of ADC
 **************************/
uint16_t ADC_Read(void)
{
    uint16_t memval;

    ADC10CTL0 |= ADC10SC;  //Start conversion

    while(ADC10CTL1 & ADC10BUSY);

    memval = (ADC10MEM & 0x03FF);  //Reading the 10-bit digital value

    return memval;
}
