/************************************************ 
EXERCISE <1>    : DS#6: Circular Buffer
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 18/4/2023
File          : CBuffer.c
*************************************************/

#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */

#include "cbuffer.h"
 
struct c_buff
{
	size_t read; 
	size_t size; 
	size_t capacity;
	char arr[1];
};

c_buff_t *CBuffCreate(size_t capacity)
{
	c_buff_t *buff = NULL;	
	
	assert(0 != capacity);

	buff = (c_buff_t*)malloc(offsetof(c_buff_t,arr) + capacity * sizeof(char));
	if (NULL == buff)
	{
		return NULL;
	}
	
	buff -> read = 0;
	buff -> size = 0;
	buff -> capacity = capacity;
	
	return buff;
}

void CBuffDestroy(c_buff_t *c_buff)
{
	assert(c_buff);
	free(c_buff);
}

ssize_t CBuffRead(c_buff_t *c_buff, void *dest, size_t count)
{
	size_t byte_counter = 0;
	size_t size = 0;
	char *runner = NULL;
	
	assert(c_buff);
	assert(dest);
	
	runner = (char*)dest;
	size = CBuffSiz(c_buff); 

	if (size < count)
	{
		count = size;
	}
	
	while(byte_counter < count)
	{
		size_t index = (c_buff -> read) + (c_buff -> size) % (c_buff -> capacity);
		*runner = (c_buff -> arr[index]);
		
		c_buff -> read = (c_buff -> read + 1) % (c_buff -> capacity);
		c_buff -> size = (c_buff -> size - 1);		
		
		++byte_counter;
		++runner;
	}
	
	return (byte_counter);  
}

ssize_t CBuffWrite(c_buff_t *c_buff, const void *src, size_t count)
{
	size_t byte_counter = 0;
	char *dest = NULL;
	char *runner = NULL;
	size_t free_space = 0;
	
	assert(c_buff);
	assert(src);
	
	runner = (char*)src;
	free_space = CBuffGetFreeSpace(c_buff); 
	
	if (0 == free_space)
	{
		return (-1);
	}
	
	if (free_space < count)
	{
		count = free_space;
	}
	
	while(byte_counter < count)
	{
		dest = (c_buff -> arr) + (c_buff -> size) % (c_buff -> capacity);
		*dest = *runner;
		
		c_buff -> size = (c_buff -> size + 1);
		++byte_counter;
		++runner;
	}
	
	return (byte_counter);  
}

size_t CBuffSiz(const c_buff_t *c_buff)
{
	if (c_buff->size > c_buff->capacity)
	{
		return (c_buff->capacity);	
	}
	return (c_buff->size);
}

size_t CBuffGetFreeSpace(const c_buff_t *c_buff)
{
	assert(c_buff);
	return (c_buff -> capacity) - (c_buff -> size);
}

int CBuffIsEmpty(const c_buff_t *c_buff)
{
	assert(c_buff);
	return (0 == CBuffSiz(c_buff)); 
}

