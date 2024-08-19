/*
 * analog.c
 *
 *  Created on: Jan 26, 2023
 *      Author: derso
 */

#include "main.h"
#include "utils.h"

#define CONV_SIZE 9

uint32_t dma_values[CONV_SIZE];

ADC_HandleTypeDef* hadc;

const float ADC_PARAM[CONV_SIZE][2] = {
		{0.00451247059549503,	0.00499522123572937	},	//VSS
		{0.00458452171742679,	-0.14378501661517100},	//VS4
		{0.00406673462085215,	-0.03340410964194260},	//IS4
		{0.00451578404934587,	0.00802584511215443	},	//VS3
		{0.00406673462085215,	-0.03340410964194260},	//IS3
		{0.00451902643623771,	-0.00422189384020477},	//VS2
		{0.00406673462085215,	-0.03340410964194260},	//IS2
		{0.00450319142812937,	0.03147624044763120	},	//VS1
		{0.00406673462085215,	-0.03340410964194260}		//IS1
};


/**
  * @brief  Analog initialization
  * @param  hadc: ADC handle
  * @retval None
  */
uint8_t initAnalog(ADC_HandleTypeDef* _hadc){

	hadc = _hadc; //Stores the ADC to a local variable

	if(HAL_ADCEx_Calibration_Start(hadc) != HAL_OK) return 0;			//Starts the ADC calibration
	if(HAL_ADC_Start_DMA(hadc, dma_values, CONV_SIZE) != HAL_OK) return 0;		//Starts the ADC DMA

	return 1;

}

uint64_t sumADC[CONV_SIZE];
uint64_t cntADC = 1;

#define FULL_BIT 0
uint8_t status_ADC = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

	if(bitRead(status_ADC, FULL_BIT)) return;
	if(cntADC == 0xFFFFFFFFFFFFFFFF){
		bitSet(status_ADC, FULL_BIT);
		return;
	}
	for(uint8_t i = 0; i < CONV_SIZE; i++){
		if(sumADC[i] > 0xFFFFFFFFFFFFFFFF - dma_values[i]){
			bitSet(status_ADC, FULL_BIT);
			return;
		}
	}

	for(uint8_t i = 0; i < CONV_SIZE; i++){
		sumADC[i] += dma_values[i];
	}
	cntADC++;

}

uint32_t readRAW(uint32_t *read){

	HAL_ADC_Stop_DMA(hadc);
	uint32_t cnt = cntADC;
	for(uint8_t i = 0; i < CONV_SIZE; i++){
		sumADC[i] = sumADC[i]/cntADC;
		read[i] = sumADC[i];
	}
	HAL_ADC_Start_DMA(hadc, dma_values, CONV_SIZE);

	bitClear(status_ADC, FULL_BIT);
	cntADC = 1;
	return cnt;

}

uint32_t readValues(float *read){
	uint32_t _read[CONV_SIZE];
	uint32_t cnt = readRAW(_read);

	for(uint8_t i = 0; i < CONV_SIZE; i++){
		read[i] = ((float)_read[i]) * ADC_PARAM[i][0] + ADC_PARAM[i][1];
	}
	return cnt;
}
