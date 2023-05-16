/**
 * @file rtd_task.c
 * @author Amar Patel (arp397@drexel.edu)
 * @brief
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "tasks/rtd_task.h"


void rtd_task_fn(void *arg);

TaskHandle_t rtd_task_start(struct app_data *data) {
    TaskHandle_t handle;
    xTaskCreate(rtd_task_fn, "RTD Task", 128, (void *)data, 8, &handle);
    return handle;
}

void rtd_task_fn(void *arg) {
	#define HIGH_VALUE ((GPIO_PinState) 1)
    struct app_data *data = (struct app_data *)arg;


    //INPUTS
    int tractiveSystemValue; // ??
    int brakeValue; // ??
    int rtdButtonValue;


    while(1) {
    	tractiveSystemValue = null; //Where does this come from
    	brakeValue = null; //change once the brake values are confirmed
    	rtdButtonValue = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);

        if (tractiveSystemValue == 1 && brakeValue == 1 && rtdButtonValue == 1) {
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, HIGH_VALUE); //Set Buzzer High

			//ENABLE APPS

			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, HIGH_VALUE); //Set RFE High

			HAL_Delay(650);

			 if (tractiveSystemValue == 1 && brakeValue == 1) {
				 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, HIGH_VALUE);
			 }
			 else {
				 //logging error and sending ERROR message
			 }
        	
        }
        osDelay(100);
    }
}
