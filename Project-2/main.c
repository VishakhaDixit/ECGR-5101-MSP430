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
    uint8_t result;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    sevenSegPin_Config_t setPinVal;

    setPinVal.a = BIT6;
    setPinVal.b = BIT5;
    setPinVal.c = BIT4;
    setPinVal.d = BIT3;
    setPinVal.e = BIT2;
    setPinVal.f = BIT1;
    setPinVal.g = BIT0;

	// Initialize 7 segment display
    sevenSegDisplay_Init(PORT_1, &setPinVal);

	//Set config parameters for ADC
	adc_config_args_t config_params;

	config_params.adc_ch            = CH_7;                             // Set ADC channel
	config_params.clk_src           = INTERNAL_OSC;                     // Set clk source for ADC
	config_params.conv_seq_mode     = SINGLE_CH_SINGLE_CONV;            // Set conversion seq mode
	config_params.sample_hold_src   = ADC_OSC;                          // Set sample and hold source
	config_params.sample_hold_time  = SIXTEEN_ADC_CLK;                  // Set sample and hold time

	// Initialize ADC
	ADC_Init(&config_params, PIN_7);

    while(1)
    {
        result = ADC_Read();

        // Display result in 7 seg display
        sevenSegDisplay_Set(PORT_1, &setPinVal, result);
	}
}
