/*
 * pressTrans.h
 *
 *  Created on: April 24, 2023
 *      Author: Benedict Hofmockel
 */

#ifndef INC_EXT_DRIVERS_PRESSTRANS_H_
#define INC_EXT_DRIVERS_PRESSTRANS_H_

#include <stdint.h>

struct pressTrans {
	uint16_t min;
	uint16_t max;

	uint16_t count;
	short percent;

	void *handle; //ADC handle goes here
	uint8_t channelNum; //ADC channel number

	uint16_t(*read_count)(void *arg); //this is a function pointer in C, kinda weird ain't it.
};

void pressTransduc_init(struct pressTrans *pressTrans,
		uint16_t min,
		uint16_t max,
		void *handle,
		uint8_t channelNum,
		uint16_t(*read_count)(void *arg));

long map(long x,
		long in_min,
		long in_max,
		long out_min,
		long out_max);

//short adc_raw_to_percent(struct pressTrans *root,
//		uint16_t raw);

uint16_t percent_to_trq_hex(short percent);

uint8_t check_implausability(short L,
		short R);

#endif /* INC_EXT_DRIVERS_PRESSTRANS_H_ */
