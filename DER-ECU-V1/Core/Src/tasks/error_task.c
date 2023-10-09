/**
 * @file error_task.c
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief
 * @version 0.1
 * @date 2023-09-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"
#include "tasks/error_task.h"

/**
 * @brief Actual ERROR task function
 *
 * @param arg App_data struct pointer converted to void pointer
 */
void error_task_fn(void *arg);

TaskHandle_t error_task_start(struct app_data *data) {
    TaskHandle_t handle;
    xTaskCreate(error_task_fn, "ERROR task", 128, (void *)data, 10, &handle);
    return handle;
}

void error_task_fn(void *arg) {
    struct app_data *data = (struct app_data *)arg;

    uint32_t entryTicksCount;

    while(1){
        entryTicksCount = osKernelGetTickCount();

        if(!data->hardSystemFault){
            if(data->appsFaultFlag || data->bseFaultFlag){
                data->hardSystemFault = true;
                setRFE(0);
            }
        }
        
        if(data->bppcFaultFlag){
            data->softSystemFault = true;
            setRFE(0);
        }else{
            data->softSystemFault = false;
            setRFE(1);
        }

        osDelayUntil(entryTicksCount + (1000 / ERROR_FREQ));
    }
}
