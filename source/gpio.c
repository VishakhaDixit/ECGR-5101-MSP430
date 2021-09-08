/**************************
 *
 * @file    gpio.c
 *
 * @brief   This file contains definition of functions for initializing msp430 gpio.
 *
 * @date    Aug 29, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include "include/gpio.h"
#include <stdint.h>


/**************************
 * @brief       This function initializes the gpio pin based on the direction provided.
 *
 * @param [in]  portNum, pinNum, direction
 *
 * @return      NULL
 **************************/
void gpioInit(port_e portNum, pin_num_e pinNum, dir_e direction)
{
    if (portNum == PORT_1)
    {
        if( direction == INPUT )
        {
            //set direction
            P1DIR &= ~(1 << pinNum);
            //enable pull up resistor
            P1REN |= 1 << pinNum;
        }
        else
        {
            //set direction
            P1DIR |= 1 << pinNum;
        }

        //Setting initial value to 1
        P1OUT |= 1 << pinNum;
    }
    else
    {
        if( direction == INPUT )
        {
            //set direction
            P2DIR &= ~(1 << pinNum);
            //enable pull up resistor
            P2REN |= 1 << pinNum;
        }
        else
        {
            //set direction
            P2DIR |= 1 << pinNum;
        }

        //Setting initial value to 1
        P2OUT |= 1 << pinNum;
    }
}


/**************************
 * @brief       This function is used to get the switch status
 *
 * @param [in]  portNum, pinNum
 *
 * @return      bool  Status of the switch
 **************************/
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


/**************************
 * @brief       This function sets the gpio pin as either high or low based on switch status
 *
 * @param [in]  portNum, pinNum, val
 *
 * @return      NULL
 **************************/
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
