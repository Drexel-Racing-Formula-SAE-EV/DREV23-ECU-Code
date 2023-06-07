/*
 * app.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <app.h>
#include <tasks/bse_task.h>
#include "tasks/rtd_task.h"

#include "tasks/dev_task.h"

struct app_data app = {0};

void app_create() {
	app.APPS_Control_flag = false;
	app.system_shutdown = false;
	app.torque = 0;

	board_init(&app.board);

	assert(app.dev_task = dev_task_start(&app));
	assert(app.rtd_task = rtd_task_start(&app));
	assert(app.ppc_task = ppc_task_start(&app));
}
