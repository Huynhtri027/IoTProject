/*
 * I2C.h
 *
 *  Created on: Jan 24, 2017
 *      Author: tri
 */

#ifndef I2C_I2C_H_
#define I2C_I2C_H_

/*
 * Define varible
 */
#define SDA  BIT7 //P1.7
#define SCL  BIT6 //P1.6
#define LED  BIT0 //P1.0

/*
 * Created Funtions
 */

extern void init_I2C(void);
extern void Transmit(void);
extern void Receive(void);
extern uint8_t I2C_USCI_Write_Byte(uint8_t address, uint8_t data);
extern uint8_t I2C_USCI_Read_Byte(uint8_t address);

#endif /* I2C_I2C_H_ */
