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
    	bse1->percent = presstrans_raw_to_percent(bse1, bse1->raw_value);
    	bse2->percent = presstrans_raw_to_percent(bse2, bse2->raw_value);
    	data->brakePercentage = (bse1->percent + bse2->percent) / 2;
	}

    // Get rid of unused warning for dev task.
    (void)data;
}
