/*
Author: Nidhi Goswami
Date: 7-04-2026
Description: Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<string.h>
#include<stdlib.h>
#define MAXLINES 5000
#define MAXLEN   1000

extern char *line_ptr[MAXLINES];
int32_t strcmp_fold(char *, char *);
/*
Author: Nidhi Goswami
Date: 07-04-2026
Description : function for string comparision for fold uppercase and lowercase toghether 
*/
int32_t strcmp_fold(char *String1, char *String2)
{
    while (tolower(*String1) == tolower(*String2)) {
        if (*String1 == '\0')
            return 0;
        String1++;
        String2++;
    }

    return tolower(*String1) - tolower(*String2);
}

void handle_flag_RNF(int32_t argc, char *argv[])
{
    int32_t nlines;
    int32_t numeric = 0;
    int32_t reverse = 0;
    int32_t fold = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        char *p = *argv;
        while (*++p) {
            if (*p == 'n')
                numeric = 1;
            else if (*p == 'r')
                reverse = 1;
            else if (*p == 'f')
                fold = 1;
        }
    }

    printf("numeric=%d reverse=%d fold=%d\n", numeric, reverse, fold);

    if ((nlines = readlines_fun(line_ptr, MAXLINES)) >= 0) {

        my_qsort_fun((void **)line_ptr, 0, nlines - 1,
            (int32_t (*)(void *, void *))(
                numeric ? numcmp : (fold ? strcmp_fold : strcmp)),reverse);

        writelines_fun(line_ptr, nlines);

    } else {
        printf("error: input too big for sort\n");
    }
}
