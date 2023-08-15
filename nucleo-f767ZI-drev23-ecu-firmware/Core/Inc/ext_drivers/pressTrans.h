/*
 * pressTrans.h
 *
 *  Created on: April 24, 2023
 *      Author: Benedict Hofmockel
 */

#ifndef INC_EXT_DRIVERS_PRESSTRANS_H_
#define INC_EXT_DRIVERS_PRESSTRANS_H_

#include <stdint.h>
#include <stm32f7xx_hal.h>

struct pressTrans {
	uint16_t min;
	uint16_t max;

	uint16_t raw_value;
	float percent;

	void *handle; //ADC handle goes here
	uint32_t channelNum; //ADC channel number

	uint16_t(*read_count)(void *arg); //this is a function pointer in C, kinda weird ain't it.
};

void pressTrans_init(struct pressTrans *pressTrans, uint16_t min, uint16_t max, void *handle, uint8_t channelNum, uint16_t(*read_count)(void *arg));

float presstrans_raw_to_percent(struct pressTrans *root, uint16_t raw);

uint8_t presstrans_check_implausability(short L, short R);

uint8_t switch_to_defined_channel (struct pressTrans *root);
#endif /* INC_EXT_DRIVERS_PRESSTRANS_H_ */
