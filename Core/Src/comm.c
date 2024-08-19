/*
 * comm.c
 *
 *  Created on: Aug 14, 2024
 *      Author: derso
 */

#include "comm.h"

uint8_t status_COMM = 1;
uint16_t txDelay = 500;

#define ENABLE_SIZE 6
const char enable_msg[ENABLE_SIZE] = "ENABLE";

#define DISABLE_SIZE 7
const char disable_msg[DISABLE_SIZE] = "DISABLE";

#define USB_DEBUG 0

uint8_t initComm(){

	if(!getTransmissionDelay(&txDelay)) return 0;

	if(txDelay < 250){
		if(!setTransmissionDelay(250)) return 0;
		txDelay = 250;
	}

	if(!getTransmissionStatus(&status_COMM)) return 0;

	if(bitRead(status_COMM,USB_DEBUG)){

		uint8_t msg_enabled[51] = "USB Debug Enabled with a transmission delay     ms\n";

		msg_enabled[44] = (txDelay/1000)%10+'0';
		msg_enabled[45] = (txDelay/100)%10+'0';
		msg_enabled[46] = (txDelay/10)%10+'0';
		msg_enabled[47] = (txDelay/1)%10+'0';

		CDC_Transmit_FS(msg_enabled, 51);
	}else{
		CDC_Transmit_FS("USB Debug Disabled\n", 19);
	}

	return 1;
}

void USB_CDC_RxHandler(uint8_t* Buf, uint32_t Len){
	uint8_t cnt_state = 0;
	if(Len >= ENABLE_SIZE && !bitRead(status_COMM,USB_DEBUG)){
		for(uint8_t i = 0; i < ENABLE_SIZE; i++){
			if(Buf[i] != enable_msg[i]){
				break;
			}
			cnt_state++;
		}
		if(cnt_state == ENABLE_SIZE){

			uint8_t lstStatus = status_COMM;

			bitSet(status_COMM, USB_DEBUG);

			if(!setTransmissionStatus(status_COMM)){
				CDC_Transmit_FS("EEPROM ERROR\n", 13);
				status_COMM = lstStatus;
				return;
			}

			uint8_t msg_enabled[51] = "USB Debug Enabled with a transmission delay     ms\n";

			msg_enabled[44] = (txDelay/1000)%10+'0';
			msg_enabled[45] = (txDelay/100)%10+'0';
			msg_enabled[46] = (txDelay/10)%10+'0';
			msg_enabled[47] = (txDelay/1)%10+'0';

			CDC_Transmit_FS(msg_enabled, 51);
			return;
		}
	}

	cnt_state = 0;

	if(Len >= DISABLE_SIZE && bitRead(status_COMM,USB_DEBUG)){
		for(uint8_t i = 0; i < DISABLE_SIZE; i++){
			if(Buf[i] != disable_msg[i]){
				break;
			}
			cnt_state++;
		}
		if(cnt_state == DISABLE_SIZE){
			uint8_t lstStatus = status_COMM;

			bitClear(status_COMM, USB_DEBUG);

			if(!setTransmissionStatus(status_COMM)){
				CDC_Transmit_FS("EEPROM ERROR\n", 13);
				status_COMM = lstStatus;
				return;
			}

			CDC_Transmit_FS("USB Debug Disabled\n", 19);
			return;
		}
	}


	if(Len >= 5 && Buf[0] == 'T'){

		uint16_t lstTxDelay = txDelay;

		txDelay = ((Buf[1]-'0')%10)*1000 + ((Buf[2]-'0')%10)*100 + ((Buf[3]-'0')%10)*10 + ((Buf[4]-'0')%10);
		if(!setTransmissionDelay(txDelay)){
			txDelay = lstTxDelay;
			CDC_Transmit_FS("EEPROM ERROR\n", 13);
			return;
		}

		if(txDelay < 250) txDelay = 250;

		uint8_t msg_tx[26] = "Transmission Delay     ms\n";

		msg_tx[19] = (txDelay/1000)%10+'0';
		msg_tx[20] = (txDelay/100)%10+'0';
		msg_tx[21] = (txDelay/10)%10+'0';
		msg_tx[22] = (txDelay/1)%10+'0';

		CDC_Transmit_FS(msg_tx, 26);
		return;

	}

}

extern float latestRead[9];

void transmitMessage(uint32_t time){

	char msg[600];

	uint8_t values[9][2];

	for(uint8_t i = 0; i < 9; i++){
		values[i][0] = (uint8_t)latestRead[i];
		values[i][1] = (uint8_t)((latestRead[i]-(float)values[i][0])*100.0);
	}


	sprintf(msg,
			"------%d------\nVCC - %d.%02d\n\nCHANNEL 1| VS1: %d.%02dV\n         | IS1: %d.%02dA\n--------------------------\nCHANNEL 2| VS2: %d.%02dV\n         | IS2: %d.%02dA\n--------------------------\nCHANNEL 3| VS3: %d.%02dV\n         | IS3: %d.%02dA\n--------------------------\nCHANNEL 4| VS4: %d.%02dV\n         | IS4: %d.%02dA\n\0",
			(int)time,values[0][0],values[0][1],
			values[7][0],values[7][1],values[8][0],values[8][1],
			values[5][0],values[5][1],values[6][0],values[6][1],
			values[3][0],values[3][1],values[4][0],values[4][1],
			values[1][0],values[1][1],values[2][0],values[2][1]);

	uint32_t cnt_char = strlen(msg);
	/*
	for(uint8_t i = 0; i < 9; i++)

	for(uint8_t i = 0; i < 9; i++){

		uint8_t len;
		char tmp[7];

		string2Float(latestRead[i], 2, 6, tmp, &len);
		if(len > 6) return;
		tmp[len] = ';';
		for(uint8_t j = 0; j < len+1; j++){
			msg[cnt_char + j] = tmp[j];
		}
		cnt_char +=len+1;

	}
	msg[cnt_char] = '\n';*/
	CDC_Transmit_FS(msg, cnt_char);

}
