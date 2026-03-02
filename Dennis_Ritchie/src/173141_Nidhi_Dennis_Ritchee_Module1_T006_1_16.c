/*
Author : Nidhi Goswami
Date : 14-02-2026
Description : Revise the main routine of the longest-line program so it will correctly print the length of arbitrary long input lines, and as much as possible of the text.
*/

#include <stdio.h>

#define MAXLINE 1000

void longest_line()
{
    char line[MAXLINE];
    char longest[MAXLINE];
    int Char, len = 0, max = 0, index = 0;

    printf("enter a string (press (CTRL + D) for exit):\n");
    while ((Char = getchar()) != EOF) {
        if (Char != '\n') {
            if (index < MAXLINE - 1) {
                line[index++] = Char;
            }
            len++;
        } else {
            line[index] = '\0';
            if (len > max) {
                max = len;
                for (index = 0; (longest[index] = line[index]) != '\0'; index++);
            }

            len = 0;
            index = 0;
        }
    }
    if (max > 0) {
    printf("Longest length: %d\n", max);
    printf("Text: %s\n", longest);
    }
}

