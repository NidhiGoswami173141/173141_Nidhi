/*
Author: Nidhi Goswami
Date: 18-05-2026
Description: Implement  braket matching problem using stack .
*/


#include<stdio.h>
#include"../header/header.h"
#include<stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isMatching(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool BracketMatching(char str[])
{
    struct node* stack = NULL;

    for (int32_t index = 0; str[index] != '\0'; index++)
    {
        char ch = str[index];

        if (ch == '(' || ch == '{' || ch == '[')
        {
            Push(&stack, ch);
        }

        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (stack == NULL)
            {
                return false;
            }

            char top = Pop(&stack);

            if (!isMatching(top, ch))
            {
                return false;
            }
        }
    }

    return stack == NULL;
}

void BracketMatchingTest()
{
    char str[1000];

    printf("enter Expression:\n");
    getchar();
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    if (BracketMatching(str))
    {
        printf("brackets are Balanced\n");
    }
    else
    {
        printf("brackets are Not Balanced\n");
    }
}

