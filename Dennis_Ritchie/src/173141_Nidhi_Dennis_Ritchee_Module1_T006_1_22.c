/*
*AIM: Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column. 
*Author: Nidhi Goswami 
*Created: 15/2/2026
*/

/* Required Libraries */
#include <stdio.h>
#include<stdint.h>
#include"module.h"

#define LEN_OF_LINE 10
#define IN 1
#define OUT 0

void fold_line()
{
	char Choice;
	do
	{
		int32_t Char;
		int32_t interval_counter = 0;

		int8_t state = OUT; 

		printf("\nEnter a string to fold it after interval of 10 characters: \n");
		getchar();
		while((Char = getchar()) != '\n' && Char!= EOF)
		{
			if (Char != '\n')
				interval_counter++;

			if (Char != ' ' && Char != '\t' && Char != '\n' && state == OUT)
				state = IN;


			if ((Char == ' ' || Char == '\t' || Char == '\n') && (state == IN))
				state = OUT;

			if(state == OUT && interval_counter >= LEN_OF_LINE)
			{
				putchar('\n');
				interval_counter = 0;
			}
			else
				putchar(Char);
		}

        printf("\nDo you want to enter 1 more string? (y / n): ");

        scanf(" %c", &Choice);

        if(Choice != 'y' && Choice != 'Y' && Choice != 'n' && Choice != 'N')
        {
            printf("invalid input");
            return 1;
        }
        while ((Char = getchar()) != '\n' && Char != EOF);
    } while (Choice == 'y' || Choice == 'Y');

}


