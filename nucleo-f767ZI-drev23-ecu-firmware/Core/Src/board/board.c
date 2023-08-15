/**
 * @file board.c
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief 
 * @version 0.1
 * @date 2023-04-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <board/board.h>
#include "app.h"

void board_init(struct board* dev) {
	stm32f767_init(&dev->stm32f767);

	poten_init(&dev->apps1, APPS1_MIN, APPS1_MAX, &dev->stm32f767.hadc1, apps_read_count);
	poten_init(&dev->apps2, APPS2_MIN, APPS2_MAX, &dev->stm32f767.hadc2, apps_read_count);
	pressTrans_init(&dev->bse1, BSE1_MIN, BSE1_MAX, &dev->stm32f767.hadc3, 13, bse_read_value);
	pressTrans_init(&dev->bse2, BSE2_MIN, BSE2_MAX, &dev->stm32f767.hadc3, 9, bse_read_value);

	canbus_device_init(&dev->canbus_device, &dev->stm32f767.hcan1, &dev->stm32f767.can1_txheader);
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

uint16_t bse_read_value (void *arg){
	struct pressTrans *pt = (struct pressTrans *)arg;
	ADC_HandleTypeDef *hadc = (ADC_HandleTypeDef *) pt->handle;
	uint16_t raw_value;

	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	raw_value = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);

	pt->raw_value = raw_value;

	return raw_value;
}
