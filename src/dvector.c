/************************************************ 
EXERCISE #3   : Data Structure - Dynamic Vector
Implmented by : Snir Holland
Reviewed by   : Daniel Haimov
Date          : 27/4/2023
File          : DVector.c
*************************************************/

#include "dvector.h" 
#include <stdlib.h>  /* malloc , free */
#include <assert.h>  /* assert */
#include <string.h>  /* memset , memcpy */

enum status {SUCCESS = 0 , FAILURE = 1};

#define GROWTH_FACTOR   (2)
#define SHRINK_CONST    (4)

d_vector_t *DVectorCreate(size_t capacity, size_t element_size)
{
	d_vector_t *vector = (d_vector_t *)malloc(sizeof(d_vector_t)); 
	if (NULL == vector)
	{
		return NULL;
	}
	
	vector -> element_count = 0;
	vector -> element_size = element_size;
	vector -> capacity = capacity;
	vector -> start = NULL;
	
	vector -> start = malloc(capacity * element_size);
	if (NULL == vector -> start)
	{
		return NULL;
	}
	
	memset(vector -> start , '\0' , capacity * element_size); 
	
	return vector;
}

void DVectorDestroy(d_vector_t *vector)
{
	assert(vector);
	assert(vector -> start);
	
	free(vector -> start);
	free(vector);
}

size_t DVectorGetSize(const d_vector_t *vector)
{
	assert(vector);
	
	return (vector -> element_count);
}

size_t DVectorGetCapacity(const d_vector_t *vector)
{
	assert(vector);
	
	return (vector -> capacity);
}

void *DVectorGetAccess(const d_vector_t *vector, size_t index)
{
	char* start = NULL;
	size_t elem_size = 0;
	
	assert(vector);
	assert(index < (vector -> element_count));
	
	start = vector -> start;
	elem_size = vector -> element_size;
	
	return (start + (index * elem_size));  
}

int DVectorPushBack(d_vector_t *vector, const void *value)
{
	size_t capacity = 0;
	size_t elem_count = 0;
	size_t elem_size = 0;
	char* start = NULL; 
	
	assert(vector);
	assert(value);
	
	capacity = vector -> capacity;
	elem_count = vector -> element_count;
	elem_size = vector -> element_size;
	
	if (capacity == elem_count)
	{
		if (FAILURE == DVectorReserve(vector , capacity * GROWTH_FACTOR))
		{
			return FAILURE;
		}		
	}
	
	start = vector -> start;
	 
	if (NULL == memcpy(start + (elem_count * elem_size) , value , elem_size))
	{
		return FAILURE;
	}  
	  
	++(vector -> element_count);
	
	return SUCCESS;
}

int DVectorPopBack(d_vector_t *vector)
{
	size_t capacity = 0;
	size_t elem_count = 0;
	
	assert(vector);
	assert(vector -> element_count > 0);
	
	--(vector -> element_count);
	
	capacity = vector -> capacity;
	elem_count = vector -> element_count;
		
	if ( (capacity == elem_count * SHRINK_CONST)  &&  (capacity > 1) )
	{
		if( FAILURE == DVectorReserve(vector , capacity / GROWTH_FACTOR))
		{
			++(vector -> element_count);
			return FAILURE;
		}			
	}
		
	return SUCCESS;
}

int DVectorReserve(d_vector_t *vector, size_t new_capacity)
{
	size_t elem_count = 0;
	size_t elem_size = 0;
	size_t original_capacity = 0;
	void *new_buf = NULL;
	
	assert(vector);
	assert(new_capacity > 0);
	
	elem_count = vector -> element_count;
	elem_size = vector -> element_size;
	original_capacity = vector -> capacity;
	
	if (new_capacity <= elem_count)
	{		
		vector -> capacity = elem_count;
	}
	else
	{
		vector -> capacity = new_capacity;		
	}		
	
	if (elem_count > 0)
	{
		new_buf = realloc(vector -> start , (vector -> capacity) * elem_size);
		if (NULL == new_buf)
		{
			vector -> capacity = original_capacity; 
			return FAILURE;
		}
		
		vector -> start = new_buf;
	}
	return SUCCESS;
}

int DVectorShrink(d_vector_t *vector)
{
	size_t capacity = 0;
	size_t elem_count = 0;
	int status = SUCCESS;
	
	assert(vector);
	
	capacity = vector -> capacity;
	elem_count = vector -> element_count;
	
	if (0 == elem_count)
	{
		status = DVectorReserve(vector , 1);
	}	
	else if (elem_count * GROWTH_FACTOR < capacity)
	{
		status = DVectorReserve(vector , elem_count * GROWTH_FACTOR); 		
	}
	else
	{
		status = SUCCESS;
	}
	
	return status;
}

