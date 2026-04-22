/*
Author: Nidhi Goswami
Date : 2-3-2026
Description : Write the function strindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<ctype.h>

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for return the position of the rightmost occurrence
*/

void strindex()
{
    char s[100], t[100];
    int32_t index, sec_index, third_index;
    int32_t position = -1;

    printf("Enter main string:\n");
    scanf(" %[^\n]", s);

    printf("Enter substring:\n");
    scanf(" %[^\n]", t);

    for (index = 0; s[index] != '\0'; index++)
    {
        sec_index = index;
        third_index = 0;

        while (t[third_index] != '\0' &&
               tolower(s[sec_index]) == tolower(t[third_index]))
        {
            sec_index++;
            third_index++;
        }

        if (t[third_index] == '\0')
            position = index;
    }

    printf("\nString with indexes:\n");
    for (index = 0; s[index] != '\0'; index++)
        printf("%d:%c  ", index + 1, s[index]);

    if (position == -1)
        printf("\n\nRightmost index = -1\n");
    else
        printf("\n\nRightmost index = %d\n", position + 1);
}

