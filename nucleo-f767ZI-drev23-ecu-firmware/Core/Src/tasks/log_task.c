/*
 * log_task.c
 *
 *  Created on: June 9th, 2023
 *      Author: Benedict Hofmockel
 *
 *      RESOURCES:
 *      https://01001000.xyz/2020-08-09-Tutorial-STM32CubeIDE-SD-card/
 *      http://elm-chan.org/fsw/ff/00index_e.html
 *      http://elm-chan.org/docs/mmc/mmc_e.html
 *
 */
#include "tasks/log_task.h"

void log_task_fn(void *args);

TaskHandle_t log_task_start(struct app_data *data)
{
    TaskHandle_t handle;
    xTaskCreate(log_task_fn, "Logging Task that writes to SD card over SPI", 4096, (void *)data, tskIDLE_PRIORITY + 5, &handle);
    return handle;
}

void log_task_fn(void *args)
{
    struct app_data *data = (struct app_data *)args;
	char msg[128];
	FATFS FatFs; //Fatfs handle
	FIL fil; //File handle
	FRESULT fres; //Result after SD card driver operations
	DWORD freeClusters, freeSectors, totalSectors;
	FATFS* getFreeFs;

	sprintf(msg,"SD card Task START\r\n");
	HAL_UART_Transmit(&data->board.stm32f767.huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	osDelay(100); //according to Chan, we need to wait for "1ms at least" : http://elm-chan.org/docs/mmc/mmc_e.html#:~:text=Power%20ON%20or,accept%20native%20command.

	/* Open the file system */
	fres = f_mount(&FatFs, "", 1); //1 = mount now
	if (fres != FR_OK){ //if mounting the file system on SD card did not succeed...
		sprintf(msg,"ERROR in Logging TASK: f_mount error\r\n");
		HAL_UART_Transmit(&data->board.stm32f767.huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		Error_Handler();
	}

	fres = f_getfree("", &freeClusters, &getFreeFs);
	if (fres != FR_OK){
		sprintf(msg,"ERROR in Logging TASK: f_getfree error\r\n");
		HAL_UART_Transmit(&data->board.stm32f767.huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		Error_Handler();
	}

	//Formula comes from elm-ChaN's documentation
	totalSectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	freeSectors = freeClusters * getFreeFs->csize;

	sprintf(msg,"SD card statistics:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", totalSectors / 2, freeSectors / 2);
	HAL_UART_Transmit(&data->board.stm32f767.huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    while (1)
    {
    	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
    	osDelay(250);
    }

    // Get rid of unused warning for log task.
    (void)data;
}
