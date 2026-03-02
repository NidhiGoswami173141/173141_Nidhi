/*
Author: Nidhi Goswami
Date: 15-02-2026
Description:Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.
*/

#include <stdio.h>
#include<stdint.h>
#define MAXLINE 1000

void remove_trailing_blanks()
{
    char line[MAXLINE];
    int32_t Char, index = 0;
    int32_t last;
    int32_t Input = 0;

    printf("Enter string  (press (CTRL + D)for exit):\n");

    getchar();
    while ((Char = getchar()) != EOF)
    {
        if (Char == '\n')
        {
            Input = 1;
            line[index] = '\0';

            printf("Typed : ");
            for (int ind = 0; ind < index; ind++) {
                if (line[ind] == ' ')
                    printf("_");
                else if (line[ind] == '\t')
                    printf("\\t");
                else
                    putchar(line[ind]);
            }
            printf("\n");

            last = index - 1;
            while (last >= 0 && (line[last] == ' ' || line[last] == '\t')) {
                last--;
            }

            line[last + 1] = '\0';

            if (last < 0) {
                printf("Output  : Empty string\n\n");
            } else {
                printf("Output  : %s\n\n", line);
            }

            index = 0;
        }
        else {
            if (index < MAXLINE - 1)
                line[index++] = Char;
        }
    }
}

