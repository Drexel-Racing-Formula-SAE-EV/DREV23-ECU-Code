/*
 * stm32f767.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <board/stm32f767.h>
#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

extern CAN_HandleTypeDef hcan1;

extern I2C_HandleTypeDef hi2c2;

extern RTC_HandleTypeDef hrtc;

extern SPI_HandleTypeDef hspi4;
extern SPI_HandleTypeDef hspi6;

extern UART_HandleTypeDef huart3;

const osMutexAttr_t can_mutex_attr = {
	.name = "CAN Bus 1 Mutex",
	.attr_bits = osMutexPrioInherit | osMutexRecursive,
	.cb_mem = NULL,
	.cb_size = 0UL,
};

void stm32f767_init(struct stm32f767_device *dev) {
	MX_GPIO_Init();
	MX_USART3_UART_Init();
	MX_ADC1_Init();
	MX_CAN1_Init();
	MX_SPI4_Init();
	MX_ADC2_Init();
	MX_ADC3_Init();
	MX_I2C2_Init();
	MX_RTC_Init();
	MX_SPI6_Init();

	dev->hadc1 = hadc1;
	dev->hadc2 = hadc2;
	dev->hadc3 = hadc3;

	dev->hcan1 = hcan1;

	dev->hi2c2 = hi2c2;

	dev->hrtc = hrtc;

	dev->hspi4 = hspi4;
	dev->hspi6 = hspi6;

	dev->huart3 = huart3;

	dev->can_mutex = osMutexCreate(&can_mutex_attr);
	assert(dev->can_mutex);
}

