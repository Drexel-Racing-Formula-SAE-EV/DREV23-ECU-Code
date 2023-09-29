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

	uint16_t count;
	float percent;

	void *handle; //ADC handle goes here
	uint32_t channelNum; //ADC channel number

	uint16_t(*read_count)(void *hadc); //this is a function pointer in C, kinda weird ain't it.
};

void pressTrans_init(struct pressTrans *pressTrans, uint16_t min, uint16_t max, void *handle, uint8_t channelNum, uint16_t(*read_count)(void *hadc));

float presstransGetPercent(struct pressTrans *root);

uint8_t presstransCheckImplausability(float L, float R, int thresh, int count);

uint8_t switchChannelADC (struct pressTrans *root);
#endif /* INC_EXT_DRIVERS_PRESSTRANS_H_ */
