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

	poten_init(&dev->apps1, APPS1_MIN, APPS1_MAX, &dev->stm32f767.hadc1, apps_read_count);
	poten_init(&dev->apps2, APPS2_MIN, APPS2_MAX, &dev->stm32f767.hadc2, apps_read_count);
}

uint16_t apps_read_count(void *arg) {
	struct poten *apps = (struct poten *)arg;
	ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *)apps->handle;
	uint16_t count;

	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	count = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);

	apps->count = count;

	return count;
}
