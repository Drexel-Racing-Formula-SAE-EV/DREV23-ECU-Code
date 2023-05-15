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

#define APPS1_MIN 502
#define APPS1_MAX 1900
#define APPS2_MIN 890
#define APPS2_MAX 2105

struct app_data {
	// 
	short torque;
	bool system_shutdown;
	bool rtd_flag;
	struct board board;

	TaskHandle_t dev_task;
	TaskHandle_t apps_task;
	TaskHandle_t canbus_task;
};

void app_create();

#endif /* APP_H_ */
