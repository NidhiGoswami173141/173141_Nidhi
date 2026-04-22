#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<string.h>
#include<stdlib.h>
#include"module.h"
#define MAXLINES 5000
#define MAXLEN   1000

char *line_ptr[MAXLINES];

/* function declarations */
int32_t readlines_fun(char *line_ptr[], int32_t maxlines);
void writelines_fun(char *line_ptr[], int32_t nlines);
void my_qsort_fun(char *v[], int32_t left, int32_t right,
                 int32_t (*comp)(void *, void *), int32_t reverse);

int32_t numcmp(char *, char *);
int32_t getline1(char *, int32_t);
char *alloc(int);
void swap_fun(char *v[], int32_t i, int32_t j);

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return NULL;
}

int32_t readlines_fun(char *line_ptr[], int32_t maxlines)
{
    int32_t len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getline1(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;

        line[len - 1] = '\0';
        strcpy(p, line);
        line_ptr[nlines++] = p;
    }
    return nlines;
}

void writelines_fun(char *line_ptr[], int32_t nlines)
{
    for (int32_t i = 0; i < nlines; i++)
        printf("%s\n", line_ptr[i]);
}

int32_t getline1(char *s, int32_t lim)
{
    int32_t c, i = 0;

    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    return i;
}

void my_qsort_fun(char *v[], int32_t left, int32_t right,
                 int32_t (*comp)(void *, void *), int32_t reverse)
{
    int32_t i, last;

    if (left >= right)
        return;

    swap_fun(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        int result = comp(v[i], v[left]);

        if (reverse)
            result = -result;

        if (result < 0)
            swap_fun(v, ++last, i);
    }

    swap_fun(v, left, last);

    my_qsort_fun(v, left, last - 1, comp, reverse);
    my_qsort_fun(v, last + 1, right, comp, reverse);
}

/* numeric compare */
int32_t numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}

/* swap */
void swap_fun(char *v[], int32_t i, int32_t j)
{
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
