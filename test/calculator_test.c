/************************************************ 
EXERCISE      : Calculator
Implmented by : Snir Holland
Reviewed by   : Chen Lev-Ron
Date          : 8/6/2023
File          : calculator_test.c
*************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

static void TestAddSub();
static void TestMulDiv();
static void TestPow();
static void TestParentheses();
static void TestSpaces();
static void TestBadInput();

int main(void)
{
	TestAddSub();
	TestMulDiv();
	TestPow();
	TestParentheses();
	TestSpaces();
	TestBadInput();

	return (0);
}

static void TestAddSub()
{
	double result = 0.0;
	status_t status = SUCCESS;
	size_t test_count_add_sub = 2;

	calculator_t *calculator = FSMCreate();

	printf("--------------- Testing Add/Sub ----------------\t");
	status = FSMCalculate(calculator,"7+8", &result);
	(15 == result && 0 == status) ? --test_count_add_sub : test_count_add_sub;

	result = 0.0;

	status = FSMCalculate(calculator, "-3+-7", &result);
	(-10 == result && 0 == status) ? --test_count_add_sub : test_count_add_sub;
	
	(0 == test_count_add_sub) ? printf("Success") : printf("Failure");
	printf("\n");

	FSMDestroy(calculator);

}

static void TestMulDiv()
{
	double result = 0.0;
	status_t status = SUCCESS;
	size_t test_count_mul_div = 3;

	calculator_t *calculator = FSMCreate();

	printf("--------------- Testing Mul/Div ----------------\t");
	status = FSMCalculate(calculator, "2*5", &result);
	(10 == result && 0 == status) ? --test_count_mul_div : test_count_mul_div;

	result = 0.0;

	status = FSMCalculate(calculator, "4+2-3*7", &result);
	(-15 == result && 0 == status) ? --test_count_mul_div : test_count_mul_div;

	result = 0.0;

	status = FSMCalculate(calculator, "2/0", &result);
	(0 == result && 2 == status) ? --test_count_mul_div : test_count_mul_div;
	
	(0 == test_count_mul_div) ? printf("Success") : printf("Failure");
	printf("\n");

	FSMDestroy(calculator);
}

static void TestPow()
{
	double result = 0.0;
	status_t status = SUCCESS;
	size_t test_count_pow = 2;

	calculator_t *calculator = FSMCreate();

	printf("--------------- Testing Pow ---------------------\t");
	status = FSMCalculate(calculator, "8+8*3+-2^5", &result);
	(0 == result && 0 == status) ? --test_count_pow : test_count_pow;

	result = 0.0;

	status = FSMCalculate(calculator, "8+8*3-2^", &result);
	(0 == result && 1 == status) ? --test_count_pow : test_count_pow;
	
	(0 == test_count_pow) ? printf("Success") : printf("Failure");
	printf("\n");

	FSMDestroy(calculator);
}

static void TestParentheses()
{
	double result = 0.0;
	status_t status = SUCCESS;
	size_t test_count_parentheses = 2;

	calculator_t *calculator = FSMCreate();

	printf("--------------- Testing Parentheses --------------\t");
	status = FSMCalculate(calculator, "8++8*((3-2)*5)", &result);
	(48 == result && 0 == status) ? --test_count_parentheses : test_count_parentheses;

	result = 0.0;

	status = FSMCalculate(calculator, "3-2)*5", &result);
	(0 == result && 1 == status) ? --test_count_parentheses : test_count_parentheses;
	
	(0 == test_count_parentheses) ? printf("Success") : printf("Failure");
	printf("\n");

	FSMDestroy(calculator);
}

static void TestSpaces()
{
	double result = 0.0;
	status_t status = SUCCESS;
	size_t test_count_spaces = 1;

	calculator_t *calculator = FSMCreate();

	printf("--------------- Testing Spaces ------------------\t");
	status = FSMCalculate(calculator, "(3-2)*5+ 5*(4+4+4", &result);
	(0 == result && 1 == status) ? --test_count_spaces : test_count_spaces;

	result = 0.0;

	(0 == test_count_spaces) ? printf("Success") : printf("Failure");
	printf("\n");

	FSMDestroy(calculator);
}

static void TestBadInput()
{
	double result = 0.0;
	status_t status = SUCCESS;
	size_t test_count_bad_input = 1;

	calculator_t *calculator = FSMCreate();

	printf("--------------- Testing Bad Input ------------------\t");
	
	result = 0.0;
	status = FSMCalculate(calculator, "A", &result);
	(0 == result && 1 == status) ? --test_count_bad_input : test_count_bad_input;
	
	(0 == test_count_bad_input) ? printf("Success") : printf("Failure");
	printf("\n");

	FSMDestroy(calculator);
}

