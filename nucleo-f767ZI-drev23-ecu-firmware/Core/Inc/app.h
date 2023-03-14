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

struct app_data {
	// 
	short torque;
	bool system_shutdown;
	bool rtd_flag;
	struct board board;

	TaskHandle_t dev_task;
};

void app_create();

#endif /* APP_H_ */
