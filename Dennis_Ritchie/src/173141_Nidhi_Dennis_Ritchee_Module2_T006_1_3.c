#include <stdio.h>
#include <ctype.h>
#include"module.h"
#include<stdint.h>

void htoi() {
    int32_t index = 0;
    int8_t number = 0;
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
