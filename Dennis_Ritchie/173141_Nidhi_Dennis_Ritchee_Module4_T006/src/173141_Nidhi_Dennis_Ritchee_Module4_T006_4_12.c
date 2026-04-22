/*
Author: Nidhi Goswami
Date : 9-03-2026
Description : Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"

void itoa_recursive(int32_t number)
{
    if(number/10)
        itoa_recursive(number/10);

    putchar(number%10 + '0');
}

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for convert integer into string using recursive
*/

void itoa_recursive_function()
{
    int32_t number;

    printf("Enter number: ");
    scanf("%d",&number);

    if(number<0)
    {
        putchar('-');
        number=-number;
    }

    itoa_recursive(number);

}

