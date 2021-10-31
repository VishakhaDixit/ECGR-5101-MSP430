/**************************
 *
 * @file    main.c
 *
 * @brief   This program receives input at port1 and sets corresponding output at port2.
 *
 * @date    Oct 31, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/common.h>
#include <include/gpio.h>

int main(void)
{
    uint8_t input;
    uint8_t output;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    gpioInitPort(PORT_1, INPUT);
    gpioInitPort(PORT_2, OUTPUT);

    while(1)
    {
        input = P1IN & 0x0F;

        switch(input)
        {
        case 8:
            output = 0x01;
            gpioSetPort(PORT_2, output);
            break;
        case 9:
            output = 0x02;
            gpioSetPort(PORT_2, output);
            break;
        case 10:
            output = 0x04;
            gpioSetPort(PORT_2, output);
            break;
        case 11:
            output = 0x08;
            gpioSetPort(PORT_2, output);
            break;
        case 12:
            output = 0x10;
            gpioSetPort(PORT_2, output);
            break;
        case 13:
            output = 0x20;
            gpioSetPort(PORT_2, output);
            break;
        case 14:
            output = 0x40;
            gpioSetPort(PORT_2, output);
            break;
        case 15:
            output = 0x80;
            gpioSetPort(PORT_2, output);
            break;
        default:
            output = 0xFF;
            gpioSetPort(PORT_2, output);
            break;
        }
    }
}

