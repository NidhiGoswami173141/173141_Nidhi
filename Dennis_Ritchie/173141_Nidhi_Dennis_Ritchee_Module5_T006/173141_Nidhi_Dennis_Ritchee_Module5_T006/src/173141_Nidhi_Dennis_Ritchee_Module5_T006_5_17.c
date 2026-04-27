/*
Author: Nidhi Goswami
Date: 07-04-2026
Description: Task is 
Identify and sort specific fields within each line.
Apply different sorting options to each field independently.
*/

#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"module.h"

#define MAXLINES 5000

extern char *line_ptr[MAXLINES];
int32_t fold_flag = 0;
int32_t dir_flag = 0;
int32_t reverse_flag = 0;

void get_field1(char *line, char *out)
{
    int32_t index = 0;

    while (line[index] != ',' && line[index] != '\0') {
        out[index] = line[index];
        index++;
    }
    out[index] = '\0';
}


void get_field2(char *line, char *out)
{
    int32_t index = 0;
    char *p = strchr(line, ',');

    if (!p) {
        out[0] = '\0';
        return;
    }

    p++;
    while (*p == ' ') p++;

    while (*p != '\0') {
        out[index++] = *p;
        p++;
    }
    out[index] = '\0';
}

int32_t strcmp_df(char *String1, char *String2, int32_t fold, int directory)
{
    while (*String1 || *String2) {

        if (directory) {
            while (*String1 && !isalnum(*String1) && !isspace(*String1)) String1++;
            while (*String2 && !isalnum(*String2) && !isspace(*String2)) String2++;
        }

        char ch1 = fold ? tolower(*String1) : *String1;
        char ch2 = fold ? tolower(*String2) : *String2;

        if (ch1 != ch2)
            return ch1 - ch2;

        if (*String1) String1++;
        if (*String2) String2++;
    }
    return 0;
}

int32_t numcmp_field(char *String1, char *String2)
{
    double v1 = atof(strchr(String1, ':') ? strchr(String1, ':') + 1 : String1);
    double v2 = atof(strchr(String2, ':') ? strchr(String2, ':') + 1 : String2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

int field_compare(void *ch1, void *ch2)
{
    char *line1 = (char *)ch1;
    char *line2 = (char *)ch2;

    char f1_line1[100], f1_line2[100];
    char f2_line1[100], f2_line2[100];

    get_field1(line1, f1_line1);
    get_field1(line2, f1_line2);

    int32_t result = strcmp_df(f1_line1, f1_line2, fold_flag, dir_flag);

    if (result != 0)
        return result;

    get_field2(line1, f2_line1);
    get_field2(line2, f2_line2);

    return numcmp(f2_line1, f2_line2);
}
void handle_field_sort(int32_t argc, char *argv[])
{
    int32_t nlines;

    /* parse flags like previous questions */
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *p = *argv;
        while (*++p) {
            if (*p == 'f') fold_flag = 1;
            else if (*p == 'd') dir_flag = 1;
            else if (*p == 'r') reverse_flag = 1;
        }
    }

    if ((nlines = readlines_fun(line_ptr, MAXLINES)) >= 0) {

        my_qsort_fun(
            (void **)line_ptr,
            0,
            nlines - 1,
            field_compare,
            reverse_flag
        );

        writelines_fun(line_ptr, nlines);

    } else {
        printf("error: input too big\n");
    }
}

