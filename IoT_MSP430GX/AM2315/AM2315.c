/*
 * AM2315.c
 *
 *  Created on: Jan 24, 2017
 *      Author: tri
 */

/*
 * Include lib
 */
#include "../include.h"
#include "AM2315.h"


extern _Bool readData(void){
    uint8_t reply[10];
    uint8_t temp, humidity;
    return true;

}

extern void readTemperature(void){
    if(! readData()) return true;
}

extern void readHumidity(void){
    if(! readData()) return true;
}
extern void readTemperatureAndHumidity(float_t *temperature, float_t *humidity){
//    if(! readData()) return false;
}

/* Funtion: uint16_t crc16 (uint8_t *ptr, uint8_t len)
 * Description: This program calculates the lenght of *ptr within the first len byte of the CRC.
 */
extern uint16_t crc16 (uint8_t *ptr, uint8_t len){
    uint16_t crc = 0xFFFF;
    uint16_t i;
    while(len --){
        crc ^= *ptr++;
        for(i = 0; i < 8; i++){
            if(crc & 0x01){
                crc>>=1;
                crc^=0xA001;
            }else {
                crc>>=1;
            }
        }
    }
    return crc;
}


