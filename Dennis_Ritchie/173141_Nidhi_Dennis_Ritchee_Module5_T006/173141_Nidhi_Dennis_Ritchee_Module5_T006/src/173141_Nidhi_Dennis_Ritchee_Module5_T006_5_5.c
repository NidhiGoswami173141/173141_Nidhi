/*
Author : Nidhi Goswami
Date : 31-3-2026
Description : Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/

#include <stdio.h>
#include <stdlib.h>
#include"module.h"
#include<stdint.h>
#include <string.h>
char *read_line_function() {
    int Char, index = 0, size = 10;
    char *String = (char *)malloc(size);

    if (String == NULL)
        return NULL;

    while ((Char = getchar()) != '\n' && Char != EOF) {
        String[index++] = Char;

        if (index >= size) {
            size = size * 2;
            String = realloc(String, size);
        }
    }

    String[index] = '\0';
    return String;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
    char *start = dest;

    while (n > 0 && *src != '\0') {
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    while (n > 0) {
        *dest = '\0';
        dest++;
        n--;
    }

    return start;
}

char *my_strncat(char *dest, const char *src, size_t n) {
    char *start = dest;

    while (*dest != '\0') {
        dest++;
    }

    while (n > 0 && *src != '\0') {
        *dest = *src;
        dest++;
        src++;
        n--;
    }

    *dest = '\0';

    return start;
}

int32_t my_strncmp(const char *String1, const char *String2, size_t n) {

    while (n > 0) {

        if (*String1 != *String2)
            return *String1 - *String2;

        if (*String1 == '\0')
            return 0;

        String1++;
        String2++;
        n--;
    }

    return 0;
}

void strn_function(){
    char *String1, *String2;
    size_t n;
    int32_t choice;

    getchar();

    printf("enter string1: ");
    String1 = read_line_function();

    printf("enter string2: ");
    String2 = read_line_function();

    printf("enter n: ");
    scanf("%zu", &n);

    if (!String1 || !String2) {
        printf("memory allocation failed\n");
        return;
    }

    printf("\nchoose operation:\n");
    printf("1. strncpy\n");
    printf("2. strncat\n");
    printf("3. strncmp\n");
    printf("enter choice: ");
    scanf("%d", &choice);

    char *dest = malloc(strlen(String1) + strlen(String2) + 1);

    if (!dest) {
        printf("memory allocation failed\n");
        return;
    }
    char *d = dest;
    char *temp = String1;

    while (*temp != '\0') {
        *d = *temp;
        d++;
        temp++;
    }
    *d = '\0';

    switch(choice) {

        case 1:
        {
            char *p = dest;
            char *src = String2;
            size_t index = 0;

            while (index < n && *src != '\0') {
                *p = *src;
                p++;
                src++;
                index++;
            }

            printf("\nresult: %s\n", dest);
            break;
        }

        case 2:
            my_strncat(dest, String2, n);
            printf("\nresult: %s\n", dest);
            break;

        case 3:
        {
            int res = my_strncmp(String1, String2, n);

            if (res == 0)
                printf("\nresult: match found\n");
            else
                printf("\nresult: no match\n");

            break;
        }

        default:
            printf("invalid choice\n");
    }

    free(String1);
    free(String2);
    free(dest);
}

