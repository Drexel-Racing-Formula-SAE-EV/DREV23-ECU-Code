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
#include <string.h>

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

	app.rtc_datetime.second = 0;
	app.rtc_datetime.minute = 0;
	app.rtc_datetime.hour = 0;
	app.rtc_datetime.day = 1;
	app.rtc_datetime.month = 1;
	app.rtc_datetime.year = 24;
	//write_time();

	HAL_UART_Receive_IT(app.board.cli.huart, &app.board.cli.c, 1);
	//assert(app.dev_task = dev_task_start(&app));
	assert(app.cli_task = cli_task_start(&app));
	assert(app.rtd_task = rtd_task_start(&app));
	assert(app.error_task = error_task_start(&app));
	assert(app.canbus_task = canbus_task_start(&app));
	assert(app.bse_task = bse_task_start(&app));
	assert(app.apps_task = apps_task_start(&app));
	assert(app.bppc_task = bppc_task_start(&app));
}

void cli_putline(char *line){
	static uint8_t nl[] = "\r\n";
	
	if(xPortIsInsideInterrupt()){
		HAL_UART_Transmit_IT(app.board.cli.huart, (uint8_t *)line, strlen(line));
		HAL_UART_Transmit_IT(app.board.cli.huart, nl, strlen(nl));
	}else{
		HAL_UART_Transmit(app.board.cli.huart, (uint8_t *)line, strlen(line), HAL_MAX_DELAY);
		HAL_UART_Transmit(app.board.cli.huart, nl, strlen(nl), HAL_MAX_DELAY);
	}
}

void read_time(){
	RTC_TimeTypeDef rTime;
	RTC_DateTypeDef rDate;

	HAL_RTC_GetTime(&app.board.stm32f767.hrtc, &rTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&app.board.stm32f767.hrtc, &rDate, RTC_FORMAT_BIN);

	app.rtc_datetime.second = rTime.Seconds;
	app.rtc_datetime.minute = rTime.Minutes;
	app.rtc_datetime.hour = rTime.Hours;
	app.rtc_datetime.day = rDate.Date;
	app.rtc_datetime.month = rDate.Month;
	app.rtc_datetime.year = rDate.Year;
}

void write_time(){
	RTC_TimeTypeDef rTime;
	RTC_DateTypeDef rDate;

	rTime.Seconds = HEX2DEC(app.rtc_datetime.second);
	rTime.Minutes = HEX2DEC(app.rtc_datetime.minute);
	rTime.Hours = HEX2DEC(app.rtc_datetime.hour);
	rDate.Date = HEX2DEC(app.rtc_datetime.day);
	rDate.Month = HEX2DEC(app.rtc_datetime.month);
	rDate.Year = HEX2DEC(app.rtc_datetime.year);
	rDate.WeekDay = RTC_WEEKDAY_MONDAY;

	HAL_RTC_SetTime(&app.board.stm32f767.hrtc, &rTime, RTC_FORMAT_BCD);
	HAL_RTC_SetDate(&app.board.stm32f767.hrtc, &rDate, RTC_FORMAT_BCD);
}

