/*
 * board.c
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#include <board/board.h>

void board_init(struct board* dev) {
	stm32f767_init(&dev->stm32f767);
}
