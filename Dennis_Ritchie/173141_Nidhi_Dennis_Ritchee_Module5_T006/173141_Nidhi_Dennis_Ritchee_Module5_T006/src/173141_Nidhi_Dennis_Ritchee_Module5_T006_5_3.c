/*
Author: Nidhi Goswami
Date : 31-03-2026
Description : Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.
*/

#include <stdio.h>
#include<stdint.h>
#include <string.h>
#include <stdlib.h>
#include"module.h"
/*
Author : nidhi Goswami
Date : 31-03-2026
Description : function for concatnate stirng 
*/

void strcat_ptr(char *String1, char *String2) {
    while (*String1)
        String1++;

    while ((*String1++ = *String2++));
}

/*
Author : nidhi goswami
Date : 31-03-2026
Description : function for read input 
*/

char *read_line() {
    int32_t Char;
    int32_t len = 0;
    int32_t size = 10;

    char *str = (char *)malloc(size);
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
Author : nidhi goswami
Date : 31-03-2026
Description : function for check special character 
*/
int32_t is_special(char *String) {
    return (String[0] == '&' && String[1] == '\0');
}


void strcat_string() {
    char *String1, *String2, *result;

    getchar();

    printf("Enter the first string: ");
    String1 = read_line();

    printf("Enter the second string: ");
    String2 = read_line();

    if (!String1 || !String2) {
        printf("Memory allocation failed\n");
        return;
    }


    if (is_special(String1) && is_special(String2)) {
        result = malloc(1);
        result[0] = '\0';
    }
    else if (is_special(String1)) {
        result = malloc(strlen(String2) + 1);
        char *d = result;
        char *src = String2;
        while ((*d++ = *src++));
    }
    else if (is_special(String2)) {
        result = malloc(strlen(String1) + 1);
        char *d = result;
        char *src = String1;
        while ((*d++ = *src++));
    }
    else {
        int len_s = 0, len_t = 0;

        while (String1[len_s]) len_s++;
        while (String2[len_t]) len_t++;

        result = malloc(len_s + len_t + 1);

        char *d = result;
        char *temp = String1;

        while ((*d++ = *temp++));
        d--;

        temp = String2;
        while ((*d++ = *temp++));
    }

    printf("Result: %s\n", result);

    free(String1);
    free(String2);
    free(result);
}
