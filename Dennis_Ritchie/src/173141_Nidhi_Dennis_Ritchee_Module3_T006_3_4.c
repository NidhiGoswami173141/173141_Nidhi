/*
Author : Nidhi Goswami
Date : 27-02-2026
Description: In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
*/


#include <stdio.h>
#include <stdint.h>
#include"module.h"
#define MAX_SIZE 1000

void itoa(int32_t number, char s[MAX_SIZE]) {
    uint32_t num;
    int32_t index = 0, sign;

    printf("Enter number: ");
    scanf("%d", &number);

    sign = number;

    if (number < 0)
        num = -(uint32_t)number;
    else
        num = number;

    do {
        s[index++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    if (sign < 0)
        s[index++] = '-';

    s[index] = '\0';

    int32_t start = 0, end = index - 1;
    while (start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }

    printf("String: %s\n", s);
}

