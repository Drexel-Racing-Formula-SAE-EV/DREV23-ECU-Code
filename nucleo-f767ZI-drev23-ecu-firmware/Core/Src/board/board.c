/*
 * board.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <board/board.h>
#include "app.h"

void board_init(struct board* dev) {
	stm32f767_init(&dev->stm32f767);

	pressTrans_init(&dev->bse1, BSE1_MIN, BSE1_MAX, &dev->stm32f767.hadc3, 13, bse_read_count);
	pressTrans_init(&dev->bse2, BSE2_MIN, BSE2_MAX, &dev->stm32f767.hadc3, 9, bse_read_count);
}

uint16_t bse_read_count (void *arg){
//		struct poten *apps = (struct poten *)arg;
//		ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)apps->handle;
//		uint16_t count;
//
//		HAL_ADC_Start(hadc);
//		HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
//		count = HAL_ADC_GetValue(hadc);
//		HAL_ADC_Stop(hadc);
//
//		apps->count = count;
//
//		return count;
	struct pressTrans *pt = (struct pressTrans *)arg;
	ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *) pt->handle;
	uint16_t count;

	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	count = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);

	pt->count = count;

	return count;
}
