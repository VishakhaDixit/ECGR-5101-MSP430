/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to modify led brightness wrt potentiometer. Pwm modifies the led brightness by using ADC to sample
 *          duty cycle wrt pot vol and transmits the same using UART.
 *
 * @date    Sep 15, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <msp430.h>
#include <include/adc.h>
#include <include/PWM.h>
#include <include/UART.h>
#include <include/pin_common.h>

int main(void)
{
    int dutyCycle;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //Set config parameters for ADC
    adc_config_args_t config_params;

    config_params.adc_ch            = CH_3;                             // Set ADC channel
    config_params.clk_src           = INTERNAL_OSC;                     // Set clk source for ADC
    config_params.conv_seq_mode     = SINGLE_CH_SINGLE_CONV;            // Set conversion seq mode
    config_params.sample_hold_src   = ADC_OSC;                          // Set sample and hold source
    config_params.sample_hold_time  = SIXTEEN_ADC_CLK;                  // Set sample and hold time

    // Initialize ADC
    ADC_Init(&config_params, GPIO_PIN3);

    //Initialize UART
    uartInit();

    while(1)
    {
        //Read digital value of potentiometer voltage and configure duty cycle.
        dutyCycle = ADC_Read();

        //Set duty cycle and port, pin configuration for pwm
        pwmSetDuty(dutyCycle);
        pinSetPWM(GPIO_BASE_PORT1, GPIO_PIN6);

        //Transmit the value of duty cycle using UART.
        uartTransmitChar((uint8_t) dutyCycle);
    }
}




