/*
 * app.h
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#ifndef APP_H_
#define APP_H_

#include <stdbool.h>
#include <stdint.h>

struct app_data {
		short torque;
		bool system_shutdown;
		bool rtd_flag;
};

void app_create(struct app_data* data);

#endif /* APP_H_ */
