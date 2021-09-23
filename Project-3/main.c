/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to modify led brightness using potentiometer.
 *          Potentiometer turns on one board will affect the brightness of a light on the other board.
 *
 * @date    Sep 21, 2021
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

    //Initialize UART
    uartInit();

    pinSetPWM(GPIO_PORT_P2, GPIO_PIN1);     //LED at Port2 Pin1

    //Set config parameters for ADC
    adc_config_args_t config_params;

    config_params.adc_ch            = CH_4;                             // Set ADC channel
    config_params.clk_src           = INTERNAL_OSC;                     // Set clk source for ADC
    config_params.conv_seq_mode     = SINGLE_CH_SINGLE_CONV;            // Set conversion seq mode
    config_params.sample_hold_src   = ADC_OSC;                          // Set sample and hold source
    config_params.sample_hold_time  = SIXTEEN_ADC_CLK;                  // Set sample and hold time

    while(1)
    {
        if(!(P1IN & BIT3))
        {
            // Initialize ADC
            ADC_Init(&config_params, GPIO_PIN4);

            //Read digital value of potentiometer voltage and configure duty cycle.
            dutyCycle = ADC_Read();

            //Set duty cycle
            pwmSetDuty(dutyCycle);

            //Transmit the value of duty cycle using UART.
            uartTransmitChar((uint8_t) dutyCycle);
        }
        else
        {
            //Read received duty cycle from UART.
            dutyCycle = uartReceiveChar();

            //Set duty cycle
            pwmSetDuty(dutyCycle);
        }
    }
}
