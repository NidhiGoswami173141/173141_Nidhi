/*
Author : Nidhi Goswami
Date: 3-4-2026
Desscription : Rewrite the routines day_of_year and month_day with pointers instead of indexing.
*/


#include<stdio.h>
#include <stdio.h>
#include"module.h"
#include<stdint.h>
/* days in months */
static int32_t daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int32_t day_of_year(int32_t year, int32_t month, int32_t day) {
    int32_t leap;
    leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);

    int32_t *p = daytab[leap];        /* pointer to row*/
    int32_t *end = p + month;         /* till given month*/

    p++; /* skip index 0*/

    while (p < end) {
        day += *p;
        p++;
    }

    return day;
}

void month_day(int32_t year, int32_t yearday, int32_t *month, int32_t *day) {
    int32_t leap;
    leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);

    int32_t *p = daytab[leap];
    int32_t i = 1;

    p++;

    while (yearday > *p) {
        yearday -= *p;
        p++;
        i++;
    }

    *month = i;
    *day = yearday;
}

void day_month_function() {
    int32_t year, month, day, yearday;
    int32_t m, d;

    printf("Enter year, month, and day: ");
    scanf("%d %d %d", &year, &month, &day);

    int32_t result = day_of_year(year, month, day);
    printf("Day of year: %d\n", result);

    printf("Enter year and day of year: ");
    scanf("%d %d", &year, &yearday);

    month_day(year, yearday, &m, &d);

    printf("Month: %d, Day: %d\n", m, d);
    printf("Date would be: %d/%d/%d\n", m, d, year);
}

