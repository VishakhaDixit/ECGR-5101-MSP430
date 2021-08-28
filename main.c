#include <include/adc.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	ADC_Init();
	
	return 0;
}
