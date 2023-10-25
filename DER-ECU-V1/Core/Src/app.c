/**
* @file app.c
* @author Cole Bardin (cab572@drexel.edu)
* @brief
* @version 0.1
* @date 2023-03-19
*
* @copyright Copyright (c) 2023
*
*/

#include "app.h"
#include "tasks/bse_task.h"
#include "tasks/dev_task.h"
#include "tasks/rtd_task.h"
#include "tasks/error_task.h"
#include "tasks/bse_task.h"
#include "tasks/bppc_task.h"
#include "tasks/apps_task.h"
#include "tasks/canbus_task.h"
#include "tasks/cli_task.h"

struct app_data app = {0};

void app_create() {
	app.rtdFlag = false;

	app.hardSystemFault = false;
	app.softSystemFault = false;

	app.appsFaultFlag = false;
	app.bseFaultFlag = false;
	app.bppcFaultFlag = false;

	app.brakeLightState = false;

	app.throttlePercent = 0;
	app.brakePercent = 0;

	board_init(&app.board);

	HAL_UART_Receive_IT(app.board.cli.huart, app.board.cli.line, 1);
	//assert(app.dev_task = dev_task_start(&app));
	assert(app.cli_task = cli_task_start(&app));
	assert(app.rtd_task = rtd_task_start(&app));
	assert(app.error_task = error_task_start(&app));
	assert(app.canbus_task = canbus_task_start(&app));
	assert(app.bse_task = bse_task_start(&app));
	assert(app.apps_task = apps_task_start(&app));
	assert(app.bppc_task = bppc_task_start(&app));
}
