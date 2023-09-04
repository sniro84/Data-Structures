/************************************************ 
EXERCISE <1>    : DS#1: Bit Array
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 16/4/2023
File          : BitArray_Test.c
*************************************************/

#include "bitarray.h" 
#include <stdio.h>

static void TestBitArrSetBit();
static void TestBitArrGetValue();
static void TestBitArrSetAll();
static void TestBitArrResetAll();
static void TestBitArrFlipBit();
static void TestBitArrMirrorBits();
static void TestBitArrCountOn();
static void TestBitArrCountOff();
static void TestBitArrToString();
static void TestBitArrRotateR();
static void TestBitArrRotateL();

static char my_bin_str[65] = {'\0'};

int main(void)
{
	TestBitArrSetBit();
	
	TestBitArrGetValue();
	
	TestBitArrSetAll();
	
	TestBitArrResetAll();
	
	TestBitArrFlipBit();
	
	TestBitArrMirrorBits();
	
	TestBitArrCountOn();
	
	TestBitArrCountOff();
	
	TestBitArrToString();
	
	TestBitArrRotateL();
	
	TestBitArrRotateR();
	
	return (0);
}

static void TestBitArrSetBit()
{
	bit_array_t x = 167;
	printf("------------ Testing SetBit Function ------------\n");
	printf("%lu in binary          = %s\n" ,x , BitArrToString(x, my_bin_str));
	
	x = BitArrSetBit(167,63,1);
	printf("BitArrSetBit(167,63,1) = %s\n"  , BitArrToString(x, my_bin_str));
	
	x = BitArrSetBit(167,2,0);
	printf("BitArrSetBit(167,2,0)  = %s\n"  , BitArrToString(x, my_bin_str));

	x = BitArrSetBit(167,6,1);
	printf("BitArrSetBit(167,6,1)  = %s\n"  , BitArrToString(x, my_bin_str));
	
	x = BitArrSetBit(167,47,1);
	printf("BitArrSetBit(167,47,1) = %s\n"  , BitArrToString(x, my_bin_str));
	
	x = BitArrSetBit(167,0,0);
	printf("BitArrSetBit(167,0,0)  = %s\n"  , BitArrToString(x, my_bin_str));
	
	printf("--------------------------------------------------\n");
}


static void TestBitArrGetValue()
{
	bit_array_t x = 167;
	size_t i = 0;
	
	printf("------------ Testing GetValue Function ------------\n");
	printf("%lu in binary         = %s\n" ,x , BitArrToString(x, my_bin_str));
	for(i=0; i<8; i++)
	{
		printf("BitArrGetValue(167,%lu) = %d\n" , i , BitArrGetValue(167,i));
	}
	printf("--------------------------------------------------\n");
}

static void TestBitArrFlipBit()
{
	bit_array_t x = 167;
	size_t i = 0;

	printf("------------ Testing FlipBit Function ------------\n");	
	printf("%lu in binary               = %s\n" ,x , BitArrToString(x, my_bin_str));
	
	for(i=0; i<6; i++)
	{
		x = BitArrFlipBit(167 ,i);
		printf("After BitArrFlipBit(167 ,%lu) = %s\n" , i , BitArrToString(x, my_bin_str));
	}
	printf("--------------------------------------------------\n");
}

static void TestBitArrSetAll()
{
	bit_array_t x = 167;
	x = BitArrSetAll(x);
	printf("------------ Testing SetAll Function ------------\n");	
	printf("After BitArrSetAll() = %s\n" , BitArrToString(x, my_bin_str));
	printf("--------------------------------------------------\n");
}

static void TestBitArrResetAll()
{
	bit_array_t x = 167;
	x = BitArrResetAll(x);
	printf("------------ Testing ResetAll Function ------------\n");	
	printf("After BitArrResetAll() = %s\n" , BitArrToString(x, my_bin_str));
	printf("--------------------------------------------------\n");
}

static void TestBitArrMirrorBits()
{
	bit_array_t x = 0xFACC00000000000B;
	printf("------------ Testing MirrorBits Function ------------\n");
	printf("BitArray value before mirroring : %s\n" , BitArrToString(x, my_bin_str) );
	x = BitArrMirrorBits(x);
	printf("BitArray value after  mirroring : %s\n" , BitArrToString(x, my_bin_str) );
	printf("--------------------------------------------------\n");
}

static void TestBitArrCountOn()
{
	bit_array_t x = 0xFA0000000000000C;
	printf("------------ Testing CountOn Function ------------\n");
	printf("BitArray value : %s\n" , BitArrToString(x, my_bin_str) );
	printf("BitArray set count : %lu\n" , BitArrCountOn(x));
	printf("--------------------------------------------------\n");
}

static void TestBitArrCountOff()
{
	bit_array_t x = 0xFFFFFFFF0FFFFFFF;
	printf("------------ Testing CountOff Function ------------\n");
	printf("BitArray value : %s\n" , BitArrToString(x, my_bin_str) );
	printf("BitArray unset count : %lu\n" , BitArrCountOff(x));
	printf("--------------------------------------------------\n");
}

static void TestBitArrToString()
{
	bit_array_t x = 0xABCDABCDABCDABCD;
	printf("------------ Testing ToString Function ------------\n");
	printf("0xABCDABCDABCDABCD in binary : %s\n" , BitArrToString(x , my_bin_str));
	printf("--------------------------------------------------\n");
}

static void TestBitArrRotateR()
{
	bit_array_t x = 0xFFFF0000FFFF0000;
	printf("------------ Testing RotateRight Function ------------\n");
	printf("Original String              : %s\n" , BitArrToString(x , my_bin_str));
	x = BitArrRotateR(x , 3);
	printf("After Rotate Right (3 units) : %s\n" , BitArrToString(x , my_bin_str));
	printf("--------------------------------------------------\n");	
}

static void TestBitArrRotateL()
{
	bit_array_t x = 0xFFFF0000FFFF0000;
	printf("------------ Testing RotateLeft Function ------------\n");
	printf("Original String             : %s\n" , BitArrToString(x , my_bin_str));
	x = BitArrRotateL(x , 4);
	printf("After Rotate Left (4 units) : %s\n" , BitArrToString(x , my_bin_str));
	printf("--------------------------------------------------\n");
}




