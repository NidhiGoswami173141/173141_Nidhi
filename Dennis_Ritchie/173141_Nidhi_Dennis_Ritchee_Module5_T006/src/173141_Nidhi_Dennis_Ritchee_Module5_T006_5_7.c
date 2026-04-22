/*
Author: Nidhi Goswami
Date : 3-04-2026
Description : Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?
*/

#include <stdio.h>
#include <string.h>
#include"module.h"
#include<stdint.h>
#define MAXLINES 5000
#define MAXLEN 1000
#define BUFSIZE 10000

char *lineptr[MAXLINES];

/* modified readlines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];

    static char buffer[BUFSIZE];   /*buffer from main*/
    char *bufp = buffer;

    while ((len = getline_fun(line, MAXLEN)) > 0) {

        if (nlines >= maxlines)
            return -1;

        if (bufp + len > buffer + BUFSIZE)
            return -1;

        line[len-1] = '\0';   /*remove newline*/

        strcpy(bufp, line);   /*copy into buffer*/
        lineptr[nlines++] = bufp;

        bufp += len;          /*move pointer*/
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("Line %d: %s\n", i + 1, lineptr[i]);
}

void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort_fun(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);

    qsort_fun(v, left, last-1);
    qsort_fun(v, last+1, right);
}

int getline_fun(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 &&
         (c = getchar()) != EOF &&
         c != '\n'; i++)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

void read_lines()
{
    int nlines;

    printf("Enter lines (Ctrl+D to stop):\n");

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {

        printf("\nUnsorted Lines:\n");
        writelines(lineptr, nlines);

        qsort_fun(lineptr, 0, nlines - 1);

        printf("\nSorted Lines:\n");
        writelines(lineptr, nlines);

    } else {
        printf("error: input too big to sort\n");
    }

}

