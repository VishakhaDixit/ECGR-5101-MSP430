/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to implement 7 segment display values from 0-F for every change of potentiometer voltage.
 *
 * @date    Aug 29, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include <include/gpio.h>
#include <include/adc.h>
#include <include/7segDisplay.h>

int main(void)
{
    int16_t digital_val;
    int result;

    sevenSegPin_Config_t setPinVal;

    setPinVal.a = BIT6;
    setPinVal.b = BIT5;
    setPinVal.c = BIT4;
    setPinVal.d = BIT3;
    setPinVal.e = BIT2;
    setPinVal.f = BIT1;
    setPinVal.g = BIT0;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// Initialize 7 segment display
    sevenSegDisplay_Init(PORT_1, &setPinVal);

	//Set config parameters for ADC
	adc_config_args_t config_params;

	config_params.adc_ch = CH_7;                              // Set ADC channel
	config_params.clk_src = INTERNAL_OSC;                     // Set clk source for ADC
	config_params.conv_seq_mode = SINGLE_CH_SINGLE_CONV;      // Set conversion seq mode
	config_params.sample_hold_src = ADC_OSC;                  // Set sample and hold source
	config_params.sample_hold_time = SIXTEEN_ADC_CLK;         // Set sample and hold time

	// Initialize ADC
	ADC_Init(&config_params, PIN_7);

    while(1)
    {
        digital_val = ADC_Read();    //ADC reads 10 bit digital value between 0-1023

        // Sampling 1024 different values between 0-F

        if( (digital_val >= 0) && (digital_val <= 63) )
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
        else if( (digital_val >= 960) && (digital_val <= 1023) )
            result = 15;
        else
            result = 16;

        // Display result in 7 seg display
        sevenSegDisplay_Set(PORT_1, &setPinVal, result);
	}
}
