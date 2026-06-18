/*
Author: Nidhi Goswami
Date: 10-06-2026
Description: Write a program that copies the contents of an existing file into another file. The names of the two file should be read as an input from the command line. You may presume that any of the commands read or write may cause errors..
*/

/*
int main(int argc, char *argv[])
{
    int src_fd, dest_fd;
    char buffer[1024];
    int bytes_read;

    if (argc != 3)
    {
        printf("Usage: %s source_file destination_file\n", argv[0]);
        return 1;
    }

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0)
    {
        perror("open source");
        return 1;
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0)
    {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(dest_fd, buffer, bytes_read) < 0)
        {
            perror("write");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read < 0)
    {
        perror("read");
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully.\n");

    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include"header.h"

void copy_file(int argc, char *argv[])
{
    int src_fd;
    int dest_fd;

    struct stat file_info;

    off_t offset = 0;
    ssize_t sent;


    /*check arguments*/
    if (argc != 3)
    {
        printf("usage: %s source destination\n", argv[0]);
        return 1;
    }



    /*open source file*/
    src_fd = open(argv[1], O_RDONLY);

    if (src_fd < 0)
    {
        perror("source open");
        return 1;
    }



    /*get source file size*/
    if (fstat(src_fd, &file_info) < 0)
    {
        perror("fstat");
        close(src_fd);
        return 1;
    }



    /*create destination file*/
    dest_fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);


    if (dest_fd < 0)
    {
        perror("destination open");
        close(src_fd);
        return 1;
    }



    /*copy file*/
    while (offset < file_info.st_size)
    {

        sent = sendfile(dest_fd,src_fd,&offset,file_info.st_size - offset);


        if (sent < 0)
        {
            perror("sendfile");

            close(src_fd);
            close(dest_fd);

            unlink(argv[2]);

            return 1;
        }
    }



    close(src_fd);
    close(dest_fd);


    printf("file copied successfully\n");
}
