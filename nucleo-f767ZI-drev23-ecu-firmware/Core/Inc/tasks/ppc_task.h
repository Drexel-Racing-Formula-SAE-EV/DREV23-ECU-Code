/**
 * @file canbus_task.h
 * @author Amar Patel (arp397@drexel.edu)
 * @brief
 * @version 0.1
 * @date 2023-05-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "cmsis_os.h"
#include "app.h"
/**
 * @brief Starts the CANBus task
 *
 * @param data App data structure pointer
 * @return TaskHandle_t Handle used for task
 */
TaskHandle_t ppc_task_start(struct app_data *data);
