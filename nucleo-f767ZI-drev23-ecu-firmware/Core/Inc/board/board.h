/*
 * board.h
 *
 *  Created on: Mar 13, 2023
 *      Author: colebardin
 */

#ifndef INC_BOARD_BOARD_H_
#define INC_BOARD_BOARD_H_

#include <ext_drivers/pressTrans.h>
#include "board/stm32f767.h"

struct board {
	// Physical devices on the board
	struct stm32f767_device stm32f767;
	struct pressTransduc bse1;
	struct pressTransduc bse2;
};

void board_init(struct board* dev);

uint16_t bse_read_count (void *arg);

#endif /* INC_BOARD_BOARD_H_ */
