/*
Author: Nidhi Goswami
Date : 5-4-2026
Description : Modify the program entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.
*/

#include <stdio.h>
#include <stdlib.h>
#include"module.h"
void entab_fun(int32_t n);
void detab_fun(int32_t n);

void  detab_entab(int32_t argc, char *argv[]) {

    int32_t n;

    if (argc < 2 || argc > 3) {
        printf("Usage: ./program [en|de] [n]\n");
        return 1;
    }

    if (argc == 2) {
        n = 8;
    } else {
        n = atoi(argv[2]);
        if (n <= 0) {
            printf("Invalid tab size\n");
            return 1;
        }
    }

    if (argv[1][0] == 'e' && argv[1][1] == 'n') {
        entab_fun(n);
    }
    else if (argv[1][0] == 'd' && argv[1][1] == 'e') {
        detab_fun(n);
    }
    else {
        printf("Invalid mode. Use en or de\n");
    }

    return 0;
}

void entab_fun(int32_t n) {

    int32_t c;
    int32_t space_count = 0;
    int32_t col = 0;

    while ((c = getchar()) != EOF) {

        if (c == ' ') {
            space_count++;
        }
        else {

            while (space_count > 0) {

                int32_t tab_space = n - (col % n);

                if (space_count >= tab_space) {
                    putchar('\t');
                    space_count -= tab_space;
                    col += tab_space;
                }
                else {
                    putchar('*');
                    space_count--;
                    col++;
                }
            }

            putchar(c);
            col++;

            if (c == '\n') {
                col = 0;
                space_count = 0;
            }
        }
    }
}

void detab_fun(int n) {

    int32_t c;
    int32_t col = 0;

    while ((c = getchar()) != EOF) {

        if (c == '\t') {

            int32_t spaces = n - (col % n);

            for (int32_t i = 0; i < spaces; i++) {
                putchar('*');
                col++;
            }
        }
        else {
            putchar(c);
            col++;

            if (c == '\n')
                col = 0;
        }
    }
}
