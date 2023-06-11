/*
 * log_task.h
 *
 *  Created on: June 9th, 2023
 *      Author: Benedict Hofmockel
 */

#ifndef INC_TASKS_LOG_TASK_H_
#define INC_TASKS_LOG_TASK_H_

#include "cmsis_os.h"
#include "app.h"
#include <stdio.h>
#include <string.h>

#include "fatfs.h"

TaskHandle_t log_task_start(struct app_data *data);

#endif /* INC_TASKS_LOG_TASK_H_ */
