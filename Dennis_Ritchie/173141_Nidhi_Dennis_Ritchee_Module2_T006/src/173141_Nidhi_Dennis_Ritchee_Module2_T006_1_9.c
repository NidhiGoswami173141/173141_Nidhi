/*
Author:Nidhi Goswami
Date : 23-02-20206
Description: In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.
*/


#include<stdio.h>
#include<stdint.h>
#include"module.h"

void deletes_rightmost()
{
    unsigned int num, temp;
    int32_t binary[32], index = 0, count = 0;

    printf("Enter a decimal number: ");
    scanf("%u",&num);

    temp = num;

    if (num == 0)
        printf("Binary: 0");
    else
    {
        while (num > 0)
        {
            binary[index++] = num % 2;
            num /= 2;
        }

        printf("Binary: ");
        for (int sec_index = index - 1; sec_index >= 0; sec_index--)
            printf("%d", binary[sec_index]);
    }

    while (temp != 0)
    {
        temp &= (temp - 1);
        count++;
    }

    printf("\nNo of 1's: %d\n", count);
}

