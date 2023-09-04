/************************************************ 
EXERCISE      : Recursion
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 9/6/2023
File          : recursion.h
*************************************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "stack.h" 

/* Singly linked list node */
typedef struct node
{
    int data;
    struct node *next;
} node_t;

/* Returns the element of fibonacci series in an index (iterative solution) */
int FibonacciIter(int element_index);

/* Returns the element of fibonacci series in an index (recursive solution) */
int Fibonacci(int element_index);

/* Returns the element of fibonacci series in an index (efficient recursive solution) */
int FibonacciWithMemoization(int element_index);

/* Reverses a linked list and returns a pointer to new head of list */
node_t *FlipList(node_t * node);

/* Returns the length of a string */
size_t StrLen(char *str);

/* Returns the lexicographic difference between two strings */
int StrCmp(const char *str1, const char *str2);

/* Copy from source string into dest string */
char *StrCpy(char *dest, const char *src);

/* Appends source string into the end of dest string */
char *StrCat(char *dest, const char *src);

/* Returns the first occourence of needle string in haystack */
char *StrStr(const char *haystack, const char *needle);

/* Sorts a stack (greatest elements will be on top) */
void StackSort(stack_t *stack);

#endif /* __RECURSION_H__ */

