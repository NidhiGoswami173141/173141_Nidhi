/*
Author: Nidhi Goswami
Date: 11-02-2026
Description: Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.
*/


#include <stdio.h>
#include<stdint.h>
void removeblank() {
    uint8_t Char;
    uint8_t Space = 0;

    printf("Enter text(press (CTRL + D) for exit):\n");

    while ((Char = getchar()) != EOF) {
        if (Char == ' ' || Char == '\t') {
            if (Space == 0) {
                putchar('_');
                Space = 1;
            }
        } else {
            putchar(Char);
            Space = 0;
        }
    }
}

