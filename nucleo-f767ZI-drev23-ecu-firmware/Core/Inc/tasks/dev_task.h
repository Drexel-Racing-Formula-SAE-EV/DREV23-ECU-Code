/*
 * dev_task.h
 *
 *  Created on: Mar 14, 2023
 *      Author: colebardin
 */

#ifndef INC_TASKS_DEV_TASK_H_
#define INC_TASKS_DEV_TASK_H_

#include "cmsis_os.h"
#include "app.h"
#include "../app.h"
#include <stdio.h>
#include <string.h>

TaskHandle_t dev_task_start(struct app_data *data);

#endif /* INC_TASKS_DEV_TASK_H_ */
