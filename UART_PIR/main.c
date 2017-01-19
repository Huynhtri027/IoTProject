#include <msp430.h>
#include "uart.h"

#define DELAY_05s 62500
unsigned char counter = 0;

void main(void) {
	WDTCTL = WDTPW + WDTHOLD;       // stop WDT
	BCSCTL1 = CALBC1_1MHZ;        //2 thanh ghi cài đặt tần số hoạt động
	DCOCTL = CALDCO_1MHZ;        //Ở đây là 1 Mhz
	// P1DIR |=(BIT1 + BIT2);
	uart_init();   // khoi tao uart

	// P1.0 is PIR input
	P1REN |= BIT0;              // enable pull-up
	P1OUT |= BIT0;              // pull-up
	P1IE |= BIT0;               // interrupt enabled
	P1IES |= BIT0;      // hi/lo edge but might be changed depending on your PIR
	P1IFG &= ~BIT0;             // IFG cleared

	P1DIR |= BIT6 + BIT1 + BIT2; // P1.1 is LED

	TACCR0 = 0;
	TACTL = TASSEL_2 + MC_1 + ID_3; // SMCLK, upmode , /8
	TACCTL0 = CCIE;

	__bis_SR_register(LPM4_bits + GIE); // switch to LPM0 with interrupts

//	while (1) {
//	uart_puts(\r\n");
//			__delay_cycles(500000);
//		}
}

// Timer A interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
       if(counter == 10) {
        counter = 0;

        P1OUT &= ~BIT1; // LED off
        uart_puts("NOT");
    __bis_SR_register_on_exit(LPM4_bits); // switch from LPM0 to LPM4
       } else {
         counter++;
       }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{


     P1OUT |= BIT1; // LED on

    // TACCR0 += DELAY_05s;
        counter = 0;
        uart_puts("OK");

    __bic_SR_register_on_exit(LPM4_bits-LPM0_bits); // switch from LPM4 to LPM0

    P1IFG &= ~BIT0;                     // IFG cleared
}
