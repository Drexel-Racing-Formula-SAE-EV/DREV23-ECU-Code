/*
 * app.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include "app.h"

#include "tasks/dev_task.h"
#include "tasks/apps_task.h"
#include "tasks/canbus_task.h"
#include "tasks/rtd_task.h"

struct app_data app = {0};

void app_create() {
	app.rtd_flag = false;
	app.system_shutdown = false;
	app.torque = 0;

	board_init(&app.board);

	//assert(app.dev_task = dev_task_start(&app));
	assert(app.canbus_task = canbus_task_start(&app));
	assert(app.apps_task = apps_task_start(&app));
	assert(app.rtd_task = rtd_task_start(&app));
}
