/**
* @file stm32f767.h
* @author Cole Bardin (cab572@drexel.edu)
* @brief
* @version 0.1
* @date 2023-03-13
*
* @copyright Copyright (c) 2023
*
*/

#pragma once

#include <stm32f7xx_hal.h>
#include "cmsis_os.h"
#include "ext_drivers/cli.h"

struct stm32f767_device {
	struct cli_device cli;

	ADC_HandleTypeDef hadc1;
	ADC_HandleTypeDef hadc2;
	ADC_HandleTypeDef hadc3;

	CAN_HandleTypeDef hcan1;
	CAN_TxHeaderTypeDef can1_txheader;

	I2C_HandleTypeDef hi2c2;

	RTC_HandleTypeDef hrtc;

	SPI_HandleTypeDef hspi4;
	SPI_HandleTypeDef hspi6;

	UART_HandleTypeDef huart3;

	osMutexId_t can1_mutex;
	osMutexId_t i2c2_mutex;
	osMutexId_t spi4_mutex;
	osMutexId_t spi6_mutex;
	osMutexId_t	uart3_mutex;
	osMessageQueueId_t can1_mq;
};

void stm32f767_init(struct stm32f767_device *dev);
