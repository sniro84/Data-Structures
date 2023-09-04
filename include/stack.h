#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*
*
*	push a value to the top of the stack
*
*	Arguments:
*		stack - poiter to the stack to change
*		value - The value that we wish to push to stack.
*			Should be the same type as the stack.
*
*	Return: no return value
*
*	Time complexity: O(1),
*	Space complexity: O(1)
*
*/
void StackPush(stack_t *stack, const void *value);

/*
*
*	pop the last member of the stack
*
*	Arguments:
*		stack - poiter to the stack to change
*
*	Return: no return value
*
*	Time complexity: O(1),
*	Space complexity: O(1)
*
*/
void StackPop(stack_t *stack);

/*
*
*	return the last member of the stack
*
*	Arguments:
*		stack - poiter to the stack to check
*
*	Return: The last member in the stack.
*		the return value will be the adress of the stack member.
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
void *StackPeek(const stack_t *stack);

/*
*
*	checks if the stack is empty
*
*	Arguments:
*		stack - poiter to the stack to check
*
*	Return: 1 - if the stack is empty, 0 - otherwise
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
int StackIsEmpty(const stack_t *stack);

/*
*
*	return the number of current members in the stack 
*
*	Arguments:
*		stack - poiter to the stack to check
*
*	Return: number of members in the stack 
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
size_t StackGetSize(const stack_t *stack);

/*
*
*	return the maximum number of members the stack can contain 
*
*	Arguments:
*		stack - poiter to the stack to check
*
*	Return: the size of the stack
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
size_t StackGetCapacity(const stack_t *stack);

/*
*
*	create a new stack
*
*	Arguments:
*		capacity - the new stack size.
		element_size - the number of bytes of an element 
*
*	Return: poiter to the new stack
*
*	Time complexity: Depending on the behavior of malloc(). 
*	Space complexity: O(nm), when n the capacity and m eleement_size
*
*/
stack_t *StackCreate(size_t capacity,size_t element_size);

/*
*
*	frees all memory allocated for the stack
*
*	Arguments:
*		stack - poiter to the stack to destroy
*
*	Return: no return
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
void StackDestroy(stack_t *stack);



#endif /*__STACK_H__*/





