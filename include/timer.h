/*
 * timer.h
 *
 *  Created on: Sep 1, 2021
 *      Author: visha
 */

#ifndef TIMER_H_INCLUDE
#define TIMER_H_INCLUDE

#include <include/common.h>

void timerInit(port_e portNum, pin_num_e pinNum, uint8_t dutyCycle, float frequency);

void timerStart();

void timerStop();

#endif /* TIMER_H_INCLUDE */
