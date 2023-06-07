/**
 * @file rtd_task.c
 * @author Amar Patel (arp397@drexel.edu)
 * @brief
 * @version 0.1
 * @date 2023-06-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "tasks/ppc_task.h"


void ppc_task_fn(void *arg);

TaskHandle_t ppc_task_start(struct app_data *data) {
    TaskHandle_t handle;
    xTaskCreate(ppc_task_fn, "PPC Task", 128, (void *)data, 8, &handle);
    return handle;
}

void ppc_task_fn(void *arg) {
	#define HIGH_VALUE ((GPIO_PinState) 1)
	#define LOW_VALUE ((GPIO_PinState) 0)
	#define BREAK_THRESHOLD ((int16_t) 0.10) //TODO> NEED TO CHANGE TO ACTUAL VALUE
	#define APPS_SHUTDOWN_THRESHOLD ((int16_t) 0.25)
	#define APPS_RESEND_POWER_THRESHOLD ((int16_t) 0.05)

    struct app_data *data = (struct app_data *)arg;

    //INPUTS
    int16_t appPercentage;
    int16_t brakePercentage;
    bool ppcActivated = false;


    while(1) {
    	appPercentage = data -> torque;
    	brakePercentage = data -> brakePercentage;

    	if ((brakePercentage > BREAK_THRESHOLD) && (appPercentage > APPS_SHUTDOWN_THRESHOLD)) {
    		ppcActivated = true;
    		HAL_GPIO_WritePin(BAMOCAR_FRG_RUN_Activate_GPIO_Port, BAMOCAR_FRG_RUN_Activate_Pin, LOW_VALUE);
    		//TODO: Add logging that BPPC case was activated
    	}

    	if (ppcActivated && (appPercentage > APPS_RESEND_POWER_THRESHOLD)) {
    		HAL_GPIO_WritePin(BAMOCAR_FRG_RUN_Activate_GPIO_Port, BAMOCAR_FRG_RUN_Activate_Pin, HIGH_VALUE);
    		ppcActivated = false;
    		//TODO: Add logging that
    	}

        osDelay(100);
    }
}
