/************************************************ 
EXERCISE      : FSM
Implmented by : Snir Holland
Date          : 5/6/2023
File          : fsm_test.c
*************************************************/

#include <stdio.h>

#include "fsm.h"

int main( void ) 
{
	char *strings[6] = {"00","1000","0010010" ,"01010000001", "010" , "011"}; 
	size_t i = 0;

	for(i=0; i<6; ++i)
	{
		printf("Testing string %s :\n" , strings[i]);
		if (IsValidInput(strings[i]))
		{
			printf("Congrats! your string was accepted.\n");  
		}
		else
		{
			printf("Bummer... try different input.\n");
		}
		printf("\n");
	}

	return (0);
}

