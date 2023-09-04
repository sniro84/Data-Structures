/************************************************ 
EXERCISE #3   : Data Structure - Dynamic Vector
Implmented by : Snir Holland
Reviewed by   : Daniel Haimov
Date          : 27/4/2023
File          : DVector.h
*************************************************/

#ifndef __D_VECTOR_H__
#define __D_VECTOR_H__

#include <stddef.h>  /* size_t */

typedef struct d_vector d_vector_t;

struct d_vector
{
	size_t element_count;
	size_t capacity;
	size_t element_size;
	void *start; 
};

/*
*
*	create a new vector
*
*	Arguments:
*		capacity - the new vector size. must be larger then 0.
		element_size - the number of bytes of an element. must be larger then 0.
*
*	Return: if successful - pointer to the new vector
*				otherwise return NULL.
*
*	Time complexity: O(1) 
*	Space complexity: O(nm), when n the capacity and m element_size
*
*/
d_vector_t *DVectorCreate(size_t capacity, size_t element_size);

/*
*
*	push a value to the end of the vector. in case of failure 
*	the vector remain unchanged.
*
*	Arguments:
*		vector - pointer to the vector to change. must point to a valid address.
*		value - The value that we wish to push to the vector.
*				Should be the same type as the vector.
*
*	Return: 0 if successful or 1 upon fail
*
*	Time complexity: O(1) - amortized,
*	Space complexity: O(1)
*
*/
int DVectorPushBack(d_vector_t *vector, const void *value);

/*
*
*	pop a value from the end of the vector.
*
*	Arguments:
*		vector - pointer to the vector to change. must point to a valid address.
*
*	Return: void
*
*	Time complexity: O(1) - amortized,
*	Space complexity: O(nm)
*
*/
int DVectorPopBack(d_vector_t *vector);

/*
*
*	get access to a vector element.
*
*	Arguments:
*		vector - pointer to the vector to access. must point to a valid address.
*		index - the index of the element to access. must be smaller then 
*				the number of elements, otherwise the behavior is undefined.
*
*	Return: a pointer to the element
*
*	Time complexity: O(1),
*	Space complexity: O(1)
*
*/
void *DVectorGetAccess(const d_vector_t *vector,  size_t index);

/*
*
*	get the number of current elements in the vector 
*
*	Arguments:
*		vector - pointer to the vector. must point to a valid address.
*
*	Return: the number of elements in the vector.
*
*	Time complexity: O(1),
*	Space complexity: O(1)
*
*/
size_t DVectorGetSize(const d_vector_t *vector);

/*
*
*	get the number of current capacity of the vector 
*
*	Arguments:
*		vector - pointer to the vector. must point to a valid address.
*
*	Return: the capacity of the vector.
*
*	Time complexity: O(1),
*	Space complexity: O(1)
*
*/
size_t DVectorGetCapacity(const d_vector_t *vector);

/*
*
*	frees all memory allocated for the vector
*
*	Arguments:
*		vector - pointer to the vector to destroy. must point to a valid address.
*
*	Return: void
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
void DVectorDestroy(d_vector_t *vector);

/*
*
*	change the size of the vector if possible.
*
*	Arguments:
*		vector - pointer to the vector. must point to a valid address.
*		new_capacity - the new capacity of the vector. can be larger or smaller
*						then current capacity.
*
*	Return: 0 if capacity changed successfully or 1 if failed
*			to change.
*
*	Time complexity: O(1) - Best, O(n) - Worst. 
*	Space complexity: O(nm), when n is the new capacity and m is element_size
*
*/
int DVectorReserve(d_vector_t *vector,  size_t new_capacity);

/*
*
*	reduce the size of the vector according to internal calculation.
*
*	Arguments:
*		vector - pointer to the vector. must point to a valid address.
*
*	Return: 0 if capacity changed successfully or 1 if failed
*			to change.
*
*	Time complexity: O(1) - Best, O(n) - Worst. 
*	Space complexity: O(n), when n the number of elements and m is element size.
*
*/
int DVectorShrink(d_vector_t *vector);


#endif /*__D_VECTOR_H__*/
