/**************************
 *
 * @file    main.c
 *
 * @brief   This program timer and switch interrupts to implement a stop-watch.
 *
 * @date    Oct 1, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <msp430.h>
#include <include/timer.h>
#include <include/gpio.h>
#include <include/7segDisplay.h>

uint8_t timerCntVal = 0;
uint8_t switchPressCnt = 0;

int main(void)
{
    float result = 0.0;
    uint8_t displaySec = 0;
    uint8_t displayOneTenthSec = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    sevenSegPin_Config_t display1;

    display1.a = BIT7;
    display1.b = BIT6;
    display1.c = BIT5;
    display1.d = BIT4;
    display1.e = BIT2;
    display1.f = BIT1;
    display1.g = BIT0;

    sevenSegPin_Config_t display2;

    display2.a = BIT7;
    display2.b = BIT6;
    display2.c = BIT5;
    display2.d = BIT4;
    display2.e = BIT3;
    display2.f = BIT2;
    display2.g = BIT0;

    // Initialize 7 segment displays
    sevenSegDisplay_Init(PORT_1, &display1);
    sevenSegDisplay_Init(PORT_2, &display2);

    //Display initial value
    sevenSegDisplay_Set(PORT_1, &display1, displaySec);
    sevenSegDisplay_Set(PORT_2, &display2, displayOneTenthSec);

    //Initialize timer
    timerInit(PORT_2, PIN_1, 100, 10);
    enableTimerInterrupt(TIMER_1);          //Enabled interrupt for timer 1

    gpioInit(PORT_1, PIN_3, INPUT);         //Using P1.3 for switch
    enableGpioInterrput(PORT_1, PIN_3);     //Enable interrupt for switch

    __enable_interrupt();

    while(1)
    {
        //Start timer on first button press
        if(switchPressCnt == 1)
        {
            timerStart();
        }

        //Stop timer on second button press
        else if(switchPressCnt == 2)
        {
            timerStop();
        }

        //Display 0.0 on third button press
        else
        {
            timerCntVal = 0;
        }

        if(timerCntVal > 0)
        {
            result = (float)( timerCntVal/10.0 );
            displaySec = (uint8_t)result;
            displayOneTenthSec = (uint8_t)( (result - displaySec) * 10 );
        }
        else
        {
            displaySec = 0;
            displayOneTenthSec = 0;
        }

        //Display result on 7 segment displays
        sevenSegDisplay_Set(PORT_1, &display1, displaySec);
        sevenSegDisplay_Set(PORT_2, &display2, displayOneTenthSec);
    }
}

// Timer A1 interrupt service routine
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A (void)
{
    __disable_interrupt();

    if(timerCntVal == 99)
    {
        timerCntVal = 0;
    }
    else
    {
        timerCntVal++;
    }

    timerStart();
    TA1CCTL1 &= ~(CCIFG);

    __enable_interrupt();
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __disable_interrupt();

    if(P1IFG && BIT3)
    {
        if(switchPressCnt == 3)
        {
            switchPressCnt = 0;
        }
        else
        {
            switchPressCnt++;
        }
    }

    P1IFG &= ~(BIT3);

    __enable_interrupt();
}
