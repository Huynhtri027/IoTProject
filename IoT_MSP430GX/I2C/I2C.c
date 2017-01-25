/*
 * I2C.c
 *
 *  Created on: Jan 24, 2017
 *      Author: tri
 */

/*
 * Include lib
 */
#include "../include.h"
#include "I2C.h"
#include "msp430g2553.h"

/*
 * Created I2C
 */

extern void init_I2C(void){
    _DINT();
    P1DIR |= SCL | SDA | LED;             //Set SCL, SDA as Output
    P1REN |= SCL | SDA;             //Set Pull-Ups on SCL and SDA
    IE2 |= UCB0RXIE;                //Enable RX interrupt
    IE2 |= UCB0TXIE;                //Enable TX interrupt
    while (UCB0CTL1 & UCTXSTP)      //Ensure stop condition got sent
    UCB0CTL1 |= UCSWRST;            //Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;   //I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;          //Use SMCLK, keep SW reset
    UCB0BR0 = 12;                           //fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2CSA = 0x5c;               //Slave Address is 069h
    UCB0CTL1 &= ~UCSWRST;           //Clear Sw reset, resyme operation
}

/*
 * Transmit
 */

extern void Transmit(void){
    while (UCB0CTL1 & UCTXSTP);      //Ensure stop condition got sent
    UCB0CTL1 |= UCTR + UCTXSTT;      //I2C TX, start condition
    __bis_SR_register(CPUOFF + GIE); //Enter LPM0 w/ interrupts
}

/*
 * Receive
 */

extern void Receive(void){
    UCB0CTL1 &= ~UCTR;               //Clear UCTR
    while(UCB0CTL1 & UCTXSTP);       //Ensure stop condition got sent
    UCB0CTL1 |= UCTXSTT;             //I2C start condition
    while (UCB0CTL1 & UCTXSTT);      //I2C stop condition
    __bis_SR_register(CPUOFF + GIE); //Enter LPM0 w/ interrupts
}

/*
 *
 */

extern uint8_t I2C_USCI_Write_Byte(uint8_t address, uint8_t data){
    while(UCA0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR + UCTXSTT;

    while(!(IFG2 & UCB0TXIFG));
    if(UCA0STAT & UCNACKIFG) return UCB0STAT;
    UCB0TXBUF = address;

    while(!(IFG2 & UCB0RXIFG));
    if(UCB0STAT & UCNACKIFG) return UCB0STAT;
    UCB0TXBUF = data;

    while(!(IFG2 & UCB0TXIFG));
    if(UCB0STAT & UCNACKIFG) return UCB0STAT;
    UCB0CTL1 |= UCTXSTP;
    IFG2 &= ~UCB0TXIFG;
    return 0;
}

/*
 *
 */

extern uint8_t I2C_USCI_Read_Byte(uint8_t address){
    while(UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= UCTR +UCTXSTT;

    while(!(IFG2 & UCB0TXIFG));
    UCB0TXBUF = address;

    while(!(IFG2 & UCB0TXIFG));

    UCB0CTL1 &= ~UCTR;
    UCB0CTL1 |= UCTXSTT;
    IFG2 &= ~UCB0TXIFG;

    while(UCB0CTL1 & UCTXSTT);
    UCB0CTL1 |= UCTXSTP;
    return UCB0RXBUF;
}
