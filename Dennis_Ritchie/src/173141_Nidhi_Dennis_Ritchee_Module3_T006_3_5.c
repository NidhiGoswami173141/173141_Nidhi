/*
Author: Nidhi Goswami
Date : 27-02-2026
Description : Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s. In particular, itob(n,s,16) formats s as a hexadecimal integer in s.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"

void itob(int32_t n, char str[], int32_t base)
{

    printf("Enter number:\n");
    scanf("%d", &n);

    printf("Enter base (2-16):\n");
    scanf("%d", &base);


    if (base < 2 || base > 16) {
        printf("Enter a valid base value\n");
        str[0] = '\0';
        return;
    }

    char digits[] = "0123456789ABCDEF";
    int32_t index = 0;
    uint32_t num;

    if (n < 0)
        num = -(uint32_t)n;
    else
        num = n;

    do {
        str[index++] = digits[num % base];
        num /= base;
    } while (num > 0);

    if (n < 0)
        str[index++] = '-';

    str[index] = '\0';

    int32_t sec_index = 0;
    int32_t third_index = index - 1;

    while (sec_index < third_index) {
       char temp = str[sec_index];
         str[sec_index] = str[third_index];
         str[third_index] = temp;
         sec_index++;
         third_index--;
   }
    printf("Ans = %s\n", str);
}

