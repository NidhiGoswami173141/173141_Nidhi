/*
Author: Nidhi Goswami
Date: 11-02-2026
Description:  function to copy input to output, replacing each tab by \t, each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.
*/

#include <stdio.h>
#include <stdint.h>
#include "module.h"

void replace_tab_backspace_backslash(){

	int8_t Char;

	printf("Enter string(press (CTRL +D) for exit):\n");
	while((Char = getchar()) != EOF){
		if(Char == '\t'){
			putchar('\\');
			putchar('t');
		}

		else if(Char == '\b'){
			putchar('\\');
			putchar('b');
		}
		else if(Char == '\\'){
			putchar('\\');
			putchar('\\');
		}
		else{
			putchar(Char);
		}
	}

}

