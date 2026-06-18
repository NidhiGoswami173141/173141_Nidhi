/*
Author: Nidhi Goswami
Date: 18/06/2026
Description:Write program to sums of all return the number of bytes taken up by all files reachable from the  
       current directory (excluding soft links) using opendir/readdir/closedir, stat.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include"header.h"

long long total_size = 0;


void calculate_size(char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    char fullpath[1024];


    dir = opendir(path);

    if(dir == NULL)
    {
        perror("opendir");
        return;
    }


    while((entry = readdir(dir)) != NULL)
    {

        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
        {
            continue;
        }

        snprintf(fullpath,sizeof(fullpath),"%s/%s",path,entry->d_name);


        if(lstat(fullpath, &file_stat) == -1)
        {
            perror("lstat");
            continue;
        }


        if(S_ISLNK(file_stat.st_mode))
        {
            continue;
        }

        if(S_ISDIR(file_stat.st_mode))
        {
            calculate_size(fullpath);
        }

        else
        {
            total_size += file_stat.st_size;
        }

    }


    closedir(dir);
}



void cal_size_of_all()
{

    calculate_size(".");


    printf("Total bytes = %lld\n", total_size);
}
