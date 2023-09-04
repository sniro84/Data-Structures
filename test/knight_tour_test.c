/************************************************ 
EXERCISE      : Knight Tour
Implmented by : Snir Holland
Reviewed by   : 
Date          : 26/6/23
File          : knight_tour_test.c
*************************************************/

#include <stdio.h> /* printf */
#include <time.h>  /* time_t */

#include "knight_tour.h"

static void PrintBoard(size_t *result);

int main(void)
{
    knight_position_t start_pos = {0,0};
    size_t result[BOARD_SIZE] = {0};
    time_t timeout = 300;

    if (0 == KnightsTour(start_pos, result, timeout))
    {
        PrintBoard(result); 
    }
    else
    {
        printf("It's not working, bummer...\n");
    }

    return 0;
}

static void PrintBoard(size_t *result)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < BOARD_SIZE; ++i)
    {
        if (0 == i % BOARD_COLS)
        {
            printf("\n");
        }

        for (j = 0; j < BOARD_SIZE; ++j)
        {
            if (result[j] == i)
            {
                printf("%ld\t", j);
                break;
            }
        }
    }
    printf("\n");
}
