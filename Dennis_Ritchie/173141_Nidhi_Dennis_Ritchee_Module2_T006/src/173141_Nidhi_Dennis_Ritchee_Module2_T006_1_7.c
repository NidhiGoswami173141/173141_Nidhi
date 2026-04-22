/*
Author: Nidhi Goswami
Date : 23-02-2023
Description : Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/


#include <stdio.h>
#include<stdint.h>
#include"module.h"

void invert()
{
    int input;
    unsigned int x, result;
    int p, n;
    int bits = 16;

    printf("Enter decimal value of X: ");
    scanf("%d", &input);

    if (input < 0)
    {
        printf("Enter positive value\n");
        return;
    }

    x = (unsigned int)input;

    printf("Enter position P: ");
    scanf("%d", &p);

    printf("Enter number of bits N: ");
    scanf("%d", &n);

    if (p + n > bits)
    {
        printf("Insufficient bits.\nN should be >= P + 1\n");
        return;
    }

    printf("\nBefore invert (Binary): ");
    for (int i = bits - 1; i >= 0; i--)
        printf("%d", (x >> i) & 1);

    unsigned int mask = ((1 << n) - 1) << p;
    result = x ^ mask;

    printf("\nAfter invert  (Binary): ");
    for (int i = bits - 1; i >= 0; i--)
        printf("%d", (result >> i) & 1);

    printf("\nAfter invert  (Decimal): %u\n", result);
}

