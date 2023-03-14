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

#define APPS1_MIN 0
#define APPS1_MAX 4095
#define APPS2_MIN 0
#define APPS2_MAX 4095

struct app_data {
	// 
	short torque;
	bool system_shutdown;
	bool rtd_flag;
	struct board board;

	TaskHandle_t dev_task;
};

void app_create();

uint16_t apps1_read_count();
uint16_t apps2_read_count();

#endif /* APP_H_ */
