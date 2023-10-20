/**
 * @file cli.h
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief 
 * @version 0.1
 * @date 2023-10-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include <stm32f7xx_hal.h>

#define CLI_LINE_SIZE 32

struct cli_device {
    uint8_t line[CLI_LINE_SIZE];
    uint8_t c;
    unsigned int index;
	UART_HandleTypeDef *huart;
};

void cli_device_init(struct cli_device *dev, UART_HandleTypeDef *huart);
