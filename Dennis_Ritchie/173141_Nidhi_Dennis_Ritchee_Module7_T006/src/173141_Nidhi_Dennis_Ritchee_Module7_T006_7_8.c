/*
Author: Nidhi Goswami
Date: 24-04-2026
Description:Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file. 
*/

#include <stdio.h>
#include"module.h"
#define PAGELEN 10
#include<stdint.h>
void printFiles(int32_t argc, char *argv[])
{
    FILE *fp;
    int32_t Char;
//    int32_t line = 0, page = 1, totalLine = 0;

    if (argc < 2)
    {
        printf("give filename\n");
        return 0;
    }

    for(int32_t index=1;index < argc ; index++){
          int32_t line = 0, page = 1, totalLine = 0;
           fp = fopen(argv[index], "r");

    if (fp == NULL)
    {
        printf("file not found\n");
        return 0;
    }

    printf("title: %s\n\n", argv[index]);
    getchar();
printf("\n--------------------------------------------Page %d -------------------------------------------------------\n", page);

    printf("%d: ", totalLine + 1);
    while ((Char = fgetc(fp)) != EOF)
    {
        putchar(Char);

        if (Char == '\n')
        {
            line++;
            totalLine++;
            if (line == PAGELEN)
            {
                printf("\n--------------------------------------------Page %d -------------------------------------------------------\n", page++);
                line = 0;

                printf("press Enter........(for next prage)");
                getchar();
                printf("\n--------------------------------------------Page %d -------------------------------------------------------\n", page);
            }
            printf("%d: ", totalLine + 1);
        }
    }

    printf("\n--------------------------------------------Page %d -------------------------------------------------------\n", page);

    fclose(fp);
    }
    printf("\nend of file\n");


}
