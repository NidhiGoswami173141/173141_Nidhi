/*
Author : Nidhi Goswami
Date: 22-04-2026
Description : Rewrite postfix calculator using scanf/sscanf (pointer-based)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "module.h"

void postfix_calculator_using_scanf()
{
    char input[200];
    char token[100];
    char *ptr;

    printf("Enter the postfix expression: ");
    scanf(" %[^\n]", input);

    printf("Input: %s\n", input);

    ptr = input;

    while (*ptr != '\0')
    {
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }

        if (sscanf(ptr, "%s", token) != 1)
            break;

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            push(atof(token));
        }
        else
        {
            if (token[0] != '+' && token[0] != '-' &&
                token[0] != '*' && token[0] != '/' &&
                token[0] != '%')
            {
                printf("Error\n");
                return;
            }

            double b = pop();
            double a = pop();
            double result;

            switch (token[0])
            {
                case '+':
                    printf("Evaluated: %.2f + %.2f\n", a, b);
                    result = a + b;
                    break;

                case '-':
                    printf("Evaluated: %.2f - %.2f\n", a, b);
                    result = a - b;
                    break;

                case '*':
                    printf("Evaluated: %.2f * %.2f\n", a, b);
                    result = a * b;
                    break;

                case '/':
                    if (b == 0.0)
                    {
                        printf("Error\n");
                        return;
                    }
                    printf("Evaluated: %.2f / %.2f\n", a, b);
                    result = a / b;
                    break;

                case '%':
                {
                    int32_t a_int = (int32_t)a;
                    int32_t b_int = (int32_t)b;

                    if (b_int == 0)
                    {
                        printf("Error\n");
                        return;
                    }

                    printf("Evaluated: %d %% %d\n", a_int, b_int);

                    result = ((a_int % b_int) + b_int) % b_int;
                    break;
                }

                default:
                    printf("Error\n");
                    return;
            }

            push(result);
        }

        ptr += strlen(token);

        while (*ptr == ' ') ptr++;
    }

    double result = pop();

    printf("Result: %.16g\n", result);
}
