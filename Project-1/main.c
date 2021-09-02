/**
 * main.c
 */

#include <include/gpio.h>
#include <include/timer.h>

int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	timerInit(PORT_1, PIN_6, 50, 1);
	gpioInit(PORT_2, PIN_3, INPUT);    //Using P2.3 for switch

	while(1)
	{
	    bool switchStatus;

	    switchStatus = gpioGet(PORT_2, PIN_3);

	    if( switchStatus == 1)
	    {
	        timerStart();
	    }
	    else
	    {
	        timerStop();
	    }
	}




//	gpioInit(PORT_1, PIN_5, OUTPUT);   //Using P1.6 for led
//
//    while(1)
//    {
//        unsigned long i;
//        gpioSet(PORT_1, PIN_5, true);
//
//        i = 50000;
//        do
//        {
//            i--;
//        } while( i != 0);
//
//        gpioSet(PORT_1, PIN_5, false);
//
//        i = 50000;
//        do
//        {
//            i--;
//        } while( i != 0);
//    }
	
}
