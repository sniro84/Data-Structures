/************************************************ 
EXERCISE      : Calculator
Implmented by : Snir Holland
Reviewed by   : Chen Lev-Ron
Date          : 8/6/2023
File          : calculator.c
*************************************************/

#include "stack.h"
#include "calculator.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define STATES          (4)
#define CHARS_AMOUNT    (128)
#define EXPR_LEN        (20)

typedef status_t (*op_func_t)(double *res, double x, double y);
typedef status_t (*handler_func_t)(calculator_t *calculator, char **expression);

/* characters */
enum char_signs
{
    ASCII_ZERO = '0',
    ASCII_NINE = '9',
    NULL_TERM  = '\0',
    PLUS_SIGN  = '+',
    MINUS_SIGN = '-',
    PROD_SIGN  = '*',
    DIV_SIGN   = '/',
    POW_SIGN   = '^',
    DOT_SIGN   = '.',
    AT_SIGN    = '@',
    LEFT_PARENTHESES  = '(',
    RIGHT_PARENTHESES = ')',
    SPACE = ' '
};

/* states */
typedef enum
{
    WAIT_FOR_NUM,
    WAIT_FOR_OP,
    ERROR,
    RESULT
} state_t;

/* priority */
typedef enum
{
    DUMMY,
    LEFT_PAR,     
    ADD,
    SUB = ADD,        
    MULT,
    DIV = MULT,      
    POW,        
    INVALID      
} priority_t;

/* operator */
typedef struct operator
{
    priority_t priority;
    op_func_t op_func;
} operator_t;

/* transition */
typedef struct transition
{
    handler_func_t handler_func;
    state_t next_state;
} transition_t;

/* calculator */
struct calculator
{
    stack_t *stack_num;
    stack_t *stack_op;
    transition_t transitions[STATES][CHARS_AMOUNT];
    operator_t operators[CHARS_AMOUNT];
    state_t curr_state;
};

/* Helper Functions */
static void InitTransitionLUT(transition_t transitions[STATES][CHARS_AMOUNT]);
static void InitOperatorsLUT(operator_t *operators);
static status_t UpdateResult(calculator_t *calculator);

/* Handlers */
static status_t HandleNumber(calculator_t *calculator, char **expression);
static status_t HandleOperator(calculator_t *calculator, char **expression);
static status_t HandleError(calculator_t *calculator, char **expression);
static status_t HandleLeftParentheses(calculator_t *calculator, char **expression);
static status_t HandleRightParentheses(calculator_t *calculator, char **expression);
static status_t HandleTerminator(calculator_t *calculator, char **expression);
static status_t HandleSpaces(calculator_t *calculator, char **expression);

/* Calculation Functions */
static status_t CalcAdd(double *res, double x, double y);
static status_t CalcSub(double *res, double x, double y);
static status_t CalcMul(double *res, double x, double y);
static status_t CalcDiv(double *res, double x, double y);
static status_t CalcPow(double *res, double x, double y);
static status_t CalcErr(double *res, double x, double y);
static status_t CalcNothing(double *res, double x, double y);

/* -----------FSMCalculate------------ */
status_t FSMCalculate(calculator_t *calculator, char *expression, double *result)
{
    /* init status */
    status_t fsm_status = SUCCESS;
    char dummy = '\0';

    assert(NULL != calculator);
    assert(NULL != expression);
    assert(NULL != result);

    /* Init current state */
    calculator->curr_state = WAIT_FOR_NUM;

    dummy = AT_SIGN;
    StackPush(calculator->stack_op, &dummy);

    /* primary function of calculator */
    while(NULL_TERM != *expression)
    {
        fsm_status = calculator->transitions[calculator->curr_state][(int)*expression].handler_func(calculator, &expression);
        
        if (SUCCESS != fsm_status)
        {
            *result = 0.0;
            return fsm_status;
        }
    }

    /* handle final result */
    fsm_status = calculator->transitions[calculator->curr_state][NULL_TERM].handler_func(calculator, &expression);
    *result = (SUCCESS == fsm_status) ? *(double*)StackPeek(calculator->stack_num) : 0.0;

    return fsm_status;
}
/* end of primary function */

/* -----------FSMCreate------------ */
calculator_t *FSMCreate(void)
{
    calculator_t *calculator = NULL;

    /* Allocate memory for calculator */
    calculator = (calculator_t *)malloc(sizeof(calculator_t));
    if (NULL == calculator)
    {
        return NULL;
    }

    /* Allocate memory for two stacks */
    calculator->stack_num = StackCreate(EXPR_LEN, sizeof(double));
    if (NULL == calculator->stack_num)
    {
        free(calculator);
        calculator = NULL;

        return NULL;
    }
    calculator->stack_op = StackCreate(EXPR_LEN, sizeof(char));
    if (NULL == calculator->stack_op)
    {
        StackDestroy(calculator->stack_op);

        free(calculator);
        calculator = NULL;

        return NULL;
    }

    /* init lookup tables*/
    InitTransitionLUT(calculator->transitions);
    InitOperatorsLUT(calculator->operators);

    return calculator;
}

/* -----------FSMDestroy------------ */
void FSMDestroy(calculator_t *calculator)
{
    assert(NULL != calculator);

    StackDestroy(calculator->stack_num);
    StackDestroy(calculator->stack_op);
    
    free(calculator);
    calculator = NULL;
}

/*----------Helper functions---------*/
/* helper function: initialize LUT of ooperators */
static void InitOperatorsLUT(operator_t *operators)
{
    size_t i=0;

    assert(NULL != operators);

    for(i=0; i<CHARS_AMOUNT; ++i)
    {
        operators[i].op_func = &CalcErr;
        operators[i].priority = INVALID;
    }

    operators[PLUS_SIGN].op_func = &CalcNothing;
    operators[PLUS_SIGN].priority = DUMMY;

    operators[PLUS_SIGN].op_func = &CalcAdd;
    operators[PLUS_SIGN].priority = ADD;

    operators[MINUS_SIGN].op_func = &CalcSub;
    operators[MINUS_SIGN].priority = SUB;

    operators[PROD_SIGN].op_func = &CalcMul;
    operators[PROD_SIGN].priority = MULT;

    operators[DIV_SIGN].op_func = &CalcDiv;
    operators[DIV_SIGN].priority = DIV;

    operators[POW_SIGN].op_func = &CalcPow;
    operators[POW_SIGN].priority = POW;

    operators[LEFT_PARENTHESES].op_func  = &CalcErr;
    operators[LEFT_PARENTHESES].priority = LEFT_PAR;
}

/* helper function: initialize LUT of transitions */
static void InitTransitionLUT(transition_t transitions[STATES][CHARS_AMOUNT])
{
    size_t i = 0;
    size_t j = 0;
    int c = ASCII_ZERO; 

    assert(NULL != transitions);

    /* error by default */
    for(i=0; i<STATES; ++i)
    {
        for(j=0; j<CHARS_AMOUNT; ++j)
        {
            transitions[i][j].handler_func = &HandleError;
            transitions[i][j].next_state = ERROR;
        }
    }

    /* numbers */
    for(c=ASCII_ZERO; c<=ASCII_NINE; ++c) 
    {
       transitions[WAIT_FOR_NUM][c].handler_func = &HandleNumber;
       transitions[WAIT_FOR_NUM][c].next_state = WAIT_FOR_OP;
    }

    transitions[WAIT_FOR_NUM][PLUS_SIGN].handler_func = &HandleNumber;
    transitions[WAIT_FOR_NUM][PLUS_SIGN].next_state = WAIT_FOR_OP;

    transitions[WAIT_FOR_NUM][MINUS_SIGN].handler_func = &HandleNumber;
    transitions[WAIT_FOR_NUM][MINUS_SIGN].next_state = WAIT_FOR_OP;

    transitions[WAIT_FOR_NUM][DOT_SIGN].handler_func = &HandleNumber;
    transitions[WAIT_FOR_NUM][DOT_SIGN].next_state = WAIT_FOR_OP;

    transitions[WAIT_FOR_NUM][LEFT_PARENTHESES].handler_func = &HandleLeftParentheses;
    transitions[WAIT_FOR_NUM][LEFT_PARENTHESES].next_state = WAIT_FOR_NUM;

    /* operators*/
    transitions[WAIT_FOR_OP][PLUS_SIGN].handler_func = &HandleOperator;
    transitions[WAIT_FOR_OP][PLUS_SIGN].next_state = WAIT_FOR_NUM;

    transitions[WAIT_FOR_OP][MINUS_SIGN].handler_func = &HandleOperator;
    transitions[WAIT_FOR_OP][MINUS_SIGN].next_state = WAIT_FOR_NUM;

    transitions[WAIT_FOR_OP][PROD_SIGN].handler_func = &HandleOperator;
    transitions[WAIT_FOR_OP][PROD_SIGN].next_state = WAIT_FOR_NUM;

    transitions[WAIT_FOR_OP][DIV_SIGN].handler_func = &HandleOperator;
    transitions[WAIT_FOR_OP][DIV_SIGN].next_state = WAIT_FOR_NUM;

    transitions[WAIT_FOR_OP][POW_SIGN].handler_func = &HandleOperator;
    transitions[WAIT_FOR_OP][POW_SIGN].next_state = WAIT_FOR_NUM;
    
    transitions[WAIT_FOR_OP][RIGHT_PARENTHESES].handler_func = &HandleRightParentheses;
    transitions[WAIT_FOR_OP][RIGHT_PARENTHESES].next_state = WAIT_FOR_OP;
    
    /* terminator */
    transitions[WAIT_FOR_OP][NULL_TERM].handler_func = &HandleTerminator;
    transitions[WAIT_FOR_OP][NULL_TERM].next_state = RESULT;

    /* spaces */
    transitions[WAIT_FOR_NUM][SPACE].handler_func = &HandleSpaces;
    transitions[WAIT_FOR_NUM][SPACE].next_state = WAIT_FOR_NUM; 

    transitions[WAIT_FOR_OP][SPACE].handler_func = &HandleSpaces;
    transitions[WAIT_FOR_OP][SPACE].next_state = WAIT_FOR_OP;  
}

/* helper function: Dijksra's algorithm */
static status_t UpdateResult(calculator_t *calculator)
{
    double first_operand = 0.0;
    double second_operand = 0.0;
    double result = 0.0;
    int oper = NULL_TERM;

    status_t status = SUCCESS;

    assert(NULL != calculator);

    /* 1. pop operator from stack*/
    oper = *(char *)StackPeek(calculator->stack_op);
    StackPop(calculator->stack_op);

    /* 2. pop two values from operands stack*/
    second_operand = *(double *)StackPeek(calculator->stack_num);
    StackPop(calculator->stack_num);

    first_operand = *(double *)StackPeek(calculator->stack_num);
    StackPop(calculator->stack_num);

    /* 3. apply operator to operands in correct order */
    status = calculator->operators[oper].op_func(&result, first_operand, second_operand);

    /* 4. push result into operands stack*/
    StackPush(calculator->stack_num, &result);

    return status;
}

/*----------End of helper functions---------*/

/*-------------- Handlers-------------*/

/* handler: number */
static status_t HandleNumber(calculator_t *calculator, char **expression)
{
    char *source = NULL; 
    double res = 0.0;

    assert(NULL != calculator);
    assert(NULL != expression);

    source = *expression;
    res = strtod(source, expression);

    if (source == *expression)
    {
        return SYNTAX_ERR;
    }

    StackPush(calculator->stack_num, &res);

    calculator->curr_state = WAIT_FOR_OP;

    return SUCCESS;
}

/* handler: operator */
static status_t HandleOperator(calculator_t *calculator, char **expression)
{
    status_t status = SUCCESS;
    priority_t curr_op_priority = INVALID;

    assert(NULL != calculator);
    assert(NULL != expression);
    assert(NULL != *expression);

    curr_op_priority = calculator->operators[(int)**expression].priority;

    while  (AT_SIGN != *(char*)StackPeek(calculator->stack_op)  && 
           (calculator->operators[(int)*(char *)StackPeek(calculator->stack_op)].priority >= curr_op_priority))
    {
        status = UpdateResult(calculator);
        if (SUCCESS != status)
        {
            return status;
        }
    }
    
    StackPush(calculator->stack_op, &(**expression));

    calculator->curr_state = WAIT_FOR_NUM;

    ++(*expression);

    return SUCCESS;
}

/* handler: terminator */
static status_t HandleTerminator(calculator_t *calculator, char **expression)
{
    status_t status = SUCCESS;

    assert(NULL != calculator);

    (void)expression;

    while (AT_SIGN != *(char*)StackPeek(calculator->stack_op))
    {
        status = UpdateResult(calculator);
        if (SUCCESS != status)
        {
            break;
        }
    }

    return status; 
}

/* handler: error */
static status_t HandleError(calculator_t *calculator, char **expression)
{
    (void)calculator;
    (void)expression;
    return SYNTAX_ERR;
}

/* handler: left parentheses */
static status_t HandleLeftParentheses(calculator_t *calculator, char **expression)
{
    assert(NULL != calculator);
    assert(NULL != expression);

    StackPush(calculator->stack_op, &(**expression));
    ++(*expression);
    return SUCCESS;
}

/* handler: right parentheses */
static status_t HandleRightParentheses(calculator_t *calculator, char **expression)
{
    status_t status = SUCCESS;

    assert(NULL != calculator);
    assert(NULL != expression); 

    while ( AT_SIGN != *(char*)StackPeek(calculator->stack_op) 
            && (LEFT_PARENTHESES != *(char*)StackPeek(calculator->stack_op) ))
    {
        status = UpdateResult(calculator);
        if (status != SUCCESS)
        {
            return SYNTAX_ERR;
        }
    }

    if (LEFT_PARENTHESES == *(char*)StackPeek(calculator->stack_op))
    {
        StackPop(calculator->stack_op);
        ++(*expression);
        return SUCCESS;
    }
    
    return SYNTAX_ERR;
}

/* handler: spaces */
static status_t HandleSpaces(calculator_t *calculator, char **expression)
{
    assert(NULL != expression);
    
    (void)calculator;
    ++(*expression);
    return SUCCESS;
}
/*-------------- End of Handlers-------------*/

/*-------------- Calculation functions -------------*/

/* Calc function : CalcAdd */
static status_t CalcAdd(double *res, double x, double y)
{
    assert(NULL != res);
    
    *res = x + y;
    return SUCCESS;
}

/* Calc function : CalcSub */
static status_t CalcSub(double *res, double x, double y)
{
    assert(NULL != res);

    *res = x - y;
    return SUCCESS;
}

/* Calc function : CalcMul */
static status_t CalcMul(double *res, double x, double y)
{
    assert(NULL != res);

    *res = x * y;
    return SUCCESS;
}

/* Calc function : CalcDiv */
static status_t CalcDiv(double *res, double x, double y)
{
    assert(NULL != res);

    if (0 == y)
    {
        return MATH_ERR;
    }

    *res = x / y;
    return SUCCESS;
}

/* Calc function : CalcPow */
static status_t CalcPow(double *res, double x, double y)
{
    assert(NULL != res);

    *res = pow(x,y);
    return SUCCESS;
}

/* Calc function : CalcErr */
static status_t CalcErr(double *res, double x, double y)
{
    (void)res;
    (void)x;
    (void)y;

    return SYNTAX_ERR;
}

/* Calc function : CalcNothing */
static status_t CalcNothing(double *res, double x, double y)
{
    (void)res;
    (void)x;
    (void)y;

    return SUCCESS;
}

/*-------------- End of Calculation functions -------------*/
