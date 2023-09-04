/************************************************ 
EXERCISE <1>    : DS#1: Bit Array
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 16/4/2023
File          : BitArray.c
*************************************************/

#include "bitarray.h" 

#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */

#define MASK_1                            ( (size_t)1 )
#define MAX_UINT_64BIT                    (0xFFFFFFFFFFFFFFFF)
#define BITS_AMOUNT                       (64)
#define LUT_SIZE                          (6)
#define ASCII_ZERO                        (48)
#define HEX_PATTERN_0x5                   (0x5555555555555555)
#define HEX_PATTERN_0x3                   (0x3333333333333333)
#define HEX_PATTERN_0x0F                  (0x0F0F0F0F0F0F0F0F)
#define HEX_PATTERN_0x00FF                (0x00FF00FF00FF00FF)
#define HEX_PATTERN_0x0000FFFF            (0x0000FFFF0000FFFF)
#define HEX_PATTERN_0x00000000FFFFFFFF    (0x00000000FFFFFFFF)

static size_t lut[LUT_SIZE] = 
{
	HEX_PATTERN_0x5 ,
	HEX_PATTERN_0x3 , 
	HEX_PATTERN_0x0F , 
	HEX_PATTERN_0x00FF ,
	HEX_PATTERN_0x0000FFFF ,
	HEX_PATTERN_0x00000000FFFFFFFF
}; 


bit_array_t BitArrSetBit(bit_array_t bit_arr, size_t index, int value)
{
	assert(index < BITS_AMOUNT);
	
	return BitArrSetOff(bit_arr , index) | ( (size_t)value << index );
} 

int BitArrGetValue(bit_array_t bit_arr, size_t index)
{
	assert(index < BITS_AMOUNT);	
	
	return (bit_arr >> index) & MASK_1 ;	
}

bit_array_t BitArrSetOn(bit_array_t bit_arr, size_t index)
{
	assert(index < BITS_AMOUNT);	
	
	return bit_arr | (MASK_1 << index);
}

bit_array_t BitArrSetOff(bit_array_t bit_arr, size_t index)
{
	assert(index < BITS_AMOUNT);	
	
	return bit_arr & ~(MASK_1 << index);
}

bit_array_t BitArrFlipBit(bit_array_t bit_arr, size_t index)
{
	assert(index < BITS_AMOUNT);	
	
	return bit_arr ^ (MASK_1 << index);
}

bit_array_t BitArrSetAll(bit_array_t bit_arr)
{
	(void)bit_arr;
	return MAX_UINT_64BIT;
}

bit_array_t BitArrResetAll(bit_array_t bit_arr)
{
	(void)bit_arr;
	return (0);
}

size_t BitArrCountOn(bit_array_t bit_arr)
{
	size_t i = 0;
	size_t shift_units = 1;
	
	for(i=0; i<LUT_SIZE; ++i)
	{
		bit_arr = (bit_arr & lut[i]) + ((bit_arr >> shift_units) & lut[i]);
		shift_units <<= 1;
	}
	
	return bit_arr; 
}

size_t BitArrCountOff(bit_array_t bit_arr)
{
	return BITS_AMOUNT - BitArrCountOn(bit_arr); 
}

bit_array_t BitArrMirrorBits(bit_array_t bit_arr)
{
	size_t i = 0;
	size_t shift_units = 1;
	
	for(i=0; i<LUT_SIZE; ++i)
	{
		bit_arr = ((bit_arr & lut[i]) << shift_units)  |  ((bit_arr & ~lut[i]) >> shift_units);
		shift_units <<= 1;
	}
		
   	return bit_arr;
}

char *BitArrToString(bit_array_t bit_arr, char *str)
{
	size_t i = 0;
	char *result = NULL;
	
	assert(str);
	
	result = str;
	
	for(i=0; i<BITS_AMOUNT; ++i , ++str)
	{
		*str = BitArrGetValue(bit_arr , BITS_AMOUNT - i - 1) + ASCII_ZERO;
	}
	return result;	
} 

bit_array_t BitArrRotateR(bit_array_t bit_arr, size_t n)
{
	size_t shift_units = n % BITS_AMOUNT; 
	return (bit_arr >> shift_units | bit_arr << (BITS_AMOUNT - shift_units)); 
}


bit_array_t BitArrRotateL(bit_array_t bit_arr, size_t n)
{
	size_t shift_units = n % BITS_AMOUNT; 
	return (bit_arr << shift_units | bit_arr >> (BITS_AMOUNT - shift_units)); 
}

