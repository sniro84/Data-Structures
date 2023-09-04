/************************************************ 
EXERCISE      : FSM
Implmented by : Snir Holland
Date          : 5/6/2023
File          : fsm.c
*************************************************/

#include <stdio.h>

#include "fsm.h"

typedef enum state
{ 
	START,
	FIRST_ZERO,
	ACCEPTING,
	TRAP,
	NUM_STATES 
} state_t;

typedef state_t state_func_t(char *c);

state_t DoStateStart(char *c);
state_t DoStateFirstZero(char *c);
state_t DoStateAccept(char *c);
state_t DoStateTrap(char *c);

state_func_t* const state_table[NUM_STATES] =
{
	DoStateStart,
	DoStateFirstZero,
	DoStateAccept,
	DoStateTrap
};

state_t RunState(state_t cur_state, char *data) 
{
    return state_table[cur_state](data);
}

int IsValidInput(char *str)
{
	state_t cur_state = START;
	while('\0' != *str)
	{
    	cur_state = RunState(cur_state, str);
		++str;
	}

	return (ACCEPTING == cur_state);
}

state_t DoStateStart(char *c)
{
	return ('0' == *c) ? FIRST_ZERO : TRAP; 
}

state_t DoStateFirstZero(char *c)
{
	return ('0' == *c) ? ACCEPTING : FIRST_ZERO;
}

state_t DoStateAccept(char *c)
{
	return ('0' == *c) ? ACCEPTING : FIRST_ZERO;
}

state_t DoStateTrap(char *c)
{
	(void)c;
	return TRAP;
}



