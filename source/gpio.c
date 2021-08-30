/*
 * gpio.c
 *
 *  Created on: Aug 29, 2021
 *      Author: vishakha
 */

#include "include/gpio.h"
#include <stdint.h>

void gpio_init(port_e port_num, pin_num_e pin_num, dir_e direction)
{
    if (port_num == PORT_1)
    {
        //set direction
        //enable
        if( direction == INPUT )
        {
            P1DIR &= ~(1 << pin_num);
            P1REN |= 1 << pin_num;
        }
        else
        {
            P1DIR |= 1 << pin_num;
        }

        P1OUT |= 1 << pin_num;
    }
    else
    {
        //set direction
        //enable
        if( direction == INPUT )
        {
            P2DIR &= ~(1 << pin_num);
            P2REN |= 1 << pin_num;
        }
        else
        {
            P2DIR |= 1 << pin_num;
        }

        P2OUT |= 1 << pin_num;
    }
}

bool gpio_get(port_e port_num, pin_num_e pin_num)
{
    bool val;
    uint8_t pin_mask;

    pin_mask = 1 << pin_num;

    if (port_num == PORT_1)
    {
        val = P1IN & pin_mask;
    }
    else
    {
        val = P2IN & pin_mask;
    }

    return val;
}

void gpio_set(port_e port_num, pin_num_e pin_num, bool val)
{
    uint8_t pin_mask;
    pin_mask = 1 << pin_num;

    if(val == 1)
    {
        if (port_num == PORT_1)
        {
            P1OUT |= pin_mask;
        }
        else
        {
            P2OUT |= pin_mask;
        }
    }
    else
    {
        if (port_num == PORT_1)
        {
            P1OUT &= ~(pin_mask);
        }
        else
        {
            P2OUT &= ~(pin_mask);
        }
    }
}
