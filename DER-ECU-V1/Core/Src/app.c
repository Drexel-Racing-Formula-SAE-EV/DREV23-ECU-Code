/*
 * app.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include "app.h"
#include <tasks/bse_task.h>

#include "tasks/dev_task.h"
#include "tasks/bse_task.h"
#include "tasks/apps_task.h"
#include "tasks/canbus_task.h"

struct app_data app = {0};

void app_create() {
	app.appsFaultFlag = false;
	app.bseFaultFlag = false;
	app.systemShutdown = false;
	app.brakeLightState = false;

	app.torquePercent = 0;
	app.brakePercent = 0;

	board_init(&app.board);

	//assert(app.dev_task = dev_task_start(&app));
	assert(app.canbus_task = canbus_task_start(&app));
	assert(app.bse_task = bse_task_start(&app));
	assert(app.apps_task = apps_task_start(&app));
}
