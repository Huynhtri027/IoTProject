/*
 * UART.h
 *
 *  Created on: Jan 25, 2017
 *      Author: Tri Huynh
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#ifndef SMCLK_F
#define SMCLK_F 1000000 // frequency of Sub-System Master Clock in Hz
#endif

#define BAUDRATE  9600 // may be ... 1200, 2400, 4800, 9600, 19200, ...
// With Launch Pad, the back channel UART to the target MSP is done by
// bit-banging the otherwise unused I/O port lines of the TUSB interface chip
// (by the specific TUSB firmware), and this is limited to 9600
// So you should not try the Baud rate above 9600.

#define UART_RX_INT_EN 0
// If you enable the UART receive interrupt (define 1), you don't need to
// wait receive data by function uart_get & cuart_gets.
// Instead, you must enable GIE and write your processing code in USCI0RX_ISR
// (can be found in uart.c)

/****************************************************************************
 * HARD DEFINITIONS
******************************************************************************/


 /****************************************************************************
* FUNCTIONS 'S PROTOTYPES
******************************************************************************/
// For further description, see UART.c
void uart_init();
void uart_putc(char c);
void uart_puts(const char *s);
void uart_put_num (unsigned long val, char dec, unsigned char neg);
char uart_data_ready();
char uart_getc();
void uart_gets(char *s);


#endif /* UART_UART_H_ */
