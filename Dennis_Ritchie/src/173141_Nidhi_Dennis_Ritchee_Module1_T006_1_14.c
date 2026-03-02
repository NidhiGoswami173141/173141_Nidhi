/*
*Description: Write a program to print a histogram of the frequencies of different characters in its input.
*Author: Nidhi Goswami
*Date: 12/2/2026
*/

#include<stdio.h>
#define SIZE 97
#include<stdint.h>
void histogram_frequencies_of_characters(){
	char Char;
	char Arr[SIZE] = {0};
	int Tab, Space, Newline;
	Tab = Space = Newline = 0;

	printf("Enter the string (press (CTRL + D) for exit):\n");
	while((Char = getchar()) != EOF)
		if(Char == "\t")
			Tab++;
		else if(Char == " ")
			Space++;
		else if(Char == "\n")
			Newline++;
		else
			Arr[Char - 33]++;
	for(int Index = 0; Index < SIZE; Index++)
	{
		if(Tab > 0)
		{
			printf("\n\\t : ", 9);
			while(Tab != 0)
			{
				putchar('*');
				Tab--;
			}
		}

		else if(Space > 0)
		{
			printf("\n\s : ", 32);
			while(Space != 0)
			{
				putchar('*');
				Space--;
			}
		}
		else if(Newline > 0)
		{
			printf("\n\\n : ", 10);
			while(Newline != 0)
			{
				putchar('*');
				Newline--;
			}
		}
		if(Arr[Index] > 0)
		{
			printf("\n%c : ", Index+33);
			while(Arr[Index] != 0)
			{
				putchar('*');
				Arr[Index]--;
			}
		}
	}
	putchar('\n');
}
