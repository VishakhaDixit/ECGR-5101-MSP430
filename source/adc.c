/**************************
 *
 * @file    adc.c
 *
 * @brief   This file contains definition of functions for initializing and reading the digital value of ADC.
 *
 * @date    Aug 27, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/adc.h>


/**************************
 * @brief       This function samples the digital value of ADC.
 *
 * @param [in]  uint16_t
 *
 * @return      int Sampled data
 **************************/
static int sampleData(uint16_t digital_val)
{
    int result;

    // Sampling 1024 different values for setting duty cycles
    if( (digital_val > 0) && (digital_val <= 255) )
        result = 25;    //25% duty cycle

    else if( (digital_val >= 256) && (digital_val <= 511) )
        result = 50;    //50% duty cycle

    else if( (digital_val >= 512) && (digital_val <= 767) )
        result = 75;    //75% duty cycle

    else
        result = 100;   //100% duty cycle

    return result;
}


/**************************
 * @brief       This function initializes the provided ADC channel.
 *
 * @param [in]  *adc_config_params, pin_num
 *
 * @return      NULL
 **************************/
void ADC_Init(adc_config_args_t *adc_config_params, uint8_t pin_num)
{
    //using default ref vol as Vcc, enable the adc
    ADC10CTL0 = SREF_0|adc_config_params->sample_hold_time|ADC10ON;

    ADC10CTL1 = adc_config_params->adc_ch|adc_config_params->sample_hold_src|ADC10DIV_0|adc_config_params->clk_src|adc_config_params->conv_seq_mode;

    ADC10AE0 = pin_num;  //Configuring the pin for analog input
    ADC10CTL0 |= ENC; // Enabled conv
}


/**************************
 * @brief       This function reads the digital value of ADC.
 *
 * @param [in]  NULL
 *
 * @return      int Sampled data
 **************************/
int ADC_Read(void)
{
    uint16_t digital_val;
    uint8_t result;

    ADC10CTL0 |= ADC10SC;  //Start conversion

    while(ADC10CTL1 & ADC10BUSY);

    digital_val = (ADC10MEM & 0x03FF);  //Reading the 10-bit digital value

    result = sampleData(digital_val);
    return result;
}
