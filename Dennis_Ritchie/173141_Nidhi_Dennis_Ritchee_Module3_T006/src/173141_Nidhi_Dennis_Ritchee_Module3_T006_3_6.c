/*
Author: Nidhi Goswami
Date : 2-2-2026
Description: Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.
*/

#include <stdio.h>
#include <string.h>
#include"module.h"

/*
Author: Nidhi Goswami
Date : 2-2-2026
Description : function for convert integer to string that take three arguments 
*/

void itoa_width(int32_t num, char Str[], int32_t min_width)
{

    printf("Enter number:\n");
    scanf("%d", &num);

    printf("Enter minimum width:\n");
    scanf("%d", &min_width);

    int32_t index = 0, sign;
    char temp[50];

    if ((sign = num) < 0)
        num = -num;

    do {
        temp[index++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0)
        temp[index++] = '-';

    temp[index] = '\0';

    int32_t len = index;
    for (int32_t sec_index = 0; sec_index < len; sec_index++)
        Str[sec_index] = temp[len - sec_index - 1];

    Str[len] = '\0';

    if (len < min_width) {
        int32_t padding = min_width - len;

        for (int32_t sec_index = len; sec_index >= 0; sec_index--)
            Str[sec_index + padding] = Str[sec_index];

        for (int32_t sec_index = 0; sec_index < padding; sec_index++)
            Str[sec_index] = '0';
    }
    printf("Ans = %s\n", Str);
}

