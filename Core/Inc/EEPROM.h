/*
 * EEPROM.h
 *
 *  Created on: Jan 27, 2023
 *      Author: derso
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "main.h"

void initEEPROM(I2C_HandleTypeDef *_hi2c);

uint8_t readEEPROM(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t size, uint16_t address);
uint8_t writeEEPROM(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t size, uint16_t address);

uint8_t setTransmissionDelay(uint16_t txDelay);
uint8_t getTransmissionDelay(uint16_t *txDelay);
uint8_t setTransmissionStatus(uint8_t status_COMM);
uint8_t getTransmissionStatus(uint8_t *status_COMM);

#endif /* INC_EEPROM_H_ */
