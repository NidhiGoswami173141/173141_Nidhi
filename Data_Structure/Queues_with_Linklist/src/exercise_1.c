/*
Author: Nidhi Goswami
Date: 15-05-2026
Description: A palindrome is a string that reads the same backward as forward, e.g. "ABCBA" or "Madam, I'm Adam". Your application will read strings from the user, and for each string the user inputs, it should print a message indicating to the user whether or not the string is a palindrome. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "../header/header.h"

bool isPalindrome(char str[])
{
    struct node* stack = NULL;

    queue* Q = queue_new();

    for (int32_t index = 0; str[index] != '\0'; index++)
    {
        if (isalpha(str[index]))
        {
            char ch = tolower(str[index]);

            Push(&stack, ch);

            enq(Q, ch);
        }
    }

    while (!queue_empty(Q))
    {
        char qchar = deq(Q);

        char schar = Pop(&stack);

        if (qchar != schar)
        {
            return false;
        }
    }

    return true;
}

void PelindromeTest()
{
    char str[1000];

    printf("enter String:\n");
    getchar();
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = '\0';

    if (isPalindrome(str))
    {
        printf("palindrome\n");
    }
    else
    {
        printf("not palindrome\n");
    }
}
