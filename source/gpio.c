/*
 * gpio.c
 *
 *  Created on: Aug 29, 2021
 *      Author: vishakha
 */

#include "include/gpio.h"
#include <stdint.h>

void gpioInit(port_e portNum, pin_num_e pinNum, dir_e direction)
{
    if (portNum == PORT_1)
    {
        //set direction
        //enable
        if( direction == INPUT )
        {
            P1DIR &= ~(1 << pinNum);
            P1REN |= 1 << pinNum;
        }
        else
        {
            P1DIR |= 1 << pinNum;
        }

        P1OUT |= 1 << pinNum;
    }
    else
    {
        //set direction
        //enable
        if( direction == INPUT )
        {
            P2DIR &= ~(1 << pinNum);
            P2REN |= 1 << pinNum;
        }
        else
        {
            P2DIR |= 1 << pinNum;
        }

        P2OUT |= 1 << pinNum;
    }
}

bool gpioGet(port_e portNum, pin_num_e pinNum)
{
    bool val;
    uint8_t pinMask;

    pinMask = 1 << pinNum;

    if (portNum == PORT_1)
    {
        val = (bool) (P1IN & pinMask);
    }
    else
    {
        val = (bool) (P2IN & pinMask);
    }

    return val;
}

void gpioSet(port_e portNum, pin_num_e pinNum, bool val)
{
    uint8_t pinMask;
    pinMask = 1 << pinNum;

    if(val == 1)
    {
        if (portNum == PORT_1)
        {
            P1OUT |= pinMask;
        }
        else
        {
            P2OUT |= pinMask;
        }
    }
    else
    {
        if (portNum == PORT_1)
        {
            P1OUT &= ~(pinMask);
        }
        else
        {
            P2OUT &= ~(pinMask);
        }
    }
}
