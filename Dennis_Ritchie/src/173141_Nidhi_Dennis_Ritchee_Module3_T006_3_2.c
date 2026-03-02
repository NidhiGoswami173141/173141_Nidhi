/*
Author: Nidhi Goswami
Date : 25-02-2026
Description: Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#define Maxline 1000
void escape(char Input[], char Output[]) {

    printf("Enter string(press (Ctrl+D) for exit):\n");
    int32_t InputIndex = 0;
    int32_t Outputindex = 0;
    int32_t Char;

    while ((Char = getchar()) != EOF && InputIndex < Maxline - 1) {
        Input[InputIndex++] = Char;
    }
    Input[InputIndex] = '\0';

    InputIndex = 0;
    while (Input[InputIndex] != '\0') {
        switch (Input[InputIndex]) {
        case '\t':
            Output[Outputindex++] = '\\';
            Output[Outputindex++] = 't';
            break;
        case '\n':
            Output[Outputindex++] = '\\';
            Output[Outputindex++] = 'n';
            break;
        default:
            Output[Outputindex++] = Input[InputIndex];
            break;
        }
        ++InputIndex;
    }

    Output[Outputindex] = '\0';
    printf("\nEscaped Output:\n%s\n", Output);
}


