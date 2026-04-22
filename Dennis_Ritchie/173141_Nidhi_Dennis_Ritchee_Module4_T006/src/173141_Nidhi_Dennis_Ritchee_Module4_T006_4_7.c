/*
Author : Nidhi Goswami
Date : 9-3-2026
Description: Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch?
*/

#include<stdio.h>
#include<string.h>
#include"module.h"

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for ungets that will push an entire string into input
*/

void ungets(char s[])
{
    int32_t index;

    printf("Enter string: ");
    scanf(" %[^\n]", s);

    for(index = strlen(s) - 1; index >= 0; index--)
    {
        ungetch(s[index]);
    }

    printf("Output: %s\n", s);
}
