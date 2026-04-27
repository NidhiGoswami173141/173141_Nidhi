/*
Author : Nidhi Goswami
Date : 18-4-2026
Description: Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4). 
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include"module.h"

char *read_line_common() {
    int ch, size = 10, index = 0;
    char *str = malloc(size);

    if (!str) return NULL;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        str[index++] = ch;

        if (index >= size) {
            size *= 2;
            str = realloc(str, size);
        }
    }

    str[index] = '\0';
    return str;
}

void my_getline(char *String) {
    char *p = String;

    while (*p)
        p++;

    printf("result: %s\n", String);
}

void my_atoi_func(char *String) {
    char *p = String;
    int sign = 1, num = 0;

    if (*p == '-') {
        sign = -1;
        p++;
    }

    if (!isdigit(*p)) {
        printf("enter valid input\n");
        return;
    }

    while (isdigit(*p)) {
        num = num * 10 + (*p - '0');
        p++;
    }

    if (*p != '\0') {
        printf("enter valid input\n");
    } else {
        printf("integer: %d\n", sign * num);
    }
}

void my_itoa_func() {
    int32_t num;
    scanf("%d", &num);

    char *String = malloc(100);
    char *p = String;
    int32_t sign = num;

    if (num < 0)
        num = -num;

    do {
        *p++ = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    if (sign < 0)
        *p++ = '-';

    *p = '\0';

    char *start = String;
    char *end = p - 1;

    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }

    printf("string: %s\n", String);

    free(String);
}

void my_reverse_func(char *String) {
    char *start = String;
    char *end = String;

    while (*end)
        end++;
    end--;

    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }

    printf("result: %s\n", String);
}

void my_strindex_func(char *String1, char *String2) {
    char *p = String1;

    while (*p) {
        char *start = p;
        char *q = String2;

        while (*p == *q && *q) {
            p++;
            q++;
        }

        if (*q == '\0') {
            printf("string found at position %ld\n", start - String1 + 1);
            return;
        }

        p = start + 1;
    }

    printf("no match found\n");
}

void my_getop_func() {
    int32_t ch1, ch2;
    char op;

    scanf("%d %d %c", &ch1, &ch2, &op);

    switch(op) {
        case '+': printf("result: %d\n", ch1 + ch2); break;
        case '-': printf("result: %d\n", ch1 - ch2); break;
        case '*': printf("result: %d\n", ch1 * ch2); break;
        case '/':
            if (ch2 != 0)
                printf("result: %d\n", ch1 / ch2);
            else
                printf("division by zero\n");
            break;
        default:
            printf("invalid operator\n");
    }
}

void functions() {
    int32_t choice;
    char *String1, *String2;

    printf("\nchoose operation:\n");
    printf("1. getline\n");
    printf("2. atoi\n");
    printf("3. itoa\n");
    printf("4. reverse\n");
    printf("5. strindex\n");
    printf("6. getop\n");
    printf("enter choice: ");
    scanf("%d", &choice);
    getchar();

    switch(choice) {

        case 1:
            printf("enter string: ");
            String1 = read_line_common();
            my_getline(String1);
            free(String1);
            break;

        case 2:
            printf("enter string: ");
            String1 = read_line_common();
            my_atoi_func(String1);
            free(String1);
            break;

        case 3:
            printf("enter integer: ");
            my_itoa_func();
            break;

        case 4:
            printf("enter string: ");
            String1 = read_line_common();
            my_reverse_func(String1);
            free(String1);
            break;

        case 5:
            printf("enter string: ");
            String1 = read_line_common();

            printf("enter match: ");
            String2 = read_line_common();

            my_strindex_func(String1, String2);

            free(String1);
            free(String2);
            break;

        case 6:
            printf("enter expression (e.g., 4 3 +): ");
            my_getop_func();
            break;

        default:
            printf("invalid choice\n");
    }
}

