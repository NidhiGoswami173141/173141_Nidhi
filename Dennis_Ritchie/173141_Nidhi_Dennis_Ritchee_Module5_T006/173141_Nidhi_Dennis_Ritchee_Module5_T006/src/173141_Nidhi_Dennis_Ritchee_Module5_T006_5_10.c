/*
Author: Nidhi Goswami
Date : 3-4-2026
Description : Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example, 
expr 2 3 4 + * 
evaluates 2 * (3+4).
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"module.h"
#define MAXSTACK 100

double stack[MAXSTACK];
int32_t top = -1;

void my_push(double val) {
    stack[++top] = val;
}

double my_pop() {
    return stack[top--];
}

int32_t stack_size() {
    return top + 1;
}

void expr(int32_t argc, char *argv[]) {

    printf("Arguments are: ");
    for (int32_t index = 1; index < argc; index++) {
        printf("%s ", argv[index]);
    }
    printf("\n");

    double op1, op2, result;

    for (int32_t index = 1; index < argc; index++) {

        if (isdigit(argv[index][0]) ||
           (argv[index][0] == '-' && isdigit(argv[index][1]))) {

            my_push(atof(argv[index]));
        }
        else if (strlen(argv[index]) == 1) {

            if (stack_size() < 2) {
                printf("Error: not enough operands\n");
                return;
            }

            op2 = my_pop();
            op1 = my_pop();

            switch (argv[index][0]) {

                case '+':
                    result = op1 + op2;
                    printf("Evaluated: %.0lf + %.0lf = %.0lf\n", op1, op2, result);
                    break;

                case '-':
                    result = op1 - op2;
                    printf("Evaluated: %.0lf - %.0lf = %.0lf\n", op1, op2, result);
                    break;

                case '*':
                    result = op1 * op2;
                    printf("Evaluated: %.0lf * %.0lf = %.0lf\n", op1, op2, result);
                    break;

                case '/':
                    if (op2 == 0) {
                        printf("Error: division by zero\n");
                        return;
                    }
                    result = op1 / op2;
                    printf("Evaluated: %.0lf / %.0lf = %.0lf\n", op1, op2, result);
                    break;

                default:
                    printf("Invalid operator %s\n", argv[index]);
                    return;
            }

            my_push(result);
        }
        else {
            printf("Invalid input %s\n", argv[index]);
            return;
        }
    }

    if (stack_size() == 1) {
        printf("Result: %.0lf\n", my_pop());
    } else {
        printf("Error: invalid expression\n");
    }
}
