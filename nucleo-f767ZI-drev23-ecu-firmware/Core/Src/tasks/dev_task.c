/*
 * dev_task.c
 *
 *  Created on: Mar 14, 2023
 *      Author: colebardin
 */

#include "tasks/dev_task.h"

void dev_task_fn(void *args);

TaskHandle_t dev_task_start(struct app_data *data) {
    TaskHandle_t handle;
    xTaskCreate(dev_task_fn, "Development Task", 128, (void *)data, tskIDLE_PRIORITY + 1, &handle);
    return handle;
}

void dev_task_fn(void *args) {
    struct app_data *data = (struct app_data *)args;
    struct poten *apps1 = &data->board.apps1;
    struct poten *apps2 = &data->board.apps2;

    uint16_t adc_raw[2];

    while(1) {
        adc_raw[0] = apps1->read_count();
        adc_raw[1] = apps2->read_count();
        osDelay(100);
    }
}