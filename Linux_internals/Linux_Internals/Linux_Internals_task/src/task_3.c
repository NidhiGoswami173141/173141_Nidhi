/*
Author:Nidhi Goswami
Date: 10-06-2026
Description : Write a program that displays the contents of a directory, specifying the type for each of its files. The name for the directory should be an input parameter.
*/
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include<stdlib.h>
#include"header.h"
void display_dir_content(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;


    if(argc != 2)
    {
        printf("Usage: %s <directory_name>\n",
               argv[0]);
        return 1;
    }


    dir = opendir(argv[1]);


    if(dir == NULL)
    {
        perror("opendir");
        return 1;
    }



    printf("Contents of directory: %s\n\n",
           argv[1]);



    while((entry = readdir(dir)) != NULL)
    {

        printf("%s --> ",entry->d_name);



        switch(entry->d_type)
        {

            case DT_REG:
                printf("Regular File");
                break;


            case DT_DIR:
                printf("Directory");
                break;


            case DT_LNK:
                printf("Symbolic Link");
                break;


            case DT_FIFO:
                printf("FIFO");
                break;


            case DT_SOCK:
                printf("Socket");
                break;


            case DT_CHR:
                printf("Character Device");
                break;


            case DT_BLK:
                printf("Block Device");
                break;


            case DT_UNKNOWN:
                printf("Unknown");
                break;


            default:
                printf("Other");
        }


        printf("\n");
    }



    closedir(dir);

}
