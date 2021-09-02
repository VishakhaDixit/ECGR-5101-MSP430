/**************************
 *
 * @file    common.h
 *
 * @brief   Common Type Definition for all ports and peripherals.
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef COMMON_H_INCLUDE
#define COMMON_H_INCLUDE

#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum port
{
    PORT_1 = 0,
    PORT_2 = 1
} port_e;

typedef enum pinNum
{
    PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7
} pin_num_e;

#endif /* COMMON_H_INCLUDE */
