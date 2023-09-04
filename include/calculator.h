/************************************************ 
EXERCISE      : Calculator
Implmented by : Snir Holland
Reviewed by   : Chen Lev-Ron
Date          : 8/6/2023
File          : calculator.h
*************************************************/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef struct calculator calculator_t; 

typedef enum status
{
    SUCCESS, 
    SYNTAX_ERR, 
    MATH_ERR,
    MEMORY_ERR
} status_t;

calculator_t *FSMCreate(void);
status_t FSMCalculate(calculator_t *calculator, char *expression, double *result);
void FSMDestroy(calculator_t *calcultor);

#endif /*__CALCULATOR_H__*/