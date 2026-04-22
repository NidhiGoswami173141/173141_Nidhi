/*
Author : Nidhi Goswami
Date : 9-3-2026
Description : Modify getch() and ungetch() so that EOF can also be pushed back.
*/

#include<stdio.h>
#include"module.h"

#define BUFSIZE 100

int32_t buffer[BUFSIZE];
int32_t bufferp = 0;

int f_getch(void)
{
    if(bufferp > 0)
        return buffer[--bufferp];
    else
        return getchar();
}


void f_ungetch(int32_t c)
{
    if(bufferp >= BUFSIZE)
        printf("error: buffer full\n");
    else
        buffer[bufferp++] = c;
}

/*
Author: Nidhi Goswami
Date: 2-3-2026
Description: function for push EOF 
*/

void eof_handling()
{
    char c;

    printf("Enter input:\n");

    while((c = getch()) != EOF)
    {
        if(c == '\n')
            continue;

        printf("%c\n", c);

        while((c = getch()) != '\n' && c != EOF)
            ;
    }

    printf("EOF encountered.\n");
}
