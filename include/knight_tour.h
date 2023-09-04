/************************************************ 
EXERCISE      : Knight Tour
Implmented by : Snir Holland
Reviewed by   : 
Date          : 26/6/23
File          : knight_tour.h
*************************************************/

#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__

#include <stddef.h>
#include <time.h>

#define BOARD_ROWS (8)
#define BOARD_COLS (8)
#define BOARD_SIZE (BOARD_ROWS * BOARD_COLS)

typedef struct knight_position
{
    size_t row;
    size_t col;
} knight_position_t;

/*
 *
 *    generate random knights tour path.
 *
 *    Arguments:
 *        start_knight_position - the first position when the knight start.
 *        result_path - pointer when write the path positions. must be valid and inclued at least BOARD_SIZE knight_position_t allocated.
 *        timeout - how much time limit the run function.
 *
 *    Return: 0 if success. 1 else.
 *
 *    Time complexity: O(n) best O(8^n) average/worst
 *    Space complexity: O(n^2) best/average/worst
 *
 */
int KnightsTour(knight_position_t start_knight_position, size_t result[BOARD_SIZE], time_t timeout);

#endif /*__KNIGHTS_TOUR_H__*/