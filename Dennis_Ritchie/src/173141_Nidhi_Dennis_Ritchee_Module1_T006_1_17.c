/*
Author : Nidhi Goswami
Date : 14-02-2026
Descreption : Write a program to print all input lines that are longer than 80 characters.
*/


#include <stdio.h>
#include <stdint.h>
#define MAXLINE 1000
#define LIMIT   8

void print_long_lines()
{
    int32_t Char;
    char line[MAXLINE];
    char stored[50][MAXLINE];
    int32_t len = 0;
    int32_t count = 0;

    printf("Enter string (Press (CTRL+D) for exit):\n");

    while ((Char = getchar()) != EOF)
    {
        if (Char != '\n')
        {
            if (len < MAXLINE - 1)
                line[len++] = (char)Char;
        }

        if (Char == '\n')
        {
            line[len] = '\0';

            if (len > LIMIT)
            {
                for (int32_t index = 0; index <= len; index++)
                    stored[count][index] = line[index];
                count++;
            }
            len = 0;
        }
    }

    if (count > 0)
    {
        printf("\nLines longer than %d characters:\n", LIMIT);
        for (int32_t index = 0; index < count; index++)
            printf("%s\n", stored[index]);
    }

}
