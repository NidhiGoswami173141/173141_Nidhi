/*
Author: Nidhi Goswami
Date: 27-04-2026
Description : The standard library function
              int fseek(FILE *fp, long offset, int origin)
is identical to lseek except that fp is a file pointer instead of a file descriptor and return value
is an int status, not a position. Write fseek. Make sure that your fseek coordinates properly
with the buffering done for the other functions of the library.
*/


#include <unistd.h> /* this library is used for function like read , write , lseek */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include"module.h"
#include<stdint.h>
#define BUFSIZE 1024
/* this is flags for file open for reading and writing*/
#define _READ  01
#define _WRITE 02

typedef struct {
    int32_t cnt;
    char *ptr;
    char *base;
    int32_t flag;
    int32_t fd;
} MYFILE;

int32_t my_fflushh(MYFILE *fp)
{
    int32_t n = fp->ptr - fp->base;
    if (n > 0)
        write(fp->fd, fp->base, n);

    fp->ptr = fp->base;
    fp->cnt = 0;
    return 0;
}

int32_t _flushbuff(int32_t c, MYFILE *fp)
{
    if (!(fp->flag & _WRITE))
        return -1;

    if (fp->base == NULL) {
        fp->base = (char *)malloc(BUFSIZE);
        fp->ptr = fp->base;
        fp->cnt = BUFSIZE;
    }

    if ((fp->ptr - fp->base) >= BUFSIZE - 1) {
        write(fp->fd, fp->base, fp->ptr - fp->base);
        fp->ptr = fp->base;
        fp->cnt = BUFSIZE;
    }

    *fp->ptr++ = c;
    fp->cnt--;
    return c;
}

/*int32_t my_fseek(MYFILE *fp, long offset, int32_t origin)
{
    my_fflushh(fp);
    fp->ptr = fp->base;
    return (lseek(fp->fd, offset, origin) == -1) ? -1 : 0;
}
*/

int32_t my_fseek(MYFILE *fp, long offset, int32_t origin)
{
    if (fp->flag & _WRITE) {
        my_fflushh(fp);

    } else if (fp->flag & _READ) {
        if (origin == SEEK_CUR)
            offset -= fp->cnt;
    }

    if (lseek(fp->fd, offset, origin) == -1)
        return -1;

    fp->cnt = 0;
    fp->ptr = fp->base;

    return 0;
}

int32_t my_fclosee(MYFILE *fp)
{
    my_fflushh(fp);
    free(fp->base);
    return close(fp->fd);
}

void seek(int32_t argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    MYFILE fp;

    fp.fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fp.fd == -1) {
        perror("open failed");
        return 1;
    }

    fp.flag = _WRITE;
    fp.base = NULL;
    fp.ptr = NULL;

    char input[200];
    char w1[50], w2[50], w3[50];

    printf("Enter sentence:\n");
    getchar();
    fgets(input, sizeof(input), stdin);

    printf("Enter word1:\n");
    scanf("%s", w1);

    printf("Enter word2:\n");
    scanf("%s", w2);

    printf("Enter word3:\n");
    scanf("%s", w3);

    for (int32_t index = 0; input[index]; index++)
        _flushbuff(input[index], &fp);

    my_fflushh(&fp);

    printf("Started with:%s\n", input);

    my_fseek(&fp, 3, SEEK_SET);
    for (int32_t index = 0; w1[index]; index++)
        _flushbuff(w1[index], &fp);

    my_fseek(&fp, 10, SEEK_SET);
    for (int32_t index = 0; w2[index]; index++)
        _flushbuff(w2[index], &fp);

    my_fseek(&fp, 18, SEEK_SET);
    for (int32_t index = 0; w3[index]; index++)
        _flushbuff(w3[index], &fp);

    my_fflushh(&fp);

    char buffer[200];
    lseek(fp.fd, 0, SEEK_SET);
    int32_t n = read(fp.fd, buffer, sizeof(buffer)-1);
    buffer[n] = '\0';

    printf("Ended with:%s\n", buffer);

    lseek(fp.fd, 0, SEEK_SET);
    read(fp.fd, buffer, 20);

    my_fseek(&fp, 0, SEEK_CUR);
    memset(buffer, 0, sizeof(buffer));
    n = read(fp.fd, buffer, sizeof(buffer)-1);
    buffer[n] = '\0';

    printf("Read SEEK_CUR:%s\n", buffer);

    my_fclosee(&fp);

    return 0;
}

