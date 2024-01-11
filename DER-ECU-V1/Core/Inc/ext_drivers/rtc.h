/**
 * @file rtc.h
 * @author Cole Bardin (cab572@drexel.edu)
 * @brief 
 * @version 0.1
 * @date 2024-01-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include <stm32f7xx_hal.h>
#include <stm32f7xx_hal_rtc.h>

typedef struct {
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} datetime;
