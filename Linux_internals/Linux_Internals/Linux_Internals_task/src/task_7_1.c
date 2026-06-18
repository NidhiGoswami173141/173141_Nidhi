/*
Author: Nidhi Goswami
Description: Implement cat using stdio library
*/

#include <stdio.h>
#include <stdlib.h>
#include"header.h"
#define BUFFER_SIZE 100


void cat_using_stdio(int argc, char *argv[])
{
    FILE *fp;
    char buffer[BUFFER_SIZE];

    size_t n;


    if(argc == 3)
    {
        fp = stdin;
    }
    else
    {
        fp = fopen(argv[3],"r");

        if(fp == NULL)
        {
            perror("fopen");
            exit(1);
        }
    }


    while((n = fread(buffer,1,BUFFER_SIZE,fp)) > 0)
    {
        fwrite(buffer,1,n,stdout);
    }


    if(argc > 1)
        fclose(fp);

}
