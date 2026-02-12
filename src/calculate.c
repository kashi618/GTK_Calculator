#include "global.h"
#include "calculate.h"

/*
*  Calculates equation
*/
void calculate() {
    printf("Calculating.........\n");
    
}


/*
*  Returns True (1) if a character is an operator
*/
int is_operator(char x) {
    switch (x) {
        case '+': case '-': case 'x': case '/':
            return 1;
            break;
        default:
            return 0;
    }
}


/*
*  Returns True (1) if a character is a digit
*  -> isdigit() wrapper for consistent naming
*/
int is_digit(char x) {
    return isdigit(x) ? 1 : 0;
}




