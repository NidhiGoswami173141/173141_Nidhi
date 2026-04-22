/*
Author: Nidhi Goswami
Date: 15-02-2026
Description: Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time.
*/

#include <stdio.h>
#include<stdint.h>
#define MAXLINE 1000

void reverse(char str[])
{
    int8_t index = 0, last = 0;
    char temp;
    printf("enter string (press (CTRL + D)for exit):");
    while (str[last] != '\0')
        last++;

    last--;

    while (index < last) {
        temp = str[index];
        str[index] = str[last];
        str[last] = temp;
        index++;
        last--;
    }
}

int32_t getline_custom(char line[], int max)
{
    int8_t index = 0, Char;

    while (index < max - 1 && (Char = getchar()) != EOF && Char != '\n') {
        line[index++] = Char;
    }

    if (Char == '\n') {
        line[index++] = Char;
    }

    line[index] = '\0';
    return index;
}

void reverse_string_s()
{
    char line[MAXLINE];

    printf("Enter text:\n");

    while (getline_custom(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }


}

