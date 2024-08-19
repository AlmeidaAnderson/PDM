/*
 * EEPROM.c
 *
 *  Created on: Jan 27, 2023
 *      Author: derso
 */


#include "EEPROM.h"

const uint16_t ADDRESS_EEPROM =  0b10100000;

uint32_t lstTimeEEPROM = 0;

I2C_HandleTypeDef *hi2c;

void initEEPROM(I2C_HandleTypeDef *_hi2c){
	hi2c =  _hi2c;

	lstTimeEEPROM = HAL_GetTick();
}


uint8_t readEEPROM(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t size, uint16_t address){
	HAL_StatusTypeDef status;

	while(HAL_GetTick() - lstTimeEEPROM < 5){};

	uint8_t adr[2];
	adr[0] = address >> 8;
	adr[1] = address &0xFF;

	status = HAL_I2C_Master_Transmit(hi2c, ADDRESS_EEPROM, adr, 2,1000);
	if(status == HAL_OK){
		status = HAL_I2C_Master_Receive(hi2c,  ADDRESS_EEPROM, pData, size,1000);
	}

	lstTimeEEPROM = HAL_GetTick();
	return status == HAL_OK ? 1 : 0;
}

uint8_t writeEEPROM(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint8_t size, uint16_t address){

	HAL_StatusTypeDef status;

	while(HAL_GetTick() - lstTimeEEPROM < 5){};

	uint8_t data[size+2];
	data[0] = address >> 8;
	data[1] = address &0xFF;

	for(uint8_t i = 0; i < size; i++){
		data[i+2] = pData[i];
	}

	status = HAL_I2C_Master_Transmit(hi2c,ADDRESS_EEPROM, data, size+2,1000);

	lstTimeEEPROM = HAL_GetTick();

	return status == HAL_OK ? 1 : 0;

}

#define TRANSMISSION_DELAY_ADDR		0x0000
#define TRANSMISSION_STATUS_ADDR	0x0002

uint8_t setTransmissionDelay(uint16_t txDelay){

	uint8_t pData[2];
	pData[0] = txDelay&0xFF;
	pData[1] = (txDelay >> 8)&0xFF;

	return writeEEPROM(hi2c, pData, 2, TRANSMISSION_DELAY_ADDR);	//Write the float to the EEPROM

}

uint8_t getTransmissionDelay(uint16_t *txDelay){
	uint8_t status;

	uint8_t pData[2];

	status = readEEPROM(hi2c, pData, 2, TRANSMISSION_DELAY_ADDR);

	*txDelay = pData[1] << 8 | pData[0];

	return status;
}

uint8_t setTransmissionStatus(uint8_t status_COMM){

	uint8_t pData = status_COMM;

	return writeEEPROM(hi2c, &pData, 1, TRANSMISSION_STATUS_ADDR);	//Write the float to the EEPROM

}

uint8_t getTransmissionStatus(uint8_t *status_COMM){
	uint8_t status;

	uint8_t pData;

	status = readEEPROM(hi2c, &pData, 1, TRANSMISSION_STATUS_ADDR);

	*status_COMM = pData;

	return status;
}

#define CURRENT_CONFIG_CHANNEL_ADDR_start 0x0003
#define CURRENT_CONFIG_CHANNEL_ADDR_SIZE 4

uint8_t setChannelCurrent(float current, uint8_t channel){

	uint32_t val = * (uint32_t *) &current;	//Stores the float bits to a int

	uint8_t pData[4];						//Create a pointer to send

	pData[0] = (val >> 24)&0xFF;			//Populates the
	pData[1] = (val >> 16)&0xFF;			//pointer with
	pData[2] = (val >> 8)&0xFF;				//the floats
	pData[3] = (val)&0xFF;					//bits

	return writeEEPROM(hi2c, pData, 4, CURRENT_CONFIG_CHANNEL_ADDR_start+CURRENT_CONFIG_CHANNEL_ADDR_SIZE*channel);	//Write the float to the EEPROM



}

uint8_t getChannelCurrent(float *current, uint8_t channel){
	uint8_t status;

	uint8_t pData[4];	//Creates a pointer to receive the data

	status = readEEPROM(hi2c, pData, 4, CURRENT_CONFIG_CHANNEL_ADDR_start+CURRENT_CONFIG_CHANNEL_ADDR_SIZE*channel);	//Read the data at the channel address

	uint32_t val = pData[0] << 24 | pData[1] << 16 | pData[2] << 8 | pData[3];	//Creates a 32 bit int with the bytes read

	float k = *(float *)&val;	//Converts the bits to a float
	*current = k;

	return status;
}
