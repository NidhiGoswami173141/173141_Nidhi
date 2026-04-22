/*
Author: Nidhi Goswami
Date : 17-02-2026
Description: Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
*/


#include <stdio.h>
#include<stdint.h>
#define TABSTOP 4

void entab() {
    int32_t Char;
    int32_t space_count = 0;
    int32_t index = 0;

    printf("Enter a string:\n");

    while ((Char = getchar()) != EOF) {
        if (Char == ' ') {
            space_count++;
            index++;

            if (index % TABSTOP == 0) {
                printf("\\t");
                space_count = 0;
            }
        }
        else {
            while (space_count > 0) {
                putchar(' ');
                space_count--;
            }

            putchar(Char);

            if (Char == '\n')
                index = 0;
            else
                index++;
        }
    }
}

