/*
Author : Nidhi Goswami
Date : 9-3-2026
Description: Suppose there will never be more than one character of pushback.
Modify getch and ungetch accordingly.
*/

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"module.h"

char buff;
int32_t buffp = 0;

int fun_getch(void)
{
    if(buffp == 1)
    {
        buffp = 0;
        return buff;
    }
    else
        return getchar();
}

void fun_ungetch(int32_t c)
{
    if(buffp == 1)
        printf("error: buffer full\n");
    else
    {
        buff = c;
        buffp = 1;
    }
}

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for push a single character 
*/

void single_pushback_calculator()
{
    int32_t type;
    double op2;
    char s[MAXOP];
    getch();
    printf("Enter postfix expression:\n");

    while((type = getop(s)) != EOF)
    {
        switch(type)
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
                if(op2 != 0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;

            case '\n':
                printf("\t%.8g\n", pop());
                break;
            case 'A': case 'B': case 'C': case 'D': case 'E':
case 'F': case 'G': case 'H': case 'I': case 'J':
case 'K': case 'L': case 'M': case 'N': case 'O':
case 'P': case 'Q': case 'R': case 'S': case 'T':
case 'U': case 'V': case 'W': case 'X': case 'Y':
case 'Z':
case 'a': case 'b': case 'c': case 'd': case 'e':
case 'f': case 'g': case 'h': case 'i': case 'j':
case 'k': case 'l': case 'm': case 'n': case 'o':
case 'p': case 'q': case 'r': case 's': case 't':
case 'u': case 'v': case 'w': case 'x': case 'y':
case 'z':

    printf("\t%c\n", type);

    while((type = getch()) != '\n' && type != EOF)
        ;

    break;


            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
}

