/**
* @file bse_task.c
* @author Cole Bardin (cab572@drexel.edu)
* @brief
* @version 0.1
* @date 2023-8-15
*
* @copyright Copyright (c) 2023
*
*/

#include <tasks/bse_task.h>

/**
* @brief Actual BSE task function
*
* @param arg App_data struct pointer converted to void pointer
*/
void bse_task_fn(void *arg);

TaskHandle_t bse_task_start(struct app_data *data)
{
   TaskHandle_t handle;
   xTaskCreate(bse_task_fn, "BSE task", 128, (void *)data, 7, &handle);
   return handle;
}

void bse_task_fn(void *arg){
    struct app_data *data = (struct app_data *)arg;
    struct pressTrans *bse1 = &data->board.bse1;
    struct pressTrans *bse2 = &data->board.bse2;

	while (1){
		/* digitize the analog signal of the Brake pressure Transducers*/
		switch_to_defined_channel(bse1);
		bse1->raw_value = bse1->read_count((void *)bse1);
		osDelay(50); //TODO: this is needed here, please find out why
		switch_to_defined_channel(bse2);
		bse2->raw_value = bse2->read_count((void *)bse2);

		bse1->percent = adc_raw_to_percent(bse1, bse1->raw_value);
		bse2->percent = adc_raw_to_percent(bse2, bse2->raw_value);
		data->brakePercentage = (bse1->percent + bse2->percent) / 2;
		osDelay(50);
	}
}
