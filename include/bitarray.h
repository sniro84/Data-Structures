/************************************************ 
EXERCISE <1>    : DS#1: Bit Array
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 16/4/2023
File          : BitArray.h
*************************************************/

#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stddef.h>

typedef size_t bit_array_t;

/*
*
*	Sets on or turns off a specific bit in a bit array
*
*	Arguments:
*		bit_arr - The bit array to change
*		index - the location of the specific bit in the array.
*			Should be smaller than 64
*		value - The value to which we wish to set the bit.
*			Should be '1' or '0'
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on index
*	Space complexity: O(1)
*
*/
bit_array_t BitArrSetBit(bit_array_t bit_arr, size_t index, int value);

/*
*
*	Returns the value of a specific bit in a bit array
*
*	Arguments:
*		bit_arr - The bit array to check
*		index - the location of the specific bit in the array.
*			Should be smaller than 64
*
*	Return: The value of the specific bit
*
*	Time complexity: O(n), depending on index
*	Space complexity: O(1)
*
*/
int BitArrGetValue(bit_array_t bit_arr, size_t index);

/*
*
*	Sets on a specific bit in a bit array
*
*	Arguments:
*		bit_arr - The bit array to change
*		index - the location of the specific bit in the array.
*			Should be smaller than 64
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on index
*	Space complexity: O(1)
*
*/
bit_array_t BitArrSetOn(bit_array_t bit_arr, size_t index);

/*
*
*	Turns off a specific bit in a bit array
*
*	Arguments:
*		bit_arr - The bit array to change
*		index - the location of the specific bit in the array.
*			Should be smaller than 64
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on index
*	Space complexity: O(1)
*
*/
bit_array_t BitArrSetOff(bit_array_t bit_arr, size_t index);

/*
*
*	Shifts right n times the bits of a bit array, while placing the
*		pushed bits at the left end of the array
*
*	Arguments:
*		bit_arr - The bit array to change
*		n - The number of bits to rotate
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on the size of bit_arr
*	Space complexity: O(1)
*
*/
bit_array_t BitArrRotateR(bit_array_t bit_arr, size_t n);

/*
*
*	Shifts left n times the bits of a bit array, while placing the
*		pushed bits at the right end of the array
*
*	Arguments:
*		bit_arr - The bit array to change
*		n - The number of bits to rotate
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on the size of bit_arr
*	Space complexity: O(1)
*
*/
bit_array_t BitArrRotateL(bit_array_t bit_arr, size_t n);

/*
*
*	Counts the number of set bits in a bit array
*
*	Arguments:
*		bit_arr - The bit array to check
*
*	Return: The number of the set bits in bit_arr
*
*	Time complexity: O(log(n)), depending on the size of bit_arr
*	Space complexity: O(1)
*
*/
size_t BitArrCountOn(bit_array_t bit_arr);

/*
*
*	Counts the number of off bits in a bit array
*
*	Arguments:
*		bit_arr - The bit array to check
*
*	Return: The number of the off bits in bit_arr
*
*	Time complexity: O(log(n)), depending on the size of bit_arr
*	Space complexity: O(1)
*
*/
size_t BitArrCountOff(bit_array_t bit_arr);

/*
*
*	Flips a specific bit in a bit array
*
*	Arguments:
*		bit_arr - The bit array to change
*		index - the location of the specific bit in the array.
*			Should be smaller than 64
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on index
*	Space complexity: O(1)
*
*/
bit_array_t BitArrFlipBit(bit_array_t bit_arr, size_t index);

/*
*
*	Mirrors a bit array (MSB to LSB)
*
*	Arguments:
*		bit_arr - The bit array to change
*
*	Return: The changed bit array
*
*	Time complexity: O(n), depending on the size of bit_arr
*	Space complexity: O(1)
*
*/
bit_array_t BitArrMirrorBits(bit_array_t bit_arr);

/*
*
*	Creates a string representing a bit array. 
*	Note: The finctions uses memory allocated by the user
*
*	Arguments:
*		bit_arr - The bit array to check
*		str - Location of the allocated memory for the string.
*			Must conatin at least 65 bytes
*
*	Return: str
*
*	Time complexity: O(n), depending on the size of bit_arr
*	Space complexity: O(1)
*
*/
char *BitArrToString(bit_array_t bit_arr, char *str);

/*
*
*	Sets all bits in a bit array
*
*	Arguments:
*		bit_arr - The bit array to change
*
*	Return: The changed bit array
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
bit_array_t BitArrSetAll(bit_array_t bit_arr);

/*
*
*	Turns off all bits in a bit array
*
*	Arguments:
*		bit_arr - The bit array to change
*
*	Return: The changed bit array
*
*	Time complexity: O(1)
*	Space complexity: O(1)
*
*/
bit_array_t BitArrResetAll(bit_array_t bit_arr);

#endif /* __BITARRAY_H__ */
