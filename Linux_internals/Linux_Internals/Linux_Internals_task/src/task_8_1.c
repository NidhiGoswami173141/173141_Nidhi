#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include"header.h"
#define MAX_FILES 1000
#define NAME_LEN 256

struct file_info
{
    char name[NAME_LEN];
    long size;
};


/*int compare(const void *a, const void *b)
{
    struct file_info *f1 = (struct file_info *)a;
    struct file_info *f2 = (struct file_info *)b;

    return strcmp(f1->name, f2->name);
}*/


void ls_command_using_stat()
{
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    struct file_info files[MAX_FILES];

    int count = 0;

    dir = opendir(".");

    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {

       /* if (strcmp(entry->d_name, ".") == 0 ||strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }*/

        if (stat(entry->d_name, &file_stat) == -1)
        {
            perror("stat");
            continue;
        }

        strcpy(files[count].name, entry->d_name);

        files[count].size = file_stat.st_size;


        count++;
    }


    closedir(dir);

   /* qsort(files,count,sizeof(struct file_info),compare);*/

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

    for (int i = 0; i < count; i++)
    {
        printf("%-20s %ld bytes\n",files[i].name,files[i].size);
    }

}
