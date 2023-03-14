/*
 * stm32f767.h
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#ifndef INC_BOARD_STM32F767_H_
#define INC_BOARD_STM32F767_H_

#include "cmsis_os.h"
#include <stm32f7xx_hal.h>

struct stm32f767_device {
	ADC_HandleTypeDef *hadc1;
	ADC_HandleTypeDef *hadc2;
	ADC_HandleTypeDef *hadc3;

	CAN_HandleTypeDef *hcan1;

	I2C_HandleTypeDef *hi2c2;

	RTC_HandleTypeDef *hrtc;

	SPI_HandleTypeDef *hspi4;
	SPI_HandleTypeDef *hspi6;

	UART_HandleTypeDef *huart3;
};

void stm32f767_init(struct stm32f767_device *dev);

#endif /* INC_BOARD_STM32F767_H_ */
