/*
Author: Nidhi Goswami
Date : 3-3-2026
Description : Add commands to print the top element of the stack without popping,
duplicate it, swap the top two elements, and clear the stack.
*/

#include<stdio.h>
#include<stdint.h>
#include<math.h>
#include"module.h"
#include<stdlib.h>
#include<ctype.h>

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for  pritn , duplicate and swap two element 
*/

void RPN_calculator()
{
    int32_t type;
    double op2;
    char s[MAXOP];
    getch();
    printf("enter input:\n");

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {

        case NUMBER:
            push(atof(s));
            break;

        case '+':
            push(pop() + pop());
            break;

        case '*':
            push(pop() * pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;

        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));
            else
                printf("error: zero divisor\n");
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        case 'p':
    if (sp > 0)
        printf("Top element: %g\n", val[sp-1]);
    else
        printf("error: stack empty\n");
    break;


        case 'd':
    if (sp > 0)
    {
        printf("Stack before duplication: ");
        for(int32_t index = 0; index < sp; index++)
            printf("%g ", val[index]);
        printf("\n");

        push(val[sp-1]);

        printf("Stack after duplication: ");
        for(int32_t index = 0; index < sp; index++)
            printf("%g ", val[index]);
        printf("\n");
    }
    else
        printf("error: stack empty\n");
    break;

       case 's':
    if (sp > 1)
    {
        printf("Stack before swapping: ");
        for(int32_t index = 0; index < sp; index++)
            printf("%g ", val[index]);
        printf("\n");

        double temp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = temp;

        printf("Stack after swapping: ");
        for(int32_t index = 0; index < sp; index++)
            printf("%g ", val[index]);
        printf("\n");
    }
    else
        printf("error: not enough elements\n");
    break;


        case 'c':
    printf("Stack before clearing: ");
    for(int32_t index = 0; index < sp; index++)
        printf("%g ", val[index]);
    printf("\n");

    sp = 0;

    printf("Stack cleared\n");
    break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
}

