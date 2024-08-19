/*
 * utils.c
 *
 *  Created on: Jan 27, 2023
 *      Author: derso
 */


#include "utils.h"
#include "main.h"
#include "math.h"

#define DEC_POINT '.'

void string2Float(float value, uint8_t digits, uint8_t max_dig, char *str, uint8_t *length){
	uint8_t sig = 0;

	if(value < 0.f){
		sig = 1;
		value = -value;
	}

	float rounding = 0.5f;
	for (uint8_t i = 0; i < digits; ++i) {
		rounding /= 10.f;
	}
	value += rounding;
	uint8_t nint;
	uint32_t int_part = (uint32_t) value;
	if(int_part != 0){
		double nintF = log10(int_part);
		nint = ((uint8_t)nintF)+1;
	}else{
		nint = 1;
	}

	uint8_t msg[nint + digits +1 + sig];

	uint32_t int_part_temp = int_part;

	if(sig) msg[0] = '-';

	for(uint8_t i = 0; i < nint; i++){
		msg[nint - i - 1 + sig] = int_part_temp%10 + 48;
		int_part_temp = int_part_temp/10;
	}
	if(digits)msg[nint + sig] = DEC_POINT;

	float dec = value - ((float)int_part);

	for(uint8_t i = 0; i < digits; i++){
		dec = dec * 10;
		msg[nint + i + 1 + sig] = (uint8_t)(((uint32_t)dec)%10)+48;
	}

	*length = nint + digits +1 + sig;
	if(*length > max_dig) return;

	for(uint8_t i = 0; i < *length; i++){
		str[i] = msg[i];
	}

}
