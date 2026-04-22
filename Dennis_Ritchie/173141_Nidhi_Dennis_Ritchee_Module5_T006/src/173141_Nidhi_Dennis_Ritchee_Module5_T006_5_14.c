/*
Author: Nidhi Goswami
Date : 7-4-2026
Description : Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include <string.h>
#include <stdlib.h>
#define MAXLINES 5000
#define MAXLEN   1000

extern char *line_ptr[MAXLINES];
void handle_flag_RN(int32_t argc, char *argv[])
{
    int32_t nlines;
    int32_t numeric = 0;
    int32_t reverse = 0;

    /* process command-line arguments */
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *p = *argv;
        while (*++p) {
            if (*p == 'n')
                numeric = 1;
            else if (*p == 'r')
                reverse = 1;
        }
    }
    printf("numeric=%d reverse=%d\n", numeric, reverse);
    printf("enter input:\n");
    if ((nlines = readlines_fun(line_ptr, MAXLINES)) >= 0) {

        my_qsort_fun((void **)line_ptr, 0, nlines - 1,
                 (int32_t (*)(void *, void *))(numeric ? (int32_t (*)(void*,void*))numcmp : (int32_t (*)(void*,void*))strcmp),
                 reverse);
        printf("\n");
        writelines_fun(line_ptr, nlines);
        return 0;

    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

