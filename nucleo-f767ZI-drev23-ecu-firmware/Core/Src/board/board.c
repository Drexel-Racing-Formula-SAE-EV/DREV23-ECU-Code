/*
 * board.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <board/board.h>
#include "app.h"

void board_init(struct board* dev) {
	stm32f767_init(&dev->stm32f767);

	poten_init(&dev->apps1, APPS1_MIN, APPS1_MAX, apps1_read_count);
	poten_init(&dev->apps2, APPS2_MIN, APPS2_MAX, apps2_read_count);
}
