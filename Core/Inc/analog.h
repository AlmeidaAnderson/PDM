/*
 * analog.h
 *
 *  Created on: Jan 26, 2023
 *      Author: derso
 */

#ifndef INC_ANALOG_H_
#define INC_ANALOG_H_


uint8_t initAnalog(ADC_HandleTypeDef* _hadc);
uint32_t readRAW(uint32_t *read);
uint32_t readValues(float *read);

void stopDMA();
void startDMA();
#endif /* INC_ANALOG_H_ */
