/************************************************ 
EXERCISE <1>    : DS#6: Circular Buffer
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 18/4/2023
File          : CBuffer.c
*************************************************/


#ifndef __C_BUFFER_H__
#define __C_BUFFER_H__


#include <stddef.h>    /* size_t */
#include <monetary.h>  /* ssize_t */

typedef struct c_buff c_buff_t;

/*
*    Reads data from the buffer 
*
*    Arguments:
*        c_buffe - pointer to the circular buffer to read in. must be vaild.
*        dest - pointer to the buffer where the read data will be placed.
*            must be valid and at least count sized.
*        count - number of bytes to read from the buffer.
*            if larger than the buffer's capacity or size, the function's behavior is undefined.
*
*    Return: number of elements read from the buffer 
*
*    Time complexity: O(count) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
ssize_t CBuffRead(c_buff_t *c_buff, void *dest, size_t count);

/*
*    writes data to the buffer
*
*    Arguments:
*        c_buffe - pointer to the circular buffer to write in. must be vaild.
*        src - pointer to the buffer from which we read the data to write.
*            must be valid and at least count sized.
*        count - number of bytes to read from the buffer.
*            if larger than the buffer's capacity or size, the function's behavior is undefined.
*
*    Return: number of elements wrote to the buffer 
*
*    Time complexity: O(count) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
ssize_t CBuffWrite(c_buff_t *c_buff, const void *src, size_t count);

/*
*
*	Return the number of current values in the circular buffer 
*
*	Arguments:
*		cbuffer - pointer to the circular buffer to check. must be vaild.
*
*	Return: number of values in the circular buffer 
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
size_t CBuffSiz(const c_buff_t *c_buff);

/*
*
*	Return the number of current values in the circular buffer 
*
*	Arguments:
*		cbuffer - pointer to the circular buffer to check. must be vaild.
*
*	Return: number of values in the circular buffer 
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
size_t CBuffGetFreeSpace(const c_buff_t *c_buff);

/*
*
*	creates a new circular buffer
*
*	Arguments:
*		capacity - the capacity of the circular buffer.
*
*	Return: a new circular buffer if successful
*				otherwise return NULL.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
c_buff_t *CBuffCreate(size_t capacity);

/*
*
*	frees all memory allocated for the circular buffer
*
*	Arguments:
*		cbuffer - circular buffer to destroy. must be a valid address.
*
*	Return: void.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
void CBuffDestroy(c_buff_t *c_buff);

/*
*
*	Checks if the circular buffer is empty
*
*	Arguments:
*		cbuffer - pointer to the circular buffer to check. must be vaild.
*
*	Return: 1 - if the circular buffer is empty, 0 - otherwise
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
int CBuffIsEmpty(const c_buff_t *c_buff);

#endif /* __C_BUFFER_H__ */








