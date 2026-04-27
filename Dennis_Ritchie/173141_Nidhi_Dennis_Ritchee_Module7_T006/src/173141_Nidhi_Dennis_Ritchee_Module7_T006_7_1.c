/*
Author : Nidhi Goswami
Date : 20-4-2026
Description : Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0].
*/


#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include"module.h"
void upper_lower(int argc, char *argv[])
{
    int c;

    if (argc < 2) {
        printf("Usage: ./program upper OR lower\n");
        return;
    }

    if (strcmp(argv[1], "upper") == 0) {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    }
    else if (strcmp(argv[1], "lower") == 0) {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    }
    else {
        printf("Invalid argument. Use upper or lower\n");
    }
}

