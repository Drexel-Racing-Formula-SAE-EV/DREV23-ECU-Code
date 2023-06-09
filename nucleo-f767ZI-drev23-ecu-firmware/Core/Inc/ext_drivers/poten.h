/*
 * poten.h
 *
 *  Created on: Mar 14, 2023
 *      Author: colebardin
 */

#ifndef INC_EXT_DRIVERS_POTEN_H_
#define INC_EXT_DRIVERS_POTEN_H_

#include <stdint.h>

struct poten {
	uint16_t min;
	uint16_t max;

	uint16_t count;
	short percent;

	void *handle;

	uint16_t(*read_count)(void *arg);
};

void poten_init(struct poten *poten, uint16_t min, uint16_t max, void *handle, uint16_t(*read_count)(void *arg));

long double map(long x, long in_min, long in_max, long out_min, long out_max);

float adc_raw_to_percent(struct poten *root, uint16_t raw);

uint16_t percent_to_trq_hex(float percent);

uint8_t check_implausability(short L, short R);

#endif /* INC_EXT_DRIVERS_POTEN_H_ */
