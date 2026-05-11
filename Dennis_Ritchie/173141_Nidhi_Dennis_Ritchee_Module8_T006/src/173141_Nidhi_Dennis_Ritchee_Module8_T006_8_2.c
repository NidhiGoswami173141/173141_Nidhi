/*
Author: Nidhi Goswami
Date: 27-04-2026
Description : Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution speed.
*/


#include<stdio.h>
#include"module.h"
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <errno.h>
#include <string.h>

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20
#define PERMS 0666


typedef struct _iobuf {
 int32_t cnt; /* characters left */
 char *ptr; /* next character position */
 char *base; /* location of buffer */
 int32_t fd; /* file descriptor */

 int32_t is_read;
 int32_t is_write;
 int32_t is_unbuf;
 int32_t is_eof;
 int32_t is_err;
 } MYFILE;


MYFILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, 0, 1, 0, 0, 0, 0 }, /*stdin*/
    { 0, NULL, NULL, 1, 0, 1, 0, 0, 0 }, /*stdout*/
    { 0, NULL, NULL, 2, 0, 1, 1, 0, 0 }  /*stderr (unbuffered)*/
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

MYFILE *myfopen(char *name, char *mode);
int32_t _fillbuf(MYFILE *fp);


#define mygetc(p) (--(p)->cnt >= 0 \
 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

MYFILE *myfopen(char *name, char *mode)
{
    int32_t fd;
    MYFILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;


    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if (!fp->is_read && !fp->is_write)
            break;
    }

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1){
         perror("open failed");
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->ptr = NULL;

    fp->is_read  = (*mode == 'r');
    fp->is_write = (*mode != 'r');
    fp->is_unbuf = 0;
    fp->is_eof   = 0;
    fp->is_err   = 0;

    return fp;
}

int32_t _fillbuf(MYFILE *fp)
{
    int32_t bufsize;

    if (!fp->is_read || fp->is_eof || fp->is_err)
        return EOF;

    bufsize = (fp->is_unbuf) ? 1 : BUFSIZ;

    if (fp->base == NULL) {
        fp->base = (char *) malloc(bufsize);
        if (fp->base == NULL) {
            fp->is_err = 1;
            return EOF;
        }
    }

    fp->ptr = fp->base;

    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->is_eof = 1;
        else
            fp->is_err = 1;

        fp->cnt = 0;
        return EOF;
    }

    fp->cnt--;
    return (unsigned char) *fp->ptr++;
}

void field_comp(int32_t argc, char *argv[])
{
    MYFILE *fp;
    int32_t c;

    if (argc == 1) {
        while ((c = mygetc(stdin)) != EOF)
            putchar(c);
    }
    else {
        for (int32_t index = 1; index < argc; index++) {

            fp = myfopen(argv[index], "r");

            if (fp == NULL) {
                printf("error: cannot open %s\n", argv[index]);
                continue;
            }

            while ((c = mygetc(fp)) != EOF)
                putchar(c);
        }
    }

}
