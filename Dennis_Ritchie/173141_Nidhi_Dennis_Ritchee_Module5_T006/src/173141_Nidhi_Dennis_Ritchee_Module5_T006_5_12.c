/*
Author : Nidhi Goswami
Description : entab program with custom tab stops
              -m : starting column
              +n : interval between tab stops
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include"module.h"
int is_tabstop(int col, int m, int n) {
    if (col < m)
        return 0;
    return ((col - m) % n == 0);
}

int m(int argc, char *argv[]) {
    int m = 1;
    int n = 8;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            m = atoi(&argv[i][1]);
        }
        else if (argv[i][0] == '+') {
            n = atoi(&argv[i][1]);
        }
    }

    int c;
    int col = 1;
    int space_count = 0;


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
