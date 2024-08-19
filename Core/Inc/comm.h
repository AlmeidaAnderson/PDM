/*
 * comm.h
 *
 *  Created on: Aug 14, 2024
 *      Author: derso
 */

#ifndef INC_COMM_H_
#define INC_COMM_H_

#include "main.h"
#include "utils.h"
#include "usbd_cdc_if.h"
#include "EEPROM.h"

uint8_t initComm();
void USB_CDC_RxHandler(uint8_t*, uint32_t);

void transmitMessage(uint32_t time);

#endif /* INC_COMM_H_ */
