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

	char msg[128];

    while (1)
    {
    	/* digitize the analog signal of the Brake pressure Transducers*/
    	switch_to_defined_channel(bse1);
		bse1->raw_value = bse1->read_count((void *)bse1);
		osDelay(50); //TODO: this is needed here, please find out why
    	switch_to_defined_channel(bse2);
    	bse2->raw_value = bse2->read_count((void *)bse2);

    	/* Calculate per device percentage and combined percentage */
//    	bse1->percent = ((float)bse1->raw_value / (float)bse1->max)* 100;
//    	bse2->percent = ((float)bse2->raw_value / (float)bse2->max)* 100;
    	bse1->percent = adc_raw_to_percent(bse1, bse1->raw_value);
    	bse2->percent = adc_raw_to_percent(bse2, bse2->raw_value);
    	data->brakePercentage = (bse1->percent + bse2->percent) / 2;

		sprintf(msg,"| PT1_raw: %hu\t| PT1_perc: %hu\t| PT2_raw: %hu\t| PT2_perc: %hu\t| brakePerc: %d |\r\n", bse1->raw_value, bse1->percent, bse2->raw_value, bse2->percent, data->brakePercentage); //TODO: PLEASE, FOR THE LOVE OF THE ORGANIZATION, CHANGE adc_raw_to_percent TO BE FLAOTING POINT BASED AND ALSO CHANGE CONVERSION RANGE BETWEEN RAW AND SENT VALUES
		HAL_UART_Transmit(&data->board.stm32f767.huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    }

    // Get rid of unused warning for dev task.
    (void)data;
}
