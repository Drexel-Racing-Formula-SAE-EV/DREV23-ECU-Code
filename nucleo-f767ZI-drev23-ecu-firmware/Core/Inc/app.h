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

#define APPS1_MIN 339
#define APPS1_MAX 1900
#define APPS2_MIN 810
#define APPS2_MAX 2158

#define BAMOCAR_CANBUS_RXID 0x201
#define BAMOCAR_CANBUS_TORQUE_CMD 0x90

struct app_data {
	// 
	float torque;
	bool system_shutdown;
	bool rtd_flag;
	struct board board;

	TaskHandle_t dev_task;
	TaskHandle_t apps_task;
	TaskHandle_t canbus_task;
};

void app_create();

#endif /* APP_H_ */
