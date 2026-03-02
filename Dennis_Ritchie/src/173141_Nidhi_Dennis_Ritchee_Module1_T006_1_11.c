/*
Author: Nidhi Goswami
Date: 11-02-2026
Description: How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any?
*/
#include <stdio.h>
#include <stdint.h>
#include "module.h"
#define IN 1
#define OUT 0
void word_count() {
	 int8_t Char;
	 int8_t NewLine;
	 int8_t NewWord;
	 int8_t NewCharacter;
	 int8_t State;
	 State = OUT;
	 NewLine = NewWord = NewCharacter = 0;

	 printf("Enter string(press (CTRL + D) for exit):\n");
	 while ((Char = getchar()) != EOF) {
		 ++NewCharacter;
		 if (Char == '\n')
		 	++NewLine;

		 if (Char == ' ' || Char == '\n' || Char == '\t')
		 	State = OUT;
		 else if (State == OUT) {
			 State = IN;
			 ++NewWord;
		 }
	 }
	 printf("nl = %d\nnw = %d\nnc = %d\n", NewLine-1, NewWord, NewCharacter-1);
}


