/*
Author : Nidhi Goswami
Date : 23-02-2026
Description : Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/


#include<stdio.h>
#include<stdint.h>
#include "module.h"
void setbits()
{
    unsigned int x, y, result;
    int p, n;

    printf("Enter x: ");
    scanf("%u", &x);

    printf("Enter y: ");
    scanf("%u", &y);

    printf("Enter position p: ");
    scanf("%d", &p);

    printf("Enter number of bits n: ");
    scanf("%d", &n);

	if(x < 0 || y < 0 || p < 0 || n < 0){
		printf("Enter positive value\n");
		return;
	}

    unsigned int ybits = y & ((1 << n) - 1);

    ybits <<= (p - n + 1);

    unsigned int mask = ~(((1 << n) - 1) << (p - n + 1));
    x = x & mask;

    result = x | ybits;

    printf("Result (decimal) = %u\n", result);
}
