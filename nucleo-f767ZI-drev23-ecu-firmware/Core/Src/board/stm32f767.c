/*
 * stm32f767.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <board/stm32f767.h>
#include "main.h"

void stm32f767_init(struct stm32f767_device *stm32f767) {
	MX_GPIO_Init();
	MX_USART3_UART_Init();
	MX_USB_OTG_FS_PCD_Init();
	MX_ADC1_Init();
	MX_CAN1_Init();
	MX_SPI4_Init();
	MX_ADC2_Init();
	MX_ADC3_Init();
	MX_I2C2_Init();
	MX_RTC_Init();
	MX_SPI6_Init();
}

