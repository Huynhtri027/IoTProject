/*
 * AM2315.h
 *
 *  Created on: Jan 24, 2017
 *      Author: tri
 */

#ifndef AM2315_AM2315_H_
#define AM2315_AM2315_H_

/*
 * Define varibale
 */
#define AM2315_I2CADDR       0x5C
#define AM2315_READREG       0x03

/*
 * Funtion
 */

extern _Bool readData(void);
extern void readTemperature(void);
extern void readHumidity(void);
extern void readTemperatureAndHumidity(float_t *temperature, float_t *humidity);
extern uint16_t crc16 (uint8_t *ptr, uint8_t len);

#endif /* AM2315_AM2315_H_ */
