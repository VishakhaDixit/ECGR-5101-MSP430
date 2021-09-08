/**************************
 *
 * @file    timer.h
 *
 * @brief   This file contains functions for initializing and controlling the start-stop of timer in msp430.
 *
 * @date    Sept 01, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef TIMER_H_INCLUDE
#define TIMER_H_INCLUDE

#include <include/common.h>

void timerInit(port_e portNum, pin_num_e pinNum, uint8_t dutyCycle, float frequency);

void timerStart();

void timerStop();


#endif /* TIMER_H_INCLUDE */
