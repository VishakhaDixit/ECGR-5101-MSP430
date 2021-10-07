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
#include <stdbool.h>

static volatile uint8_t oneTenthSec = 0;
static volatile uint8_t sec = 0;
static volatile uint8_t switchPressCnt = 2;
static volatile bool switchPressed = false;

int main(void)
{
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
    sevenSegDisplay_Set(PORT_1, &display1, sec);
    sevenSegDisplay_Set(PORT_2, &display2, oneTenthSec);

    //Initialize timer
    timerInit(PORT_2, PIN_1, 100, 10);
    enableTimerInterrupt(TIMER_1);          //Enabled interrupt for timer 1

    gpioInit(PORT_1, PIN_3, INPUT);         //Using P1.3 for switch
    enableGpioInterrput(PORT_1, PIN_3);     //Enable interrupt for switch

    __enable_interrupt();

    while(1)
    {
        //Display result on 7 segment displays
        sevenSegDisplay_Set(PORT_2, &display2, oneTenthSec);
        sevenSegDisplay_Set(PORT_1, &display1, sec);

        //Start timer on first button press
        if(switchPressCnt == 0 && switchPressed == true)
        {
            timerStart();
            switchPressed = false;
        }

        //Stop timer on second button press
        else if(switchPressCnt == 1 && switchPressed == true)
        {
            timerStop();
            switchPressed = false;
        }

        //Display 0.0 on third button press
        else if(switchPressCnt == 2 && switchPressed == true)
        {
            sec = 0;
            oneTenthSec = 0;
            switchPressed = false;
        }
    }
}

// Timer A1 interrupt service routine
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer_A (void)
{
    __disable_interrupt();

    if(oneTenthSec == 9 && sec == 9)
    {
        sec = 0;
        oneTenthSec = 0;    //7-segment LEDs value correctly roll over from 9.9 to 0.0 while running longer than 10 seconds.
    }
    else if(oneTenthSec == 9)
    {
        sec++;
        oneTenthSec = 0;
    }
    else
    {
        oneTenthSec++;
    }

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
        if(switchPressCnt == 2)
        {
            switchPressCnt = 0;
        }
        else
        {
            switchPressCnt++;
        }
        switchPressed = true;
    }

    P1IFG &= ~(BIT3);

    __delay_cycles(1000);   //To compensate for button bounce

    __enable_interrupt();
}
