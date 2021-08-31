/**
 * main.c
 */

#include <include/gpio.h>

int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	gpio_init(PORT_1, PIN_5, OUTPUT);   //Using P1.6 for led
	gpio_init(PORT_1, PIN_3, INPUT);    //Using P1.3 for switch

	while(1)
	{
	    bool switch_status;

	    switch_status = gpio_get(PORT_1, PIN_3);
	    gpio_set(PORT_1, PIN_5, switch_status);
	}

//	gpio_init(PORT_1, PIN_5, OUTPUT);   //Using P1.6 for led
//
//    while(1)
//    {
//        unsigned long i;
//        gpio_set(PORT_1, PIN_5, true);
//
//        i = 50000;
//        do
//        {
//            i--;
//        } while( i != 0);
//
//        gpio_set(PORT_1, PIN_5, false);
//
//        i = 50000;
//        do
//        {
//            i--;
//        } while( i != 0);
//    }
	
}
