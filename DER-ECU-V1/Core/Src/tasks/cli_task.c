/**
* @file cli_task.c
* @author Cole Bardin (cab572@drexel.edu)
* @brief
* @version 0.1
* @date 2023-10-24
*
* @copyright Copyright (c) 2023
*
*/

#include "tasks/cli_task.h"
#include "main.h"
#include <string.h>

/**
* @brief Actual CLI task function
*
* @param arg App_data struct pointer converted to void pointer
*/
void cli_task_fn(void *arg);

void get_throttle(char *arg);
void get_brake(char *arg);

struct app_data *ad;
command cmds[] = 
{
	{"get throttle", &get_throttle},
	{"get brake", &get_brake}
};

TaskHandle_t cli_task_start(struct app_data *data){
   TaskHandle_t handle;
   xTaskCreate(cli_task_fn, "CLI task", 128, (void *)data, 10, &handle);
   return handle;
}

void cli_task_fn(void *arg){
    struct app_data *data = (struct app_data *)arg;
	ad = data;
	struct cli_device *cli = &data->board.cli;
    uint32_t taskNotification;
	int num_cmds;
	int i;
	
	num_cmds = sizeof(cmds) / sizeof(command);
	while(1){
		xTaskNotifyWait(0, 0, &taskNotification, HAL_MAX_DELAY);
		if(cli->msg_pending == true){
			for(i = 0; i < num_cmds + 1; i++){
				if(i == num_cmds){
					// cmd not found
					break;
				}
				if(!strncmp(cmds[i].name, cli->line, strlen(cmds[i].name))){
					cmds[i].func(cli->line);
					break;
				}
			}
			cli->msg_pending = false;
		}
	}
}

void get_throttle(char *arg){
	float x = ad->throttlePercent;
	x = 0;
}

void get_brake(char *arg){
	float x = ad->brakePercent;
	x = 0;
}
