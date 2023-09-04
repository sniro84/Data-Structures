/************************************************ 
EXERCISE <1>    : DS#2: Stack
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 18/4/2023
File          : Stack.c
*************************************************/

#include "stack.h" 

#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */
#include <string.h>  /* memcpy */

struct stack 
{
	size_t element_count;
	size_t capacity;
	size_t element_size;
	char *top;
};

stack_t *StackCreate(size_t capacity,size_t element_size)
{
	stack_t *stack = NULL;
	
	assert(capacity != 0);
	assert(element_size != 0);
	
	stack = (stack_t*)malloc( sizeof(stack_t) + capacity * element_size );
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack -> top = (char*)stack + sizeof(stack_t);
	stack -> element_count = 0;
	stack -> capacity = capacity;
	stack -> element_size = element_size; 
	
	return stack;
}

void StackPush(stack_t *stack, const void *value)
{
	assert(stack);
	assert(value);
	assert(stack -> element_count  <  stack -> capacity);
	  	
	memcpy(stack -> top , value , stack -> element_size);
	stack -> top += (stack -> element_size);
	++(stack -> element_count);
}

void StackPop(stack_t *stack)
{
	assert(stack);
	assert(!StackIsEmpty(stack));
		
	stack -> top -= (stack -> element_size);
	--(stack -> element_count);	
	
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	assert(!StackIsEmpty(stack));
			
	return (stack -> top) - (stack -> element_size);	
}

void StackDestroy(stack_t *stack)
{
	assert(stack);	
	
	free(stack);
	stack = NULL;
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	
	return (0 == (stack -> element_count));
}

size_t StackGetSize(const stack_t *stack)
{
	assert(stack);
	
	return stack -> element_count;
}

size_t StackGetCapacity(const stack_t *stack)
{
	assert(stack);
	
	return stack -> capacity;
}

