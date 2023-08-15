/*
 * app.h
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#ifndef APP_H_
#define APP_H_

#include <stdbool.h>
#include <stdint.h>
#include "board/board.h"

// 0.12V - 1.8V * (3/2) resistor divider => 0.18V - 2.7V
#define BSE1_MIN 155//Brake emulator min: 155 //Theoretical value (ADC max): 0
#define BSE1_MAX 2238 //Brake emulator max: 2240 //Theoretical value (ADC max): 4095
// 0.14V -1.8V *(3/2) => 0.21V - 2.7V
#define BSE2_MIN 175 //Brake emulator min: 175 //Theoretical value (ADC max): 0
#define BSE2_MAX 2250 //Brake emulator max: 2250 //Theoretical value (ADC max): 4095

struct app_data {
	// 
	short torque;
	float brakePercentage;
	bool system_shutdown;
	bool rtd_flag;
	struct board board;

	TaskHandle_t dev_task;
	TaskHandle_t apps_task;
	TaskHandle_t bse_task;
};

void app_create();

#endif /* APP_H_ */
