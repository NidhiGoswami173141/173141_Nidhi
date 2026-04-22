/*
Author: Nidhi Goswami
Date : 25-02-2026
Description: Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.
*/

#include<stdio.h>
#include<stdint.h>
#include"module.h"
#define Maxline 1000

/*
Author: Nidhi Goswami
Date : 25-2-2026
Description : function for covert character like tab and newline into visible character like \n \t
*/

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


void unescape(char s[], char t[]) {
    int index = 0, sec_index = 0;

    while (s[index] != '\0') {
        if (s[index] == '\\') {
            index++;
            switch (s[index]) {
                case 'n':
                    t[sec_index++] = '\n';
                    break;

                case 't':
                    t[sec_index++] = '\t';
                    break;

                default:
                    t[sec_index++] = s[index];
            }
        } else {
            t[sec_index++] = s[index];
        }
        index++;
    }
    t[sec_index] = '\0';
}
