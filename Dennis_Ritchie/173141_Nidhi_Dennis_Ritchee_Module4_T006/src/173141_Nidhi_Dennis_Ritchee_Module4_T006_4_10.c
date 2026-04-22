/*
Author: Nidhi Goswami
Date: 8-3-2026
Description: An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"module.h"

#define MAXLINE 100

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for read entire input line
*/

void calculator_getline()
{
    char line[MAXLINE];
    char token[50];
    double op2;
    int index, read;
    getch();
    printf("Enter postfix expression:\n");

    while(fgets(line, MAXLINE, stdin) != NULL)
    {
        index = 0;

        while (sscanf(&line[index], "%s%n", token, &read) == 1)
        {
            if(isdigit(token[0]) || (token[0]=='-' && isdigit(token[1])))
            {
                push(atof(token));
            }
            else
            {
                switch(token[0])
                {
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

                    default:
                        printf("error: unknown operator\n");
                        break;
                }
            }

            index += read;
        }

        printf("\t%.8g\n", pop());
    }
}

