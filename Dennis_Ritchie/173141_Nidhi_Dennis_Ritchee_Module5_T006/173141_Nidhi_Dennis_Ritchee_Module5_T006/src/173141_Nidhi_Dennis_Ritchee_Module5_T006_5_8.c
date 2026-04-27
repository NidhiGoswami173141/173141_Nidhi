/*
Author: Nidhi Goswami
Date: 3-4-2026
Description : There is no error checking in day_of_year or month_day. Remedy this defect.
*/
#include <stdio.h>
#include<stdint.h>
#include"module.h"

static int32_t daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

static int32_t day_of_year(int32_t year, int32_t month, int32_t day) {
    int32_t index, leap;

    if (year < 1)
        return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (month < 1 || month > 12)
        return -1;

    if (day < 1 || day > daytab[leap][month])
        return -1;

    for (index = 1; index < month; index++)
        day += daytab[leap][index];

    return day;
}

static int32_t month_day(int32_t year, int32_t yearday, int32_t *pmonth, int32_t *pday) {
    int32_t index, leap;

    if (year < 1)
        return -1;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (yearday < 1 || yearday > (leap ? 366 : 365))
        return -1;

    for (index = 1; yearday > daytab[leap][index]; index++)
        yearday -= daytab[leap][index];

    *pmonth = index;
    *pday = yearday;

    return 0;
}

void error_checking(){
    int32_t choice;
    char cont;

    do {
        printf("\nChoose operation:\n");
        printf("1. day_of_year\n");
        printf("2. month_day\n");
        printf("3. both\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1: {
                int32_t year, month, day, result;

                printf("Enter year, month, and day: ");
                scanf("%d %d %d", &year, &month, &day);

                result = day_of_year(year, month, day);

                if (result == -1)
                    printf("Invalid input\n");
                else
                    printf("Day of year: %d\n", result);

                break;
            }

            case 2: {
                int32_t year, yearday, pmonth, pday;

                printf("Enter year and day of year: ");
                scanf("%d %d", &year, &yearday);

                if (month_day(year, yearday, &pmonth, &pday) == -1)
                    printf("Invalid input\n");
                else {
                    printf("Month: %d, Day: %d\n", pmonth, pday);
                    printf("Date would be: %d/%d/%d\n", pday, pmonth, year);
                }

                break;
            }

            case 3: {
                int32_t year, month, day, yearday;
                int32_t result, pmonth, pday;

                printf("Enter year, month, and day: ");
                scanf("%d %d %d", &year, &month, &day);

                result = day_of_year(year, month, day);

                if (result == -1)
                    printf("Invalid input for day_of_year\n");
                else
                    printf("Day of year: %d\n", result);

                printf("\nEnter year and day of year: ");
                scanf("%d %d", &year, &yearday);

                if (month_day(year, yearday, &pmonth, &pday) == -1)
                    printf("Invalid input for month_day\n");
                else {
                    printf("Month: %d, Day: %d\n", pmonth, pday);
                    printf("Date would be: %d/%d/%d\n", pday, pmonth, year);
                }

                break;
            }

            default:
                printf("Invalid choice\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y');

    return 0;
}

