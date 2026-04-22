/*
Author : Nidhi Goswami
Date : 22-02-2026
Description : Write a loop equivalent to the for loop above without using && or ||.
*/

#include <stdio.h>
#include <stdint.h>
#include "module.h"

#define lim 10
/*
Author : Nidhi Goswami
Date : 19-02-2026
Description : function  for 
*/

void loop() {
    int8_t index = 0;
    int32_t Char;
    int8_t s[lim];

    while (index < lim - 1) {
        Char = getchar();

        if (Char == EOF)
            break;

        if (Char == '\n')
            break;

        s[index] = Char;
        ++index;
    }

    s[index] = '\0';

    printf("%s", s);
}

