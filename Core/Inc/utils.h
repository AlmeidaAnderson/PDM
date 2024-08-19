/*
 * utils.h
 *
 *  Created on: Jan 27, 2023
 *      Author: derso
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "main.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

void string2Float(float value, uint8_t digits, uint8_t max_dig, char *str, uint8_t *length);

#endif /* INC_UTILS_H_ */
