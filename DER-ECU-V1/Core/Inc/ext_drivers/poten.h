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
	float percent;

	void *handle;

	uint16_t(*read_count)(void *hadc);
};

void poten_init(struct poten *poten, uint16_t min, uint16_t max, void *handle, uint16_t(*read_count)(void *hadc));

float potenGetPercent(struct poten *root);

uint16_t percentToThrottleHex(float percent);

uint8_t potenCheckImplausability(float L, float R, int thresh, int count);

#endif /* INC_EXT_DRIVERS_POTEN_H_ */
