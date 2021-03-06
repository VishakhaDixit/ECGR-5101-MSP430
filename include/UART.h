/*
 * UART.h
 *
 *  Created on: Feb 4, 2019
 *      Author: Shantanu
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "msp430g2553.h"
#include "include/common.h"
#include "include/pin_common.h"

void uartInit(void);
void uartPinInit(void);
void uartConfigureCR(void);
void uartCheckTxReady(void);
void uartCheckRxReady(void);
uint8_t uartReceiveChar(void);
void uartTransmitChar(uint8_t data);


#endif /* UART_H_ */
