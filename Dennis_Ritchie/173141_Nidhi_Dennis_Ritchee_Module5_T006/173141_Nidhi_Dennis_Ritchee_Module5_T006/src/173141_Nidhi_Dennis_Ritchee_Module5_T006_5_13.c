/*
Author : Nidhi Goswami
Date : 6-04-2026
Description :Write the program tail, which prints the last n lines of its input. By default, n is set to 10, let us say, but it can be changed by an optional argument so that 
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"module.h"
#include<stdint.h>
#define MAXLINES 1000

char *readline() {

    int32_t Char, index = 0, size = 10;
    char *line = (char *)malloc(size);

    if (line == NULL)
        return NULL;

    while ((Char = getchar()) != '\n' && Char != EOF) {

        line[index++] = Char;

        if (index >= size) {
            size *= 2;
            line = realloc(line, size);
        }
    }

    if (Char == EOF && index == 0)
        return NULL;

    line[index] = '\0';
    return line;
}

void tail_function(int32_t argc, char *argv[]) {

    int32_t n = 10;

    if (argc == 2) {
        n = atoi(argv[1]);
        if (n <= 0)
            n = 10;
    }

    char *lineptr[MAXLINES];
    int32_t count = 0;

    printf("enter lines (Ctrl+D to stop):\n");

    char *line;

    while ((line = readline()) != NULL) {

        if (count < MAXLINES) {
            lineptr[count++] = line;
        }
    }

    int32_t start;

    if (count > n)
        start = count - n;
    else
        start = 0;

    printf("\nlast %d lines:\n", n);

    for (int32_t index = start; index < count; index++) {
        printf("%s\n", lineptr[index]);
    }


    for (int32_t index = 0; index < count; index++) {
        free(lineptr[index]);
    }
}

