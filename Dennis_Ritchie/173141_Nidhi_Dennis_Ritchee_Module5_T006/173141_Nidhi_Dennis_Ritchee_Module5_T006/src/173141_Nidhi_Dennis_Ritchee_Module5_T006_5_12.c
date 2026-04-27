/*
Author : Nidhi Goswami
Date : 6-4-2026
Description : entab program with custom tab stops
              -m : starting column
              +n : interval between tab stops
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include"module.h"
int32_t is_tabstop(int32_t col, int32_t m, int32_t n) {
    if (col < m)
        return 0;
    return ((col - m) % n == 0);
}

void m_n(int32_t argc, char *argv[]) {
    int32_t m = 1;
    int32_t n = 8;

    for (int32_t i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            m = atoi(&argv[i][1]);
        }
        else if (argv[i][0] == '+') {
            n = atoi(&argv[i][1]);
        }
    }

    int32_t c;
    int32_t col = 1;
    int32_t space_count = 0;


    while ((c = getchar()) != EOF) {

        if (c == ' ') {
            space_count++;
            col++;
        }
        else {
            while (space_count > 0) {
                if (is_tabstop(col - space_count, m, n) &&
                    space_count >= 1) {

                    putchar('\t');
                    space_count = 0;
                }
                else {
                    putchar(' ');
                    space_count--;
                }
            }

            putchar(c);

            if (c == '\n') {
                col = 1;
            } else {
                col++;
            }
        }
    }

    return 0;
}
