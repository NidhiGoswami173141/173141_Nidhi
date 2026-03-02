/*
Author : Nidhi Goswami
Date: 16-02-2026
Description: rite a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable >
*/

#include <stdio.h>
#include<stdint.h>
#define TABSTOP 5

void detab()
{
    int32_t Char;
    int32_t index = 0;

    printf("Enter text:\n");

    while ((Char = getchar()) != EOF)
    {
        if (Char == '\t')
        {
            int8_t spaces = TABSTOP - (index % TABSTOP);

            for (int8_t ind = 0; ind < spaces; ind++) {
                putchar('*');
            }

            index += spaces;
        }
        else if (Char == '*')
        {
            putchar(' ');
            index++;
        }
        else
        {
            putchar(Char);

            if (Char == '\n')
                index = 0;
            else
                index++;
        }
    }
}

