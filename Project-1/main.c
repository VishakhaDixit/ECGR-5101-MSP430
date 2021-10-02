/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to implement blinking of led using timer, and stops the timer using switch
 *
 * @date    Aug 29, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/gpio.h>
#include <include/timer.h>

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    bool switchStatus;

	timerInit(PORT_2, PIN_1, 50, 1);   //Using P2.1 for LED
	gpioInit(PORT_2, PIN_3, INPUT);    //Using P2.3 for switch

	while(1)
	{
	    switchStatus = gpioGet(PORT_2, PIN_3);

	    if( switchStatus == 1)
	    {
	        //Blink led when switch is not pressed
	        timerStart();
	    }
	    else
	    {
	        //Pause the blinking when switch is pressed
	        timerStop();
	    }
	}
	
}
