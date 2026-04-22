/*
Author : Nidhi Goswami
Description : Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example, 
expr 2 3 4 + *
evaluates 2 * (3+4).
Date : 12-04-2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"module.h"
#define MAX 100

int stack[MAX];
int top = -1;

int isNumber(char *str) {
    int i = 0;

    if (str[0] == '-' || str[0] == '+')
        i++;

    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

void expr(int argc, char *argv[]) {
    int i;

    if (argc < 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    printf("Arguments are: ");
    for (i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    for (i = 1; i < argc; i++) {

        /* If operand, push to stack */
        if (isNumber(argv[i])) {
            push(atoi(argv[i]));
        }
        else {
            int op2 = pop();
            int op1 = pop();
            int result;

            switch (argv[i][0]) {
                case '+':
                    result = op1 + op2;
                    printf("Evaluated: %d + %d\n", op1, op2);
                    break;

                case '-':
                    result = op1 - op2;
                    printf("Evaluated: %d - %d\n", op1, op2);
                    break;

                case '*':
                    result = op1 * op2;
                    printf("Evaluated: %d * %d\n", op1, op2);
                    break;

                case '/':
                    if (op2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    result = op1 / op2;
                    printf("Evaluated: %d / %d\n", op1, op2);
                    break;

                default:
                    printf("Error: Unknown operator %s\n", argv[i]);
                    exit(1);
            }

            push(result);
        }
    }

    if (top != 0) {
        printf("Error: Invalid Expression\n");
        return 1;
    }

    printf("Result: %d\n", pop());

}
