/*
 * timer.c
 *
 *  Created on: Sep 1, 2021
 *      Author: visha
 */

#include <include/timer.h>

void timerInit(port_e portNum, pin_num_e pinNum, uint8_t dutyCycle, float frequency)
{
    uint16_t numTicks;
    uint16_t dutyCycleTicks;

    if( portNum == PORT_1 )
    {
        P1DIR |= 1 << pinNum;
        P1SEL |= BIT6 ;
    }
    else
    {
        P2DIR |= 1 << pinNum;
        P2SEL |= BIT6;
    }

    //Selecting low frequency mode
    BCSCTL1 |= LFXT1S0;

    //Using Internal very low frequency osc which typically provides a freq of 12 KHz
    BCSCTL3 |= LFXT1S_2;

    //Set the period in the Timer A0 Capture/Compare 0 register.
    numTicks = (uint16_t)(12000 / frequency);
    TA0CCR0 = numTicks;

    //Setting Reset/Set mode.
    TA0CCTL1 = OUTMOD_7;

    dutyCycleTicks = (uint16_t)(numTicks * (dutyCycle / 100.0));
    TA0CCR1 = dutyCycleTicks;

    //Using ACLK as clock source
    TA0CTL = TASSEL_1;
}

void timerStart()
{
    TA0CTL |= MC_1;
}

void timerStop()
{
    TA0CTL &= ~(0x0030);
}
