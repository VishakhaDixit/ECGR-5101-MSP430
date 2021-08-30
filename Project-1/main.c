/**
 * main.c
 */

#include <include/gpio.h>
#include <stdbool.h>

int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	gpio_init(PORT_2, PIN_1, OUTPUT);   //Using P1.6 for led
	gpio_init(PORT_1, PIN_3, INPUT);    //Using P1.3 for switch

	while(1)
	{
	    switch_status = gpio_get(PORT_1, PIN_3);
	    gpio_set(PORT_2, PIN_1, switch_status);
	}

//	gpio_init(PORT_1, PIN_6, OUTPUT);   //Using P1.6 for led
//
//    while(1)
//    {
//        unsigned long i;
//        gpio_set(PORT_1, PIN_6, true);
//
//        i = 50000;
//        do
//        {
//            i--;
//        } while( i != 0);
//
//        gpio_set(PORT_1, PIN_6, false);
//
//        i = 50000;
//        do
//        {
//            i--;
//        } while( i != 0);
//    }
	
}
