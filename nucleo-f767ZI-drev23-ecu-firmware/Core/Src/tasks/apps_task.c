/**
 * @file apps_task.c
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief
 * @version 0.1
 * @date 2023-04-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "tasks/apps_task.h"

/**
 * @brief Actual APPS task function
 *
 * @param arg App_data struct pointer converted to void pointer
 */
void apps_task_fn(void *arg);

TaskHandle_t apps_task_start(struct app_data *data)
{
    TaskHandle_t handle;
    xTaskCreate(apps_task_fn, "APPS task", 128, (void *)data, 7, &handle);
    return handle;
}

void apps_task_fn(void *arg)
{
    struct app_data *data = (struct app_data *)arg;
    struct poten *apps1 = &data->board.apps1;
    struct poten *apps2 = &data->board.apps2;

    uint16_t adc_raw[2];

    while (1)
    {
        adc_raw[0] = apps1->read_count();
        adc_raw[1] = apps2->read_count();
        osDelay(100);
    }
}