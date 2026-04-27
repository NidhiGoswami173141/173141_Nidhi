/*
Author:Nidhi Goswami
Date:3003-2026
Description: Write a function getfloat, the floating-point analog of getint. What type does getfloat return as its function value?
*/


#include<stdio.h>
#include<stdint.h>
#include <ctype.h>
#include "module.h"
/*
Author: nidhi goswami
Date : 30-03-2026
Description : function for get float
*/
int32_t getfloat(double *pn) {
    int32_t Char, sign;
    double power = 1.0;

    printf("enter a float number: ");

    while (isspace(Char = getch()));

    if (!isdigit(Char) && Char != EOF && Char != '+' && Char != '-' && Char != '.') {
        ungetch(Char);
        printf("invalid entry\n");
        return 0;
    }

    sign = (Char == '-') ? -1 : 1;

    if (Char == '+' || Char == '-') {
        int32_t next = getch();

        if (!isdigit(next) && next != '.') {
            ungetch(next);
            ungetch(Char);
            printf("invalid entry\n");
            return 0;
        }
        Char = next;
    }

    for (*pn = 0.0; isdigit(Char); Char = getch())
        *pn = 10.0 * (*pn) + (Char - '0');

    if (Char == '.') {
        Char = getch();
        for (; isdigit(Char); Char = getch()) {
            *pn = 10.0 * (*pn) + (Char - '0');
            power *= 10.0;
        }
    }

    *pn = sign * (*pn) / power;

    if (Char != EOF)
        ungetch(Char);

    printf("valid Float: %f\n", *pn);

    return (Char == EOF) ? EOF : 1;
}

