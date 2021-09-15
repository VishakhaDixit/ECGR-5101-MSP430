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
 * @return      int Sampled data
 **************************/
uint8_t ADC_Read(void)
{
    uint16_t digital_val;
    uint8_t result;

    ADC10CTL0 |= ADC10SC;  //Start conversion

    while(ADC10CTL1 & ADC10BUSY);

    digital_val = (ADC10MEM & 0x03FF);  //Reading the 10-bit digital value

    // Sampling 1024 different values between 0-F
    if( (digital_val > 0) && (digital_val <= 63) )
        result = 0;
    else if( (digital_val >= 64) && (digital_val <= 127) )
        result = 1;
    else if( (digital_val >= 128) && (digital_val <= 191) )
        result = 2;
    else if( (digital_val >= 192) && (digital_val <= 255) )
        result = 3;
    else if( (digital_val >= 256) && (digital_val <= 319) )
        result = 4;
    else if( (digital_val >= 320) && (digital_val <= 383) )
        result = 5;
    else if( (digital_val >= 384) && (digital_val <= 447) )
        result = 6;
    else if( (digital_val >= 448) && (digital_val <= 511) )
        result = 7;
    else if( (digital_val >= 512) && (digital_val <= 575) )
        result = 8;
    else if( (digital_val >= 576) && (digital_val <= 639) )
        result = 9;
    else if( (digital_val >= 640) && (digital_val <= 703) )
        result = 10;
    else if( (digital_val >= 704) && (digital_val <= 767) )
        result = 11;
    else if( (digital_val >= 768) && (digital_val <= 831) )
        result = 12;
    else if( (digital_val >= 832) && (digital_val <= 895) )
        result = 13;
    else if( (digital_val >= 896) && (digital_val <= 959) )
        result = 14;
    else
        result = 15;

    return result;
}
