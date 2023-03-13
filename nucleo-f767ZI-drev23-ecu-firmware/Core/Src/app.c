/*
 * app.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <app.h>

struct app_data app = {0};

void app_create(struct app_data *data) {
	data->rtd_flag = false;
	data->system_shutdown = false;
	data->torque = 0;

	board_init(&data->board);

	// Create tasks
}
