/**
* @file rtd_task.c
* @author Cole Bardin (cab572@drexel.edu)
* @brief
* @version 0.1
* @date 2023-09-28
*
* @copyright Copyright (c) 2023
*
*/

#include <tasks/rtd_task.h>
#include "main.h"

/**
* @brief Actual RTD task function
*
* @param arg App_data struct pointer converted to void pointer
*/
void rtd_task_fn(void *arg);

TaskHandle_t rtd_task_start(struct app_data *data){
   TaskHandle_t handle;
   xTaskCreate(rtd_task_fn, "RTD task", 128, (void *)data, 20, &handle);
   return handle;
}

void rtd_task_fn(void *arg){
    struct app_data *data = (struct app_data *)arg;
	   
	while(1){
		if(!data->rtdFlag){
			
			osDelay(1);
		}

		rtd_task_delete(data->rtd_task);
	}
}

void rtd_task_delete(TaskHandle_t task){

}
