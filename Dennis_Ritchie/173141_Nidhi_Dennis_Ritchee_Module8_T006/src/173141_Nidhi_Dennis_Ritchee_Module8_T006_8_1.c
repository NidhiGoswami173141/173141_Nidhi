/*
Author : Nidhi Goswami
Date : 25-04-2025
Description : Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions. 
*/


/*
#include<stdio.h>
int main( int argc , char *argv[]){

       FILE *fp;
       void filecopy(FILE * , FILE *);
       if(argc == 1){
            filecopy(stdin,stdout);
       }
       else{
           while(--argc > 0){
              if((fp = fopen(*++argv, "r"))==NULL){
                 printf("cat: can't open %s\n",*argv);
                 return 1;
              }
              else{
                 filecopy(fp,stdout);
                 fclose(fp);
              }
           }
       }
     return 0;
}

void filecopy(FILE *ifp , FILE *ofp){

     int c;
     while((c = getc(ifp)) != EOF){
         puc(c , ofp);
     }

}
*/

#include <fcntl.h>    /*for function open() and file flags like O_RDONLY*/
#include <unistd.h>   /*for function  read(), write(), close()*/
#include <stdio.h>
#include"module.h"
#include<stdint.h>
#define BUFSIZE 1024
/*
Author: Nidhi Goswami
Date: 25-04-2025
Description : this function is for understading low level system architechture how it is work 
*/
void cat(int32_t argc, char *argv[])
{
    int32_t fd;      /* this is file descriptor which is small integer which is give to any process 3 block 1 is stdin , 2 is stdout , 3 is stderr*/
    int32_t num_of_bytes;
    char buf[BUFSIZE];

    /*
        file Descriptors:
        0 - standard input
        1 - standard Output
        2 - standard Error
    */

    /* this condition is for when no file provided then it will take standard input from user */
    if (argc == 1) {
        while ((num_of_bytes = read(0, buf, BUFSIZE)) > 0) {
            /* here read() function will  returns number of bytes read */
            /* write() writes exactly the number of bytes reads bytes for output*/
            write(1, buf, num_of_bytes);
        }
    }
    else {
        /*  this for loop is for multiple file input we can give */
        for (int32_t index = 1; index < argc; index++) {

            /*
                open() - opens file
                O_RDONLY - open in read-only mode
                returns:
                    >=0 - valid file descriptor
                    -1 - error (file not found, permission denied)
            */
            fd = open(argv[index], O_RDONLY);

            if (fd == -1) {
                printf("error: cannot open file %s\n", argv[index]);
                return 1;
            }

            /*
                read() - reads data from file descriptor into buffer
                parameters:
                    fd  - file descriptor
                    buf - where to store data
                    BUFSIZE - max bytes to read

                returns:
                    >0 - number of bytes read
                     0 - end of file (EOF)
                    -1 - error
            */
            while ((num_of_bytes = read(fd, buf, BUFSIZE)) > 0) {

                /*
                    write() - writes data to output

                    parameters:
                        1 - standard output
                        buf - data to write
                        n - number of bytes to write

                    IMPORTANT:
                    always write number of bytes reads not BUFSIZE,
                    otherwise garbage may be printed.
                */
                write(1, buf, num_of_bytes);
            }

            /*
                close() - closes the file
                always close files to free system resources
            */
            close(fd);
        }
    }

}


