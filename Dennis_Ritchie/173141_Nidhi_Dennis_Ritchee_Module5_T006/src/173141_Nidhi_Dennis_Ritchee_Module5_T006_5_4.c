/*
Author : Nidhi Goswami
Date : 31-03-2026
Description: Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise
*/


#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<stdint.h>

/*
Author: Nidhi Goswami
date : 31-3-2026
Description : function for read input 
*/

char *read_line_fun() {
    int32_t Char, len = 0, size = 10;

    char *str = malloc(size);
    if (!str) return NULL;

    while ((Char = getchar()) != '\n' && Char != EOF) {
        str[len++] = Char;

        if (len >= size) {
            size *= 2;
            char *temp = realloc(str, size);
            if (!temp) {
                free(str);
                return NULL;
            }
            str = temp;
        }
    }

    str[len] = '\0';
    return str;
}

/*
Author : Nidhi Goswami
Date :31-3-2026
Descriprion : function for write match indext et the end 
*/


int strend(char *String1, char *String2) {
    char *p = String1;
    char *q = String2;

    while (*p) p++;
    while (*q) q++;

    while (q > String2) {
        if (*(--p) != *(--q))
            return 0;
    }

    return 1;
}

void strend_function() {
    char *String1, *String2;

    getchar();
    printf("enter string1: ");
    String1 = read_line_fun();

    printf("enter string2: ");
    String2 = read_line_fun();

    if (!String1 || !String2) {
        printf("Memory allocation failed\n");
        return;
    }

    int32_t result = strend(String1, String2);

    printf("Output: %d\n", result);

    free(String1);
    free(String2);
}
