/*
Author : Nidhi Goswami
Date : 3-3-2026
Descripion: Extend atof to handle scientific notation of the form  123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include <ctype.h>

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function  for string to float which handle scientific naotation 
*/

void a_atof()
{
    char s[1000];
    double val = 0.0, power = 1.0;
    int32_t index = 0, sign = 1;
    int32_t exp = 0, exp_sign = 1;

    printf("Enter number: ");
    scanf("%s", s);
    while (isspace(s[index]))
        index++;

    if (s[index] == '-') {
        sign = -1;
        index++;
    } else if (s[index] == '+') {
        index++;
    }

    while (isdigit(s[index])) {
        val = 10 * val + (s[index] - '0');
        index++;
    }


    if (s[index] == '.')
        index++;

    while (isdigit(s[index])) {
        val = 10 * val + (s[index] - '0');
        power *= 10;
        index++;
    }


    if (s[index] == 'e' || s[index] == 'E') {
        index++;

        if (s[index] == '-') {
             exp_sign = -1;
	     val = sign * val / power;
             index++;
        } else if (s[index] == '+') {
            index++;
        }

        while (isdigit(s[index])) {
            exp = 10 * exp + (s[index] - '0');
            index++;
        }

        while (exp > 0) {
            if (exp_sign == 1)
                val *= 10;
            else
                val /= 10;
            exp--;
        }
    }

    printf("value: %lf\n",val);
}

