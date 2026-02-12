#ifndef GLOBAL_H



/* Includes */
#include <gtk/gtk.h>
#include <stdio.h>
#include <ctype.h>

/* Macros */
#define GLOBAL_H
#define MAX_EQUATION 100  // Max size of equation
#define BUTTON_SPACING 5  // Spacing between buttons (DEFAULT: 5)
#define BUTTON_SIZE 80    // Size of buttons (DEFAULT: 80)

/* Structures */
typedef struct {
    // List of digits in current equation
    int digits[MAX_EQUATION];
    int digitsIdx;

    // List of operators in current equation
    char operators[MAX_EQUATION];
    int operatorsIdx;

    // If current equation has an operator
    int hasOperator;
    int hasOperatorIdx;

    // Result
    double result;
} CalculatorState;

/* Global variables */
extern CalculatorState calc;



#endif
