/*
Author: Nidhi Goswami
Date: 18/06/2026
Description: Extend above program to find the size of any subdirectory recursively.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include"header.h"
long long total = 0;


void calculate_size_fun(char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    char fullpath[1024];


    dir = opendir(path);

    if (dir == NULL)
    {
        perror("opendir");
        return;
    }


    while ((entry = readdir(dir)) != NULL)
    {

        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }


        snprintf(fullpath,sizeof(fullpath),"%s/%s",path,entry->d_name);


        if (lstat(fullpath, &file_stat) == -1)
        {
            perror("lstat");
            continue;
        }

        if (S_ISLNK(file_stat.st_mode))
        {
            continue;
        }


        if (S_ISDIR(file_stat.st_mode))
        {
            calculate_size(fullpath);
        }
        else
        {
            total += file_stat.st_size;
        }
    }


    closedir(dir);
}


void cal_size_of_all_file_folder(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Usage: %s <directory>\n", argv[3]);
        return 1;
    }


    calculate_size_fun(argv[3]);


    printf("Size of %s = %lld bytes\n",argv[3],total);

}
