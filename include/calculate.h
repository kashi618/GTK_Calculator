#ifndef CALCULATOR_H



/* Includes */
#include "global.h"

/* Macros */
#define CALCULATOR_H
#define MAX_EQUATION 100  // Maximum amount of operators and digits

/* Function Signatures */
void  calculate();
int   is_digit(char x);
int   is_operator(char x);
//int   clear_equation();



#endif
