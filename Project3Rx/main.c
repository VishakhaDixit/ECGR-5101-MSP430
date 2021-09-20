/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to receive the duty cycle via UART. It uses pwm to modify led brightnes wrt to the duty received.
 *
 * @date    Sep 15, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <msp430.h>
#include <include/PWM.h>
#include <include/UART.h>
#include <include/pin_common.h>

int main(void)
{
    uint8_t dutyCycle;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //Initialize UART
    uartInit();

    while(1)
    {
        //Read the received duty cycle via UART.
        dutyCycle = uartReceiveChar();

        //Set duty cycle and port, pin configuration for pwm
        pwmSetDuty((int) dutyCycle);
        pinSetPWM(GPIO_BASE_PORT1, GPIO_PIN6);
    }
}


