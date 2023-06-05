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
    int tractiveSystemValue;
    int brakeValue;
    int rtdButtonValue;


    while(1) {
    	tractiveSystemValue = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9); //TSAL HV signal in Altium
    	brakeValue = 1; //TODO: change once the brake flag is done
    	rtdButtonValue = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

        if (tractiveSystemValue == 1 && brakeValue == 1 && rtdButtonValue == 1) {
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_13, HIGH_VALUE); //Set Buzzer High

			data->APPS_Control_flag = true;

			/* Setting Bamocar RFE and FRG/RUN signals high */
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, HIGH_VALUE); //Set BAMOCAR RFE High
			osDelay(600); //

	    	tractiveSystemValue = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_9); //change once the brake values are confirmed
	    	brakeValue = 1; //change once the brake values are confirmed

			 if (tractiveSystemValue == 1 && brakeValue == 1) {
				 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_12, HIGH_VALUE); //set BAMOCAR FRG RUN HIGH
				 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			 }
			 else {
				 //TODO: logging error and sending ERROR message
			 }
        }
        osDelay(100);
    }
}
