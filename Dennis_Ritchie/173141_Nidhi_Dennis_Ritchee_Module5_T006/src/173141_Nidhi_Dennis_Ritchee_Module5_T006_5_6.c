/*
Author: Nidhi Goswami
Date : 31-03-2026
Description : Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
*/
#include<stdio.h>
#include<stdint.h>
#include"module.h"
#include<stdlib.h>
#include<ctype.h>

char *read_line_common() {
    int Char, size = 10, index = 0;
    char *String = malloc(size);

    if (!String) return NULL;

    while ((Char = getchar()) != '\n' && Char != EOF) {
        String[index++] = Char;

        if (index >= size) {
            size *= 2;
            String = realloc(String, size);
        }
    }

    String[index] = '\0';
    return String;
}


void my_getline() {
    char *String = malloc(1000);
    char *p = String;
    int Char;

    while ((Char = getchar()) != '\n' && Char != EOF) {
        *p++ = Char;
    }
    *p = '\0';

    printf("result: %s\n", String);

    free(String);
}

void my_atoi_func() {
    char *String = malloc(1000);
    char *p;
    int sign = 1, num = 0;

    p = String;

    if (*p == '-') {
        sign = -1;
        p++;
    }

    if (!isdigit(*p)) {
        printf("enter valid input\n");
        free(String);
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

    free(String);
}

void my_itoa_func() {
    int32_t num;
    char *String = malloc(1000);
    char *p = String;
    int32_t sign;

    printf("enter integer: ");
    
    if (scanf("%d", &num) != 1) {
        printf("enter valid input\n");
        return;
    }

    sign = num;

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
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    printf("string: %s\n", String);

    free(String);
}

void my_reverse_func() {
    char String[1000];
    char *start, *end;

    printf("enter string: ");
    scanf(" %[^\n]", String);

    start = String;
    end = String;

    while (*end)
        end++;
    end--;

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    printf("result: %s\n", String);
}

void my_strindex_func() {
    char String1[1000], String2[100];
    char *p, *q, *start;

    printf("enter string: ");
    scanf(" %[^\n]", String1);

    printf("enter match: ");
    scanf(" %[^\n]", String2);

    p = String1;

    while (*p) {
        start = p;
        q = String2;

        while (*p == *q && *q != '\0') {
            p++;
            q++;
        }

        if (*q == '\0') {
            printf("string %s found in %s at position %ld\n",
                   String2, String1, start - String1 + 1);
            return;
        }

        p = start + 1;
    }

    printf("no match found\n");
}

void my_getop_func() {
    int32_t ch1, ch2;
    char op;

    printf("enter expression (e.g., 4 3 +): ");
    scanf("%d %d %c", &ch1, &ch2, &op);

    switch(op) {
        case '+':
            printf("result: %d\n", ch1 + ch2);
            break;
        case '-':
            printf("result: %d\n", ch1 - ch2);
            break;
        case '*':
            printf("result: %d\n", ch1 * ch2);
            break;
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

    getchar();

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
            getchar();
            String1 = read_line_common();
            my_getline();
            free(String1);
            break;

        case 2:
            printf("enter string: ");
            getchar();
            String1 = read_line_common();
            my_atoi_func();
            free(String1);
            break;

        case 3:
            printf("enter integer string: ");
            getchar();
            String1 = read_line_common();
            my_itoa_func();
            free(String1);
            break;

        case 4:
            printf("enter string: ");
            getchar();
            String1 = read_line_common();
            my_reverse_func();
            free(String1);
            break;

        case 5:
            printf("enter string: ");
            getchar();
            String1 = read_line_common();

            printf("enter match: ");
            String2 = read_line_common();

            my_strindex_func();

            free(String1);
            free(String2);
            break;

        case 6:
            my_getop_func();
            break;

        default:
            printf("invalid choice\n");
    }
}
