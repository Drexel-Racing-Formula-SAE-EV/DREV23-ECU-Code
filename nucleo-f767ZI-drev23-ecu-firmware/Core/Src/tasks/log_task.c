/*
 * log_task.c
 *
 *  Created on: June 9th, 2023
 *      Author: Benedict Hofmockel
 */
#include "tasks/log_task.h"

void log_task_fn(void *args);

TaskHandle_t log_task_start(struct app_data *data)
{
    TaskHandle_t handle;
    xTaskCreate(log_task_fn, "Logging Task that writes to SD card over SPI", 128, (void *)data, tskIDLE_PRIORITY + 1, &handle);
    return handle;
}

void log_task_fn(void *args)
{
    struct app_data *data = (struct app_data *)args;

	char msg[256];

    while (1)
    {

    }

    // Get rid of unused warning for log task.
    (void)data;
}
