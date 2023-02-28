/*
 * poten.h
 *
 *  Created on: Feb 27, 2023
 *      Author: colebardin
 */

#ifndef POTEN_H_
#define POTEN_H_

#include <stdint.h>

struct poten {
	uint16_t min;
	uint16_t max;
};

void poten_init(struct poten *poten, uint16_t min, uint16_t max);

long map(long x, long in_min, long in_max, long out_min, long out_max);

short adc_raw_to_percent(struct poten *root, uint16_t raw);

uint16_t percent_to_trq_hex(short percent);

uint8_t check_implausability(short L, short R);

#endif /* INC_POTEN_POTEN_H_ */
