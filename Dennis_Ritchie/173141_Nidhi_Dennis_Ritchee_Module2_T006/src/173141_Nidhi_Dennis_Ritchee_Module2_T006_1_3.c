/*
Author:Nidhi Goswami
Date:17-2-2026
Description :Write a function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.
*/


#include <stdio.h>
#include <ctype.h>
#include"module.h"
#include<stdint.h>

void htoi() {
    int32_t index = 0;
    int32_t number = 0;
    char String[50];

    printf("enter a number:\n");
    scanf("%s",&String);
    if (String[0] == '0') {
        if (String[1] == 'x' || String[1] == 'X') {
            index = 2;
        }
    }

    for (; String[index] != '\0'; index++) {
        char Char = String[index];

        if (Char >= '0' && Char <= '9')
            number = number * 16 + (Char - '0');
        else if (Char >= 'a' && Char <= 'f')
            number = number * 16 + (Char - 'a' + 10);
        else if (Char >= 'A' && Char <= 'F')
            number = number * 16 + (Char - 'A' + 10);
        else
            break;
    }

    printf("%d\n", number);
}
