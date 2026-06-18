/*
Author: Nidhi Goswami
Description: Implement cat command using system calls
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include"header.h"
#define BUFFER_SIZE 100

void cat_using_systemcall(int argc, char *argv[])
{
    int fd;
    int n;
    char buffer[BUFFER_SIZE];

    if(argc == 3)
    {
        fd = 0;
    }
    else
    {
        fd = open(argv[3], O_RDONLY);

        if(fd < 0)
        {
            perror("open");
            exit(1);
        }
    }


    while((n = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if(write(1, buffer, n) != n)
        {
            perror("write");
            exit(1);
        }
    }


    if(argc > 1)
        close(fd);
}
