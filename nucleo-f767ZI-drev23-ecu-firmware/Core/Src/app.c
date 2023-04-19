/*
 * app.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <app.h>

#include "tasks/dev_task.h"
#include "tasks/apps_task.h"

struct app_data app = {0};

void app_create() {
	app.rtd_flag = false;
	app.system_shutdown = false;
	app.torque = 0;

	board_init(&app.board);

	assert(app.dev_task = dev_task_start(&app));
	assert(app.apps_task = apps_task_start(&app));
}

uint16_t apps1_read_count() {
	ADC_HandleTypeDef *hadc = &app.board.stm32f767.hadc1;
	uint16_t count;
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	count = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
	return count;
}

uint16_t apps2_read_count() {
	ADC_HandleTypeDef *hadc = &app.board.stm32f767.hadc2;
	uint16_t count;
	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	count = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
	return count;
}
