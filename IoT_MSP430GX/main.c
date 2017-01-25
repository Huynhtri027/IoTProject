#include <msp430.h> 
#include "include.h"
/*
 * main.c
 */
void main(void) {
    WDTCTL  = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;      // Set range to 1mhz Calibrated Range
    DCOCTL  = CALDCO_1MHZ;      // Set DC0 to 1mhz Calibrated DCO SMCLK = DCO = 1mhz

    init_I2C();
    Transmit();
    Receive();
}
