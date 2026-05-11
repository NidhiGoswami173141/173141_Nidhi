/*
Author : Nidhi Goswami
Date : 27-04-2026
Description : Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
*/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "module.h"
#include <stdint.h>

#define BUFSIZE 1024

typedef struct _iobuf {
    int32_t cnt;
    char *ptr;
    char *base;
    int32_t flag;
    int32_t fd;
} MYFILE;

#define _WRITE 02
#define _UNBUF 04
#define _ERR   020

/* flush buffer */
int32_t _flushbuf(int32_t c, MYFILE *fp)
{
    int32_t bufsize;

    if (fp == NULL || (fp->flag & _WRITE) == 0)
        return -1;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZE;

    /* allocate buffer first time */
    if (fp->base == NULL) {
        fp->base = (char *)malloc(bufsize);

        if (fp->base == NULL) {
            fp->flag |= _UNBUF;
        } else {
            fp->ptr = fp->base;
            fp->cnt = bufsize - 1;

            *fp->ptr++ = c;
            return c;
        }
    }

    /* unbuffered mode */
    if (fp->flag & _UNBUF) {
        if (write(fp->fd, &c, 1) != 1) {
            fp->flag |= _ERR;
            return -1;
        }
        return c;
    }

    /* safety check */
    if (fp->ptr == NULL || fp->base == NULL)
        return -1;

    int32_t n = fp->ptr - fp->base;

    /* write existing buffer */
    if (n > 0) {
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= _ERR;
            return -1;
        }
    }

    /* reset buffer */
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;

    *fp->ptr++ = c;

    return c;
}

/* fflush */
int32_t my_fflush(MYFILE *fp)
{
    if (fp == NULL)
        return -1;

    if (fp->base == NULL || fp->ptr == NULL)
        return 0;

    int32_t n = fp->ptr - fp->base;

    if (n > 0) {
        if (write(fp->fd, fp->base, n) != n) {
            fp->flag |= _ERR;
            return -1;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = BUFSIZE - 1;

    return 0;
}

/* fclose */
int32_t my_fclose(MYFILE *fp)
{
    if (fp == NULL)
        return -1;

    my_fflush(fp);

    if (fp->base != NULL)
        free(fp->base);

    close(fp->fd);

    return 0;
}

/* your required function (unchanged name) */
void fflush_flush_fclose(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage: %s outputfile text...\n", argv[0]);
        return;
    }

    MYFILE fp;

    fp.fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fp.fd == -1) {
        perror("open failed");
        return;
    }

    fp.flag = _WRITE;
    fp.base = NULL;
    fp.ptr = NULL;
    fp.cnt = 0;

    for (int index = 2; index < argc; index++) {

        if (argv[index] == NULL)
            continue;

        /* safer than strlen */
        for (int sec_index = 0; argv[index][sec_index] != '\0'; sec_index++) {
            _flushbuf(argv[index][sec_index], &fp);
        }

        _flushbuf(' ', &fp);
    }

    _flushbuf('\n', &fp);

    my_fclose(&fp);

    printf("Data written to %s\n", argv[1]);
}
