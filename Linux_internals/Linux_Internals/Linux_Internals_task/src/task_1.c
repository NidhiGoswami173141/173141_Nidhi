/*
Author: Nidhi Goswami
Date: 10-06-2026
Description : Write a program that creates a file with a 4K bytes free space. Such files are called files with holes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include"header.h"
void sparse_file(){
    int32_t fd;

/*    fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    //Write first byte
    if (write(fd, "A", 1) != 1) {
        perror("write");
        close(fd);
        exit(1);
    }

    //Create a 4 KB hole
    if (lseek(fd, 4096, SEEK_CUR) == -1) {
        perror("lseek");
        close(fd);
        exit(1);
    }

    //Write another byte 
    if (write(fd, "B", 1) != 1) {
        perror("write");
        close(fd);
        exit(1);
    }

    close(fd);

    printf("file with a 4 KB hole created successfully.\n"); */
    /*create and open file*/
    fd = open("file.txt",O_CREAT | O_WRONLY | O_TRUNC,0644);

    if (fd < 0)
    {
        perror("open");
        exit(1);
    }

    /*make file size 4KB (4096 bytes)*/
    /* int ftruncate(int fd, off_t length); */
    if (ftruncate(fd, 4096) < 0)
    {
        perror("ftruncate");
        close(fd);
        exit(1);
    }

    close(fd);

    printf("4KB hole file created successfully\n");

}

