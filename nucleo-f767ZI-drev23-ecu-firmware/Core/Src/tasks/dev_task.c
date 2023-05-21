/*
 * dev_task.c
 *
 *  Created on: Mar 14, 2023
 *      Author: colebardin
 */

#include "tasks/dev_task.h"

void dev_task_fn(void *args);

TaskHandle_t dev_task_start(struct app_data *data)
{
    TaskHandle_t handle;
    xTaskCreate(dev_task_fn, "Development Task", 128, (void *)data, tskIDLE_PRIORITY + 1, &handle);
    return handle;
}

void dev_task_fn(void *args)
{
    struct app_data *data = (struct app_data *)args;
    struct pressTrans *bse1 = &data->board.bse1;
    struct pressTrans *bse2 = &data->board.bse2;

    uint16_t adc_raw[2];

	char msg[64];

    while (1)
    {
    	adc_raw[0] = bse1->read_count((void *)bse1);
    	adc_raw[1] = bse2->read_count((void *)bse2);

		sprintf(msg,"PT1: %hu | PT2: %hu\r\n", adc_raw[0],adc_raw[1]);
		HAL_UART_Transmit(&data->board.stm32f767.huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    }

    // Get rid of unused warning for dev task.
    (void)data;
}
