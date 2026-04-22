/*
Author: Nidhi Goswami
Date : 23-02-2026
Descritpion : Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n positions.
*/


#include <stdio.h>
#include "module.h"
#include<stdint.h>
void rightrot()
{
    int32_t input;
    uint32_t x;
    int32_t n;
    int32_t bits = 16;
    uint32_t mask = 0xFFFF;

    printf("Enter decimal value of X: ");
    scanf("%d", &input);

    if (input < 0)
    {
        printf("Error: Please enter a non-negative number\n");
        return;
    }

    x = (uint32_t)input;

    printf("Enter rotation count N: ");
    scanf("%d", &n);

    n = (n % bits + bits) % bits;

    printf("Original: ");
    for (int index = bits - 1; index >= 0; index--)
        printf("%d", (x >> index) & 1);

    x = ((x >> n) | (x << (bits - n))) & mask;

    printf("\nAfter rotation: ");
    for (int index = bits - 1; index >= 0; index--)
        printf("%d", (x >> index) & 1);

    printf("\nRotated Decimal : %u\n", x);
}

