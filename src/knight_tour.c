/************************************************ 
EXERCISE      : Knight Tour
Implmented by : Snir Holland
Reviewed by   : 
Date          : 26/6/23
File          : knight_tour.c
*************************************************/

#include <assert.h> /* assert */
#include <time.h>   /* time_t , difftime */

#include "knight_tour.h"
#include "bitarray.h"

#define MAX_MOVES   (8)

typedef struct move
{
    size_t moves_amount;
    int positions[MAX_MOVES];
} move_t;

enum status
{
    SUCCESS,
    FAILURE
};

enum steps
{
    RIGHT_ONE = 1, RIGHT_TWO = 2, LEFT_ONE = -1, LEFT_TWO = -2,
    DOWN_ONE = 1, DOWN_TWO = 2, UP_ONE = -1, UP_TWO = -2
};

/* Helper function: Initialize possible moves LUT */
static void InitPossibleMoves(move_t *moves);

/* Helper function: Insert moves for cell (row,col) */
static void UpdateCellMoves(move_t *moves, int row, int col, int move_row[MAX_MOVES], int move_col[MAX_MOVES]);

/* Helper function: Returns true if cell (i,j) is inside the board, false otherwise */
static int IsValid(int i, int j, int size);

/* Helper function: Sort array of positions from smallest to largest possible moves amount */
static void BubbleSort(move_t *moves, int index);

/* Helper function: Swap two ints */
static void Swap(int *p1, int *p2);

/* Helper function: Recursion driver */
static int FindKnightPath(int index, bit_array_t board, move_t *possible_moves, size_t result[BOARD_SIZE], size_t step_count, time_t timeout);

/* ------------------- KnightsTour ------------------- */
int KnightsTour(knight_position_t start_knight_position, size_t result[BOARD_SIZE], time_t timeout)
{
    int start_index = start_knight_position.row * BOARD_COLS + start_knight_position.col;
    bit_array_t board = 0;

    move_t moves[BOARD_SIZE] = {0};

    InitPossibleMoves(moves);
    
    return FindKnightPath(start_index, board, moves, result, 0, timeout);
}
        
/* ---------------- Static Functions ---------------- */

static int FindKnightPath(int index, bit_array_t board, move_t *possible_moves, size_t result[BOARD_SIZE], size_t step_count, time_t timeout)
{
    time_t begin = time(NULL);
    time_t end = 0;

    size_t moves_counter = 0;
    size_t i = 0;
    int next_index = 0;

    assert(NULL != possible_moves);

    if (timeout < 0)
    {
        return FAILURE;
    }

    if (1 == BitArrGetValue(board, index))
    {
        return FAILURE;
    }

    if (BOARD_SIZE - 1 == step_count)
    {
        result[step_count] = index;
        return SUCCESS;
    }

    board = BitArrSetBit(board, index, 1);
    
    moves_counter = (possible_moves[index]).moves_amount;
    for(i=0; i<moves_counter; ++i)
    {
        next_index = (possible_moves + index)->positions[i];
        
        end = time(NULL);

        if (SUCCESS == FindKnightPath(next_index, board, possible_moves, result, step_count + 1, timeout - (difftime(end, begin)) ))
        {
            result[step_count] = index;
            return SUCCESS;
        } 
    }
    
    return FAILURE;
}

static void InitPossibleMoves(move_t *moves)
{
    int move_row[MAX_MOVES] = {RIGHT_ONE, RIGHT_TWO, RIGHT_TWO, RIGHT_ONE, LEFT_ONE, LEFT_TWO, LEFT_TWO, LEFT_ONE};
    int move_col[MAX_MOVES] = {DOWN_TWO,  DOWN_ONE,  UP_ONE,    UP_TWO,    UP_TWO,   UP_ONE,   DOWN_ONE, DOWN_TWO};

    int i = 0;
    int j = 0;

    for(i=0; i<BOARD_ROWS; ++i)
    {
        for(j=0; j<BOARD_COLS; ++j)
        {
            UpdateCellMoves(moves, i, j, move_row, move_col);
        }
    }

    for(i=0; i<BOARD_SIZE; ++i)
    {
        BubbleSort(moves,i);
    }
}

static void UpdateCellMoves(move_t *moves, int row, int col, int move_row[MAX_MOVES], int move_col[MAX_MOVES])
{
    size_t count = 0;

    int index = row * BOARD_COLS + col;

    size_t i = 0;
    for(i=0; i<MAX_MOVES; ++i)
    {
        if (IsValid(row + move_row[i] , col + move_col[i], BOARD_ROWS))
        {
            int new_pos = (BOARD_ROWS * row + col) + (BOARD_ROWS * move_row[i] + move_col[i]);  

            moves[index].moves_amount += 1;
            moves[index].positions[count] = new_pos;

            ++count;
        }
    }
}

static int IsValid(int i, int j, int size)
{
    return ((i >=0) && (i<size) && (j>=0) && (j<size));    
}
         
static void BubbleSort(move_t *moves, int index)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != moves);
	
	for (i=0; i < moves[index].moves_amount - 1; ++i)
	{
		for (j=0; j < moves[index].moves_amount - i - 1; ++j)
		{
            int index1 = moves[index].positions[j];
            int index2 = moves[index].positions[j+1];

            if (moves[index1].moves_amount > moves[index2].moves_amount)
            {
                Swap(moves[index].positions + j, moves[index].positions + j + 1);
            }
		}
	}
}

static void Swap(int *p1, int *p2)
{
    *p1 = *p1 + *p2;
    *p2 = *p1 - *p2;
    *p1 = *p1 - *p2;
}
