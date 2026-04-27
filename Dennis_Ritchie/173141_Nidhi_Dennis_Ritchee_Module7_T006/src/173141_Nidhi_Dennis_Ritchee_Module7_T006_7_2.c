/*
Author: Nidhi Goswami
Date : 21-04-2026
Description : Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom and break long text line
*/


#include <stdio.h>
#include <ctype.h>
#include"module.h"
#include<stdint.h>
#define MAXTEXT 10000
#define MAXCOL 80
#define HEXLEN 4

/*
Author: Nidhi Goswami
Date : 21-04-2026
Description : function for checking if printing more character will exceed line limit 
*/


int32_t inc(int32_t position, int32_t space_required) {
    /*this if  condition will check if maxcol is greater than posion + space required */
    if (position + space_required >= MAXCOL) {
        putchar('\n'); /*if greater than maxcol then move to the next line */
        return space_required; /* this will start new line with space requireed */
    }
    return position + space_required;
}

/*
Author: Nidhi Goswami
Date : 21-04-2026
Description : this is the main function for covert the tab and new line into hexadcimal and octal
*/

void print_non_graphic_character_in_hex_or_octal() {

    char text[MAXTEXT];
    int32_t index = 0, Char;

    while ((Char = getchar()) != '\n' && Char != EOF);

    printf("enter text (Ctrl+D for exit):\n");

    /*this while loop goes until  end of file or if buffer is full*/
    while ((Char = getchar()) != EOF && index < MAXTEXT - 1) {
        text[index++] = Char;
    }
    text[index] = '\0';

    int32_t position = 0;

    printf("\noutput:\n");

    for (int32_t sec_index = 0; text[sec_index] != '\0'; sec_index++) {

        unsigned char ch = text[sec_index];

        if (isprint(ch)) {
            position = inc(position, 1);
            putchar(ch);
        }
        else {
            position = inc(position, HEXLEN + 7);
            printf("[0x%02x|0%03o]", ch, ch);

            if (ch == '\n')
                position = 0;
        }
    }

    printf("\n");
}

