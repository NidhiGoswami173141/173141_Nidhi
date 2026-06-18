/*
Author: Nidhi Goswami
Date: 17/06/2026
Description: Implement  "ls -F".  That is, it prints directories with a "/" at the end, symbolic
      (soft) links with a "@", and executable files with a “*” using the "st_mode" field of the "struct 
      buf"
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include"header.h"
#define MAX_FILES 1000
#define NAME_LEN 256

struct file_info
{
    char name[NAME_LEN];
    mode_t mode;
};


/*int compare_fun(const void *a, const void *b)
{
    struct file_info *f1 = (struct file_info *)a;
    struct file_info *f2 = (struct file_info *)b;

    return strcmp(f1->name, f2->name);
}
*/

void ls_command_f()
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    struct file_info files[MAX_FILES];

    int count = 0;

    dir = opendir(".");

    if(dir == NULL)
    {
        perror("opendir");
        return 1;
    }


    while((entry = readdir(dir)) != NULL)
    {

        /*if(strcmp(entry->d_name,".") == 0 ||strcmp(entry->d_name,"..") == 0)
        {
            continue;
        }*/
        if(lstat(entry->d_name, &file_stat) == -1)
        {
            perror("lstat");
            continue;
        }


        strcpy(files[count].name, entry->d_name);

        files[count].mode = file_stat.st_mode;


        count++;
    }


    closedir(dir);

  /*  qsort(files,count,sizeof(struct file_info),compare_fun);*/

    for(int i=0;i<count;i++)
    {
      for(int j=i+1;j<count;j++)
      {
        if(strcmp(files[i].name, files[j].name) > 0)
        {
            struct file_info temp;

            temp = files[i];
            files[i] = files[j];
            files[j] = temp;
        }
     }
   }


    for(int i = 0; i < count; i++)
    {

        printf("%s", files[i].name);

        if(S_ISDIR(files[i].mode))
        {
            printf("/");
        }

        else if(S_ISLNK(files[i].mode))
        {
            printf("@");
        }
        else if(files[i].mode & S_IXUSR)
        {
            printf("*");
        }


        printf("\n");
    }
}
