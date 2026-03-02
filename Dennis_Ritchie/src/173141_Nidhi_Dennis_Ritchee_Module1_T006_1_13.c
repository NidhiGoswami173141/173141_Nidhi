/*
Author: Nidhi Goswami
Date : 11-02-2026
Description: Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
*/

#include <stdio.h>
#include <stdint.h>
#include "module.h"

void histogram_lenght_of_words(){

	int8_t Char;
	int8_t Count = 0;

	printf("Enter the string(press (CTRL + D) for exit):\n");
	while((Char = getchar()) != EOF){

		if(Char == ' ' || Char == '\t' || Char == '\n'){
			Count += Char;
		}
		else{
			if(Count >= 9){
				putchar('\n');
				Count = 0;
			}
			putchar('*');
		}
	}
	putchar('\n');
}
