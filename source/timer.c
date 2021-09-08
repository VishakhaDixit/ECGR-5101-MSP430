/**************************
 *
 * @file    timer.c
 *
 * @brief   This file contains definition of functions for initializing msp430 timer.
 *
 * @date    Sept 01, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/
#include <include/timer.h>


/**************************
 * @brief       This function initializes the timer
 *
 * @param [in]  portNum, pinNum, dutyCycle, frequency
 *
 * @return      NULL
 **************************/
void timerInit(port_e portNum, pin_num_e pinNum, uint8_t dutyCycle, float frequency)
{
    uint16_t numTicks;
    uint16_t dutyCycleTicks;

    if( portNum == PORT_1 )
    {
        //Set direction
        P1DIR |= 1 << pinNum;
        //Select alternate function for timer
        P1SEL |= BIT6 ;
    }
    else
    {
        //Set direction
        P2DIR |= 1 << pinNum;
        //Select alternate function for timer
        P2SEL |= BIT6;
    }

    //Using ACLK as clock source for timer
    TA0CTL = TASSEL_1;

    //Selecting low frequency mode
    BCSCTL1 |= LFXT1S0;

    //Using Internal very low frequency osc which typically provides a freq of 12 KHz
    BCSCTL3 |= LFXT1S_2;

    //Set the period in the Timer A0 Capture/Compare 0 register.
    numTicks = (uint16_t)(12000 / frequency);
    TA0CCR0 = numTicks;

    dutyCycleTicks = (uint16_t)(numTicks * (dutyCycle / 100.0));
    TA0CCR1 = dutyCycleTicks;

    //Setting Reset/Set mode.
    TA0CCTL1 = OUTMOD_7;
}


/**************************
 * @brief       This function starts the timer
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void timerStart()
{
    //Setting the mode control 1 - counts upto CCR0
    TA0CTL |= MC_1;
}


/**************************
 * @brief       This function stops the timer
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void timerStop()
{
    //Setting the mode control 0 - timer stop
    TA0CTL &= ~(0x0030);
}
