/*
Author: Nidhi Goswami
Date: 3-4-2026
Description : There is no error checking in day_of_year or month_day. Remedy this defect.
*/
#include <stdio.h>
#include<stdint.h>
#include"module.h"
static int daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int32_t month_day_fun(int32_t year, int32_t yearday, int32_t *pmonth, int32_t *pday);
int32_t is_leap(int32_t year) {
    return (year%4==0 && year%100!=0) || (year%400==0);
}

int32_t day_of_year_fun(int32_t year, int32_t month, int32_t day) {
    int32_t index;
    int32_t *p;

    if (year < 1 || month < 1 || month > 12)
        return -1;

    int32_t leap = is_leap(year);

    p = daytab[leap];

    if (day < 1 || day > *(p + month))
        return -1;

    for (index = 1; index < month; index++) {
        day += *(p + index);
    }

    return day;
}

int32_t month_day_fun(int32_t year, int32_t yearday, int32_t *pmonth, int32_t *pday) {
    int32_t index;
    int32_t *p;

    if (year < 1)
        return -1;

    int32_t leap = is_leap(year);

    p = daytab[leap];

    int32_t max_days = leap ? 366 : 365;

    if (yearday < 1 || yearday > max_days)
        return -1;

    for (index = 1; index <= 12 && yearday > *(p + index); index++) {
        yearday -= *(p + index);
    }

    *pmonth = index;
    *pday   = yearday;

    return 0;
}

void error_checking() {
    int32_t year, month, day;
    int32_t yearday;
    int32_t m, d;

    printf("Enter year, month, day: ");
    scanf("%d %d %d", &year, &month, &day);

    int32_t result = day_of_year_fun(year, month, day);

    if (result == -1)
        printf("Invalid input\n");
    else
        printf("Day of year: %d\n", result);

    printf("Enter year and yearday: ");
    scanf("%d %d", &year, &yearday);

    if (month_day_fun(year, yearday, &m, &d) == -1)
        printf("Invalid input\n");
    else
        printf("Month: %d Day: %d\n", m, d);

}
