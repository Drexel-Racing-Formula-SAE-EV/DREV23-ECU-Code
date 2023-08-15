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

void pressTrans_init(struct pressTrans *pressTrans,
		uint16_t min,
		uint16_t max,
		void *handle,
		uint8_t channelNum,
		uint16_t(*read_count)(void *arg)
		);

long map(long x,
		long in_min,
		long in_max,
		long out_min,
		long out_max
		);

float adc_raw_to_percent(struct pressTrans *root, uint16_t raw);

uint16_t percent_to_trq_hex(short percent);

uint8_t check_implausability(short L, short R);

uint8_t switch_to_defined_channel (struct pressTrans *root);
#endif /* INC_EXT_DRIVERS_PRESSTRANS_H_ */
