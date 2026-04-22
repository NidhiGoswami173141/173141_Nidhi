/*
Author : Nidhi Goswami
Date : 9-3-2026
Description : Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include"module.h"

#define MAXOP 100
#define NUMBER '0'
/*
Author : Nidhi Goswami
Date : 9-3-2026
Description : getop function without ungetch()
*/
int get_op(char s[])
{
    static int32_t last = ' ';
    int32_t i = 0;

    while (last == ' ' || last == '\t')
        last = getchar();

    if (!isdigit(last) && last != '.' && last != '-')
    {
        int32_t temp = last;
        last = getchar();
        return temp;
    }

    if (last == '-')
    {
        int32_t next = getchar();

        if (!isdigit(next))
        {
            last = next;
            return '-';
        }

        s[i++] = '-';
        last = next;
    }

    while (isdigit(last))
    {
        s[i++] = last;
        last = getchar();
    }

    if (last == '.')
    {
        s[i++] = last;
        while (isdigit(last = getchar()))
            s[i++] = last;
    }

    s[i] = '\0';
    return NUMBER;
}

/*
Author : Nidhi Goswami
Date : 9-3-2026
Description : function to get output without using ungetch 
*/
void calculator_static_getop()
{
    int32_t type;
    double op2;
    char s[MAXOP];

    getchar();
    printf("Enter postfix expression:\n");

    while((type = get_op(s)) != EOF)

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

            case '%':
                op2 = pop();
                if(op2 != 0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;

            case '\n':
                printf("\t%.8g\n", pop());
                break;

            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
}

