/*
 * gpio.h
 *
 *  Created on: Aug 29, 2021
 *      Author: vishakha
 */

#ifndef MSP_430_INCLUDE_GPIO_H_
#define MSP_430_INCLUDE_GPIO_H_

#include <msp430.h>

typedef enum port
{
    PORT_1 = 0,
    PORT_2 = 1
} port_e;

typedef enum direction
{
    INPUT  = 0,
    OUTPUT = 1
} dir_e;

typedef enum pin_num
{
    PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7
} pin_num_e;


void gpio_init(port_e port_num, pin_num_e pin_num, dir_e direction);

bool gpio_get(port_e port_num, pin_num_e pin_num);

void gpio_set(port_e port_num, pin_num_e pin_num, bool val);


#endif /* MSP_430_INCLUDE_GPIO_H_ */
